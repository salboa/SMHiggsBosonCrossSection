#include "pValMaker.h"


using namespace RooFit;
using namespace RooStats;
using namespace std;


// Base class 
pValMaker::pValMaker(std::map<TString, TString>& opts, std::vector<double> binWidth)
{
	m_opts 		= opts; 
	m_binWidth 	= binWidth;
	m_outDirName = "pValues";

}
pValMaker::~pValMaker()
{

} 
 
TString pValMaker::getPVal(TH1D* prediction, TString generator, TString fidSpecial)
{
	m_prediction = prediction;
	m_generator = generator;
	m_fidSpecial = fidSpecial;

	cout << "Calculating the p-value for " << generator << endl;

	// read it in from a cached file
	if(m_opts["calcPVal"].Contains("false"))
	{
		cout << "Will read pVal from file" << endl;
		m_pValString = readPVal();
	}
	// otherwise, we will recalculate it 
	else
	{

		openWorkspace();

		// do an unconditional fit to data
	    RooFitResult* fitresultData = NULL;
	    RooNLLVar* nllData 			= NULL;
	    int statusData 				= -999;
		fitPoint(fitresultData, statusData, nllData);
		double nnlValData = 2.*nllData->getVal();


        std::vector<int> POIVect;
        if(m_fidSpecial.EqualTo("m_fidchannel")) 
        {
            POIVect.push_back(0); // 4mu
            POIVect.push_back(1); // 4e
            POIVect.push_back(2); // 2mu2e
            POIVect.push_back(3); // 2e2mu
        }
        else POIVect.push_back(-999);

        for(Size_t i = 0; i < POIVect.size(); i++)
        {
    		// set the POIs to the predition values
    		setPOIs(POIVect.at(i));

    		// do the fit again with the POI value set to a certain prediction
    	    RooFitResult* fitresultExp = NULL;
    	    RooNLLVar* nllExp 			= NULL;
    	    int statusExp 				= -999;
    		fitPoint(fitresultExp, statusExp, nllExp);
    		double nnlValExp = 2.*nllExp->getVal();

    		double deltaNNL = nnlValData - nnlValExp;
    		double dof = m_prediction->GetNbinsX();
            if(m_fidSpecial.Length() > 0 ) dof = 1;
    		cout << "Data " << nnlValData << " Exp " << nnlValExp << endl;
    		cout << "Your degrees of freedom are: " << dof << endl;


    		m_pValue = ROOT::Math::chisquared_cdf_c(fabs(deltaNNL), dof);
    		
    		m_pValString.Form("%.0f", (m_pValue)*100);

    		savePValue(POIVect.at(i));
    		cout << "The P-Value is "<< m_pValue <<" "<<m_pValString<< endl;
        }

	}


	return m_pValString;
}

void pValMaker::savePValue(int POIName)
{
	
	system("mkdir -vp " + m_outDirName);

	TString fileName = m_outDirName + "/" + "pVal_" + m_opts["variable"] + "_" + m_opts["type"] + "_" + m_generator +".txt";

	if(m_fidSpecial.Length() > 0 )
	{
        if(POIName == -999) fileName += m_outDirName + "/" + "pVal_" + m_fidSpecial + "_" + m_generator;
        else 
        {
            if(POIName == 0) fileName += "_4mu";
            if(POIName == 1) fileName += "_4e";
            if(POIName == 2) fileName += "_2mu2e";
            if(POIName == 3) fileName += "_2e2mu";
        }
        fileName += ".txt";

	}


	ofstream myfile;
	myfile.open (fileName);
	myfile << m_pValString;
	myfile.close();
}

int pValMaker::getNDOF()
{
	return 1;
}

int pValMaker::countPOIs()
{
	TIterator* itr = m_POI->createIterator();
    RooRealVar* var;
    int numPOIs = 0;
    while ((var = (RooRealVar*)itr->Next())) numPOIs++;

    return numPOIs;
}

void pValMaker::setPOIs(int setPOI)
{

	TIterator* itr = m_POI->createIterator();
    RooRealVar* var = NULL;
    cout << "Before setting" << endl;
    cout << "-----------------------" << endl;
    m_POI->Print("v");
    double c_binWidth = 1;


	for(Size_t bin=0; bin < m_prediction->GetNbinsX(); bin++)
  	{
  		if(m_binWidth.size() == 0) c_binWidth = 1;
  		else c_binWidth = m_binWidth.at(bin);

  		cout << "From histogram: "<< bin+1 << "\t" <<m_prediction->GetBinContent(bin+1) << "\t" << c_binWidth << endl;
  	}

    int bin = 0;

    // special setting 
    if(m_fidSpecial.EqualTo("m_fid2l2l") || m_fidSpecial.EqualTo("m_fid4l") || m_fidSpecial.EqualTo("m_fidsum") ||  m_fidSpecial.EqualTo("m_fidchannel") )
    {
    	if(m_fidSpecial.EqualTo("m_fid2l2l"))
    	{
			m_ws->var("sigma_2l2l")->setVal(m_prediction->GetBinContent(1));
			m_ws->var("sigma_2l2l")->setConstant(true);      		
    	}
    	else if(m_fidSpecial.EqualTo("m_fid4l"))
    	{
			m_ws->var("sigma_4l")->setVal(m_prediction->GetBinContent(1));
			m_ws->var("sigma_4l")->setConstant(true);        		
    	} 
    	else if(m_fidSpecial.EqualTo("m_fidsum"))
    	{
			m_ws->var("sigma_sum")->setVal(m_prediction->GetBinContent(1));
			m_ws->var("sigma_sum")->setConstant(true);    	
    	}   	

        else if(m_fidSpecial.EqualTo("m_fidchannel"))
        {
            // what a stupid way to do things
            if(setPOI == 0)
            {
                m_ws->var("sigma_4mu")->setVal(m_prediction->GetBinContent(1));
                m_ws->var("sigma_4mu")->setConstant(true); 

                m_ws->var("sigma_4e")->setConstant(false); 
                m_ws->var("sigma_2mu2e")->setConstant(false); 
                m_ws->var("sigma_2e2mu")->setConstant(false); 

            }    
            else if(setPOI == 1)
            {
                m_ws->var("sigma_4e")->setVal(m_prediction->GetBinContent(2));
                m_ws->var("sigma_4e")->setConstant(true); 

                m_ws->var("sigma_4mu")->setConstant(false); 
                m_ws->var("sigma_2mu2e")->setConstant(false); 
                m_ws->var("sigma_2e2mu")->setConstant(false); 
            }  
            else if(setPOI == 2)
            {
                m_ws->var("sigma_2mu2e")->setVal(m_prediction->GetBinContent(3));
                m_ws->var("sigma_2mu2e")->setConstant(true); 

                m_ws->var("sigma_4mu")->setConstant(false); 
                m_ws->var("sigma_4e")->setConstant(false); 
                m_ws->var("sigma_2e2mu")->setConstant(false); 
            }  
            else if(setPOI == 3)
            {
                m_ws->var("sigma_2e2mu")->setVal(m_prediction->GetBinContent(4));
                m_ws->var("sigma_2e2mu")->setConstant(true); 

                m_ws->var("sigma_4mu")->setConstant(false); 
                m_ws->var("sigma_4e")->setConstant(false); 
                m_ws->var("sigma_2mu2e")->setConstant(false); 
            }  

        } 	    		

    }
   
	else
	{
		while ((var = (RooRealVar*)itr->Next())) 
		{
		    TString varName = var->GetName();

				if(m_binWidth.size() == 0) c_binWidth = 1;
				else c_binWidth = m_binWidth.at(bin);

			var->setVal(c_binWidth*m_prediction->GetBinContent(bin+1));
			var->setConstant(true);
			bin++;
		}
	}
    cout << "After setting" << endl;
    cout << "-----------------------" << endl;
    m_POI->Print("v");




}

TString pValMaker::readPVal()
{

	TString fileName = m_outDirName + "/" + "pVal_" + m_opts["variable"] + "_" + m_opts["type"] + "_" + m_generator +".txt";
	
	string line;
	cout << "Opening file " << fileName << endl;
	ifstream myfile (fileName);
	if (myfile.is_open())
	{
		while ( getline (myfile, line) )
		{
		  cout << "Found p-value: " << line << '\n';
		}
		myfile.close();
	}

	TString pValStr = line;

	return line;
}

void pValMaker::openWorkspace()
{

	TString unFoldType = "FixMe";
	if(m_opts["type"].Contains("matrix")) unFoldType = "mtx";
	else if(m_opts["type"].Contains("cf")) unFoldType = "cf";
	TString workSpaceName = "./workspaces/ws_" + m_opts["variable"] + "_wsys_data_" + unFoldType + ".root";

	if(m_fidSpecial.Length() > 0 )
	{
		workSpaceName = "./workspaces/ws_" + m_fidSpecial + "_wsys_data.root";
	}

	m_file = TFile::Open(workSpaceName, "read");

	if(m_file->IsZombie())
	{
		cout << "Workspace not found: " <<  workSpaceName << endl;
		exit(1);
	}

    m_ws = (RooWorkspace*)m_file->Get("myWS");

    m_mc = (ModelConfig*)m_ws->obj("ModelConfig");

    TString rooDataSetName = "obsData";

    m_dataSet = (RooDataSet*)m_ws->data(rooDataSetName);

    m_globs = (RooArgSet*)m_mc->GetGlobalObservables(); 
    m_POI = m_mc->GetParametersOfInterest();
    m_Sys = m_mc->GetNuisanceParameters();


    cout << "Workspace" << workSpaceName << " read in" << endl;

}




void pValMaker::fitPoint(RooFitResult* &fitresult, int &status, RooNLLVar* &nll, RooArgSet* minosSet)
{
	nll = getNLL();

    fitresult = minimize(nll, status, minosSet);
    cout<<"NLL val: "<<2*nll->getVal()<<endl;


}


RooNLLVar* pValMaker::getNLL()
{
	fixRooStarMomentMorphCache();

	bool doOffSet = false;
    // if(m_opts["applyOffset"].Contains("true")) doOffSet = true;

	int numCPU = 1;
    RooNLLVar* nll = 0;

    nll = (RooNLLVar*)m_mc->GetPdf()->createNLL(*m_dataSet, Constrain(*m_Sys), GlobalObservables(*m_globs), Offset(doOffSet), CloneData(kFALSE), NumCPU(numCPU, RooFit::Hybrid));

    fixRooStarMomentMorphCache();

    return nll;
}




RooFitResult* pValMaker::minimize(RooAbsReal* fcn, int& statusOut, RooArgSet* minosSet) 
{
    TStopwatch timer;
    timer.Start();
    ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2");
    ROOT::Math::MinimizerOptions::SetDefaultStrategy(2);        
    // ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(-1);
    RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL); 
    // if(m_opts["doOffSet"].EqualTo("true")) fcn->enableOffsetting(true);

    int printLevel = ROOT::Math::MinimizerOptions::DefaultPrintLevel();
    RooFit::MsgLevel msglevel = RooMsgService::instance().globalKillBelow();
    if (printLevel < 0) RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);

    int strat = ROOT::Math::MinimizerOptions::DefaultStrategy();
    int save_strat = strat;

    //cout<<"Default startegy: "<<strat<<endl;

    RooMinimizer minim(*fcn);

    // if(m_opts.find("optimizeConst") != m_opts.end()) minim.optimizeConst(m_opts["optimizeConst"].Atoi());
    
    minim.setStrategy(strat);
    minim.setPrintLevel(printLevel);
    //minim.setProfile(1);
    //minim.setMaxFunctionCalls(1e6);
    //minim.setMaxIterations(1e6);
    // This changes the 2*NLL value used for Minuit error determination
    // which will be used for the Minuit error determination,
    // used as starting point for findSigma. Best not to change this!
    // BEtter to use setEps to change the tolerance.
    //minim.setErrorLevel(0.1);

    // Added this
    minim.setEps(0.01);

    int status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());

    // up the strategy
    if (status != 0 && status != 1 && strat < 2) {
        strat++;
        cout << "Fit failed with status " << status << ". Retrying with strategy " << strat << endl;
        minim.setStrategy(strat);
        status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
    }
    if (status != 0 && status != 1 && strat == 2) {
        cout << "Fit failed with status " << status << ". Retrying with strategy " << strat << endl;
        minim.setStrategy(strat);
        status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
    }
    if (status != 0 && status != 1) {
        cout << "Fit failed with status " << status << endl;
    }
    else
    {
        //cout<<"fit is ok"<<endl;
    }

    if (printLevel < 0) RooMsgService::instance().setGlobalKillBelow(msglevel);
    ROOT::Math::MinimizerOptions::SetDefaultStrategy(save_strat);

    string name = Form("fitresult_%s",fcn->GetName());
    string title = Form("fitresult_%s",fcn->GetName());

    RooFitResult* fitresult = minim.save(name.c_str(), title.c_str());

    if (minosSet != NULL) {
        minim.minos(*minosSet);
    }

    ROOT::Math::MinimizerOptions::SetDefaultStrategy(save_strat);

    statusOut = status;

    timer.Stop();
    timer.Print();

    return fitresult;
}



void pValMaker::fixRooStarMomentMorphCache()
{
	// if(m_opts["applyRooStartMomentFix"].EqualTo("false")) return;

	// 395784
    #if (ROOT_VERSION_CODE == 395270)   or (ROOT_VERSION_CODE == 395784)
    	cout << "Fixing the cache" << endl;
        RooFIter iter2 = m_ws->components().fwdIterator();
        RooAbsArg* arg2;
        while ((arg2 = iter2.next())) 
        {
            if (arg2->IsA() == RooStarMomentMorph::Class()) 
            {
                ((RooStarMomentMorph*)arg2)->fixCache();
            }
        }
        return;
    #endif
}



