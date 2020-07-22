/* Class includes */
#include "shapeComp.h"
/* C++ includes*/
#include <cassert>
#include <ctime>

class Options{
  
public:
  std::string file1;
  std::string file2;
  std::string path ;
  std::string variable;
  std::string channel; 
  std::string GetDateTime(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,80,"%d.%m.%Y_%I.%M.%S",timeinfo);
    std::string str(buffer);
    return str;
  }

  void SetDefault(){
    file1    = "XsecInputs_15bin_Powheg.root";
    file2    = "XsecInputs_15bin_Sherpa.root";
    path     = "../varsDistro/"              ;
    variable = ""                            ;
    channel  = "incl"                        ;
  }

  bool checkOpt(char* opt, char* value){
    std::string val = value;
    if( 0==val.find("-") ){
      std::cout << "WARNING:: Option " << opt <<
	" requires value -> skipping " << std::endl;
      return false;
    }
    return true;
  }
  
};


int main( int argc, char* argv[] ) {

  assert(argc>1);
  Options opt;
  opt.SetDefault();
  bool printHelp = false;
  
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--channel")     ){
      if( opt.checkOpt(argv[i],argv[i+1]) )   opt.channel  = argv[i+1]; }
    if( !strcmp(argv[i],"--variable")    ){
      if( opt.checkOpt(argv[i],argv[i+1]) )   opt.variable = argv[i+1]; }
    if( !strcmp(argv[i],"--file1")       ){
      if( opt.checkOpt(argv[i],argv[i+1]) )   opt.file1    = argv[i+1]; }
    if( !strcmp(argv[i],"--file2")       ){
      if( opt.checkOpt(argv[i],argv[i+1]) )   opt.file2    = argv[i+1]; }
    if( !strcmp(argv[i],"--path")        ){
      if( opt.checkOpt(argv[i],argv[i+1]) )   opt.path     = argv[i+1]; }
    if( !strcmp(argv[i],"--help")        ){   printHelp    = true;      } 
  }
  if( printHelp ){
    std::cout << "shapeComp(): compare Powheg/Sherpa qqHZZ shapes!!"                        << std::endl;
    std::cout << "  Usage  :  shapeComp [Options]"                                          << std::endl;
    std::cout << "             --channel   [Define channel to be used: default is 'incl'."  << std::endl;
    std::cout << "                          Options are: '4mu', '4e', '2e2mu', '2mu2e',"    << std::endl;
    std::cout << "             --variable  [Set variable to plot: Needed options]"          << std::endl;
    std::cout << "             --file1     [Define Powheg qqZZ input filename:"             << std::endl;
    std::cout << "                          default is 'XsecInputs_15bin_Powheg.root']"     << std::endl;
    std::cout << "             --file2     [Define Sherpa qqZZ input filename:"             << std::endl;
    std::cout << "                          default is 'XsecInputs_15bin_Sherpa.root']"     << std::endl;
    std::cout << "             --path      [Define path to ROOT files:"                     << std::endl;
    std::cout << "                          default is '../varsDistro/']"                   << std::endl;
    std::cout << "             --help      [Print this help]"                               << std::endl;
    exit(0);
  }

  if(opt.variable==""){
    std::cout << "<shapeComp()>:: variable not set: please provide it. Exiting ... " << std::endl;
    exit(0);
  }

  std::cout << "Calling shapeComp with options: " << std::endl;
  std::cout << "    channel   = " << opt.channel  << std::endl;
  std::cout << "    variable  = " << opt.variable << std::endl;
  std::cout << "    file1     = " << opt.file1    << std::endl;
  std::cout << "    file2     = " << opt.file2	  << std::endl;
  std::cout << "    path      = " << opt.path     << std::endl;

  m_File1 = opt.file1;
  m_File2 = opt.file2;
  m_Path  = opt.path;

  TRint *myApp = new TRint("RootSession",&argc,argv,NULL,0);

  CompShape(opt.variable, opt.channel);

  std::cout<<" Using Rint: Opening ROOT ..." << std::endl;
  myApp->Run();
  
  return 0;
  
}

std::string ConvertToStringWithPrecision(double value, int n){
  
  std::ostringstream out;
  out << std::setprecision(n) << value;
  return out.str();
  
}

void CompShape(std::string var, std::string chan){

  gStyle->SetOptStat(00000);
  
  TFile *_file0 = new TFile( (m_Path+m_File1).c_str() );
  TFile *_file1 = new TFile( (m_Path+m_File2).c_str() );
  
  TH1F *Powheg = (TH1F*)_file0->Get( ("h"+var+"_"+chan+"_qqZZ").c_str() );
  TH1F *Sherpa = (TH1F*)_file1->Get( ("h"+var+"_"+chan+"_qqZZ").c_str() );
  
  Powheg->Scale(36.1);
  Sherpa->Scale(36.1);

  Powheg->SetLineColor(1);
  Powheg->SetLineWidth(2);
  Sherpa->SetLineColor(2);
  Sherpa->SetLineWidth(2);

  double IntPow = 0;
  double IntShe = 0;
  
  for(int i=1; i<Powheg->GetNbinsX()+1; i++){
    IntPow += Powheg->GetBinContent(i)*Powheg->GetBinWidth(i);
    IntShe += Sherpa->GetBinContent(i)*Sherpa->GetBinWidth(i);
  }
  
  TCanvas *c = new TCanvas("PowhegSherpa","PowhegSherpa",600,600);
  c->Draw();
  Powheg->GetYaxis()->SetTitleOffset(1.40);
  if(var=="njet" || var=="nbjet" || var=="m12m34" || var=="m")
    Powheg->GetYaxis()->SetTitle("Events");

  Double_t Ymax = getYmax(Powheg,Sherpa);
  Powheg->GetYaxis()->SetRangeUser(0,Ymax);
  Sherpa->GetYaxis()->SetRangeUser(0,Ymax);
  Powheg->Draw("histE");
  Sherpa->Draw("histEsame");

  TLatex Yiel;
  Yiel.SetNDC();
  Yiel.SetTextFont(42);
  Yiel.SetTextSize(0.033);
  Yiel.SetTextColor(kBlack);
  Yiel.DrawLatex( 0.68, 0.85, ("Powheg : "+ConvertToStringWithPrecision(IntPow,4)).c_str() );
  Yiel.SetTextColor(kRed);
  Yiel.DrawLatex( 0.68, 0.80, ("Sherpa : "+ConvertToStringWithPrecision(IntShe,4)).c_str() );

  c->SaveAs( (m_Path+"shapesComp/"+var+"_"+chan+".pdf").c_str() );
  
}

Double_t getYmax(TH1F *h1, TH1F *h2){

  double m_val = 0;
  double v1 = h1->GetMaximum();
  double v2 = h2->GetMaximum();

  if(v1>v2)
    m_val = v1*1.03;
  else
    m_val = v2*1.03;
  
  return m_val;
  
}
