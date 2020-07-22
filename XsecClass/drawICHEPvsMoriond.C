void drawICHEPvsMoriond(){

  TFile *_file0 = TFile::Open("g.root");

//  std::vector<string> poi = {"_bin0","_bin1","_bin2","_bin3","_bin4","_bin5","_bin6","_bin7","_bin8","_bin9"};
//  std::vector<string> poi = {"_4mu","_4e","_2e2mu","_2mu2e"};
//  std::vector<string> poi = {"_4l"};
//  std::vector<string> poi = {"_2l2l"};
//  std::vector<string> poi = {"_sum"};
  std::vector<string> poi = {""};
  
  cout << poi.size() << endl;
  
  TCanvas s("s","s", 1200,1000);
  if ( poi.size()>1 ) s.Divide( int(poi.size()/2. + 0.5),2) ;
  
  TF1 *sigma1 = new TF1 ("sigma1","1",0,210000);
  TF1 *sigma2 = new TF1 ("sigma2","4",0,210000);
  sigma1->SetLineColor(kRed);
  sigma1->SetLineWidth(1);
  sigma2->SetLineColor(kRed);
  sigma2->SetLineWidth(1);

  for (unsigned int i =0; i <poi.size(); ++i ){
    s.cd(i+1);
    TGraph *t = (TGraph *) _file0->Get(("sigma"+poi.at(i)).c_str() );
    t->SetMaximum(5);
    t->Draw();
    TGraph *tichep = (TGraph *) _file0->Get(("sigma"+poi.at(i)+"ICHEP").c_str() );
    tichep->Draw("same");
    sigma1->Draw("same");
    sigma2->Draw("same");
    
  }
  s.SaveAs("test.eps");
}
