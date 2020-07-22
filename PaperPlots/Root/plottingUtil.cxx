#include "plottingUtil.h"


using namespace std;




void setStyle(std::string sample, TGraphAsymmErrors *h, bool isPoint)
{
    h->SetMarkerSize(0.5);
    gStyle->SetEndErrorSize(0);

	if(sample == "Data")
	{
	    h->SetMarkerSize(0.7);
	    h->SetMarkerStyle(20);
	    h->SetLineWidth(2);
	}
  if(sample == "ZZData")
  {
      int ZZC_light    = TColor::GetColor("#BA0A07");
      int ZZC_dark    = TColor::GetColor("#A30907");
      h->SetMarkerColor(ZZC_dark);
      h->SetLineColor(ZZC_light);
      h->SetMarkerSize(0.7);
      h->SetMarkerStyle(20);
      h->SetLineWidth(2);
      h->SetMarkerStyle(21);
  }
	if(sample=="DataSys")
	{
		h->SetLineColor(kBlack);
		h->SetFillColor(kWhite);
		h->SetFillStyle(0);
		h->SetMarkerSize(0.);
		h->SetLineWidth(1);
	}

	if(sample=="HResFid")
	{
		h->SetFillColor(kGreen-8);
		h->SetLineStyle(1);
		h->SetLineColor(kGreen-8);
		h->SetMarkerColor(kGreen+3);
		h->SetMarkerSize(0.8);
		h->SetMarkerStyle(22);
	}
	if(sample=="NNLOPS_N3LO")
	{
		h->SetFillColor(kRed-10);
		h->SetLineStyle(1);
		h->SetLineColor(kRed-10);
		h->SetMarkerColor(kRed);
		h->SetMarkerSize(0.8);
		h->SetMarkerStyle(21);
	}
	if(sample=="NNLOPS_N2LO")
	{
		h->SetFillColor(kOrange-4);
		h->SetLineStyle(1);
		h->SetLineColor(kOrange-4);
		h->SetMarkerColor(kOrange+2);
		h->SetMarkerSize(1.1);
		h->SetMarkerStyle(34);		
	}
	if(sample=="MG5Fid")
	{
		h->SetFillColor(kBlue-10);
		h->SetLineStyle(1);
		h->SetLineColor(kBlue-10);
		h->SetMarkerColor(kBlue);
		h->SetMarkerSize(1.1);
		h->SetMarkerStyle(33);		
	}
  
	if(sample=="obsratio")
	{
		h->SetLineStyle(1);
		h->SetLineColor(18);
		h->SetFillColor(18);
		h->SetFillStyle(1001);
		h->SetMarkerStyle(33);
		h->SetMarkerColor(kGray);
		h->SetMarkerSize(0.);
	}

    if(sample == "MG5_XH")
    {
        h->SetLineStyle(1);
        h->SetLineColor(kAzure-4);
        h->SetFillColor(kAzure-4);
        h->SetFillStyle(1001);
        h->SetMarkerStyle(33);
        h->SetMarkerColor(kBlue);
        //if(opts["variable"].EqualTo("Njets"))
        //{
        //    h->SetMarkerSize(1);
        //}
    }
    if(sample=="MG5ratio")
    {
        h->SetLineColor(kBlue);
        h->SetLineWidth(1);
        h->SetMarkerStyle(33);
        h->SetMarkerColor(kBlue);
        h->SetFillColor(kAzure-4);
    }
    if(sample=="NNLOPS")
    {
        h->SetLineStyle(3);
        h->SetLineWidth(0);
        h->SetLineColor(kRed+1);
        h->SetMarkerColor(kRed);
        h->SetMarkerStyle(21);
        h->SetFillColor(kRed-10);
        h->SetFillStyle(1001);
    }
    if(sample=="NNLOPS_XH")
    {
        h->SetLineColor(kRed);
        h->SetLineWidth(1);
        h->SetFillStyle(1001);
        h->SetMarkerStyle(21);
        h->SetMarkerColor(kRed);
        h->SetLineColor(kRed-10);
        h->SetFillColor(kRed-10);
    }
    if(sample=="NNLOPSratio")
    {
        h->SetLineColor(kRed);
        h->SetLineWidth(1);
        h->SetMarkerStyle(21);
        h->SetMarkerColor(kRed);
        h->SetLineColor(kRed-10);
        h->SetFillColor(kRed-10);
    }
    if(sample=="HRes_XH" or sample=="NNLL_XH" or sample == "SCETlib_XH" or sample == "STWZ_XH")
    {
        h->SetLineStyle(1);
        h->SetLineColor(kGreen-8);
        h->SetMarkerStyle(22);
        h->SetMarkerColor(kGreen+3);
        h->SetFillColor(kGreen-8);
        h->SetFillStyle(1001);
    }
    if(sample=="JVE_XH" or sample=="RadISH_XH")
    {
        h->SetLineStyle(1);
        h->SetLineColor(kMagenta-8);
        h->SetMarkerStyle(23);
        h->SetMarkerColor(kMagenta+3);
        h->SetFillColor(kMagenta-8);
        h->SetFillStyle(1001);
    }
    if(sample=="HResRatio")
    {
        h->SetLineColor(kGreen+3);
        h->SetLineWidth(1);
        h->SetMarkerStyle(22);
        h->SetMarkerColor(kGreen+3);
        h->SetFillColor(kGreen-8);
    }
    if(sample=="XH")
    {
        h->SetLineStyle(3);
        h->SetLineColor(kBlack);
        h->SetLineWidth(3);
        h->SetFillColor(kBlack);
        h->SetFillStyle(3004);
        h->SetMarkerSize(0.0);        
    }
}
void setStyle(std::string sample, TH1D *h)
{
    if(!h) return;

    if(sample=="NNLOPS")
    {
        h->SetLineColor(kRed+1);
        h->SetLineStyle(3);
        h->SetLineWidth(2);
        h->SetFillColor(kWhite);
    }
    if(sample=="XH")
    {
        h->SetLineStyle(2);
        h->SetLineColor(kBlack);
        h->SetLineWidth(2);
        h->SetMarkerSize(0);
        h->SetFillColor(kBlack);
        h->SetFillStyle(3004);
        gStyle->SetHatchesLineWidth(2);
    }
}


void plotPValue(TString NNLOPSPVal, TString MG5PVal)
{
    TLatex pVal;
    pVal.SetNDC();
    pVal.SetTextFont(42);
    pVal.SetTextSize(0.04);
    pVal.SetTextColor(kBlack);

    Double_t xVal = 0.58;
    Double_t yVal = 0.42;

    pVal.DrawLatex(xVal,yVal,("#font[12]{p}-value NNLOPS = "+ NNLOPSPVal +"%"));
    pVal.DrawLatex(xVal,yVal-0.07,("#font[12]{p}-value MG5 FxFx = "+ MG5PVal +"%"));

}


void setAxisLabels(TH1D *g, TString var, bool ratio, double aspectRatio, bool isZZ)
{

  std::map<TString,std::vector<TString>> name;
  std::map<TString,float> range;  
  
  name["pt"]     = { "#font[12]{p}_{T}^{4#font[12]{l}} [GeV]", "d#sigma/d#font[12]{p}_{T}^{4#font[12]{l}} [fb/GeV]" };
  name["m12"]    = { "#font[12]{m}_{12} [GeV]", "d#sigma/d#font[12]{m}_{12} [fb/GeV]" };
  name["m34"]    = { "#font[12]{m}_{34} [GeV]", "d#sigma/d#font[12]{m}_{34} [fb/GeV]" };
  name["y"]      = { "#left|#font[12]{y}_{4#font[12]{l}}#right|", "d#sigma/d#left|#font[12]{y}_{4#font[12]{l}}#right| [fb]" };
  name["njet"]   = { "#font[12]{N}_{jets}", "#sigma [fb]"};
  name["njetv4"]   = { "#font[12]{N}_{jets}", "#sigma [fb]"};
  name["nbjet"]  = { "#font[12]{N}_{b-jets}", "d#sigma/d#font[12]{N}_{b-jets} [fb]"};
  name["m12m34"] = { "#font[12]{m}_{12} vs #font[12]{m}_{34}" , "#sigma [fb]" };
  name["cts"]    = { "|cos#theta*|", "d#sigma/d(|cos#theta*|) [fb]" };
  name["mjj"]    = { "#font[12]{m}_{jj} [GeV]",  "d#sigma/d#font[12]{m}_{jj} [fb/GeV]" };
  name["etajj"]  = { "#Delta#eta_{jj}", "d#sigma/d(#Delta#eta_{jj}) [fb]" };
  name["phijj"]  = { "#Delta#phi_{jj} [rad]", "d#sigma/d(#Delta#phi_{jj}) [fb/rad]" };
  name["ljpt"]   = { "#font[12]{p}_{T}^{lead. jet} [GeV]","d#sigma/d#font[12]{p}_{T}^{lead. jet} [fb/GeV]" };
  name["pt0j"]   = { "#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=0} [GeV]" , "d#sigma/d#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=0} [fb/GeV]" };
  name["pt1j"]   = { "#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=1} [GeV]", "d#sigma/d#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=1} [fb/GeV]" };
  name["pt2j"]   = { "#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}#geq2} [GeV]", "d#sigma/d#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}#geq2} [fb/GeV]" };

  range["pt"]     = 0.13;
  range["m12"]    = 0.65;
  range["m34"]    = 0.38;
  range["y"]      = 5.50;
  range["njet"]   = 3.50;
  range["njetv4"]   = 3.3;
  range["nbjet"]  = 5.50;
  range["m12m34"] = 2.80;
  range["cts"]    = 11.0;
  range["mjj"]    = 0.0025;
  range["etajj"]  = 0.35;
  range["phijj"]  = 0.35;
  range["ljpt"]   = 0.073;
  range["pt0j"]   = 0.08;
  range["pt1j"]   = 0.027;
  range["pt2j"]   = 0.008;
  
  // g->GetXaxis()->SetTitle(name[var].at(0));
  // g->GetYaxis()->SetTitleFont(42);
  // g->GetYaxis()->SetTitleSize(14);

  // g->GetXaxis()->SetTitleFont(42);
  // g->GetXaxis()->SetTitleSize(14);

  if(ratio)
  {
     double mult = 1/(aspectRatio/0.345);

    /* x axis */
    
    g->GetXaxis()->SetLabelSize(mult*g->GetXaxis()->GetLabelSize());
    
    /* y axis */
    // g->GetYaxis()->SetTitleSize(0.17);
    // g->GetYaxis()->SetTitleOffset(0.45);

    // g->GetYaxis()->SetTitleFont(63);
    // g->GetYaxis()->SetTitleSize(14);

    g->GetYaxis()->SetTitle("Theory/Data");

    g->GetYaxis()->SetRangeUser(0.0001, 2.4);
    g->GetYaxis()->SetLabelSize(mult*0.095);

    g->GetYaxis()->SetNdivisions(8);
    g->GetYaxis()->CenterTitle(kTRUE);

    if(!isZZ) g->GetXaxis()->SetTitle(name[var].at(0));
    if(isZZ)
    {
      g->GetYaxis()->SetTitle("N/N_{MC}");
      g->GetYaxis()->SetNdivisions(4);
      g->GetYaxis()->SetRangeUser(0.4, 1.8);

      // g->GetYaxis()->SetTitleSize(0.14);
      // g->GetYaxis()->SetTitleOffset(0.5);

      // g->GetXaxis()->SetTitleSize(0.18);
      // g->GetXaxis()->SetTitleOffset(1.3);
      g->GetXaxis()->SetTitle(name[var].at(0));

    }


  }
  else
  {

    // g->GetYaxis()->SetTitleFont(42);
    // g->GetYaxis()->SetTitleSize(14);

    // g->GetXaxis()->SetTitleFont(42);
    // g->GetXaxis()->SetTitleSize(14);

    double mult = 1/(aspectRatio/(0.8-0.345));

    // g->GetYaxis()->SetTitleSize(0.065);
    g->GetYaxis()->SetLabelSize(0.05*mult);

    // g->GetYaxis()->SetTitleOffset(1.20);
    g->GetYaxis()->SetTitle(name[var].at(1));
    g->GetYaxis()->SetRangeUser(0.,range[var]);
  }
    int sizeText = 19;
    int fontStyle = 43;
    
    g->GetYaxis()->SetTitleSize(sizeText);
    g->GetYaxis()->SetTitleFont(fontStyle);

    g->GetXaxis()->SetTitleFont(fontStyle);
    g->GetXaxis()->SetTitleSize(sizeText);

    g->GetYaxis()->SetTitleOffset(2);
    g->GetXaxis()->SetTitleOffset(8);

    g->GetYaxis()->SetLabelSize(sizeText);
    g->GetYaxis()->SetLabelFont(fontStyle);

    g->GetXaxis()->SetLabelSize(sizeText);
    g->GetXaxis()->SetLabelFont(fontStyle);


  
}


void setupFidFrame(TH1D* hist)
{
    // dummy->Reset();
    hist->SetLineColor(0);
    // dummy->GetXaxis()->SetRangeUser( dummy->GetXaxis()->GetXmin(),dummy->GetXaxis()->GetXmax() );
    hist->GetYaxis()->SetRangeUser(0.0001, 7.5);
    hist->GetXaxis()->SetBinLabel( 1 , "#scale[0.6]{#sigma_{4#mu}^{fid}}"          );
    hist->GetXaxis()->SetBinLabel( 2 , "#scale[0.6]{#sigma_{4e}^{fid}}"            );
    hist->GetXaxis()->SetBinLabel( 3 , "#scale[0.6]{#sigma_{2#mu2e}^{fid}}"        );
    hist->GetXaxis()->SetBinLabel( 4 , "#scale[0.6]{#sigma_{2e2#mu}^{fid}}"        );
    hist->GetXaxis()->SetBinLabel( 5 , " "                                   );
    hist->GetXaxis()->SetBinLabel( 6 , " "                                   );
    hist->GetXaxis()->SetBinLabel( 7 , "#scale[0.6]{#sigma_{4#mu+4e}^{fid}}"       );
    hist->GetXaxis()->SetBinLabel( 8 , "#scale[0.6]{#sigma_{2#mu2e+2e2#mu}^{fid}}" );
    hist->GetXaxis()->SetBinLabel( 9, "#scale[0.6]{#sigma_{4#font[12]{l} (sum)}^{fid}}"           );
    hist->GetXaxis()->SetBinLabel( 10, "#scale[0.6]{#sigma_{4#font[12]{l} (comb)}^{fid}}"          );
    hist->GetXaxis()->SetBinLabel( 11, " "                                  				       );
    hist->GetXaxis()->SetBinLabel( 12, " "                                 						   );
    hist->GetXaxis()->SetBinLabel( 13, " "         												   );
    hist->GetXaxis()->SetBinLabel( 14, " "                                   );
    hist->GetXaxis()->SetBinLabel( 15, "#scale[0.6]{#sigma_{H}}"                                   );
    hist->GetXaxis()->SetBinLabel( 16, " "                                   );
    hist->GetXaxis()->SetBinLabel( 17, " "                                   );

    hist->GetYaxis()->SetTitleOffset(1.4);
    hist->GetXaxis()->SetLabelSize(0.07);
    hist->GetXaxis()->SetLabelOffset(0.013);
    hist->GetXaxis()->SetTickLength(0.);
    hist->GetYaxis()->CenterTitle(kTRUE);
    hist->GetYaxis()->SetNdivisions(000);

}

TGaxis* getAxis(TString position)
{
	TGaxis* axis = NULL;
	if(position.Contains("left"))
	{
	 	axis = new TGaxis(0, 0, 0, 4.8, 0, 1.92, 510,"");
	 	axis->SetName("leftAx");
	 	axis->SetTitle("Cross section [fb]");
	}
	else if(position.Contains("center"))
	{	
		axis = new TGaxis(5.8, 0, 5.8, 4.8, 0, 4.8, 510,"");
		axis->SetName("CenterAx");
		axis->SetTitle("[fb]");

	}
	else if(position.Contains("right")) 
	{
		axis = new TGaxis(11.6, 0, 11.6, 4.8, 0, 95, 510,"");
		axis->SetName("RightAx");
		axis->SetTitle("[pb]");
	}
	axis->SetLabelSize(0.028);
	axis->SetLabelFont(42);
	axis->SetTitleSize(0.035);
	axis->SetTitleOffset(1.1);
	axis->SetTitleFont(42);
	axis->ChangeLabel(1,-1,-1,-1,-1,-1," ");

	return axis;

}


void AdjustXaxis(TH1D* h, TString var)
{

  Double_t Xmin = h->GetXaxis()->GetXmin();
  Double_t Xmax = h->GetXaxis()->GetXmax();
  
  if(var.EqualTo("pt"))
  {
    // Xmax=11;
    h->GetXaxis()->SetNdivisions(0015);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"10");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"20");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"30");
    h->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"45");
    h->GetXaxis()->ChangeLabel(6,-1,-1,-1,-1,-1,"60");
    h->GetXaxis()->ChangeLabel(7,-1,-1,-1,-1,-1,"80");
    h->GetXaxis()->ChangeLabel(8,-1,-1,-1,-1,-1,"120");
    h->GetXaxis()->ChangeLabel(9,-1,-1,-1,-1,-1,"200");
    h->GetXaxis()->ChangeLabel(10,-1,-1,-1,-1,-1,"350");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"1000");

    // {0.0, 10.0,  20.0,   30.0,   45.0, 60.0, 80.0, 120.0,  200.0,  350.0, 1000.0};
    h->GetXaxis()->SetLabelOffset(0.02);
    h->GetXaxis()->SetLabelSize(0.09);
  }
  else if(var.EqualTo("njet"))
  {
    h->GetXaxis()->SetBinLabel(1,"0");
    h->GetXaxis()->SetBinLabel(2,"1");
    h->GetXaxis()->SetBinLabel(3,"2");
    h->GetXaxis()->SetBinLabel(4,"#geq3");
    // h->GetXaxis()->SetBinLabel(5,"#geq4");
    h->GetXaxis()->SetLabelSize(0.14);
    h->GetXaxis()->SetLabelOffset(0.02);
  }
  else if(var.EqualTo("m12m34"))
  {
    h->GetXaxis()->SetBinLabel(1,"bin 0");
    h->GetXaxis()->SetBinLabel(2,"bin 1");
    h->GetXaxis()->SetBinLabel(3,"bin 2");
    h->GetXaxis()->SetBinLabel(4,"bin 3");
    h->GetXaxis()->SetBinLabel(5,"bin 4");
    h->GetXaxis()->SetLabelSize(0.14);
    h->GetXaxis()->SetLabelOffset(0.02);
  }
  else if(var.EqualTo("nbjet"))
  {
    h->GetXaxis()->SetBinLabel(1,"0");
    h->GetXaxis()->SetBinLabel(2,"#geq1");
    h->GetXaxis()->SetLabelSize(0.14);
    h->GetXaxis()->SetLabelOffset(0.02);
  }
  else if(var.EqualTo("mjj"))
  {
    h->GetXaxis()->SetNdivisions(504);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"120");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1," ");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1," ");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"3000");
    h->GetXaxis()->SetLabelSize(0.09);
    h->GetXaxis()->SetTickSize(0);
  }
  else if(var.EqualTo("pt0j"))
  {
    Xmax=4;
    h->GetXaxis()->SetNdivisions(0005);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"15");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"30");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"120");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"350");
    h->GetXaxis()->SetLabelSize(0.09);
  }
  else if(var.EqualTo("pt1j"))
  {
    Xmax=5;
    h->GetXaxis()->SetNdivisions(0006);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"30");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"60");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"80");
    h->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"120");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"350");
    h->GetXaxis()->SetLabelSize(0.09);
  }
  else if(var.EqualTo("pt2j"))
  {
    Xmax=2;
    h->GetXaxis()->SetNdivisions(0002);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"120");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"350");
    h->GetXaxis()->SetLabelSize(0.09);
  }
  else if(var.EqualTo("ljpt"))
  {
    Xmax=5;
    h->GetXaxis()->SetNdivisions(0006);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"30");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"40");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"55");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"75");
    h->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"120");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"350");
    h->GetXaxis()->SetLabelSize(0.09);
  }
  else if(var.EqualTo("njetv4"))
  {
    h->GetXaxis()->SetBinLabel( 1 , "0"     );
    h->GetXaxis()->SetBinLabel( 2 , "1"     );
    h->GetXaxis()->SetBinLabel( 3 , "2"     );
    h->GetXaxis()->SetBinLabel( 4 , "#geq1" );
    h->GetXaxis()->SetBinLabel( 5 , "#geq2" );
    h->GetXaxis()->SetBinLabel( 6 , "#geq3" );
    h->GetXaxis()->SetTitle("#font[12]{N}_{jets}");
    h->GetXaxis()->SetLabelSize(0.14);
    h->GetXaxis()->SetLabelOffset(0.02);
    
  }
  else
  {
    h->GetXaxis()->SetLabelOffset(0.02);
    h->GetXaxis()->SetLabelSize(0.09);
  }
  h->GetXaxis()->SetRangeUser(Xmin,Xmax);
  
}

std::pair<double,double> GetBarSize(TString var)
{
  std::pair<double,double> m_val;
  if( var.EqualTo("m12m34") || 
  	  var.EqualTo("pt0j")  || 
  	  var.EqualTo("pt1j") || 
  	  var.EqualTo("mjj") ||
      var.EqualTo("ljpt")   || 
      var.EqualTo("njet")  || 
      var.EqualTo("pt")   || 
      var.EqualTo("njetv4") )

    m_val = std::make_pair(0.08,0.08); //1.00
	if(var.Contains("fid")) m_val= std::make_pair(0.2,0.2);
  // else if(var=="nbjet" || var=="pt2j")
  //   m_val = std::make_pair(0.025,0.025); //1.00
  // else if(var=="y")
  //   m_val = std::make_pair(0.01,0.01); //0.3
  // else if(var=="cts")
  //   m_val = std::make_pair(0.006,0.006); //0.125;
  // else if(var=="m12")
  //   m_val = std::make_pair(0.5,0.4); //6.00;
  // else if(var=="m34")
  //   m_val = std::make_pair(0.3,0.2); //4.00;
  // else if(var=="etajj")
  //   m_val = std::make_pair(0.1,0.1); //2.00;
  // else if(var=="phijj")
  //   m_val = std::make_pair(0.07,0.07); //3.14

  return m_val;
}

TLegend* CreateLegend(std::string var, bool isFid)
{
  TLegend *leg = NULL;
  if(var=="pt" || var=="y")
    leg = new TLegend(0.50,0.58,0.92,0.92);
  else if (var=="njetv4" )
    leg = new TLegend(0.50,0.67,0.92,0.92);
  else{
    if(isFid)
      leg = new TLegend(0.48,0.71,0.89,0.93);
    else
      leg = new TLegend(0.48,0.50,0.89,0.90);
  }
  
  leg->ConvertNDCtoPad();
  leg->SetTextFont(42);
  if(isFid) leg->SetTextSize(0.030);
  else leg->SetTextSize(0.040);
  leg->SetFillStyle(0);
  leg->SetShadowColor(0);
  leg->SetLineColor(0);
  leg->SetBorderSize(0);
  return leg;
  
}


double GetBarSpacing(TString var)
{
	double m_val = 0.2;
	

  
  // if( var=="m12m34" || var=="pt0j"  || var=="pt1j" || var=="pt2j" ||
  //     var=="mjj"    || var=="ljpt"  || var=="njet" || var=="pt"   ||
  //     var=="njetv4" )
  // else if(var=="nbjet" )
  //   m_val = 0.10;
  // else if(var=="y")
  //   m_val = 0.05;
  // else if(var=="cts")
  //   m_val = 0.02;
  // else if(var=="m12")
  //   m_val = 1.20;
  // else if(var=="m34")
  //   m_val = 0.90;
  // else if(var=="etajj")
  //   m_val = 0.40;
  // else if(var=="phijj")
  //   m_val = 0.30;

  return m_val;
  
}

void drawLabels(bool isFiducial, TString unFoldType)
{

  Double_t Xval = 0.18;
  Double_t Txt  = 0.04;
  std::string Pub = "     Internal";

  // if(m_Conf)      {       Pub = "Preliminary"; }
  // else if(m_Paper){ Pub = "";            }
    
  if(!isFiducial){
    Xval = 0.18; Txt = 0.05;
  }
  double moveDown = 0.04;
  if(isFiducial) moveDown = 0;

  TLatex AT;
  AT.SetNDC();
  AT.SetTextFont(72);
  AT.SetTextSize(0.04);
  AT.SetTextColor(kBlack);
  if(!isFiducial)
    AT.SetTextSize(Txt + 0.01);
  AT.DrawLatex(Xval, 0.88 - moveDown,"ATLAS" );
    
  TLatex Lab;
  Lab.SetNDC();
  Lab.SetTextFont(42);
  if(!isFiducial)
    Lab.SetTextSize(Txt);
  Lab.SetTextColor(kBlack);
  // if(isFiducial)
  // //   Lab.DrawLatex( Xval+0.13,0.88, Pub.c_str() );
  // else
    Lab.DrawLatex( Xval+0.10,0.88 - moveDown, Pub.c_str() );
  
  TLatex lumi;
  lumi.SetNDC();
  lumi.SetTextFont(42);
  lumi.SetTextSize(Txt );
  lumi.SetTextColor(kBlack);
  lumi.DrawLatex( Xval,0.76 -moveDown ,/*"#sqrt{s} =*/ "13 TeV, 139 fb^{-1}" );
  
  if(!isFiducial)
  {
	  TLatex unFoldingLabel;
	  unFoldingLabel.SetNDC();
	  unFoldingLabel.SetTextFont(42);
	  unFoldingLabel.SetTextSize(Txt - 0.01);
	  unFoldingLabel.SetTextColor(kBlack);
    if(unFoldType.Contains("matrix"))unFoldingLabel.DrawLatex( Xval,0.70 -moveDown,"Matrix Unfolding" );
    else unFoldingLabel.DrawLatex( Xval,0.70 - moveDown,"Bin-by-Bin Unfolding" );

  }

  TLatex Chan;
  Chan.SetNDC();
  Chan.SetTextFont(42);
  Chan.SetTextSize(Txt);
  Chan.SetTextColor(kBlack);
  Chan.DrawLatex( Xval,0.82 - moveDown,"H #rightarrow ZZ* #rightarrow 4#font[12]{l}" );
  
}

void drawLimit()
{
  TLatex upLim;
  upLim.SetNDC();
  upLim.SetTextFont(42);
  upLim.SetTextSize(0.03);
  upLim.SetTextColor(kBlack);
  upLim.SetTextAngle(90);
  upLim.DrawLatex(0.91,0.05,"#sigma < 36 ab 95% CL_{s}" );

}

void SetAtlasStyle()
{

  TStyle *atlasStyle= new TStyle("ATLAS","Atlas style");
  
  /*use plain black on white colors*/
  Int_t icol=0; // WHITE
  atlasStyle->SetFrameBorderMode(icol);
  atlasStyle->SetFrameFillColor(icol);
  atlasStyle->SetCanvasBorderMode(icol);
  atlasStyle->SetCanvasColor(icol);
  atlasStyle->SetPadBorderMode(icol);
  atlasStyle->SetPadColor(icol);
  atlasStyle->SetStatColor(icol);
  /*don't use: white fill color for *all* objects*/
  //atlasStyle->SetFillColor(icol); 

  /*set the paper & margin sizes*/
  atlasStyle->SetPaperSize(20,26);

  /*set margin sizes*/
  atlasStyle->SetPadTopMargin(0.05);
  atlasStyle->SetPadRightMargin(0.05);
  atlasStyle->SetPadBottomMargin(0.16); //ATLAS style 0.16
  atlasStyle->SetPadLeftMargin(0.14);

  /*set title offsets (for axis label)*/
  atlasStyle->SetTitleXOffset(1.4);
  atlasStyle->SetTitleYOffset(1.4);

  /*use large fonts*/
  //Int_t font=72; // Helvetica italics
  Int_t font=42; // Helvetica
  Double_t tsize=0.04; //io=0.04
  atlasStyle->SetTextFont(font);

  atlasStyle->SetTextSize(tsize);
  atlasStyle->SetLabelFont(font,"x");
  atlasStyle->SetTitleFont(font,"x");
  atlasStyle->SetLabelFont(font,"y");
  atlasStyle->SetTitleFont(font,"y");
  atlasStyle->SetLabelFont(font,"z");
  atlasStyle->SetTitleFont(font,"z");

  atlasStyle->SetLabelSize(tsize,"x");
  atlasStyle->SetTitleSize(tsize,"x");
  atlasStyle->SetLabelSize(tsize,"y");
  atlasStyle->SetTitleSize(tsize,"y");
  atlasStyle->SetLabelSize(tsize,"z");
  atlasStyle->SetTitleSize(tsize,"z");

  /*use bold lines and markers*/
  atlasStyle->SetMarkerStyle(20);
  atlasStyle->SetMarkerSize(1.2);
  atlasStyle->SetHistLineWidth(1.);
  atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  /*get rid of X error bars*/
  //atlasStyle->SetErrorX(0.001);
  /*get rid of error bar caps*/
  atlasStyle->SetEndErrorSize(0.00001);

  /*do not display any of the standard histogram decorations*/
  atlasStyle->SetOptTitle(0);
  //atlasStyle->SetOptStat(1111);
  atlasStyle->SetOptStat(0);
  //atlasStyle->SetOptFit(1111);
  atlasStyle->SetOptFit(0);

  /*put tick marks on top and RHS of plots*/
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(1);

  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();

}

TLine* MakeHorLine(TH1D* h)
{

  Double_t Xmin = h->GetXaxis()->GetXmin();
  Double_t Xmax = h->GetXaxis()->GetXmax();

  TLine *line = new TLine(Xmin,1,Xmax,1);
  line->SetLineStyle(2);
  
  return line;
  
}

// TGraphAsymmErrors* plotMaker::getTotalUncertainty(tgraphGroup dataGroup, TH1D* frame)
// {
//     TGraphAsymmErrors* totalUncertainty = new TGraphAsymmErrors();

//     for (unsigned int i = 0 ; i < frame->GetNbinsX(); ++i)
//     {
//         double x; 
//         double y;
//         double obsSysUp     = 0;
//         double obsSysDown   = 0;

//         dataGroup.dataGraph->GetPoint(i, x, y);

//         // wont error out if you are missing the sys only scan
//         if(dataGroup.dataSysGraph != NULL)
//         {
//             obsSysUp     = dataGroup.dataSysGraph->GetErrorYhigh(i);
//             obsSysDown   = dataGroup.dataSysGraph->GetErrorYlow(i);
//         }

//         double obsStatUp    = sqrt(pow(dataGroup.dataGraph->GetErrorYhigh(i),2) - pow(obsSysUp,2));
//         double obsStatDown  = sqrt(pow(dataGroup.dataGraph->GetErrorYlow(i),2)  - pow(obsSysDown,2));

//         totalUncertainty->SetPoint(i, x, y);
//         totalUncertainty->SetPointError(i, GetBarSize(m_opts["variable"]).second, GetBarSize(m_opts["variable"]).second, ,);        
   
//     }
// }


