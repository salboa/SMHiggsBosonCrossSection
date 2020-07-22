TF1 *constraint1, *constraint2, *constrainth;
TLine *constraint3, *constraint4, *constraint5, *constraintv1, *constraintv2;
TLine *constrainth1, *constrainth3;


void plotcut();
void binm12m34(string);
void doloop();

void binm12m34(string chan = "incl"){
  
  TFile *_file0 = TFile::Open("../varsDistro/XsecInputs_15bin.root");
  cout << "channel processed: " << chan << endl;
  
  TH2F *hbin1Z1Z2mtx_chan_AllSig = (TH2F*) _file0->Get(("hbin1Z1Z2mtx_"+chan+"_AllSig").c_str());
  TH2F *hbin2Z1Z2mtx_chan_AllSig = (TH2F*) _file0->Get(("hbin2Z1Z2mtx_"+chan+"_AllSig").c_str());
  TH2F *hbin3Z1Z2mtx_chan_AllSig = (TH2F*) _file0->Get(("hbin3Z1Z2mtx_"+chan+"_AllSig").c_str());
  TH2F *hbin4Z1Z2mtx_chan_AllSig = (TH2F*) _file0->Get(("hbin4Z1Z2mtx_"+chan+"_AllSig").c_str());
  TH2F *hbin5Z1Z2mtx_chan_AllSig = (TH2F*) _file0->Get(("hbin5Z1Z2mtx_"+chan+"_AllSig").c_str());

  
  constraint1= new TF1("constraint1", "130-x", 65 , 106);
  constraint2= new TF1("constraint2", "x", 50 , 65);
  
  constraint3 = new TLine (50, 12, 50, 50);
  constraint4 = new TLine (50, 12, 106, 12);
  constraint5 = new TLine (106, 12, 106, 24);
  constraintv1 = new TLine (74, 32, 74, 56);
  constraintv2 = new TLine (82, 12, 82, 32);
  
  constrainth1 = new TLine (82, 24, 106, 24);
  
  constrainth= new TF1("constrainth", "32", 50 , 98);
  
  TCanvas c("c","c",800,800);
  
  hbin1Z1Z2mtx_chan_AllSig->GetZaxis()->SetRangeUser(0.00000001, 0.001); hbin1Z1Z2mtx_chan_AllSig->Draw("COLZ"); plotcut(); c.SaveAs(("../varsDistro/plots/responsem12m34_bin1_"+chan+".eps").c_str());
  hbin2Z1Z2mtx_chan_AllSig->GetZaxis()->SetRangeUser(0.00000001, 0.001); hbin2Z1Z2mtx_chan_AllSig->Draw("COLZ"); plotcut(); c.SaveAs(("../varsDistro/plots/responsem12m34_bin2_"+chan+".eps").c_str());
  hbin3Z1Z2mtx_chan_AllSig->GetZaxis()->SetRangeUser(0.00000001, 0.001); hbin3Z1Z2mtx_chan_AllSig->Draw("COLZ"); plotcut(); c.SaveAs(("../varsDistro/plots/responsem12m34_bin3_"+chan+".eps").c_str());
  hbin4Z1Z2mtx_chan_AllSig->GetZaxis()->SetRangeUser(0.00000001, 0.001); hbin4Z1Z2mtx_chan_AllSig->Draw("COLZ"); plotcut(); c.SaveAs(("../varsDistro/plots/responsem12m34_bin4_"+chan+".eps").c_str());
  hbin5Z1Z2mtx_chan_AllSig->GetZaxis()->SetRangeUser(0.00000001, 0.001); hbin5Z1Z2mtx_chan_AllSig->Draw("COLZ"); plotcut(); c.SaveAs(("../varsDistro/plots/responsem12m34_bin5_"+chan+".eps").c_str());

  
  
}

void plotcut(){
  constraint1->SetLineColor(kRed); constraint1->SetLineWidth(7);
  constraint2->SetLineColor(kRed); constraint2->SetLineWidth(7);
  constraint3->SetLineColor(kRed); constraint3->SetLineWidth(7);
  constraint4->SetLineColor(kRed); constraint4->SetLineWidth(7);
  constraint5->SetLineColor(kRed); constraint5->SetLineWidth(7);
  constraintv1->SetLineColor(kRed); constraintv1->SetLineWidth(3);
  constraintv2->SetLineColor(kRed); constraintv2->SetLineWidth(3);
  constrainth1->SetLineColor(kRed); constrainth1->SetLineWidth(3);
  constrainth->SetLineColor(kRed); constrainth->SetLineWidth(3);
  constraint1->Draw("same");
  constraint2->Draw("same");
  constraint3->Draw("same");
  constraint4->Draw("same");
  constraint5->Draw("same");
  constrainth->Draw("same");
  constraintv1->Draw("same");
  constraintv2->Draw("same");
  constrainth1->Draw("same");
}

void doloop(){
  binm12m34("incl");
  binm12m34("4mu");
  //binm12m34("4e");
  binm12m34("2e2mu");
  //binm12m34("2mu2e");
}
