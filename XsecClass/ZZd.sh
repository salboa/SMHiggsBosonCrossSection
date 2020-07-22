rm ../ws_output/*



./WorkSpaceMaker --Variable m34 --doFit --WithData --DataSet ZZd_data_expSignal15
hadd ../ws_output/expSignal15.root  ../ws_output/scan_m34__sigma_bin*data.root
mv ../ws_output/fit_m34_data_unfolded.eps ../ws_output/fit_m34_data_unfoldedSignal15.eps

./WorkSpaceMaker --Variable m34 --doFit --WithData --DataSet ZZd_data_expSignal20
hadd ../ws_output/expSignal20.root  ../ws_output/scan_m34__sigma_bin*data.root
mv ../ws_output/fit_m34_data_unfolded.eps ../ws_output/fit_m34_data_unfoldedSignal20.eps

./WorkSpaceMaker --Variable m34 --doFit --WithData --DataSet ZZd_data_expSignal25
hadd ../ws_output/expSignal25.root  ../ws_output/scan_m34__sigma_bin*data.root
mv ../ws_output/fit_m34_data_unfolded.eps ../ws_output/fit_m34_data_unfoldedSignal25.eps

./WorkSpaceMaker --Variable m34 --doFit --WithData --DataSet ZZd_data_expSignal30
hadd ../ws_output/expSignal30.root  ../ws_output/scan_m34__sigma_bin*data.root
mv ../ws_output/fit_m34_data_unfolded.eps ../ws_output/fit_m34_data_unfoldedSignal30.eps

./WorkSpaceMaker --Variable m34 --doFit --WithData --DataSet ZZd_data_expSignal35
hadd ../ws_output/expSignal35.root  ../ws_output/scan_m34__sigma_bin*data.root
mv ../ws_output/fit_m34_data_unfolded.eps ../ws_output/fit_m34_data_unfoldedSignal35.eps

./WorkSpaceMaker --Variable m34 --doFit --WithData --DataSet ZZd_data_expSignal40
hadd ../ws_output/expSignal40.root  ../ws_output/scan_m34__sigma_bin*data.root
mv ../ws_output/fit_m34_data_unfolded.eps ../ws_output/fit_m34_data_unfoldedSignal40.eps

./WorkSpaceMaker --Variable m34 --doFit --WithData --DataSet ZZd_data_expSignal45
hadd ../ws_output/expSignal45.root  ../ws_output/scan_m34__sigma_bin*data.root
mv ../ws_output/fit_m34_data_unfolded.eps ../ws_output/fit_m34_data_unfoldedSignal45.eps

./WorkSpaceMaker --Variable m34 --doFit --WithData --DataSet ZZd_data_expSignal50
hadd ../ws_output/expSignal50.root  ../ws_output/scan_m34__sigma_bin*data.root
mv ../ws_output/fit_m34_data_unfolded.eps ../ws_output/fit_m34_data_unfoldedSignal50.eps

./WorkSpaceMaker --Variable m34 --doFit --WithData --DataSet ZZd_data_expSignal55
hadd ../ws_output/expSignal55.root  ../ws_output/scan_m34__sigma_bin*data.root
mv ../ws_output/fit_m34_data_unfolded.eps ../ws_output/fit_m34_data_unfoldedSignal55.eps
