#!/usr/bin/env python
import os
import math

import argparse
parser = argparse.ArgumentParser()
parser.add_argument("--queue",           type = str, default = "workday",                       help = "Queue to submit to.")
parser.add_argument("--outputDir",       type = str, default = "Test_diffXS",                        help = "STXS scheme, check commonCode.cxx")
parser.add_argument("--isCedar",         default = True, action='store_true',   help = "submission for cedar")
parser.add_argument("--dryRun",         default = False, action='store_true',   help = "submission for cedar")
args = parser.parse_args()

listToProcess = [
'python RunCreateInputs.py --makeXsecAll --nBins 110 --maxProcesses 16',
]


def main(): 
    counter = 0

    # main info for condor
    jobMap    = []
    jobListBaseDir  = ""
    condorBaseDir   = ""

    os.system("mkdir -vp %s" % args.outputDir)
    # just to distinguish.. more like a hack
    # and at the start so that it doesn't care about 
    jobListBaseDir  = "jobList/J{0}".format(args.outputDir)
    condorBaseDir   = "condor/%s"   %(args.outputDir)
    bsubBaseDir     = "bsub/%s"   %(args.outputDir)

    os.system("mkdir -vp %s" % jobListBaseDir)
    os.system("mkdir -vp %s" % condorBaseDir)
    if(args.isCedar): 
        os.system("mkdir -vp %s" % bsubBaseDir)
        os.system("mkdir -vp %s/outputs/" % bsubBaseDir)


    
    for job in listToProcess:
        # get the job command list
        cmdToRun = job
        print(cmdToRun)
        
        # # write this out to a file
        jobFile = "job_%i.sh" %(counter)
        jobFile = jobFile.replace(".txt", ".sh")
        
        fileObj=open(jobListBaseDir + "/" +jobFile, 'w')
        fileObj.write("#!/bin/bash\n")
        fileObj.write(cmdToRun)
        fileObj.close() 

           
        cedarJobDef = getCedarDef(counter, jobListBaseDir, jobFile, bsubBaseDir)
        # write this out to a file
        bsubFile = "bsubFile_%i" %(counter) 
        bsubFile = bsubFile + ".sh"
        bsubFile = bsubBaseDir + "/" + bsubFile

        print(bsubFile)
        fileObj=open(bsubFile, 'w')
        fileObj.write(cedarJobDef)
        fileObj.close() 

        counter += 1
        if args.dryRun == True:
            continue

        os.system("chmod -R 775 " + bsubFile)
        command = ""
        command = "sbatch "+ bsubFile
        print(command)
        os.system(command)
        # print job



def getCedarDef(jobNum, jobBasePath, jobFile, bsubBaseDir):
    OutFileName = "stdout_%i.txt" %(jobNum)

    text = """#!/bin/bash    
#SBATCH 
#SBATCH --time=30:00:00
#SBATCH --mem=10000M
#SBATCH --cpus-per-task=16
"""
    text += """
#SBATCH --job-name job_%i """ %(jobNum)

    if(os.environ["USER"] == "ciungubi"):
        text += """
#SBATCH --account=def-sinervo""" 
    else:
        text += """
#SBATCH --account=def-psavard""" 
    
    text += """
#SBATCH --output %s/outputs/%s""" %(bsubBaseDir, OutFileName)


    text += """

cd ~/
module load nixpkgs/16.09  gcc/5.4.0 root/6.14.04 boost python/3.7.0
cd /home/ciungubi/Moriond2019/MiniTreeReader
""" 
    text += "source " + jobBasePath + "/" + jobFile
    text += """
pwd""" 
    text += """
ls""" 
    return text



# run the main function
if __name__ == "__main__":
    main()

