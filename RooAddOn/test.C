void test(){
	using namespace RooFit;
	using namespace RooStats;

	RooRealVar obs("obs","obs", 115, 130);

	obs.Print();
	RooRealVar mean1("mean1","mean1", 126);
	RooRealVar mean2("mean2","mean2",  124);
	RooRealVar sigma1("sigma1","sigma1", 3);
	RooRealVar sigma2("sigma2","sigma2", 2);

	RooRealVar mean3("mean3","mean3", 123);
	RooRealVar mean4("mean4","mean4",  127);
	RooRealVar sigma3("sigma3","sigma3", 1);
	RooRealVar sigma4("sigma4","sigma4", 1);


	RooGaussian g1("g1", "g1", obs, mean1, sigma1);

	g1.Print();
	RooGaussian g2("g2", "g2", obs, mean2, sigma2);

	RooGaussian g3("g3", "g3", obs, mean3, sigma3);
	RooGaussian g4("g4", "g4", obs, mean4, sigma4);

	RooRealVar alpha("alpha", "alpha", 0, -5, 5);
	RooRealVar alpha1("alpha1", "alpha1", 0, -5, 5);
	RooRealVar mean("mean","mean", 125);
	RooRealVar sigma("sigma","sigma", 2.5);
	RooGaussian g("g", "g", obs, mean, sigma);
	vector<double> nref;
	vector<int> nn;
	nn.push_back(2);
	nn.push_back(2);
	nref.push_back(-1);
	nref.push_back(1);
	nref.push_back(-1);
	nref.push_back(1);

	RooStarMomentMorph mm("mm", "mm", RooArgList(alpha, alpha1), RooArgList(obs), RooArgList(g2,g1,g3,g4,g), nn, nref, RooStarMomentMorph::Linear);

	RooPlot *frame = obs.frame();
	alpha.setVal(0);
	mm.plotOn(frame, LineColor(kCyan), LineWidth(8));
	frame->Draw();
	alpha.setVal(-1);
	mm.plotOn(frame, LineColor(kGreen), LineWidth(8));
	frame->Draw();
	alpha.setVal(1);
	mm.plotOn(frame, LineColor(kRed), LineWidth(8));
	frame->Draw();
	g1.plotOn(frame, LineColor(kBlack));
	g2.plotOn(frame, LineColor(kBlue));
	g.plotOn(frame, LineColor(kViolet));
	frame->Draw();
	alpha.setVal(0);
	alpha1.setVal(0);
	mm.plotOn(frame, LineColor(kCyan-3), LineWidth(8));
	frame->Draw();
	alpha1.setVal(-1);
	mm.plotOn(frame, LineColor(kGreen-3), LineWidth(8));
	frame->Draw();
	alpha1.setVal(1);
	mm.plotOn(frame, LineColor(kRed-3), LineWidth(8));
	frame->Draw();
	g3.plotOn(frame, LineColor(kBlack-3));
	g4.plotOn(frame, LineColor(kBlue-3));
	g.plotOn(frame, LineColor(kViolet));
	frame->Draw();

        mm.Print("v");
}
