#ifndef ENUMDEF_H
#define ENUMDEF_H

enum Process{
  Signal = 0,
  ggH    = 1,
  VBF    = 2,
  WH     = 3,
  ZH     = 4,
  ttH    = 5,
  bbH    = 6,
  ggZZ   = 7,
  qqZZ   = 8,
  redBkg = 9
};

enum Channel{
  AllChannels = 0,
  FourMu      = 1,
  FourEl      = 2,
  TwoMuTwoEl  = 3,
  TwoElTwoMu  = 4  
};

enum Variable{
  pt           = 1,
  pt_0jet      = 2,
  pt_1jet      = 3,
  pt_2jet      = 4,
  m12          = 5,
  m34          = 6,
  y            = 7,
  njet         = 8,
  costhetastar = 9,
  LeadJetPt    = 10,
  mjj          = 11,
  deltaetajj   = 12,
  deltaphijj   = 13,
  nbjet        = 14,
  m12m34       = 15,
  njetv2       = 16,
  njetv3       = 17
};

#endif
