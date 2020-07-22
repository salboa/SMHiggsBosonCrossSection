#include "plotMaker.h"
// #include "AtlasStyle.C"
// #include "AtlasLabels.C"

using namespace std;

// Base class 
plotMaker::plotMaker(std::map<TString, TString>& opts)
{
	m_opts = opts;    
}
plotMaker::~plotMaker()
{

} 



void plotMaker::run()
{
    // fill the map that has the internal variable names
    setVariableMap();

    //push file names into vector
    getFitFiles();

    //get predictions from NNLOPS, MG5, etc
    getPredictions();

    //get the appropriate TGraphs inside those files
    getFitTGraphs();



    if(m_opts["variable"].Contains("fid")) plotFid();
    else 
    {
        m_binWidth = getBinWidth();
        // modify observable data (divide by binwidth etc)
        modifyObs(m_fitGraphVect.at(0));
        plot1D();
    }

}

void plotMaker::getFitFiles()
{
    // Getting the files from the analysis
    TString dirStructure = "/XXX/YYY/";

    // getting the subfolder vector depending on the type of run we want to do
    if(m_opts["type"].Contains("cf") || m_opts["type"].Contains("bin")) m_subFolderVect.push_back("cf");
    else if(m_opts["type"].Contains("matrix")) m_subFolderVect.push_back("matrix");
    else if(m_opts["type"].Contains("comb"))
    {
        m_subFolderVect.push_back("cf");
        m_subFolderVect.push_back("matrix");
    }  

    TString addQual = "";
    if(m_opts["type"].Contains("cf")) addQual = "_binbybin_";

    if(m_opts["variable"].Contains("fid"))
    {
        std::vector<TFile*> fileVec;
        std::vector<TFile*> fileSysVec;

        TFile* file_fid_2l2l       = NULL;
        TFile* file_fid_4l         = NULL;
        TFile* file_fid_comb       = NULL;
        TFile* file_fid_perChan    = NULL;
        TFile* file_fid_sum        = NULL;
        TFile* file_total          = NULL;

        TFile* sysFile_fid_2l2l       = NULL;
        TFile* sysFile_fid_4l         = NULL;
        TFile* sysFile_fid_comb       = NULL;
        TFile* sysFile_fid_perChan    = NULL;
        TFile* sysFile_fid_sum        = NULL;
        TFile* sysFile_total          = NULL;

        TString suffix = "data";

        if(m_opts["doExpected"].Contains("true")) suffix = "Expected";

        file_fid_perChan       = new TFile(m_opts["inputDir"] + "/fid/fid_perChan/" + "fid_perChan_wsys" + suffix +".root");
        file_fid_2l2l          = new TFile(m_opts["inputDir"] + "/fid/fid_2l2l/" + "fid_2l2l_wsys" + suffix +".root");
        file_fid_4l            = new TFile(m_opts["inputDir"] + "/fid/fid_4l/" + "fid_4l_wsys" + suffix +".root");
        file_fid_comb          = new TFile(m_opts["inputDir"] + "/fid/fid_comb/" + "fid_comb_wsys" + suffix +".root");
        file_fid_sum           = new TFile(m_opts["inputDir"] + "/fid/fid_sum/" + "fid_sum_wsys" + suffix +".root");
        file_total             = new TFile(m_opts["inputDir"] + "/fid/total/" + "total_wsys" + suffix +".root");
        fileVec.push_back(file_fid_perChan); fileVec.push_back(file_fid_2l2l); fileVec.push_back(file_fid_4l); 
        fileVec.push_back(file_fid_sum); fileVec.push_back(file_fid_comb); fileVec.push_back(file_total);

        sysFile_fid_perChan    = new TFile(m_opts["inputDir"] + "/fid/fid_perChan/" + "fid_perChan_wonlysys" + suffix +".root");
        sysFile_fid_2l2l       = new TFile(m_opts["inputDir"] + "/fid/fid_2l2l/" + "fid_2l2l_wonlysys" + suffix +".root");
        sysFile_fid_4l         = new TFile(m_opts["inputDir"] + "/fid/fid_4l/" + "fid_4l_wonlysys" + suffix +".root");
        sysFile_fid_comb       = new TFile(m_opts["inputDir"] + "/fid/fid_comb/" + "fid_comb_wonlysys" + suffix +".root");
        sysFile_fid_sum        = new TFile(m_opts["inputDir"] + "/fid/fid_sum/" + "fid_sum_wonlysys" + suffix +".root");
        sysFile_total          = new TFile(m_opts["inputDir"] + "/fid/total/" + "total_wonlysys" + suffix +".root");
        fileSysVec.push_back(sysFile_fid_perChan); fileSysVec.push_back(sysFile_fid_2l2l); fileSysVec.push_back(sysFile_fid_4l); 
        fileSysVec.push_back(sysFile_fid_sum); fileSysVec.push_back(sysFile_fid_comb); fileSysVec.push_back(sysFile_total);

        for(auto file:fileVec)
        {
            if(file->IsZombie())
            {
                cout << "Input file not found" << endl;
                cout << "Exiting..." << endl;
                exit(1);
            }
        }
        bool missingSys = false;
        for(auto file:fileSysVec)
        {
            if(file->IsZombie())
            {
                cout << "Sys only file not found, will use all sys for now" << endl;
                missingSys = true;   
            }
        }

        // channel, 2l2l, 4l, sum, comb, total
        m_fidFiles = {fileVec.at(0), fileVec.at(1), fileVec.at(2), fileVec.at(3), fileVec.at(4), fileVec.at(5)};
        if(missingSys) m_fidSysFiles = m_fidFiles;
        else m_fidSysFiles = {fileSysVec.at(0), fileSysVec.at(1), fileSysVec.at(2), fileSysVec.at(3), fileSysVec.at(4), fileSysVec.at(5)};
    
    }

    else
    {
        for(auto sub:m_subFolderVect)
        {

            dirStructure.ReplaceAll("YYY", m_opts["variable"]);
            dirStructure.ReplaceAll("XXX", m_opts["type"]);
            TString fileName = "";
            TString sysFileName = "";
            TFile *inFile    = NULL;
            TFile *inSysFile = NULL;

            if(m_opts["doExpected"].Contains("true"))
            {
                fileName       = m_opts["inputDir"] + dirStructure + m_opts["variable"] +"_wsysExpected.root";
                sysFileName    = m_opts["inputDir"] + dirStructure + m_opts["variable"] +"_wonlysysExpected.root";
            }
            else
            {
                fileName        = m_opts["inputDir"] + dirStructure + m_opts["variable"] +"_wsysdata.root";
                sysFileName     = m_opts["inputDir"] + dirStructure + m_opts["variable"] +"_wonlysysdata.root";              
            }

            inFile         = new TFile(fileName);
            inSysFile      = new TFile(sysFileName);  

            if(inFile->IsZombie())
            {
                cout << "File " << fileName <<" not found" << endl;
                cout << "Exciting..." << endl;
                exit(1);
            }

            if(inSysFile->IsZombie())
            {
                cout << "Sys file " << sysFileName << "not found, will plot full sys for now" << endl;
                inSysFile = inFile;
            }

            TString unfoldType = "Matrix Unfold";
            if(m_opts["type"].Contains("cf")) unfoldType = "Bin-by-bin";

            m_fitFileVect.push_back({inFile, inSysFile, unfoldType});
        }
    }
}
void plotMaker::saveFidPVal()
{
    std::vector<double> cBinWidth;
    cBinWidth.push_back(1);
    pValMaker* worker   = new pValMaker(m_opts, m_binWidth);
    TString pval_nnlopos_perChan =  worker->getPVal(m_NNLOPS_N3LO_Fid.fidPerChan.nom, "NNLOPS", "m_fidchannel");
    TString pval_nnlopos_2l2l    =  worker->getPVal(m_NNLOPS_N3LO_Fid.fid2l2l.nom,  "NNLOPS", "m_fid2l2l");
    TString pval_nnlopos_4l      =  worker->getPVal(m_NNLOPS_N3LO_Fid.fid4l.nom,    "NNLOPS", "m_fid4l");
    TString pval_nnlopos_comb    =  worker->getPVal(m_NNLOPS_N3LO_Fid.fidComb.nom,  "NNLOPS", "m_comb");
    TString pval_nnlopos_sum     =  worker->getPVal(m_NNLOPS_N3LO_Fid.fidSum.nom,   "NNLOPS", "m_fidsum");
    

    // // total 
    TString pval_nnlopos_total  =  worker->getPVal(m_NNLOPS_N3LO_Fid.fidTotal.nom,   "NNLOPS", "m_total");
    // TString pval_MG5_total      =  worker->getPVal(m_MG5FxFxFid.fidTotal.nom,        "MG5", "m_total");
    // TString pval_N2LO_total     =  worker->getPVal(m_NNLOPS_N2LO_Fid.fidTotal.nom,   "NNLOPS@N2LO", "m_total");
    // TString pval_HRes_total     =  worker->getPVal(m_HRESFid.fidTotal.nom,           "HRes", "m_total");

    delete worker;

}

void plotMaker::plotFid()
{

    if(m_opts["calcPVal"].Contains("true")) saveFidPVal();
    SetAtlasStyle();
    TCanvas* c = new TCanvas( "Fiducial", "Fiducial", 600, 600 );

    TH1D* frame = new TH1D("frame", "frame", 17, 0, 17);
    setupFidFrame(frame);
    frame->Draw();

    // plotting the TGraphs for the predictions 
    TGraphAsymmErrors* NNLOPS_N3LO      = getFidBinning(m_NNLOPS_N3LO_Fid,      false, "NNLOPS_N3LO");
    TGraphAsymmErrors* MG5              = getFidBinning(m_MG5FxFxFid,           true,  "MG5Fid");
    TGraphAsymmErrors* NNLOPS_N2LO      = getFidBinning(m_NNLOPS_N2LO_Fid,      true,  "NNLOPS_N2LO");
    TGraphAsymmErrors* HRES             = getFidBinning(m_HRESFid,              true,  "HResFid");

    setStyle("NNLOPS_N3LO",     NNLOPS_N3LO, false);
    setStyle("MG5Fid",          MG5,    false);
    setStyle("NNLOPS_N2LO",     NNLOPS_N2LO,     false);
    setStyle("HResFid",         HRES,   false);


    for(Int_t ii=0; ii<NNLOPS_N3LO->GetN(); ii++)
    {
        double x, y;
        NNLOPS_N3LO->GetPoint(ii, x, y);
        cout << ii << "\t" << y << "\t" << NNLOPS_N3LO->GetErrorYhigh(ii) << "\t" << NNLOPS_N3LO->GetErrorYlow(ii) << endl;
    }

    NNLOPS_N3LO->Draw("2,same");
    NNLOPS_N3LO->Draw("pX,same");
    MG5->Draw("2,same");
    MG5->Draw("pX,same");
    NNLOPS_N2LO->Draw("2,same");
    NNLOPS_N2LO->Draw("pX,same");
    HRES->Draw("2,same");
    HRES->Draw("pX,same");

    //plotting the data
    TGraphAsymmErrors *obs      = getFidBinning(m_fidResults, false); 
    TGraphAsymmErrors *obsSys   = getFidBinning(m_fidSysResults, true);
    setStyle("Data",    obs,    false);
    setStyle("DataSys", obsSys, false);

    obs->Draw("pez");
    obsSys->Draw("E5,same");


    // making the axis for the graph
    TGaxis *LeftAx   = getAxis("left");
    TGaxis *CenterAx = getAxis("center");
    TGaxis *RightAx  = getAxis("right");
    LeftAx->Draw();
    CenterAx->Draw();
    RightAx->Draw();

    // plotting the legend and labels
    TLegend *leg = CreateLegend("",true);
    leg->AddEntry(obs, "Data", "pez");
    leg->AddEntry(obsSys, "Syst. uncertainties", "f");
    leg->AddEntry(NNLOPS_N3LO, "ggF@N3LO + XH", "pf");
    leg->AddEntry(MG5,"MG5 FxFx + XH","pf");
    leg->AddEntry(NNLOPS_N2LO,"NNLOPS + XH","pf");
    leg->AddEntry(HRES,"HRes 2.3, NNLO+NNLL + XH","pf");
    drawLabels(true, "");
    leg->SetY1(0.72);
    leg->Draw();    


    system("mkdir -vp " + m_opts["outputDir"]);
    c->SaveAs(m_opts["outputDir"] + "/fid.eps");

    delete c;

}

void plotMaker::getPredictions()
{

    if(m_opts["variable"].Contains("fid"))
    {
        m_NNLOPS_N3LO_Fid   = loadFidPreditions("expected/prediction_N3LOggF.root", false);
        m_MG5FxFxFid        = loadFidPreditions("expected/prediction_MG5.root", true);
        m_NNLOPS_N2LO_Fid   = loadFidPreditions("expected/N2LOggF.root", true);
        m_HRESFid           = loadFidPreditions("expected/HRes.root", true);
        m_XHFid             = loadFidPreditions("expected/prediction_XH.root", false);


        // scaleHist(m_MG5FxFxFid.fidTotal, 1.47);
        // cout << "NNLOPS: "<< m_NNLOPSFid.fidTotal.nom->GetBinContent(1) << " HRes " << m_XHFid.fidTotal.nom->GetBinContent(1) << endl;

        // add XH
        addXH(m_NNLOPS_N3LO_Fid,    m_XHFid,    false);
        addXH(m_MG5FxFxFid,         m_XHFid,    true);
        addXH(m_NNLOPS_N2LO_Fid,    m_XHFid,    true);
        addXH(m_HRESFid,            m_XHFid,    true);


    }

    else
    {

        m_NNLOPS    = loadPreditions("expected/prediction_N3LOggF.root");
        m_NNLOPS_XH = loadPreditions("expected/prediction_XH.root");
        m_MG5FxFx   = loadPreditions("expected/prediction_MG5.root");

        scaleHist(m_MG5FxFx, 1.47);

        // add XH
        addXH(m_NNLOPS,  m_NNLOPS_XH);
        addXH(m_MG5FxFx, m_NNLOPS_XH);

        for(int i = 0; i < m_NNLOPS.nom->GetNbinsX(); i++)
        {
            cout <<"XS  " << m_NNLOPS.nom->GetBinContent(i+1) << endl;
        }
    }
}

void plotMaker::setFidPoint(TGraphAsymmErrors *newGraph, int newBin, TGraphAsymmErrors *oldGraph, int oldBin, bool isSys, double scaling)
{
    double x, y;
    double shift = 0.5;

    if(oldGraph == NULL) newGraph->SetPoint(newBin, newBin + shift, 0);

    else
    {
        oldGraph->GetPoint(oldBin, x, y); 
        double yErrLow  =  oldGraph->GetErrorYlow(oldBin)/scaling;
        double yErrHigh =  oldGraph->GetErrorYhigh(oldBin)/scaling;
        newGraph->SetPoint(newBin, newBin + shift, y/scaling);
           
        if(isSys) newGraph->SetPointError(newBin, GetBarSize(m_opts["variable"]).second, GetBarSize(m_opts["variable"]).second, yErrLow, yErrHigh);
        else newGraph->SetPointError(newBin, 0.0, 0.0, yErrLow, yErrHigh);
    }


}

TGraphAsymmErrors* plotMaker::getFidBinning(histPredFid resultTGraphs, bool totalOnly, TString inName)
{

    // Shift for the bin
    int specialBin = 10;
    if(inName.EqualTo("NNLOPS_N3LO"))       specialBin = 13;
    if(inName.EqualTo("MG5Fid"))            specialBin = 14;
    if(inName.EqualTo("NNLOPS_N2LO"))       specialBin = 15;
    if(inName.EqualTo("HResFid"))           specialBin = 16;

    TGraphAsymmErrors* rebinnedGraph = new TGraphAsymmErrors();

    // first we need to convert our histograms with up/down/nom into TGraphs
    // The we can send them to rebining
    TGraphAsymmErrors *fidTotalGraph    = NULL;
    TGraphAsymmErrors *fidPerChanGraph  = NULL;
    TGraphAsymmErrors *fid4lGraph       = NULL;
    TGraphAsymmErrors *fid2l2lGraph     = NULL;
    TGraphAsymmErrors *fidSumGraph      = NULL;
    TGraphAsymmErrors *fidCombGraph     = NULL;


    if(totalOnly)
        fidTotalGraph    = makeTGraph(resultTGraphs.fidTotal, "fid");
    else
    {    
        fidPerChanGraph  = makeTGraph(resultTGraphs.fidPerChan, "fid");
        fid4lGraph       = makeTGraph(resultTGraphs.fid4l, "fid");
        fid2l2lGraph     = makeTGraph(resultTGraphs.fid2l2l, "fid");


        fidSumGraph      = makeTGraph(resultTGraphs.fidSum, "fid");
        fidCombGraph     = makeTGraph(resultTGraphs.fidComb, "fid");
        fidTotalGraph    = makeTGraph(resultTGraphs.fidTotal, "fid");
    }    

    bool isSys = true;

    double sChannelScale = 1.92/4.8;
    double cChannelScale = 4.8/4.8;
    double fChannelScale = 95*1000/4.8;


    // double sChannelScale = 1;
    // double cChannelScale = 1;
    // double fChannelScale = 1;

    // hard-coded recasting of Tgraphs into the bins for the fiducial plot 
    setFidPoint(rebinnedGraph,0, fidPerChanGraph,0, isSys, sChannelScale); //4mu
    setFidPoint(rebinnedGraph,1, fidPerChanGraph,1, isSys, sChannelScale); // 4e
    setFidPoint(rebinnedGraph,2, fidPerChanGraph,2, isSys, sChannelScale); // 2mu2e
    setFidPoint(rebinnedGraph,3, fidPerChanGraph,3, isSys, sChannelScale); // 2e2mu

    // points 4 and 5 are empty bins for the axis
    setFidPoint(rebinnedGraph,6, fid4lGraph,    0, isSys,   cChannelScale); //4l
    setFidPoint(rebinnedGraph,7, fid2l2lGraph,  0, isSys,   cChannelScale); // 2l2l
    setFidPoint(rebinnedGraph,8, fidSumGraph,   0, isSys,   cChannelScale); // sum
    setFidPoint(rebinnedGraph,9, fidCombGraph,  0, isSys,   cChannelScale); // comb

    // points 10, 11, 12, 13 are empty for the axis
    setFidPoint(rebinnedGraph, specialBin, fidTotalGraph, 0, isSys, fChannelScale); // comb

    return rebinnedGraph;
}

    
TGraphAsymmErrors* plotMaker::getFidBinning(fidResTGraphs resultTGraphs, bool isSys)
{
    TGraphAsymmErrors* rebinnedGraph = new TGraphAsymmErrors();
    
    double sChannelScale = 1.92/4.8;
    double cChannelScale = 4.8/4.8;
    double fChannelScale = 95*1000/4.8;

    // hard-coded recasting of Tgraphs into the bins for the fiducial plot 
    setFidPoint(rebinnedGraph,0, resultTGraphs.fidPerChan,0, isSys, sChannelScale); //4mu
    setFidPoint(rebinnedGraph,1, resultTGraphs.fidPerChan,1, isSys, sChannelScale); // 4e
    setFidPoint(rebinnedGraph,2, resultTGraphs.fidPerChan,2, isSys, sChannelScale); // 2mu2e
    setFidPoint(rebinnedGraph,3, resultTGraphs.fidPerChan,3, isSys, sChannelScale); // 2e2mu

    // points 4 and 5 are empty bins for the axis
    setFidPoint(rebinnedGraph,6, resultTGraphs.fid4l,   0, isSys,   cChannelScale); //4l
    setFidPoint(rebinnedGraph,7, resultTGraphs.fid2l2l, 0, isSys,   cChannelScale); // 2l2l
    setFidPoint(rebinnedGraph,8, resultTGraphs.fidSum,  0, isSys,   cChannelScale); // sum
    setFidPoint(rebinnedGraph,9, resultTGraphs.fidComb, 0, isSys,   cChannelScale); // comb

    // points 10, 11, 12, 13 are empty for the axis
    setFidPoint(rebinnedGraph,12, resultTGraphs.fidTotal, 0, isSys, fChannelScale); // comb


    return rebinnedGraph;

}
void plotMaker::addXH(histPred &prediction, histPred XH)
{
    prediction.nom->Add(XH.nom);

    // adding in quadrature
    for(Size_t bin = 0; bin < prediction.nom->GetNbinsX(); bin++)
    {
        double upErr = pow(prediction.up->GetBinContent(bin+1),2) + pow(XH.up->GetBinContent(bin+1),2);
        double downErr = pow(prediction.down->GetBinContent(bin+1),2) + pow(XH.down->GetBinContent(bin+1),2);
        double nomVal = prediction.nom->GetBinContent(bin+1);
        prediction.up->SetBinContent(bin+1,     nomVal + sqrt(upErr));
        prediction.down->SetBinContent(bin+1,   nomVal -sqrt(downErr));

    }

}


void plotMaker::addXH(histPredFid &ggF, histPredFid XH, bool totalOnly)
{
    if(!totalOnly)
    {
        addXH(ggF.fidPerChan,   XH.fidPerChan);
        addXH(ggF.fid2l2l,      XH.fid2l2l);
        addXH(ggF.fid4l,        XH.fid4l);
        addXH(ggF.fidSum,       XH.fidSum);
        addXH(ggF.fidComb,      XH.fidComb);

    }
        addXH(ggF.fidTotal, XH.fidTotal);
}



plotMaker::histPred plotMaker::loadPreditions(TString fileName)
{
    histPred prediction;

    TFile *inFile = new TFile(fileName);
    if(inFile->IsZombie())
    {
        cout << "Expected file not found "<< fileName << endl;
        exit(1);
    } 



    prediction.nom  = (TH1D*) inFile->Get(m_variableMap[m_opts["variable"]] + "_nom");
    prediction.up   = (TH1D*) inFile->Get(m_variableMap[m_opts["variable"]] + "_up");
    prediction.down = (TH1D*) inFile->Get(m_variableMap[m_opts["variable"]] + "_down");

    cout << "For Laurelle " << fileName << endl;
    cout << "-------------------" << endl;
    for(int i = 0; i < prediction.nom->GetNbinsX(); i++) 
    {
        cout<<"bin: "<<i+1<<" "<<prediction.nom->GetBinContent(i+1)<<" "<<prediction.up->GetBinContent(i+1)<<" "<<prediction.down->GetBinContent(i+1)<<endl;
    }


    // prediction.nom->SetDirectory(0);
    // prediction.up->SetDirectory(0);
    // prediction.down->SetDirectory(0);

    return prediction;
}

void plotMaker::printFidPredition(plotMaker::histPred hist )
{
    cout <<"\t" << hist.nom->GetBinContent(1) << "\t" << " + " << hist.nom->GetBinContent(1) << " - " << hist.down->GetBinContent(1) << endl;
}

plotMaker::histPredFid plotMaker::loadFidPreditions(TString fileName, bool onlyTotal)
{
    histPredFid prediction;
    TFile *inFile = new TFile(fileName);
    if(inFile->IsZombie())
    {
        cout << "Expected file not found "<< fileName << endl;
        exit(1);
    } 

    if(!onlyTotal)
    {
        // getting 4e, 4mu, 2mu2e, 2e2mu
        prediction.fidPerChan.nom   = (TH1D*) inFile->Get("fid_perChan_nom");
        prediction.fidPerChan.up    = (TH1D*) inFile->Get("fid_perChan_up");
        prediction.fidPerChan.down  = (TH1D*) inFile->Get("fid_perChan_down");
        cout << "Prediction for per channel ... " << fileName<< endl;
        for(int bin = 0; bin < prediction.fidPerChan.nom->GetNbinsX(); bin ++)
        {
            cout << bin << "\t" << prediction.fidPerChan.nom->GetBinContent(bin + 1) << endl; 
        }

        // getting 4l
        prediction.fid4l.nom    = (TH1D*) inFile->Get("fid_4l_nom");
        prediction.fid4l.up     = (TH1D*) inFile->Get("fid_4l_up");
        prediction.fid4l.down   = (TH1D*) inFile->Get("fid_4l_down");    
        cout << "Prediction for 4l ... " << fileName ; printFidPredition(prediction.fid4l);

        // getting 2l2l
        prediction.fid2l2l.nom  = (TH1D*) inFile->Get("fid_2l2l_nom");
        prediction.fid2l2l.up   = (TH1D*) inFile->Get("fid_2l2l_up");
        prediction.fid2l2l.down = (TH1D*) inFile->Get("fid_2l2l_down");    
        cout << "Prediction for 2l2l ... " << fileName ; printFidPredition(prediction.fid2l2l);

        // getting fidSum
        prediction.fidSum.nom   = (TH1D*) inFile->Get("fid_sum_nom");
        prediction.fidSum.up    = (TH1D*) inFile->Get("fid_sum_up");
        prediction.fidSum.down  = (TH1D*) inFile->Get("fid_sum_down"); 
        cout << "Prediction for sum ... " << fileName ; printFidPredition(prediction.fidSum);   

        // getting fidCom (same as fidSum)
        prediction.fidComb.nom   = (TH1D*) inFile->Get("fid_sum_nom")->Clone("fid_comb_nom");
        prediction.fidComb.up    = (TH1D*) inFile->Get("fid_sum_up")->Clone("fid_comb_up");
        prediction.fidComb.down  = (TH1D*) inFile->Get("fid_sum_down")->Clone("fid_comb_down");
        cout << "Prediction for comb ... " << fileName ; printFidPredition(prediction.fidComb);   
    }

    // total higgs XS
    prediction.fidTotal.nom  = (TH1D*) inFile->Get("inc_nom");
    prediction.fidTotal.up   = (TH1D*) inFile->Get("inc_up");
    prediction.fidTotal.down = (TH1D*) inFile->Get("inc_down");  
    cout << "Prediction for total ... " << fileName ; printFidPredition(prediction.fidTotal);

    return prediction;
}


plotMaker::fidResTGraphs plotMaker::getFidTGraphs(fidResFiles fidFiles)
{

    fidResTGraphs fidResults;

    TGraphAsymmErrors* fidPerChanTGraph = (TGraphAsymmErrors*)fidFiles.fidPerChan->Get("fid_perChan");
    TGraphAsymmErrors* fid2l2lTGraph    = (TGraphAsymmErrors*)fidFiles.fid2l2l->Get("fid_2l2l");
    TGraphAsymmErrors* fid4lTGraph      = (TGraphAsymmErrors*)fidFiles.fid4l->Get("fid_4l");

    TGraphAsymmErrors* fidSumTGraph     = (TGraphAsymmErrors*)fidFiles.fidSum->Get("fid_sum");
    TGraphAsymmErrors* fidCombTGraph    = (TGraphAsymmErrors*)fidFiles.fidComb->Get("fid_comb");
    TGraphAsymmErrors* fidTotalTGraph   = (TGraphAsymmErrors*)fidFiles.fidTotal->Get("total");

    fidResults = {fidPerChanTGraph, fid2l2lTGraph, fid4lTGraph, fidSumTGraph, fidCombTGraph, fidTotalTGraph};

    return fidResults;
}


void plotMaker::getFitTGraphs()
{
    if(m_opts["variable"].EqualTo("fid") )
    {
        m_fidResults    = getFidTGraphs(m_fidFiles);
        m_fidSysResults = getFidTGraphs(m_fidSysFiles);
    }

    else 
    {
        // if item is 1D
        for(auto item:m_fitFileVect)
        {

            TGraphAsymmErrors* fitGraph     = (TGraphAsymmErrors*)item.fitFile->Get(m_opts["variable"]);
            TGraphAsymmErrors* sysFitGraph  = (TGraphAsymmErrors*)item.sysFitFile->Get(m_opts["variable"]);      


            TGraphAsymmErrors* ZZfitGraph     = (TGraphAsymmErrors*)item.fitFile->Get(m_opts["variable"] + "_ZZINT");
            TGraphAsymmErrors* ZZsysFitGraph  = (TGraphAsymmErrors*)item.sysFitFile->Get(m_opts["variable"] + "_ZZINT");      


            m_fitGraphVect.push_back({fitGraph, sysFitGraph,ZZfitGraph,ZZsysFitGraph,item.unFoldType});

        }
    }

}

void plotMaker::plot1D()
{
    // special atlas style? 
    SetAtlasStyle();

    // gStyle->SetTitleFont(62);
    // gStyle->SetTitleFont(62);

    // gStyle->SetTitleFontSize(14);
    // gStyle->SetTitleFontSize(14);



    // // gStyle->SetTitleSize(0.18,"y");
    // // gStyle->SetTitleSize(0.18,"x");

    // gStyle->SetTitleOffset(0.18,"y");
    // gStyle->SetTitleOffset(0.18,"x");



    int upCanLim = 600;

    double p1Lw = 0.345;
    double p1Up = 0.99;

    double p2Lw = 0.01;
    double p2Up = 0.345;

    double p3Lw = 0;
    double p3Up = 0;

    double p2LowerMarg = 0.3;


    if(m_opts["plotZZ"].Contains("true"))
    {
        p1Lw = 0.4;

        double padSapce = 0.025/(p1Up - p1Lw);
        double p2marg = (p2Up - p2Lw)/padSapce;

        p2Lw = p1Lw/1.8; //0,2
        p2Up = p1Lw;

        p3Lw = 0.01;
        p3Up = p2Lw; //0.2

        p2LowerMarg = p2marg;

        upCanLim = 700;

        // 
    }

    TCanvas *c = new TCanvas( m_opts["variable"], m_opts["variable"], 600, upCanLim);
    c->Draw();

    double leftMargin = 0.14;
    TPad* p1 = new TPad("p1","p1",0.01,p1Lw,0.99,p1Up);
    p1->Draw();
    p1->SetBottomMargin(0.025);
    p1->SetLeftMargin(leftMargin);

    TPad* p2 = new TPad("p2","p2",0.01,p2Lw,0.99,p2Up);
    p2->Draw();
    p2->SetTopMargin(0.);
    p2->SetLeftMargin(leftMargin);
    p2->SetBottomMargin(p2LowerMarg);

    TPad* p3 = NULL;

    if(m_opts["plotZZ"].Contains("true"))
    {
        p3 = new TPad("p3","p3",0.01,p3Lw,0.99,p3Up);
        p3->Draw();
        p3->SetTopMargin(0.0);
        p3->SetLeftMargin(leftMargin);
        p3->SetBottomMargin(0.5);
    }

    p1->cd();




    // making the frame we will label with axis, fix labels, etc 
    TH1D* frame = NULL;
    if(m_opts["intBins"].Contains("true"))
    {   
        rebin(m_NNLOPS);
        rebin(m_MG5FxFx);
        rebin(m_NNLOPS_XH);

    }

    frame = (TH1D*)m_NNLOPS.nom->Clone("frame");
    frame->SetLabelOffset(3);

    bool threePad = false;
    if(m_opts["plotZZ"].Contains("true")) threePad = true;

    setAxisLabels(frame, m_opts["variable"], false, fabs(p1Lw-0.01), false);
    AdjustXaxis(frame, m_opts["variable"]);
    frame->Reset(0);
    frame->Draw("hist");

    // same thing as the frame, but this will be the dotted red
    TH1D* NNLOPS_hist = (TH1D*)m_NNLOPS.nom->Clone("NNLOPS_hist");
    setStyle("NNLOPS", NNLOPS_hist);
    NNLOPS_hist->Draw("histsame");


    // make out predictions into TAsym errors so we can offset them to look fancy etc.
    TGraphAsymmErrors* nnlopsexpected   = makeTGraph(m_NNLOPS, "NNLOPS");
    TGraphAsymmErrors* mgexpected       = makeTGraph(m_MG5FxFx, "MG5");
    setStyle("NNLOPS_XH",   nnlopsexpected,                 false);
    setStyle("MG5_XH",      mgexpected,                     false);
    setStyle("XH",          m_NNLOPS_XH.nom);
    setStyle("Data",        m_fitGraphVect.at(0).fitGraph, false);
    setStyle("DataSys",     m_fitGraphVect.at(0).sysFitGraph,false);


    nnlopsexpected->Draw("2,same");
    nnlopsexpected->Draw("pX,same");
    mgexpected->Draw("2,same");
    mgexpected->Draw("pX,same");
    m_NNLOPS_XH.nom->Draw("histsame");
    m_fitGraphVect.at(0).sysFitGraph->Draw("E5,same");
    m_fitGraphVect.at(0).fitGraph->Draw("pez");

    //draw the legend
    TLegend *leg = CreateLegend("",false);
    leg->AddEntry(m_fitGraphVect.at(0).fitGraph, "Data","pez");
    leg->AddEntry(m_fitGraphVect.at(0).sysFitGraph, "Syst. uncertainties","f");
    leg->AddEntry(mgexpected, "MG5 FxFx #font[12]{K} = 1.47, +XH", "pf");
    leg->AddEntry(nnlopsexpected, "NNLOPS #font[12]{K} = 1.1, +XH", "pf");
    leg->AddEntry(m_NNLOPS_XH.nom, "XH = VBF+VH+ttH+bbH+tH", "lf");


    leg->Draw();
    drawLabels(false,m_opts["type"]);
    if(m_opts["variable"].Contains("pt")) drawLimit();
    

    // getting the pValue (either fitting, or reading the results from a previous fit)
    pValMaker* worker   = new pValMaker(m_opts, m_binWidth);
    TString pval_nnlopos =  worker->getPVal(m_NNLOPS.nom,    "NNLOPS");
    TString pval_mg5     =  worker->getPVal(m_MG5FxFx.nom,   "MG5");
    delete worker;
    plotPValue(pval_nnlopos, pval_mg5);

    // do the ratio and draw it
    p2->cd();
    TH1D* ratioFrame = (TH1D*)frame->Clone("ratioFrame");
    ratioFrame->GetYaxis()->SetRangeUser(0.4,1.85);
    AdjustXaxis(ratioFrame, m_opts["variable"]);
    setAxisLabels(ratioFrame, m_opts["variable"], true, fabs(p2Lw-p2Up), false);
    if(m_opts["plotZZ"].Contains("true"))
    {
       ratioFrame->GetXaxis()->SetTitle(""); 
       ratioFrame->GetXaxis()->SetLabelSize(0); 
    }
    ratioFrame->Draw("hist"); 
    TGraphAsymmErrors* obs_ratio         = makeRatio(m_fitGraphVect.at(0).fitGraph, m_fitGraphVect.at(0).fitGraph,ratioFrame,"Data");
    TGraphAsymmErrors* exp_ratio_MG      = makeRatio(mgexpected,                     m_fitGraphVect.at(0).fitGraph,ratioFrame,"MG5");
    TGraphAsymmErrors* exp_ratio_NNLOPS  = makeRatio(nnlopsexpected,                 m_fitGraphVect.at(0).fitGraph,ratioFrame,"NNLOPS");
    setStyle("obsratio",obs_ratio, false);
    leg->AddEntry(obs_ratio, "Total stat. #oplus syst. uncertainty", "lf");
    setStyle("MG5ratio",exp_ratio_MG, false);
    setStyle("NNLOPSratio",exp_ratio_NNLOPS, false);
    exp_ratio_MG->Draw("2p,same");
    exp_ratio_NNLOPS->Draw("2p,same"); 
    TLine *l = MakeHorLine(ratioFrame);
    l->Draw();
    obs_ratio->Draw("2p,same");
    l->Draw();
    exp_ratio_MG->Draw("2p,same");
    exp_ratio_NNLOPS->Draw("2p,same");
    for (unsigned int i =0; i< m_Arrows.size(); ++i) m_Arrows.at(i)->Draw(); 
    gPad->RedrawAxis();


    if(m_opts["plotZZ"].Contains("true"))
    {
        p3->cd();
        TH1D* ratioFrameZZ = (TH1D*)frame->Clone("ratioFrame");
        ratioFrameZZ->GetYaxis()->SetRangeUser(0.4,1.85);
        AdjustXaxis(ratioFrameZZ, m_opts["variable"]);
        setAxisLabels(ratioFrameZZ, m_opts["variable"], true, fabs(p3Lw-p3Up), true);
        ratioFrameZZ->Draw("hist");
        TLine *lZZ = MakeHorLine(ratioFrameZZ);
        lZZ->Draw();
        setStyle("ZZData",     m_fitGraphVect.at(0).ZZfitGraph,false);
        m_fitGraphVect.at(0).ZZfitGraph->Draw("pez");
        if(m_opts["plotZZ"].Contains("true")) leg->AddEntry(m_fitGraphVect.at(0).ZZfitGraph, "Fitted ZZ Normalization", "pel");

    
    }


    // save plot
    system("mkdir -vp " + m_opts["outputDir"]);
    TString saveName = m_opts["outputDir"]+ "/" + m_opts["variable"] + "_" + m_opts["type"]+ ".eps";
    c->SaveAs(saveName);

    delete c;
}





TGraphAsymmErrors* plotMaker::makeRatio(TGraphAsymmErrors* input, TGraphAsymmErrors* reference, TH1D* frame, TString compareTo)
{
  double eps = 0.0000000001;
  TGraphAsymmErrors* m_ratio = new TGraphAsymmErrors();
  double x; double y;
  double x1; double y1;
  double offset = 0;
  if(compareTo.Contains("MG5"))       { offset = -GetBarSpacing(m_opts["variable"]); }
  // else if(MC=="hres"){ offset =  GetBarSpacing(m_opts["variable"]); }
  else if(compareTo.Contains("NNLOPS")) offset =  GetBarSpacing(m_opts["variable"]);

  for(Int_t ii=0; ii<input->GetN(); ii++)
  {

    reference->GetPoint(ii, x, y);
    input->GetPoint(ii, x1, y1);

    bool resetY = false;
    if(fabs(y) < eps)
    {
        y = 0.000000001;
        resetY = true;
    }
    double inputErrLow = input->GetErrorYlow(ii);
    double inputErrHigh = input->GetErrorYhigh(ii);
    double ratioVal = y1/y;
    double yErrLow = inputErrLow/y;
    double yErrHigh = inputErrHigh/y;
    if(compareTo.Contains("Data") && resetY)
    {
        yErrLow = 0;
        yErrHigh = 2;
        ratioVal = 1;
    }

    cout <<"Ratio " << compareTo << "\t" << ii <<"\t" << ratioVal <<"\t" << yErrLow <<"\t" << inputErrLow <<"\t" << inputErrHigh  << endl;


    m_ratio->SetPoint(ii, frame->GetBinCenter(ii+1) + offset, ratioVal);
    m_ratio->SetPointError(ii, GetBarSize(m_opts["variable"]).second, GetBarSize(m_opts["variable"]).second, yErrLow, yErrHigh);
    if (compareTo.Contains("Data")) m_ratio->SetPointError(ii, 0.5,0.5, yErrLow, yErrHigh);

    if( ratioVal > 2.0 ||  ratioVal < 0 )
    {    
        m_Arrows.push_back( MakeArrows(frame->GetBinCenter(ii+1)+offset,ratioVal, compareTo) );
        cout << "arrow found " << frame->GetBinCenter(ii+1)+offset<< endl;
    }
  }

  return m_ratio;
  
}

TArrow* plotMaker::MakeArrows(double u, double y, TString compareTo)
{
  double v = 0, off1 = 0, off2 = 0;
  if(y>1){
    v = 2.0; off1 = -0.2; off2 = 0.2;
  }
  else{
    v = 0.5; off1 = 0.2; off2 = -0.2; //0.5
  }
  TArrow *ar2 = new TArrow(u,v+off1,u,v+off2,0.005,"|>");
  ar2->SetLineWidth(2);
  if(compareTo.Contains("MG5"))
  {
    ar2->SetLineColor(kBlue);
    ar2->SetFillColor(kBlue);
  }
  else if(compareTo.Contains("NNLOPS"))
  {
    ar2->SetLineColor(kRed);
    ar2->SetFillColor(kRed);
  }
  else if(compareTo.Contains("hres"))
  {
    ar2->SetLineColor(kGreen+3);
    ar2->SetFillColor(kGreen+3);
  }
  return ar2;

}

void plotMaker::modifyObs(tgraphGroup &fitResults)
{
    double x, y;
    int offsetbin = 0;
    int nbins     = fitResults.fitGraph->GetN();
    float offset  = 0; 

    std::vector<double> binWidth = getBinWidth();
    for(int i=0; i < nbins; ++i)
    {
        fitResults.fitGraph->GetPoint(i + offsetbin, x, y);
    }
    fitResults.fitGraph      = modifyObs(fitResults.fitGraph,      "Data");
    fitResults.sysFitGraph   = modifyObs(fitResults.sysFitGraph,   "DataSys");

}


TGraphAsymmErrors* plotMaker::modifyObs(TGraphAsymmErrors* inGraph, TString type)
{
    TGraphAsymmErrors* outGraph = new TGraphAsymmErrors();
 
    // cout << type << endl;
    if(!inGraph) return outGraph;

    double x, y;
    int offsetbin = 0;
    int nbins     = inGraph->GetN();
    float offset  = 0; 

    std::vector<double> binWidth = getBinWidth();
    for(int i=0; i < nbins; ++i)
    {
        inGraph->GetPoint(i + offsetbin, x, y);
        if(m_opts["intBins"])
        {
            outGraph->SetPoint(i, i - offset + 0.5, y/(binWidth.at(i)) );
        }
        else
        {

            outGraph->SetPoint(i, x - offset, y/(binWidth.at(i)) );;
        }
        if(type.EqualTo("DataSys")) outGraph->SetPointError(i, GetBarSize(m_opts["variable"]).second, GetBarSize(m_opts["variable"]).second, fabs(inGraph->GetErrorYlow(i))/(binWidth.at(i)), fabs(inGraph->GetErrorYhigh(i))/(binWidth.at(i)));
        else outGraph->SetPointError(i, 0.0, 0.0, fabs(inGraph->GetErrorYlow(i))/(binWidth.at(i)), fabs(inGraph->GetErrorYhigh(i))/(binWidth.at(i)));
        cout << "Bin " << y << "\t" << inGraph->GetErrorYlow(i) << "\t" << inGraph->GetErrorYhigh(i) << "\t" << binWidth.at(i) << endl;
    }

    return outGraph;
  
}



std::vector<double> plotMaker::getBinWidth()
{
    std::vector<double> binWidth;
    for (int bin = 0; bin < m_NNLOPS.nom->GetNbinsX(); ++bin)
    {
        double width = m_NNLOPS.nom->GetBinWidth(bin + 1);
        if(m_opts["variable"].Contains("njet")) width = 1;
        binWidth.push_back(width);
    }

    return binWidth;
}


void plotMaker::rebin(histPred &hist)
{
    hist.nom    = rebin(hist.nom);
    hist.up     = rebin(hist.up);
    hist.down   = rebin(hist.down);
}

TH1D* plotMaker::rebin(TH1D* hist)
{
    TString histName = hist->GetName();
    histName += "_rebinned";
    TH1D* rebined = new TH1D(histName, histName, hist->GetNbinsX(), 0, hist->GetNbinsX());
    
    for(int bin = 0; bin < hist->GetNbinsX(); bin++)
    {
        rebined->SetBinContent(bin+1, hist->GetBinContent(bin+1));
        rebined->SetBinError(bin+1, hist->GetBinError(bin+1));
    }
    return rebined;
}

void plotMaker::scaleHist(histPred &hist, double scaleVal)
{
    hist.nom->Scale(scaleVal);
    hist.up->Scale(scaleVal);
    hist.down->Scale(scaleVal);
}

TGraphAsymmErrors* plotMaker::makeTGraph(histPred predictions, TString name)
{
    float shift = 0;
    float scale = 1;

    if(name.EqualTo("MG5"))
    {
        scale = 0.8;
        shift = -GetBarSpacing(m_opts["variable"]);//0.15;
    }
    if(name=="HRES")
    {
        scale = 0.1;
        shift = GetBarSpacing(m_opts["variable"]);//0.15;
    }
    if(name.EqualTo("NNLOPS"))
    {
        scale = 0.2;
        shift =0.;
        shift = GetBarSpacing(m_opts["variable"]);//0.15;
    }
    if(name.EqualTo("fid"))
    {
      scale = 0.2;
      shift =0.;
      shift = GetBarSpacing(m_opts["variable"]);//0.15;
    }

    TGraphAsymmErrors *tmp = new TGraphAsymmErrors();

    for(Int_t ii=0; ii< predictions.nom->GetNbinsX(); ii++)
    {

        double mul = 1.0;
        // if( name.EqualTo("ExpectedFid") && ii<5 ) mul = 2.5;

        tmp->SetPoint( ii, predictions.nom->GetBinCenter(ii+1)+shift, predictions.nom->GetBinContent(ii+1)*mul );
        Double_t eYdw = (std::abs(predictions.nom->GetBinContent(ii+1) - predictions.down->GetBinContent(ii+1)))*mul;
        Double_t eYup = (std::abs(predictions.nom->GetBinContent(ii+1) - predictions.up->GetBinContent(ii+1)))*mul;
        tmp->SetPointError( ii, GetBarSize(m_opts["variable"]).first, GetBarSize(m_opts["variable"]).second, eYdw, eYup ); 
        
        // cout <<name<<" "<< ii+1<<"\t"<<predictions.nom->GetBinContent(ii+1) << "\t + "<< predictions.up->GetBinContent(ii+1)  << "\t - " << predictions.down->GetBinContent(ii+1) << endl;
    }

    return tmp;
}

void plotMaker::setVariableMap()
{
    m_variableMap["pt"]   = "higgs_pt_fidDres_4lsel"; 
    m_variableMap["njet"] = "n_jets_fidDres_4lsel";
}

void plotMaker::getVarPlotType()
{
    std::vector<TString> oneDVars;
    oneDVars.push_back("pt");
    oneDVars.push_back("njets");
    oneDVars.push_back("n_jet_v1");
    oneDVars.push_back("n_jet_v2");
    oneDVars.push_back("n_jet_v3");
    oneDVars.push_back("n_jet_v4");
    oneDVars.push_back("rapidity");
    oneDVars.push_back("cts");    
    oneDVars.push_back("ct1");
    oneDVars.push_back("ct2");
    oneDVars.push_back("phi");
    oneDVars.push_back("phi1");


    std::vector<TString> twoDVars;
    twoDVars.push_back("pt4l_0");


}
