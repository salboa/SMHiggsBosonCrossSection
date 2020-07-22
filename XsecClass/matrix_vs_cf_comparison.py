#/usr/bin/python
import sys
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import math
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--variable", type=str  , default='njetv4', help="specify the variable to be used: default 'njet'")
parser.add_argument("--nBins"   , type=str  , default='30'    , help="specify the # bins of m4l range: default 30"    )
parser.add_argument("--lumi"    , type=float, default=145     , help="specify integrated luminosity: default 145"     )
parser.add_argument("--nSteps"  , type=int  , default=200     , help="specify the # of steps: default is 200"         )
args = parser.parse_args()


def response_matrix(mtx,nBins):

  """ response matrix taken from MC """
  _result = np.matrix( np.loadtxt( mtx, skiprows=1,
                                   usecols=[num for num in range(0,nBins*2) if num%2==1] ) )
  return _result
 
def correction_factors(cF,nBins):

  """ cF taken from MC """
  
  _result = np.array( np.loadtxt(cF, skiprows=1, usecols=1) )
  return _result

def NotFiducialPart(fnotFid,nBins):

  _result = [];
  _fNonFid = np.loadtxt(fnotFid, skiprows=1, usecols=2)
  for n in range(0,nBins):
    _result.append(1+_fNonFid[n])

  return _result
  
def inv_response_matrix(a):

  """ response matrix inversion """
  _inv = np.linalg.inv(a)
  return _inv 

def poisson_fluctuation(number):

  """ apply Poissonian fluctuation """
  return np.random.poisson(number,1)

def expected_truth_events(): #expected truth njets distribution

  """ expected truth distribution """
  ntruth = np.array([1.85682,0.948409,0.426674,0.17552])
  return ntruth
  
def error_measurement(): #expected truth njets distribution

  """ measured xsec errors """
  
  ntruth_up_m = np.array([.14,.22,.355,0.526])
  ntruth_dn_m = np.array([.132,.207,.319,.449])
  ntruth_up_c = np.array([.128,.151,.215,.335])
  ntruth_dn_c = np.array([.121,.14,.192,.281])
  return ntruth_up_m, ntruth_dn_m, ntruth_up_c, ntruth_dn_c  
   
def plot_bin(df, bin_number, ax, exp, errorup, errordn, errorup_cf, errordn_cf):
  
  df1 = df[df['binvariated']==bin_number]
  df1['relative matrix'] = (df1['nunfolded matrix bin'+str(bin_number)]-df1['ntruth bin'+str(bin_number)])/df1['ntruth bin'+str(bin_number)]
  df1['relative cf']     = (df1['nunfolded cf bin'+str(bin_number)]-df1['ntruth bin'+str(bin_number)])/df1['ntruth bin'+str(bin_number)]
  ax.plot(df1['ntruth bin'+str(bin_number)],df1['relative matrix'], label='relative matrix')
  ax.plot(df1['ntruth bin'+str(bin_number)],df1['relative cf'], label='relative cf')
  ax.axvspan( exp[bin_number]*(1.+errorup[bin_number]),exp[bin_number]*(1.-errordn[bin_number]), color='C0', alpha=0.2, label='error matrix' )
  ax.axvspan( exp[bin_number]*(1.+errorup_cf[bin_number]),exp[bin_number]*(1.-errordn_cf[bin_number]), color='C1', alpha=0.2, label='error cf' )
  ax.axhline
  ax.set_title('sigma bin'+str(bin_number))
  ax.legend()
      
def uniform_generation_eff(events):
  
  return np.random.uniform(0,1.,events)

def fill_reco_based_on_RM(response_matrix , nevents_truth,
                          bin_number_truth, reco_spectrum):

  tmp=uniform_generation_eff(nevents_truth)

  eff_array=np.array(response_matrix[:,bin_number_truth])
  a= eff_array[0]
  b= eff_array[1]
  eff_array=np.cumsum(eff_array, dtype=float)  #cumulative to have bin range
  
  find_recobin=np.digitize(tmp, eff_array, right=True)      
  find_recobin=find_recobin[find_recobin < len(reco_spectrum)] # remove overflow = inefficiency

  for i in np.nditer(find_recobin):
    reco_spectrum[i]+=1
  return reco_spectrum

def getFiles():

  _prefix   = "../ValReader/Values/Diff/"+args.variable+"/mc16/Dressed/"
  _file_cF  = _prefix+"cF_AllSig_"+str(args.nBins)+"bin.dat"
  _file_mtx = _prefix+"rspmtx_AllSig_incl_"+str(args.nBins)+"bin.dat"
  _file_fnf = _prefix+"rspmtx_fNonFid_AllSig_"+str(args.nBins)+"bin.dat"
  
  return _file_cF, _file_mtx, _file_fnf

def getColumns(nBins):

  _columns = []
  for n in range(0,nBins):
    _columns.append( 'nreco bin'+str(n)            )
    _columns.append( 'ntruth bin'+str(n)           )
    _columns.append( 'nunfolded matrix bin'+str(n) )
    _columns.append( 'nunfolded cf bin'+str(n)     )
  _columns.append( 'binvariated' )

  return _columns

def getNotFiducialPart(fnotFid,nBins):

  _result = [];
  _fNonFid = np.loadtxt(fnotFid, skiprows=1, usecols=1)
  for n in range(0,nBins):
    _result.append(1+_fNonFid[n])

  return _result

def getGrid(nBins):

  """ defining grid for final plot """
  _nrows = nBins/4
  _ncols  = 4
  if _nrows==0:
    _nrows = nBins
    _ncols = 1
  elif _nrows==1 and _nrows*4-nBins==0:
    _nrows = 2
    _ncols = 2
  else:
    if _nrows*4-nBins!=0:
      _nrows = _nrows+1
    
  return _nrows, _ncols

def main():

  #global variable
  Lumi   = args.lumi
  nSteps = args.nSteps

  #files and nBins
  cF, mtx, fnotFid = getFiles();
  vBins = len(open(cF).readlines())-1
    
  np.random.seed(1)  #seed needed to be able to reproduce results
  
  ntruth = expected_truth_events() #to be done dynamically

  #Define DataFrame
  df = pd.DataFrame( columns=getColumns(vBins) )

  #Fill fNonFid part
  f_notfid=NotFiducialPart(fnotFid,vBins)
 
  #Start evaluation
  for j in range(0, vBins):
    print("Processing bin ", j)
    
    for i in range(0,nSteps):
      
      ntruth = expected_truth_events()
      ntruth[j] = ntruth[j]*(1-0.5+0.005*i)
      reco_spectrum = np.zeros(len(ntruth))

      rm       = response_matrix(mtx,vBins)
      cf_array = correction_factors(cF,vBins)
      
      allinfo = np.zeros(len(df.columns))

      ntruth=ntruth*Lumi
      reco_spectrum=np.array(np.matmul(rm,ntruth))
      reco_spectrum=reco_spectrum.flatten()
      
      reco_spectrum=reco_spectrum*f_notfid
      
      inv_rm = np.matrix(inv_response_matrix(rm))
      unfolded_spectrum_cf = np.divide(reco_spectrum, cf_array)
      
      reco_spectrum = reco_spectrum/f_notfid
      
      unfolded_spectrum_matrix = np.array(np.matmul(inv_rm,reco_spectrum))
      unfolded_spectrum_matrix = unfolded_spectrum_matrix.flatten()

      for k in range(0, len(reco_spectrum)):
        allinfo[0+k*len(reco_spectrum)]=reco_spectrum[k]
        allinfo[1+k*len(reco_spectrum)]=ntruth[k]
        allinfo[2+k*len(reco_spectrum)]=unfolded_spectrum_matrix[k]
        allinfo[3+k*len(reco_spectrum)]=unfolded_spectrum_cf[k]

      allinfo=allinfo/Lumi
      allinfo[len(allinfo)-1]=j

    
      df.loc[i+200*j] = allinfo

  print( df.describe() )

  exp = np.array(expected_truth_events())
  errorup, errordn, errorup_cf, errordn_cf = error_measurement()

  
  nrows, ncols = getGrid(vBins)
  for i in range(0,len(exp)):
    ax=plt.subplot(nrows,ncols,i+1)
    plot_bin(df, i, ax, exp, errorup, errordn, errorup_cf, errordn_cf)

  plt.show()

  
if __name__ == "__main__":
    main()
