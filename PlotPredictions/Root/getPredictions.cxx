#include "getPredictions.h"


using namespace std;

// Base class 
getPredictions::getPredictions(std::map<TString, TString>& opts)
{
	m_opts = opts;
	m_outFolderName = "predictions/";
}; 
getPredictions::~getPredictions(){}; 



void getPredictions::run()
{
    if(m_opts["type"].Contains("HRes") || m_opts["type"].Contains("N2LOggF") ) stupidFill();
    else
    {
        loadMaps();

    	readFiles();

        std::set<TString> uniqueDSIDs;
        for(auto& fileName: m_fileListVect)
        {
            std::vector<TString> fileSplit = tokenizeStr(fileName, ".");
            uniqueDSIDs.insert(fileSplit[fileSplit.size() - 3]);

        }



        for(auto cDISD: uniqueDSIDs)
        {
            m_DSID = cDISD;
            m_fileChain       = new TChain("tree_incl_all");
            
            for(auto file:m_fileListVect)
            {
                if(!file.Contains(m_DSID)) continue;
                cout<< "Adding: " << file << endl;
                m_fileChain->Add(file);
            }

            fillSysMap();

            for(const auto obs:m_obsMap)
            {
                cout << "Doing " << obs.first << endl;
                cout << "--------------------" << endl;
                m_keyName = obs.first;
                calcFid();
            }

            m_fileChain = NULL;

            saveFiles();
            
        }

        haddFiles();
    }

}



std::vector<TString> getPredictions::tokenizeStr(TString str, TString key)
{
    TObjArray *Varparts = str.Tokenize(key);
    vector<TString> varNameVec;
    if(Varparts->GetEntriesFast()) {
        TIter iString(Varparts);
        TObjString* os=0;
        while ((os=(TObjString*)iString())) {
            varNameVec.push_back(os->GetString());
        }
    }
    return varNameVec;
}




void getPredictions::calcFid()
{

    TString fidHistName     = m_keyName + "_fid";
    TString incHistName     = m_keyName + "_incl";

    TString fidName         = m_obsMap[m_keyName]; 
    TString fidCut          = m_cutsMap[m_keyName];
    fidName                 = fidName.ReplaceAll("_XXX", "_fidDres_4lsel"); 
    fidCut                  = fidCut.ReplaceAll("_XXX", "_fidDres_4lsel");

    if(m_keyName.EqualTo("inc"))
    {
        fidName   = m_obsMap[m_keyName]; 
        fidCut    = m_cutsMap[m_keyName];
        fidName   = fidName.ReplaceAll("_XXX", "_fidDres_truth"); 
        fidCut    = fidCut.ReplaceAll("_XXX", "_fidDres_truth");
    }

    TString incName   = m_obsMap[m_keyName];
    TString incCut    = m_cutsMap[m_keyName];
    incName   = incName.ReplaceAll("_XXX", "_fidBorn_truth");
    incCut    = incCut.ReplaceAll("_XXX", "_fidBorn_truth");

    // dealing with taus
    bool isTau = false;
    if(m_fileChain->GetMaximum("event_type_fidDres_truth") >= 4) isTau = true;
    TString mult    = "1";
    TString fidMult = "1";

    TString fidWeightStr = "FixMe";
    TString incWeightStr = "FixMe";

    if(isTau && m_keyName.Contains("fid_")) mult = "(event_type_fidBorn_truth < 4)";
    if(isTau && m_keyName.Contains("fid_")) fidMult = "(event_type_fidBorn_truth < 4)/2.25";


    fidWeightStr = "w_MCw*w_xs*w_br*(higgs_m_fidDres_4lsel > 105 && higgs_m_fidDres_4lsel < 160)*" + fidCut;
    if(m_keyName.EqualTo("inc")) fidWeightStr = "w_MCw*w_xs*(higgs_m_fidBorn_truth > 105 && higgs_m_fidBorn_truth < 160)*" + fidCut;
    incWeightStr = "w_MCw*(higgs_m_fidBorn_truth > 105 && higgs_m_fidBorn_truth < 160)";

    fidWeightStr += "*" + fidMult;
    incWeightStr += "*" + mult;


    // Special case for MG5
    if(m_DSID.EqualTo("344158") && m_keyName.EqualTo("inc"))
    {
        fidWeightStr += "/0.000124";
    }

    cleanHist();

    m_fidHist = getHist(fidHistName, fidName, fidWeightStr);
    m_incHist = getHist(incHistName, incName, incWeightStr);

    m_nomHist = (TH1D*)m_fidHist->Clone("nomHist");
    m_nomHist->Scale(1.0/m_incHist->Integral());

    TString saveHistLabel = fidName;
    if(m_keyName.Contains("fid") || m_keyName.EqualTo("inc"))
    {
        saveHistLabel = m_keyName;
    }

    if(m_opts["doSys"].Contains("true"))
    {
        // getting the up and down variations
        if(m_opts["type"].Contains("N3LOggF")) quadSys(fidWeightStr, fidName);
        else if(m_opts["type"].Contains("MG5") || m_opts["type"].Contains("XH")) evelopeSys(fidWeightStr, fidName);
    }   

    // pushing all this stuff into a vector of cloned histograms so that it can be saved into a rootFile
    TH1D* nomHistTemp   = (TH1D*) m_nomHist->Clone(saveHistLabel+ "_nom");
    TH1D* upHistTemp    = (TH1D*) m_nomHist->Clone(saveHistLabel+ "_upSqr");
    TH1D* downHistTemp  = (TH1D*) m_nomHist->Clone(saveHistLabel+ "_downSqr");

    for(int bin = 0; bin < nomHistTemp->GetNbinsX(); bin++)
    {
        double binWidth = fabs(nomHistTemp->GetXaxis()->GetBinUpEdge(bin+1) - nomHistTemp->GetXaxis()->GetBinLowEdge(bin+1));
        if(m_keyName.Contains("inc") || m_keyName.Contains("fid_sum") || m_keyName.Contains("n_jet")) binWidth = 1;

        nomHistTemp->SetBinContent(bin + 1,     m_nomHist->GetBinContent(bin + 1)/binWidth);


        double nomVal = nomHistTemp->GetBinContent(bin + 1);
        double upVal = nomVal ;
        double downVal = nomVal;

        if(m_opts["doSys"].Contains("true"))
        {

            upVal = nomVal * ( sqrt(m_upHist->GetBinContent(bin + 1)));
            downVal = nomVal * ( sqrt(fabs(m_downHist->GetBinContent(bin + 1))));

            upHistTemp->SetBinContent(bin + 1,      upVal * upVal);
            downHistTemp->SetBinContent(bin + 1,    downVal * downVal);
        }
        else
        {
            upHistTemp->SetBinContent(bin + 1,      0);
            downHistTemp->SetBinContent(bin + 1,    0);
        }


        cout << m_keyName << "\t" << "Bin: " << bin +1 << "\t"<< nomVal  <<" +/- "<<(upVal + downVal)/2.0<<"\t + "<< nomVal + upVal<< "\t - "<< nomVal - downVal << " fb"<< endl;
    }

    m_nomHistVect.push_back(nomHistTemp);
    m_upHistVect.push_back(upHistTemp);
    m_downHistVect.push_back(downHistTemp);
    
    // delete nomHistTemp;
    // delete upHistTemp;
    // delete downHistTemp;

}

void getPredictions::cleanHist()
{
    m_fidHist       = NULL;
    m_incHist       = NULL;
      
    m_nomHist       = NULL;
    m_upHist        = NULL;
    m_downHist      = NULL;

}

TH1D* getPredictions::getHist(TString histName, TString varName, TString weightName)
{

    TH1D* hist = new TH1D(histName, histName, m_binMap[m_keyName].size() - 1 ,&m_binMap[m_keyName][0]);
    m_fileChain->Draw(varName + ">>" + histName, weightName);  
    // cout<<weightName<<" "<<hist->Integral()<<endl;
    return hist;
}


void getPredictions::stupidFill()
{
    TH1D* nom   = new TH1D("inc_nom", "inc_nom", 1, 0, 1);
    TH1D* up    = new TH1D("inc_up", "inc_up", 1, 0, 1);
    TH1D* down  = new TH1D("inc_down", "inc_down", 1, 0, 1);

    if(m_opts["type"].Contains("N2LOggF"))
    {
        double factor   = 1.105047749;
        double nomVal   = 48600/factor;
        double upErr    = 51606.9/factor;
        double downErr  = 45593.1/factor;

        upErr = fabs(nomVal - upErr);
        downErr = fabs(nomVal - downErr);

        nom->SetBinContent(1, nomVal);
        up->SetBinContent(1, upErr);
        down->SetBinContent(1, downErr);

    }
    else if(m_opts["type"].Contains("HRes"))
    {
        double factor   = 1.105047749;
        double nomVal   = 42.3*1000;
        double upErr    = 42.3*1000*(1 + 11.5/100);
        double downErr  = 42.3*1000*(1 - 11.5/100);

        upErr = fabs(nomVal - upErr);
        downErr = fabs(nomVal - downErr);

        nom->SetBinContent(1, nomVal);
        up->SetBinContent(1, upErr);
        down->SetBinContent(1, downErr);
    }


    system("mkdir -vp " + m_outFolderName);
    TString fileName = m_outFolderName + "/" + m_opts["type"]+".root";
    TFile* outFile = new TFile(fileName, "recreate");

    nom->Write();
    up->Write();
    down->Write();

    outFile->Close();
}


TH1D* getPredictions::getPDFSys(TString fidWeightName, TString fidVarName)
{
    TH1D* pdfHist = (TH1D*)m_nomHist->Clone("pdfHist");

    TString nomWeightName       = fidWeightName + "*weight_var_th_pdf_90400";
    TH1D* nomHistFid            = getHist("nomFidHist", fidVarName, nomWeightName);

    // cout<<"nomWeightName: "<<nomWeightName<<endl;


    std::map<TString, TH1D*> c_pdfHistMap;

    // All the weights with name weight_var_th_pdf_904XX have to looked at wrt 90400 which is the nom
    // this is getting the variation for that
    for(Int_t i = 1; i < 32; i++)
    {
        TString pdfHistName;
        if(i < 10) pdfHistName.Form("weight_var_th_pdf_9040%d",i);
        else pdfHistName.Form("weight_var_th_pdf_904%d",i);
        
        TString pdfWeightName = fidWeightName+ "*" + pdfHistName;

        c_pdfHistMap["Sys_" + pdfHistName] = getHist(pdfHistName, fidVarName, pdfWeightName);
        c_pdfHistMap["Sys_" + pdfHistName]->Divide(nomHistFid);
        c_pdfHistMap["Sys_" + pdfHistName]->Multiply(m_fidHist);
    }

    for(auto hist:c_pdfHistMap)
    {
        if(hist.first.Contains("Sys_"))
        {
            hist.second->Scale(1.0/m_incHist->Integral());
        }        
    }
    for(Int_t bin = 0; bin < m_nomHist->GetNbinsX(); bin++)
    {
        double binErr = -999;
        double sum = 0;
        for(auto hist:c_pdfHistMap)
        {
            if(hist.first.Contains("Sys_"))
            {
                binErr = 1 - hist.second->GetBinContent(bin+1)/m_nomHist->GetBinContent(bin+1);
                // cout << hist.first << "\t" << hist.second->GetBinContent(bin+1) << "\t" << binErr << endl;
                sum += pow(binErr, 2);
            }
        }

        pdfHist->SetBinContent(bin+1, fabs(sum));
    }
    for(auto& hist:c_pdfHistMap) delete hist.second;
    delete nomHistFid;
    return pdfHist;
}


void getPredictions::quadSys(TString fidWeightName, TString fidVarName)
{
    std::map<TString, TH1D*> c_histMap;

    // Lets get the PDF uncert
    c_histMap["PDF"] = getPDFSys(fidWeightName, fidVarName);

    TH1D* m_upErrHist = (TH1D*)m_nomHist->Clone("m_upErrHist");
    TH1D* m_downErrHist = (TH1D*)m_nomHist->Clone("m_downErrHist");

    for(const auto &sysName: m_sysMap)
    {
        TString sysHistName     = sysName.first;
        TString weightName      = fidWeightName + "*" + sysName.second;
        c_histMap[sysHistName]  = getHist(sysHistName, fidVarName, weightName);
    }

    for(auto hist:c_histMap)
    {
        if(hist.first.Contains("Sys_"))
        {
            hist.second->Scale(1.0/m_incHist->Integral());
        }        
    }

    m_upHist    = (TH1D*)m_nomHist->Clone("m_upHist");
    m_downHist  = (TH1D*)m_nomHist->Clone("m_downHist");

    // now add them in quadrature
    for(Int_t bin = 0; bin < m_nomHist->GetNbinsX(); bin++)
    {
        double binErr = -999;
        double sum = 0;
        for(auto hist:c_histMap)
        {
            if(hist.first.Contains("Sys_"))
            {

                binErr = 1 - hist.second->GetBinContent(bin+1)/m_nomHist->GetBinContent(bin+1);
                // cout << hist.first << "\t" << hist.second->GetBinContent(bin+1) << "\t" << binErr << endl;
                sum += pow(binErr, 2);
            }
        }


        m_upHist->SetBinContent(bin+1,    sum + c_histMap["PDF"]->GetBinContent(bin+1));
        m_downHist->SetBinContent(bin+1, -sum - c_histMap["PDF"]->GetBinContent(bin+1));
        // cout << "Sum: "<< sum << "\t+" << c_histMap["PDF"]->GetBinContent(bin+1)  << endl;
        // cout << "Percent Variation: "<<m_nomHist->GetBinContent(bin+1) << "\t+" << m_upHist->GetBinContent(bin+1) << "\t -" << m_downHist->GetBinContent(bin+1) << endl;


        m_upErrHist->SetBinContent(bin+1,     m_nomHist->GetBinContent(bin+1)*(1+sqrt(m_upHist->GetBinContent(bin+1))));
        m_downErrHist->SetBinContent(bin+1,   m_nomHist->GetBinContent(bin+1)*(1-sqrt(m_downHist->GetBinContent(bin+1))));
        // cout << "Final Vals: "<<m_nomHist->GetBinContent(bin+1) << "\t " << m_upErrHist->GetBinContent(bin+1) << "\t " << m_downErrHist->GetBinContent(bin+1) << endl;


    }

    for(auto hist:c_histMap) delete hist.second;
    
}

void getPredictions::evelopeSys(TString fidWeightName, TString fidVarName)
{
    std::map<TString, TH1D*> c_histMap;

    TString nomWeightName       = fidWeightName + "*" + getNominalSys();
    TH1D* nomHistFid            = getHist("nomFidHist", fidVarName, nomWeightName);

    for(auto sysName:m_sysMap)
    {
        TString sysHistName = sysName.first;
        TString weightName = fidWeightName + "*" + sysName.second;

        c_histMap[sysHistName] = getHist(sysHistName, fidVarName, weightName);
        c_histMap[sysHistName]->Divide(nomHistFid);
        c_histMap[sysHistName]->Multiply(m_fidHist);

        // cout << c_histMap[sysHistName]->Integral() << "\t" << m_nomHist->Integral() << endl;
    }

    for(auto hist:c_histMap)
    {
        if(hist.first.Contains("Sys_"))
        {
            hist.second->Scale(1.0/m_incHist->Integral());
        }        
    }

    m_upHist    = (TH1D*)m_nomHist->Clone("m_upHist");
    m_downHist  = (TH1D*)m_nomHist->Clone("m_downHist");

    for(Int_t bin = 0; bin < m_nomHist->GetNbinsX()+0; bin++)
    {
        double lwrBinErr = 999;
        double uprBinErr = -999;
        double variation = 0;

        // get Envelope for systematics
        for(auto hist:c_histMap)
        {
            if(hist.first.Contains("Sys_"))
            {
                variation = 1 - hist.second->GetBinContent(bin+1)/m_nomHist->GetBinContent(bin+1);
                // cout <<hist.first  << "\t" << variation << endl;
                
                if(variation > uprBinErr) uprBinErr = variation; 
                if(variation < lwrBinErr) lwrBinErr = variation;   
            }

        }
        uprBinErr *= uprBinErr;
        lwrBinErr *= lwrBinErr;

        m_upHist->SetBinContent(bin + 1,     uprBinErr);
        m_downHist->SetBinContent(bin + 1,   lwrBinErr);
    }


    if(m_DSID.Contains("344235") ||
       m_DSID.Contains("345038") ||
       m_DSID.Contains("345039") ||
       m_DSID.Contains("346340") ||
       m_DSID.Contains("345066"))
    {
        // get the PDF uncertainty
        c_histMap["PDF"] = getPDFSys(fidWeightName, fidVarName);
        // add it in quadrature to the envelop ones
        m_upHist->Add(c_histMap["PDF"]);
        m_downHist->Add(c_histMap["PDF"]);
    }

    delete nomHistFid;
    for(auto hist:c_histMap) delete hist.second;

}

void getPredictions::saveFiles()
{
    system("mkdir -vp " + m_outFolderName + "/tmp/");
    TString fileName = m_outFolderName + "/tmp/" + m_DSID + ".root";
    m_haddFileList.push_back(fileName);
    TFile* outFile = new TFile(fileName, "recreate");

    for(Int_t i = 0; i < m_nomHistVect.size(); i++)
    {
        m_nomHistVect.at(i)->Write();
        m_upHistVect.at(i)->Write();
        m_downHistVect.at(i)->Write();
    }
    outFile->Close();
}

void getPredictions::haddFiles()
{ 
    TString tmpFileName = "preprediction_" + m_opts["type"] + ".root";
    TString fileName    = "prediction_" + m_opts["type"] + ".root";


    // Hadd all together
    system("mkdir -vp " + m_outFolderName + "/tmp/");
    TString haddString = "hadd -f " + m_outFolderName + "/tmp/" + tmpFileName;
    for(const auto& iD: m_haddFileList) haddString += " " + iD;
    system(haddString);


    // Process the final file
    TFile* inFile = new TFile(m_outFolderName + "/tmp/" + tmpFileName);

    TFile* outFile = new TFile(m_outFolderName + "/" + fileName, "recreate");


    TIter nextkey(inFile->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)nextkey())) {
        TObject* Obj = key->ReadObj();
        if(Obj->IsA()->InheritsFrom("TH1D"))
        {
            TString name = Obj->GetName();

            TH1D* hist = (TH1D*) Obj;
            if(name.Contains("Sqr"))
            {
                TString newName = name.ReplaceAll("Sqr", "");
                hist = (TH1D*) Obj->Clone(newName);

                for(int i = 0 ; i < hist->GetNbinsX(); i++)
                {
                    double val = hist->GetBinContent(i+1);
                    val = sqrt(fabs(val));
                    hist->SetBinContent(i+1, val);
                }
            }

            outFile->cd();
            hist->Write();
            inFile->cd();
        }
    }
}

void getPredictions::readFiles()
{

    TString baseDir = "/eos/atlas/atlascerngroupdisk/phys-higgs/HSG2/H4l/2018/MiniTrees/Prod_v20Fix/";
    std::vector<TString> mcCamp;
    // mcCamp.push_back("mc16a/");  
    // mcCamp.push_back("mc16d/");  
    mcCamp.push_back("mc16e/"); 
    

    for(Int_t i= 0; i < mcCamp.size(); i++)
    {
        if(m_opts["type"].Contains("N3LOggF"))
        { 
          m_fileListVect.push_back(baseDir + mcCamp.at(i) + "FidTheory/mc16_13TeV.345060.PowhegPythia8EvtGen_NNLOPS_nnlo_30_ggH125_ZZ4l.root");
        }
        if(m_opts["type"].Contains("MG5"))
        { 
            baseDir = "/eos/user/b/bciungu/HZZ/FxFxDiff/miniTrees/mc16a/";
            m_fileListVect.push_back(baseDir +"FidTheory/mc16_13TeV.344158.aMcAtNloPythia8EvtGen_A14NNPDF23LO_ppx0_FxFx_Np012_SM.root");
        }
        if(m_opts["type"].Contains("XH"))
        { 
            m_fileListVect.push_back(baseDir + mcCamp.at(i) + "FidTheory/mc16_13TeV.344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.root");
            m_fileListVect.push_back(baseDir + mcCamp.at(i) + "FidTheory/mc16_13TeV.345038.PowhegPythia8EvtGen_NNPDF30_AZNLO_ZH125J_Zincl_MINLO.root");
            m_fileListVect.push_back(baseDir + mcCamp.at(i) + "FidTheory/mc16_13TeV.345039.PowhegPythia8EvtGen_NNPDF30_AZNLO_WpH125J_Wincl_MINLO.root");
            m_fileListVect.push_back(baseDir + mcCamp.at(i) + "FidTheory/mc16_13TeV.345040.PowhegPythia8EvtGen_NNPDF30_AZNLO_WmH125J_Wincl_MINLO.root");
            m_fileListVect.push_back(baseDir + mcCamp.at(i) + "FidTheory/mc16_13TeV.345066.PowhegPythia8EvtGen_NNPDF3_AZNLO_ggZH125_ZZ4lepZinc.root");
            m_fileListVect.push_back(baseDir + mcCamp.at(i) + "FidTheory/mc16_13TeV.346342.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_dilep.root");
            m_fileListVect.push_back(baseDir + mcCamp.at(i) + "FidTheory/mc16_13TeV.346341.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_semilep.root");
            m_fileListVect.push_back(baseDir + mcCamp.at(i) + "FidTheory/mc16_13TeV.346340.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_allhad.root");
            m_fileListVect.push_back(baseDir + mcCamp.at(i) + "FidTheory/mc16_13TeV.346414.aMcAtNloPythia8EvtGen_tHjb125_4fl_ZZ4l.root");
            m_fileListVect.push_back(baseDir + mcCamp.at(i) + "FidTheory/mc16_13TeV.346511.aMcAtNloPythia8EvtGen_tWH125_ZZ4l.root");
            m_fileListVect.push_back(baseDir + mcCamp.at(i) + "FidTheory/mc16_13TeV.344973.aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_yb2_ZZ4lep_noTau.root");
            m_fileListVect.push_back(baseDir + mcCamp.at(i) + "FidTheory/mc16_13TeV.344974.aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_ybyt_ZZ4lep_noTau.root");            
        }
    }
}

void getPredictions::loadMaps()
{

    double pi = TMath::Pi();

    m_cutsMap["n_jet_v1"]            = "(1==1)";
    m_cutsMap["n_jet_v2"]            = "(1==1)";
    m_cutsMap["n_jet_v3"]            = "(1==1)";
    m_cutsMap["n_jet_v4"]            = "(1==1)";
    m_cutsMap["n_bjets"]             = "(1==1)";
    m_cutsMap["rapidity"]            = "(1==1)";
    m_cutsMap["cts"]                 = "(1==1)";
    m_cutsMap["ct1"]                 = "(1==1)";
    m_cutsMap["ct2"]                 = "(1==1)";
    m_cutsMap["phi"]                 = "(1==1)";
    m_cutsMap["phi1"]                = "(1==1)";
    m_cutsMap["pt4l"]                = "(1==1)";
    m_cutsMap["pt4l_0"]              = "(n_jets_XXX == 0)";
    m_cutsMap["pt4l_1"]              = "(n_jets_XXX == 1)";
    m_cutsMap["pt4l_2"]              = "(n_jets_XXX == 2)";
    m_cutsMap["pt4l_3"]              = "(n_jets_XXX >= 3)";
    m_cutsMap["pt4l_y0"]             = "fabs(higgs_y_XXX) < 0.5";
    m_cutsMap["pt4l_y1"]             = "fabs(higgs_y_XXX) < 1.0 && fabs(higgs_y_XXX) > 0.5";
    m_cutsMap["pt4l_y2"]             = "fabs(higgs_y_XXX) < 1.5 && fabs(higgs_y_XXX) > 1.0";
    m_cutsMap["pt4l_y3"]             = "fabs(higgs_y_XXX) < 2.5 && fabs(higgs_y_XXX) > 1.5";
    m_cutsMap["mjj"]                 = "(1==1)";
    m_cutsMap["m12"]                 = "(1==1)";
    m_cutsMap["m34"]                 = "(1==1)";
    m_cutsMap["leadingJetPt"]        = "(1==1)";
    m_cutsMap["subleadingJetPt"]     = "(1==1)";
    m_cutsMap["dijet_deltaphi"]      = "(1==1)";
    m_cutsMap["dijet_deltaeta"]      = "(1==1)";
    m_cutsMap["m12m34_bin1"]         = "(Z1_m_XXX < 82 && Z2_m_XXX < 32)";
    m_cutsMap["m12m34_bin2"]         = "(Z1_m_XXX < 74 && Z2_m_XXX > 32)";
    m_cutsMap["m12m34_bin3"]         = "(Z1_m_XXX > 74 && Z2_m_XXX > 32)";
    m_cutsMap["m12m34_bin4"]         = "(Z1_m_XXX > 82 && ((Z2_m_XXX > 24) && (Z2_m_XXX < 32)))";
    m_cutsMap["m12m34_bin5"]         = "(Z1_m_XXX > 82 && Z2_m_XXX < 24)";
    m_cutsMap["fid_perChan"]         = "(1==1)";
    m_cutsMap["fid_4e"]              = "(event_type_XXX == 1)";
    m_cutsMap["fid_4mu"]             = "(event_type_XXX == 0)";
    m_cutsMap["fid_2mu2e"]           = "(event_type_XXX == 2)";
    m_cutsMap["fid_2e2mu"]           = "(event_type_XXX == 3)";
    m_cutsMap["fid_4l"]              = "(event_type_XXX == 0 || event_type_XXX == 1)";
    m_cutsMap["fid_2l2l"]            = "(event_type_XXX == 2 || event_type_XXX == 3)";
    m_cutsMap["fid_sum"]             = "(event_type_XXX == 0 || event_type_XXX == 1 || event_type_XXX == 2 || event_type_XXX == 3)";
    m_cutsMap["inc"]                 = "(1==1)";


    m_obsMap["fid_perChan"]          = "event_type_XXX";
    m_obsMap["fid_4mu"]              = "0.5";
    m_obsMap["fid_4e"]               = "0.5";
    m_obsMap["fid_2e2mu"]            = "0.5";
    m_obsMap["fid_2mu2e"]            = "0.5";
    m_obsMap["fid_4l"]               = "0.5";
    m_obsMap["fid_2l2l"]             = "0.5";
    m_obsMap["fid_sum"]              = "0.5";
    m_obsMap["inc"]                  = "0.5";
    m_obsMap["n_jet_v1"]             = "n_jets_XXX";
    // m_obsMap["n_jet_v2"]            = "n_jets_XXX";
    // m_obsMap["n_jet_v3"]            = "n_jets_XXX";
    // m_obsMap["n_jet_v4"]            = "n_jets_XXX";
    // m_obsMap["n_bjets"]             = "n_bjets_XXX";
    // m_obsMap["rapidity"]            = "higgs_y_XXX";
    // m_obsMap["cts"]                 = "cthstr_XXX";
    // m_obsMap["ct1"]                 = "cth1_XXX";
    // m_obsMap["ct2"]                 = "cth2_XXX";
    // m_obsMap["phi"]                 = "phi_XXX";
    // m_obsMap["phi1"]                = "phi1_XXX";
    m_obsMap["pt4l"]                  = "higgs_pt_XXX";
    // m_obsMap["pt4l_0"]              = "higgs_pt_XXX";
    // m_obsMap["pt4l_1"]              = "higgs_pt_XXX";
    // m_obsMap["pt4l_2"]              = "higgs_pt_XXX";
    // m_obsMap["pt4l_3"]              = "higgs_pt_XXX";
    // m_obsMap["pt4l_y0"]             = "higgs_pt_XXX";
    // m_obsMap["pt4l_y1"]             = "higgs_pt_XXX";
    // m_obsMap["pt4l_y2"]             = "higgs_pt_XXX";
    // m_obsMap["pt4l_y3"]             = "higgs_pt_XXX";
    // m_obsMap["mjj"]                 = "dijet_m_XXX";
    // m_obsMap["m12"]                 = "Z1_m_XXX";
    // m_obsMap["m34"]                 = "Z2_m_XXX";
    // m_obsMap["leadingJetPt"]        = "jet_pt_XXX[0]";
    // m_obsMap["subleadingJetPt"]     = "jet_pt_XXX[1]";
    // m_obsMap["dijet_deltaphi"]      = "fabs(dijet_deltaphi_XXX)";
    // m_obsMap["dijet_deltaeta"]      = "fabs(dijet_deltaeta_XXX)";

    // m_obsMap["m12m34_bin1"]         = "1";
    // m_obsMap["m12m34_bin2"]         = "1";
    // m_obsMap["m12m34_bin3"]         = "1";
    // m_obsMap["m12m34_bin4"]         = "1";
    // m_obsMap["m12m34_bin5"]         = "1";


    m_binMap["n_jet_v1"]            = vector<double> {0, 1, 2, 3, 20};
    m_binMap["n_jet_v2"]            = vector<double> {0, 1, 20};
    m_binMap["n_jet_v3"]            = vector<double> {0, 1, 2, 20};
    m_binMap["n_jet_v4"]            = vector<double> {0, 1, 2, 3, 4, 20};
    m_binMap["n_bjets"]             = vector<double> {0.0, 1.0, 2.0};
    m_binMap["rapidity"]            = vector<double> {0.0, 0.15, 0.3, 0.45, 0.6, 0.75, 0.9, 1.2, 1.6, 2.0, 2.5};
    m_binMap["cts"]                 = vector<double> {0.0, 0.125, 0.250, 0.375, 0.500, 0.625, 0.750, 0.875, 1.0};
    m_binMap["ct1"]                 = vector<double> {-1.0, -0.750, -0.500, -0.250, 0.0, 0.250, 0.500, 0.750, 1.0};
    m_binMap["ct2"]                 = vector<double> {-1.0, -0.750, -0.500, -0.250, 0.0, 0.250, 0.500, 0.750, 1.0};
    m_binMap["phi"]                 = vector<double> {-pi, -6*pi/8, -4*pi/8, -2*pi/8, 0.0, 2*pi/8, 4*pi/8, 6*pi/8, pi};
    m_binMap["phi1"]                = vector<double> {-pi, -6*pi/8, -4*pi/8, -2*pi/8, 0.0, 2*pi/8, 4*pi/8, 6*pi/8, pi};
    m_binMap["pt4l"]                = vector<double> {0.0, 10.0,  20.0,   30.0,   45.0, 60.0, 80.0, 120.0,  200.0,  350.0, 1000.0};
    m_binMap["pt4l_0"]              = vector<double> {0.0,  15.0,  30.0,  120.0, 350.0};
    m_binMap["pt4l_1"]              = vector<double> {0.0,  30.0,  60.0,   80.0,  120.0,  350.0};
    m_binMap["pt4l_2"]              = vector<double> {0.0, 120.0, 350.0};
    m_binMap["pt4l_3"]              = vector<double> {0.0, 120.0, 350.0};  
    m_binMap["pt4l_y0"]             = vector<double> {0.0, 45.0, 120.0, 350.0};
    m_binMap["pt4l_y1"]             = vector<double> {0.0, 45.0, 120.0, 350.0};
    m_binMap["pt4l_y2"]             = vector<double> {0.0, 45.0, 120.0, 350.0};
    m_binMap["pt4l_y3"]             = vector<double> {0.0, 45.0, 120.0, 350.0};
    m_binMap["mjj"]                 = vector<double> {0.0, 120.0, 450.0, 3000.0};
    m_binMap["m12"]                 = vector<double> {50.0, 64.0, 73.0, 85.0, 106.0};
    m_binMap["m34"]                 = vector<double> {12.0, 20.0, 24.0, 28.0, 32.0, 40.0, 55.0, 65.0};
    m_binMap["leadingJetPt"]        = vector<double> {29.0, 30.0,  60.0,   120.0,  350.0};
    m_binMap["subleadingJetPt"]     = vector<double> {29.0, 30.0,  60.0,   120.0,  350.0};
    m_binMap["dijet_deltaphi"]      = vector<double> {0.0, 0.5*pi, pi, 1.5*pi, 2*pi};
    m_binMap["dijet_deltaeta"]      = vector<double> {0.0, 1.0, 2.0, 9.0};
    m_binMap["fid_perChan"]         = vector<double> {0, 1, 2, 3, 4};
    m_binMap["fid_4mu"]             = vector<double> {0,1};
    m_binMap["fid_4e"]              = vector<double> {0,1};
    m_binMap["fid_2mu2e"]           = vector<double> {0,1};
    m_binMap["fid_2e2mu"]           = vector<double> {0,1};
    m_binMap["fid_4l"]              = vector<double> {0,1};
    m_binMap["fid_2l2l"]            = vector<double> {0,1};
    m_binMap["fid_sum"]             = vector<double> {0,1};
    m_binMap["inc"]                 = vector<double> {0,1};
    m_binMap["m12m34_bin1"]         = vector<double> {0.0, 2.0};
    m_binMap["m12m34_bin2"]         = vector<double> {0.0, 2.0};
    m_binMap["m12m34_bin3"]         = vector<double> {0.0, 2.0};
    m_binMap["m12m34_bin4"]         = vector<double> {0.0, 2.0};
    m_binMap["m12m34_bin5"]         = vector<double> {0.0, 2.0};
}

void getPredictions::fillSysMap()
{
    std::map<TString, TString> sysMap;

    if(m_DSID.Contains("345060"))
    {
        sysMap["Sys_1"] = "weight_var_th_qcd_wg1_mu";
        sysMap["Sys_2"] = "weight_var_th_qcd_wg1_res";
        sysMap["Sys_3"] = "weight_var_th_qcd_wg1_mig01";
        sysMap["Sys_4"] = "weight_var_th_qcd_wg1_mig12";
        sysMap["Sys_5"] = "weight_var_th_qcd_wg1_vbf2j";
        sysMap["Sys_6"] = "weight_var_th_qcd_wg1_vbf3j";
        sysMap["Sys_7"] = "weight_var_th_ggF_qcd_2017_pTH60";
        sysMap["Sys_8"] = "weight_var_th_qcd_wg1_qm_t";
        sysMap["Sys_9"] = "weight_var_th_ggF_qcd_2017_pTH120";
    }
    else if(m_DSID.Contains("344235")) // VBF
    {
        // sysMap["Sys_1"] = "weight_var_th_nominal";
        sysMap["Sys_2"] = "weight_var_th_muR0p5_muF0p5";
        sysMap["Sys_3"] = "weight_var_th_muR0p5_muF2p0";
        sysMap["Sys_4"] = "weight_var_th_muR1p0_muF0p5";
        sysMap["Sys_5"] = "weight_var_th_muR1p0_muF2p0";
        sysMap["Sys_6"] = "weight_var_th_muR2p0_muF0p5";
        sysMap["Sys_7"] = "weight_var_th_muR2p0_muF2p0";
    }
    else if(m_DSID.Contains("345038") ||  // VH, ttH
       m_DSID.Contains("345039") ||
       m_DSID.Contains("345040") ||
       m_DSID.Contains("345066") ||
       m_DSID.Contains("346342") ||
       m_DSID.Contains("346341") ||
       m_DSID.Contains("346340") )
    {
        // sysMap["Sys_1"] = "weight_var_th_nominal";
        sysMap["Sys_2"] = "weight_var_th_muR0p5_muF0p5";
        sysMap["Sys_3"] = "weight_var_th_muR0p5_muF2p0";
        sysMap["Sys_4"] = "weight_var_th_muR0p5_muF1p0";
        sysMap["Sys_5"] = "weight_var_th_muR1p0_muF0p5";
        sysMap["Sys_6"] = "weight_var_th_muR1p0_muF2p0";
        sysMap["Sys_7"] = "weight_var_th_muR2p0_muF0p5";
        sysMap["Sys_8"] = "weight_var_th_muR2p0_muF1p0";
        sysMap["Sys_9"] = "weight_var_th_muR2p0_muF2p0";
    }
    else if(m_DSID.Contains("346414") ||
       m_DSID.Contains("346511") ||
       m_DSID.Contains("344973") ||
       m_DSID.Contains("344974"))
    {
        // sysMap["Sys_1"] = "weight_var_th_nominal";
        sysMap["Sys_2"] = "weight_var_th_muR0p5_muF0p5";
        sysMap["Sys_3"] = "weight_var_th_muR0p5_muF1p0";
        sysMap["Sys_4"] = "weight_var_th_muR0p5_muF2p0";
        sysMap["Sys_5"] = "weight_var_th_muR1p0_muF0p5";
        sysMap["Sys_6"] = "weight_var_th_muR1p0_muF2p0";
        sysMap["Sys_7"] = "weight_var_th_muR2p0_muF0p5";
        sysMap["Sys_8"] = "weight_var_th_muR2p0_muF1p0";
        sysMap["Sys_9"] = "weight_var_th_muR2p0_muF2p0";
    }
    else if(m_DSID.EqualTo("344158"))
    {
        // MG5
        sysMap["Sys_1"] = "weight_var_th_muR1p0_muF0p5";
        sysMap["Sys_2"] = "weight_var_th_muR0p5_muF1p0";
        sysMap["Sys_3"] = "weight_var_th_muR0p5_muF2p0";
        sysMap["Sys_4"] = "weight_var_th_muR1p0_muF0p5";
        sysMap["Sys_5"] = "weight_var_th_muR1p0_muF1p0";
        sysMap["Sys_6"] = "weight_var_th_muR1p0_muF2p0";
        sysMap["Sys_7"] = "weight_var_th_muR2p0_muF0p5";
        sysMap["Sys_8"] = "weight_var_th_muR2p0_muF1p0";
        sysMap["Sys_9"] = "weight_var_th_muR2p0_muF2p0";
    }
    else
    {
        cout<<"Can't recognize DSID WUDOTHIS?"<<endl;
        exit(1);
    }

    m_sysMap = sysMap;
}

TString getPredictions::getNominalSys()
{
    if(m_DSID.Contains("345060") ||
       m_DSID.Contains("344973") ||
       m_DSID.Contains("344974")) return "1";
    else if(m_DSID.Contains("344235")) return "weight_var_th_nominal"; // VBF 

    else if(m_DSID.Contains("345038") ||  // VH, ttH
       m_DSID.Contains("345039") ||
       m_DSID.Contains("345040") ||
       m_DSID.Contains("345066") ||
       m_DSID.Contains("346342") ||
       m_DSID.Contains("346341") ||
       m_DSID.Contains("346340") )
    {
        return "weight_var_th_nominal";
    }
    else if(m_DSID.Contains("346414") ||
       m_DSID.Contains("346511"))
    {
        return "1";
    }
    else if(m_DSID.EqualTo("344158"))
    {
        // MG5
        return "1";
    }
    else
    {
        cout<<"Can't recognize DSID WUDOTHIS?"<<endl;
        exit(1);
    }

    return "1";
}





















