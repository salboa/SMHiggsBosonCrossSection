#include "TFile.h"
#include "TH1.h"
#include "iostream"

void PrintYields(double Lumi){

  TFile *f = new TFile( "../varsDistro/XsecInputs_15bin.root" );
  TH1F *hm4mu_AllSig   = (TH1F*)f->Get( "hm_4mu_AllSig"   );
  TH1F *hm4e_AllSig    = (TH1F*)f->Get( "hm_4e_AllSig"    );
  TH1F *hm2mu2e_AllSig = (TH1F*)f->Get( "hm_2mu2e_AllSig" ); 
  TH1F *hm2e2mu_AllSig = (TH1F*)f->Get( "hm_2e2mu_AllSig" );
  TH1F *hm4l_AllSig    = (TH1F*)f->Get( "hm_incl_AllSig"    );
	               			               
  TH1F *hm4mu_qqZZ     = (TH1F*)f->Get( "hm_4mu_qqZZ"     );
  TH1F *hm4e_qqZZ      = (TH1F*)f->Get( "hm_4e_qqZZ"      );
  TH1F *hm2mu2e_qqZZ   = (TH1F*)f->Get( "hm_2mu2e_qqZZ"   );
  TH1F *hm2e2mu_qqZZ   = (TH1F*)f->Get( "hm_2e2mu_qqZZ"   );
  TH1F *hm4l_qqZZ      = (TH1F*)f->Get( "hm_incl_qqZZ"      );
		       				       
  TH1F *hm4mu_ggZZ     = (TH1F*)f->Get( "hm_4mu_ggZZ"     );
  TH1F *hm4e_ggZZ      = (TH1F*)f->Get( "hm_4e_ggZZ"      );
  TH1F *hm2mu2e_ggZZ   = (TH1F*)f->Get( "hm_2mu2e_ggZZ"   );
  TH1F *hm2e2mu_ggZZ   = (TH1F*)f->Get( "hm_2e2mu_ggZZ"   );
  TH1F *hm4l_ggZZ      = (TH1F*)f->Get( "hm_incl_ggZZ"      );

/*		       				       
  TH1F *hm4mu_Zjets    = (TH1F*)f->Get( "hm_4mu_Zjets"    ); 
  TH1F *hm4e_Zjets     = (TH1F*)f->Get( "hm_4e_Zjets"     );
  TH1F *hm2mu2e_Zjets  = (TH1F*)f->Get( "hm_2mu2e_Zjets"  );  
  TH1F *hm2e2mu_Zjets  = (TH1F*)f->Get( "hm_2e2mu_Zjets"  );
  TH1F *hm4l_Zjets     = (TH1F*)f->Get( "hm_incl_Zjets"     );

  TH1F *hm4mu_data    = (TH1F*)f->Get( "hm_4mu_data"    ); 
  TH1F *hm4e_data     = (TH1F*)f->Get( "hm_4e_data"     );
  TH1F *hm2mu2e_data  = (TH1F*)f->Get( "hm_2mu2e_data"  );  
  TH1F *hm2e2mu_data  = (TH1F*)f->Get( "hm_2e2mu_data"  );
  TH1F *hm4l_data     = (TH1F*)f->Get( "hm_incl_data"     );
 */ 

  std::cout<<" Yields per fb-1 "<<std::endl;
  std::cout<<"     Sig 4mu   : " <<hm4mu_AllSig  ->Integral()<<std::endl; 
  std::cout<<"     Sig 4e    : " <<hm4e_AllSig   ->Integral()<<std::endl;
  std::cout<<"     Sig 2mu2e : " <<hm2mu2e_AllSig->Integral()<<std::endl;  
  std::cout<<"     Sig 2e2mu : " <<hm2e2mu_AllSig->Integral()<<std::endl;
  std::cout<<"     Sig 4l    : " <<hm4l_AllSig   ->Integral()<<std::endl;
  std::cout<<""<<std::endl;  
  std::cout<<"     qqZZ 4mu   : " <<hm4mu_qqZZ  ->Integral()<<std::endl; 
  std::cout<<"     qqZZ 4e    : " <<hm4e_qqZZ   ->Integral()<<std::endl;
  std::cout<<"     qqZZ 2mu2e : " <<hm2mu2e_qqZZ->Integral()<<std::endl;  
  std::cout<<"     qqZZ 2e2mu : " <<hm2e2mu_qqZZ->Integral()<<std::endl;
  std::cout<<"     qqZZ 4l    : " <<hm4l_qqZZ   ->Integral()<<std::endl;
  std::cout<<""<<std::endl;
  std::cout<<"     ggZZ 4mu   : " <<hm4mu_ggZZ  ->Integral()<<std::endl; 
  std::cout<<"     ggZZ 4e    : " <<hm4e_ggZZ   ->Integral()<<std::endl;
  std::cout<<"     ggZZ 2mu2e : " <<hm2mu2e_ggZZ->Integral()<<std::endl;  
  std::cout<<"     ggZZ 2e2mu : " <<hm2e2mu_ggZZ->Integral()<<std::endl;
  std::cout<<"     ggZZ 4l    : " <<hm4l_ggZZ   ->Integral()<<std::endl;
  std::cout<<""<<std::endl;
/*  std::cout<<"     Zjets 4mu   : " <<hm4mu_Zjets  ->Integral()<<std::endl; 
  std::cout<<"     Zjets 4e    : " <<hm4e_Zjets   ->Integral()<<std::endl;
  std::cout<<"     Zjets 2mu2e : " <<hm2mu2e_Zjets->Integral()<<std::endl;  
  std::cout<<"     Zjets 2e2mu : " <<hm2e2mu_Zjets->Integral()<<std::endl;
  std::cout<<"     Zjets 4l    : " <<hm4l_Zjets   ->Integral()<<std::endl;
  std::cout<<""<<std::endl;
*/
  std::cout<<" Yields per "<<Lumi<<" fb-1 "<<std::endl;
  std::cout<<"     Sig 4mu   : " <<hm4mu_AllSig  ->Integral()*Lumi<<std::endl; 
  std::cout<<"     Sig 4e    : " <<hm4e_AllSig   ->Integral()*Lumi<<std::endl;
  std::cout<<"     Sig 2mu2e : " <<hm2mu2e_AllSig->Integral()*Lumi<<std::endl;  
  std::cout<<"     Sig 2e2mu : " <<hm2e2mu_AllSig->Integral()*Lumi<<std::endl;
  std::cout<<"     Sig 4l    : " <<hm4l_AllSig   ->Integral()*Lumi<<std::endl;
  std::cout<<""<<std::endl;  
  std::cout<<"     qqZZ 4mu   : " <<hm4mu_qqZZ  ->Integral()*Lumi<<std::endl; 
  std::cout<<"     qqZZ 4e    : " <<hm4e_qqZZ   ->Integral()*Lumi<<std::endl;
  std::cout<<"     qqZZ 2mu2e : " <<hm2mu2e_qqZZ->Integral()*Lumi<<std::endl;  
  std::cout<<"     qqZZ 2e2mu : " <<hm2e2mu_qqZZ->Integral()*Lumi<<std::endl;
  std::cout<<"     qqZZ 4l    : " <<hm4l_qqZZ   ->Integral()*Lumi<<std::endl;
  std::cout<<""<<std::endl;
  std::cout<<"     ggZZ 4mu   : " <<hm4mu_ggZZ  ->Integral()*Lumi<<std::endl; 
  std::cout<<"     ggZZ 4e    : " <<hm4e_ggZZ   ->Integral()*Lumi<<std::endl;
  std::cout<<"     ggZZ 2mu2e : " <<hm2mu2e_ggZZ->Integral()*Lumi<<std::endl;  
  std::cout<<"     ggZZ 2e2mu : " <<hm2e2mu_ggZZ->Integral()*Lumi<<std::endl;
  std::cout<<"     ggZZ 4l    : " <<hm4l_ggZZ   ->Integral()*Lumi<<std::endl;
  std::cout<<""<<std::endl;
/*
  std::cout<<"     Zjets 4mu   : " <<hm4mu_Zjets  ->Integral()*Lumi<<std::endl;
  std::cout<<"     Zjets 4e    : " <<hm4e_Zjets   ->Integral()*Lumi<<std::endl;
  std::cout<<"     Zjets 2mu2e : " <<hm2mu2e_Zjets->Integral()*Lumi<<std::endl;
  std::cout<<"     Zjets 2e2mu : " <<hm2e2mu_Zjets->Integral()*Lumi<<std::endl;
  std::cout<<"     Zjets 4l    : " <<hm4l_Zjets   ->Integral()*Lumi<<std::endl;
  std::cout<<""<<std::endl;
  std::cout<<"     Data 4mu   : " <<hm4mu_data  ->Integral()<<std::endl;
  std::cout<<"     Data 4e    : " <<hm4e_data   ->Integral()<<std::endl;
  std::cout<<"     Data 2mu2e : " <<hm2mu2e_data->Integral()<<std::endl;
  std::cout<<"     Data 2e2mu : " <<hm2e2mu_data->Integral()<<std::endl;
  std::cout<<"     Data 4l    : " <<hm4l_data   ->Integral()<<std::endl;
*/
}
