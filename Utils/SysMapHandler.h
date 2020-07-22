#include "map"
#include "iostream"
#include "Enum.h"


void FillNormalizationSystematics(std::map<short int,std::string> &sysMap);
void FillNormPart1Systematics(std::map<short int,std::string> &sysMap);
void FillNormPart2Systematics(std::map<short int,std::string> &sysMap);

void FillShapeSystematics(std::map<short int,std::string> &sysMap);
void FillShapePart1Systematics(std::map<short int,std::string> &sysMap);
void FillShapePart2Systematics(std::map<short int,std::string> &sysMap);
void FillShapePart3Systematics(std::map<short int,std::string> &sysMap);

void FillSigTheoryScaleSystematics(std::map<short int,std::string> &sysMap);
void FillSigTheoryScalePart1Systematics(std::map<short int,std::string> &sysMap);
void FillSigTheoryScalePart2Systematics(std::map<short int,std::string> &sysMap);
void FillSigTheoryScalePart3Systematics(std::map<short int,std::string> &sysMap);

void FillSigTheoryPdfSystematics(std::map<short int,std::string> &sysMap);
void FillSigTheoryPdfPart1Systematics(std::map<short int,std::string> &sysMap);
void FillSigTheoryPdfPart2Systematics(std::map<short int,std::string> &sysMap);
void FillSigTheoryPdfPart3Systematics(std::map<short int,std::string> &sysMap);
void FillSigTheoryPdfPart4Systematics(std::map<short int,std::string> &sysMap);

void FillSigTheoryQcdSystematics(std::map<short int,std::string> &sysMap);
void FillSigTheoryQcdPart1Systematics(std::map<short int,std::string> &sysMap);
void FillSigTheoryQcdPart2Systematics(std::map<short int,std::string> &sysMap);
void FillSigTheoryQcdPart3Systematics(std::map<short int,std::string> &sysMap);

void FillSignalShowerSystematics(std::map<short int,std::string> &sysMap);
void FillSignalShowerPart1Systematics(std::map<short int,std::string> &sysMap);
void FillSignalShowerPart2Systematics(std::map<short int,std::string> &sysMap);
void FillSignalShowerPart3Systematics(std::map<short int,std::string> &sysMap);

void FillSignalShowerHerwigSystematics(std::map<short int,std::string> &sysMap);

void FillSignalCompositionSystematics(std::map<short int,std::string> &sysMap);

void FillSignalMassShapeSystematics(std::map<short int,std::string> &sysMap);

void FillZZTheorySystematics(std::map<short int,std::string> &sysMap);
void FillZZTheoryPart1Systematics(std::map<short int,std::string> &sysMap);
void FillZZTheoryPart2Systematics(std::map<short int,std::string> &sysMap);

std::map<short int,std::string> MakeSysMap(bool addNom, int sysNum){

  std::map<short int,std::string> m_sysMap;
  m_sysMap.clear();

  bool doSys=false;
  if(sysNum!=0) doSys=true;
  if(sysNum%2==0 && sysNum!=0){
    PRINT_WARNING("<MakeSysMap()>:: even sysNum ("+std::to_string(sysNum)+") "+
		  "not valid (odd only accepted): switching off map filling");
    doSys=false;
  }

  /* add nominal */
  if(addNom){ m_sysMap[ Syst::NOMINAL ] = "Nominal" ; }

  /* deal systematics */
  if(doSys){

    switch(sysNum){
      /* Normalization systematics */
    case Syst::EL_EFF_ID_CorrUncertaintyNP0:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_CorrUncertaintyNP0__1down" ; 
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_CorrUncertaintyNP0__1up"   ;
      break;
    case Syst::EL_EFF_ID_CorrUncertaintyNP1:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_CorrUncertaintyNP1__1down" ; 
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_CorrUncertaintyNP1__1up"   ;
      break;
    case Syst::EL_EFF_ID_CorrUncertaintyNP2:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_CorrUncertaintyNP2__1down" ;
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_CorrUncertaintyNP2__1up"   ;
      break;
    case Syst::EL_EFF_ID_CorrUncertaintyNP3:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_CorrUncertaintyNP3__1down" ;
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_CorrUncertaintyNP3__1up"   ;
      break;
    case Syst::EL_EFF_ID_CorrUncertaintyNP4:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_CorrUncertaintyNP4__1down" ;
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_CorrUncertaintyNP4__1up"   ;
      break;
    case Syst::EL_EFF_ID_CorrUncertaintyNP5:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_CorrUncertaintyNP5__1down" ; 
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_CorrUncertaintyNP5__1up"   ;
      break;
    case Syst::EL_EFF_ID_CorrUncertaintyNP6:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_CorrUncertaintyNP6__1down" ;
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_CorrUncertaintyNP6__1up"   ;
      break;
    case Syst::EL_EFF_ID_CorrUncertaintyNP7:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_CorrUncertaintyNP7__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_CorrUncertaintyNP7__1up"  ;
      break;
    case Syst::EL_EFF_ID_CorrUncertaintyNP8:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_CorrUncertaintyNP8__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_CorrUncertaintyNP8__1up"  ;
      break;
    case Syst::EL_EFF_ID_CorrUncertaintyNP9:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_CorrUncertaintyNP9__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_CorrUncertaintyNP9__1up"  ;
      break;
    case Syst::EL_EFF_ID_CorrUncertaintyNP10:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_CorrUncertaintyNP10__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_CorrUncertaintyNP10__1up"  ;
      break;
    case Syst::EL_EFF_ID_CorrUncertaintyNP11:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_CorrUncertaintyNP11__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_CorrUncertaintyNP11__1up"  ;
      break;
    case Syst::EL_EFF_ID_CorrUncertaintyNP12:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_CorrUncertaintyNP12__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_CorrUncertaintyNP12__1up"  ;
      break;
    case Syst::EL_EFF_ID_CorrUncertaintyNP13:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_CorrUncertaintyNP13__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_CorrUncertaintyNP13__1up"  ;
      break;
    case Syst::EL_EFF_ID_CorrUncertaintyNP14:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_CorrUncertaintyNP14__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_CorrUncertaintyNP14__1up"  ;
      break;
    case Syst::EL_EFF_ID_CorrUncertaintyNP15:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_CorrUncertaintyNP15__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_CorrUncertaintyNP15__1up"  ;
      break;
    case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up"  ;
      break;
    case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up"  ;
      break;
    case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up"  ;
      break;
    case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up"  ;
      break;
    case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up"  ;
      break;
    case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up"  ;
      break;
    case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up"  ;
      break;
    case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up"  ;
      break;
    case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up"  ;
      break;
    case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up"  ;
      break;
    case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down" ;
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up"   ;
      break;
    case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up"  ;
      break;
    case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down" ;
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up"   ;
      break;
    case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down" ;
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up"   ;
      break;
    case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up"  ;
      break;
    case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up"  ;
      break;
    case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1up"  ;
      break;
    case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17:
      m_sysMap[ sysNum   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1up"  ;
      break;
    case Syst::EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR:
      m_sysMap[ sysNum   ] = "EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up"  ;
      break;
    case Syst::EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR:
      m_sysMap[ sysNum   ] = "EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down";
      m_sysMap[ sysNum+1 ] = "EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up"  ;
      break;
    case Syst::FT_EFF_Eigen_B_0:
      m_sysMap[ sysNum   ] = "FT_EFF_Eigen_B_0__1down";
      m_sysMap[ sysNum+1 ] = "FT_EFF_Eigen_B_0__1up"  ;
      break;
    case Syst::FT_EFF_Eigen_B_1:
      m_sysMap[ sysNum   ] = "FT_EFF_Eigen_B_1__1down";
      m_sysMap[ sysNum+1 ] = "FT_EFF_Eigen_B_1__1up"  ;
      break;
    case Syst::FT_EFF_Eigen_B_2:
      m_sysMap[ sysNum   ] = "FT_EFF_Eigen_B_2__1down";
      m_sysMap[ sysNum+1 ] = "FT_EFF_Eigen_B_2__1up"  ;
      break;
    case Syst::FT_EFF_Eigen_C_0:
      m_sysMap[ sysNum   ] = "FT_EFF_Eigen_C_0__1down";
      m_sysMap[ sysNum+1 ] = "FT_EFF_Eigen_C_0__1up"  ;
    case Syst::FT_EFF_Eigen_C_1:
      m_sysMap[ sysNum   ] = "FT_EFF_Eigen_C_1__1down";
      m_sysMap[ sysNum+1 ] = "FT_EFF_Eigen_C_1__1up"  ;
      break;
    case Syst::FT_EFF_Eigen_C_2:
      m_sysMap[ sysNum   ] = "FT_EFF_Eigen_C_2__1down";
      m_sysMap[ sysNum+1 ] = "FT_EFF_Eigen_C_2__1up"  ;
      break;
    case Syst::FT_EFF_Eigen_C_3:
      m_sysMap[ sysNum   ] = "FT_EFF_Eigen_C_3__1down";
      m_sysMap[ sysNum+1 ] = "FT_EFF_Eigen_C_3__1up"  ;
      break;
    case Syst::FT_EFF_Eigen_Light_0:
      m_sysMap[ sysNum   ] = "FT_EFF_Eigen_Light_0__1down";
      m_sysMap[ sysNum+1 ] = "FT_EFF_Eigen_Light_0__1up"  ;
      break;
    case Syst::FT_EFF_Eigen_Light_1:
      m_sysMap[ sysNum   ] = "FT_EFF_Eigen_Light_1__1down";
      m_sysMap[ sysNum+1 ] = "FT_EFF_Eigen_Light_1__1up"  ;
      break;
    case Syst::FT_EFF_Eigen_Light_2:
      m_sysMap[ sysNum   ] = "FT_EFF_Eigen_Light_2__1down";
      m_sysMap[ sysNum+1 ] = "FT_EFF_Eigen_Light_2__1up"  ;
      break;
    case Syst::FT_EFF_Eigen_Light_3:
      m_sysMap[ sysNum   ] = "FT_EFF_Eigen_Light_3__1down";
      m_sysMap[ sysNum+1 ] = "FT_EFF_Eigen_Light_3__1up"  ;
      break;
    case Syst::FT_EFF_Eigen_Light_4:
      m_sysMap[ sysNum   ] = "FT_EFF_Eigen_Light_4__1down";
      m_sysMap[ sysNum+1 ] = "FT_EFF_Eigen_Light_4__1up"  ;
      break;
    case Syst::JET_JvtEfficiency:
      m_sysMap[ sysNum ] = "JET_JvtEfficiency__1down";
      m_sysMap[ sysNum ] = "JET_JvtEfficiency__1up"  ;
      break;
    case Syst::JET_fJvtEfficiency:
      m_sysMap[ sysNum ] = "JET_fJvtEfficiency__1down";
      m_sysMap[ sysNum ] = "JET_fJvtEfficiency__1up"  ;
      break;
    case Syst::HOEW_QCD_syst:
      m_sysMap[ sysNum   ] = "HOEW_QCD_syst__1down";
      m_sysMap[ sysNum+1 ] = "HOEW_QCD_syst__1up"  ;
      break;
    case Syst::HOEW_syst:
      m_sysMap[ sysNum   ] = "HOEW_syst__1down";
      m_sysMap[ sysNum+1 ] = "HOEW_syst__1up"  ;
      break;
    case Syst::HOQCD_scale_syst:
      m_sysMap[ sysNum   ] = "HOQCD_scale_syst__1down";
      m_sysMap[ sysNum+1 ] = "HOQCD_scale_syst__1up"  ;
      break;
    case Syst::MUON_EFF_ISO_STAT:
      m_sysMap[ sysNum   ] = "MUON_EFF_ISO_STAT__1down";
      m_sysMap[ sysNum+1 ] = "MUON_EFF_ISO_STAT__1up"  ;
      break;
    case Syst::MUON_EFF_ISO_SYS:
      m_sysMap[ sysNum   ] = "MUON_EFF_ISO_SYS__1down";
      m_sysMap[ sysNum+1 ] = "MUON_EFF_ISO_SYS__1up"  ;
      break;
    case Syst::MUON_EFF_RECO_STAT_LOWPT:
      m_sysMap[ sysNum   ] = "MUON_EFF_RECO_STAT_LOWPT__1down";
      m_sysMap[ sysNum+1 ] = "MUON_EFF_RECO_STAT_LOWPT__1up"  ;
      break;
    case Syst::MUON_EFF_RECO_STAT:
      m_sysMap[ sysNum   ] = "MUON_EFF_RECO_STAT__1down";
      m_sysMap[ sysNum+1 ] = "MUON_EFF_RECO_STAT__1up"  ;
      break;
    case Syst::MUON_EFF_RECO_SYS_LOWPT:
      m_sysMap[ sysNum   ] = "MUON_EFF_RECO_SYS_LOWPT__1down";
      m_sysMap[ sysNum+1 ] = "MUON_EFF_RECO_SYS_LOWPT__1up"  ;
      break;
    case Syst::MUON_EFF_RECO_SYS:
      m_sysMap[ sysNum   ] = "MUON_EFF_RECO_SYS__1down";
      m_sysMap[ sysNum+1 ] = "MUON_EFF_RECO_SYS__1up"  ;
      break;
    case Syst::MUON_EFF_TTVA_STAT:
      m_sysMap[ sysNum   ] = "MUON_EFF_TTVA_STAT__1down";
      m_sysMap[ sysNum+1 ] = "MUON_EFF_TTVA_STAT__1up"  ;
      break;
    case Syst::MUON_EFF_TTVA_SYS:
      m_sysMap[ sysNum   ] = "MUON_EFF_TTVA_SYS__1down";
      m_sysMap[ sysNum+1 ] = "MUON_EFF_TTVA_SYS__1up"  ;
      break;
    case Syst::PRW_DATASF:
      m_sysMap[ sysNum   ] = "PRW_DATASF__1down";
      m_sysMap[ sysNum+1 ] = "PRW_DATASF__1up"  ;
      break;

      /* Shape Systematics */
    case Syst::EG_RESOLUTION_ALL:
      m_sysMap[ sysNum   ] = "EG_RESOLUTION_ALL__1down";
      m_sysMap[ sysNum+1 ] = "EG_RESOLUTION_ALL__1up"  ;
      break;
    case Syst::EG_SCALE_AF2:
      m_sysMap[ sysNum   ] = "EG_SCALE_AF2__1down";
      m_sysMap[ sysNum+1 ] = "EG_SCALE_AF2__1up"  ;
      break;
    case Syst::EG_SCALE_ALL:
      m_sysMap[ sysNum   ] = "EG_SCALE_ALL__1down";
      m_sysMap[ sysNum+1 ] = "EG_SCALE_ALL__1up"  ;
      break;
    case Syst::EG_SCALE_LARCALIB_EXTRA2015PRE:
      m_sysMap[ sysNum   ] = "EG_SCALE_LARCALIB_EXTRA2015PRE__1down";
      m_sysMap[ sysNum+1 ] = "EG_SCALE_LARCALIB_EXTRA2015PRE__1up"  ;
      break;
    case Syst::EG_SCALE_LARTEMPERATURE_EXTRA2015PRE:
      m_sysMap[ sysNum   ] = "EG_SCALE_LARTEMPERATURE_EXTRA2015PRE__1down";
      m_sysMap[ sysNum+1 ] = "EG_SCALE_LARTEMPERATURE_EXTRA2015PRE__1up"  ;
      break;
    case Syst::EG_SCALE_LARTEMPERATURE_EXTRA2016PRE:
      m_sysMap[ sysNum   ] = "EG_SCALE_LARTEMPERATURE_EXTRA2016PRE__1down";
      m_sysMap[ sysNum+1 ] = "EG_SCALE_LARTEMPERATURE_EXTRA2016PRE__1up"  ;
      break;
    case Syst::JET_BJES_Response:
      m_sysMap[ sysNum   ] = "JET_BJES_Response__1down";
      m_sysMap[ sysNum+1 ] = "JET_BJES_Response__1up"  ;
      break;
    case Syst::JET_EffectiveNP_1:
      m_sysMap[ sysNum   ] = "JET_EffectiveNP_1__1down";
      m_sysMap[ sysNum+1 ] = "JET_EffectiveNP_1__1up"  ;
      break;
    case Syst::JET_EffectiveNP_2:
      m_sysMap[ sysNum   ] = "JET_EffectiveNP_2__1down";
      m_sysMap[ sysNum+1 ] = "JET_EffectiveNP_2__1up"  ;
      break;
    case Syst::JET_EffectiveNP_3:
      m_sysMap[ sysNum   ] = "JET_EffectiveNP_3__1down";
      m_sysMap[ sysNum+1 ] = "JET_EffectiveNP_3__1up"  ;
      break;
    case Syst::JET_EffectiveNP_4:
      m_sysMap[ sysNum   ] = "JET_EffectiveNP_4__1down";
      m_sysMap[ sysNum+1 ] = "JET_EffectiveNP_4__1up"  ;
      break;
    case Syst::JET_EffectiveNP_5:
      m_sysMap[ sysNum   ] = "JET_EffectiveNP_5__1down";
      m_sysMap[ sysNum+1 ] = "JET_EffectiveNP_5__1up"  ;
      break;
    case Syst::JET_EffectiveNP_6:
      m_sysMap[ sysNum   ] = "JET_EffectiveNP_6__1down";
      m_sysMap[ sysNum+1 ] = "JET_EffectiveNP_6__1up"  ;
      break;
    case Syst::JET_EffectiveNP_7:
      m_sysMap[ sysNum   ] = "JET_EffectiveNP_7__1down";
      m_sysMap[ sysNum+1 ] = "JET_EffectiveNP_7__1up"  ;
      break;
    case Syst::JET_EffectiveNP_8restTerm:
      m_sysMap[ sysNum   ] = "JET_EffectiveNP_8restTerm__1down";
      m_sysMap[ sysNum+1 ] = "JET_EffectiveNP_8restTerm__1up"  ;
      break;
    case Syst::JET_EtaIntercalibration_Modelling:
      m_sysMap[ sysNum   ] = "JET_EtaIntercalibration_Modelling__1down";
      m_sysMap[ sysNum+1 ] = "JET_EtaIntercalibration_Modelling__1up"  ;
      break;
    case Syst::JET_EtaIntercalibration_NonClosure_highE:
      m_sysMap[ sysNum   ] = "JET_EtaIntercalibration_NonClosure_highE__1down";
      m_sysMap[ sysNum+1 ] = "JET_EtaIntercalibration_NonClosure_highE__1up"  ;
      break;
    case Syst::JET_EtaIntercalibration_NonClosure_negEta:
      m_sysMap[ sysNum   ] = "JET_EtaIntercalibration_NonClosure_negEta__1down";
      m_sysMap[ sysNum+1 ] = "JET_EtaIntercalibration_NonClosure_negEta__1up"  ;
      break;
    case Syst::JET_EtaIntercalibration_NonClosure_posEta:
      m_sysMap[ sysNum   ] = "JET_EtaIntercalibration_NonClosure_posEta__1down";
      m_sysMap[ sysNum+1 ] = "JET_EtaIntercalibration_NonClosure_posEta__1up"  ;
      break;
    case Syst::JET_EtaIntercalibration_TotalStat:
      m_sysMap[ sysNum   ] = "JET_EtaIntercalibration_TotalStat__1down";
      m_sysMap[ sysNum+1 ] = "JET_EtaIntercalibration_TotalStat__1up"  ;
      break;
    case Syst::JET_Flavor_Composition_ggHbbH:
      m_sysMap[ sysNum   ] = "JET_Flavor_Composition_ggHbbH__1down";
      m_sysMap[ sysNum+1 ] = "JET_Flavor_Composition_ggHbbH__1up"  ;
      break;
    case Syst::JET_Flavor_Composition_VBF:
      m_sysMap[ sysNum   ] = "JET_Flavor_Composition_VBF__1down";
      m_sysMap[ sysNum+1 ] = "JET_Flavor_Composition_VBF__1up"  ;
      break;
    case Syst::JET_Flavor_Composition_VH:
      m_sysMap[ sysNum   ] = "JET_Flavor_Composition_VH__1down";
      m_sysMap[ sysNum+1 ] = "JET_Flavor_Composition_VH__1up"  ;
      break;
    case Syst::JET_Flavor_Composition_ttHtH:
      m_sysMap[ sysNum   ] = "JET_Flavor_Composition_ttHtH__1down";
      m_sysMap[ sysNum+1 ] = "JET_Flavor_Composition_ttHtH__1up"  ;
      break;
    case Syst::JET_Flavor_Composition_ZZ:
      m_sysMap[ sysNum   ] = "JET_Flavor_Composition_ZZ__1down";
      m_sysMap[ sysNum+1 ] = "JET_Flavor_Composition_ZZ__1up"  ;
      break;
    case Syst::JET_Flavor_Response_ggHbbH:
      m_sysMap[ sysNum   ] = "JET_Flavor_Response_ggHbbH__1down";
      m_sysMap[ sysNum+1 ] = "JET_Flavor_Response_ggHbbH__1up"  ;
      break;
    case Syst::JET_Flavor_Response_VBF:
      m_sysMap[ sysNum   ] = "JET_Flavor_Response_VBF__1down";
      m_sysMap[ sysNum+1 ] = "JET_Flavor_Response_VBF__1up"  ;
      break;
    case Syst::JET_Flavor_Response_VH:
      m_sysMap[ sysNum   ] = "JET_Flavor_Response_VH__1down";
      m_sysMap[ sysNum+1 ] = "JET_Flavor_Response_VH__1up"  ;
      break;
    case Syst::JET_Flavor_Response_ttHtH:
      m_sysMap[ sysNum   ] = "JET_Flavor_Response_ttHtH__1down";
      m_sysMap[ sysNum+1 ] = "JET_Flavor_Response_ttHtH__1up"  ;
      break;
    case Syst::JET_Flavor_Response_ZZ:
      m_sysMap[ sysNum   ] = "JET_Flavor_Response_ZZ__1down";
      m_sysMap[ sysNum+1 ] = "JET_Flavor_Response_ZZ__1up"  ;
      break;
    case Syst::JET_JER_DataVsMC:
      m_sysMap[ sysNum ] = "JET_JER_DataVsMC__1down";
      m_sysMap[ sysNum ] = "JET_JER_DataVsMC__1up"  ;
      break;
    case Syst::JET_JER_EffectiveNP_1:
      m_sysMap[ sysNum ] = "JET_JER_EffectiveNP_1__1down";
      m_sysMap[ sysNum ] = "JET_JER_EffectiveNP_1__1up"  ;
      break;
    case Syst::JET_JER_EffectiveNP_2:
      m_sysMap[ sysNum ] = "JET_JER_EffectiveNP_2__1down";
      m_sysMap[ sysNum ] = "JET_JER_EffectiveNP_2__1up"  ;
      break;
    case Syst::JET_JER_EffectiveNP_3:
      m_sysMap[ sysNum ] = "JET_JER_EffectiveNP_3__1down";
      m_sysMap[ sysNum ] = "JET_JER_EffectiveNP_3__1up"  ;
      break;
    case Syst::JET_JER_EffectiveNP_4:
      m_sysMap[ sysNum ] = "JET_JER_EffectiveNP_4__1down";
      m_sysMap[ sysNum ] = "JET_JER_EffectiveNP_4__1up"  ;
      break;
    case Syst::JET_JER_EffectiveNP_5:
      m_sysMap[ sysNum ] = "JET_JER_EffectiveNP_5__1down";
      m_sysMap[ sysNum ] = "JET_JER_EffectiveNP_5__1up"  ;
      break;
    case Syst::JET_JER_EffectiveNP_6:
      m_sysMap[ sysNum ] = "JET_JER_EffectiveNP_6__1down";
      m_sysMap[ sysNum ] = "JET_JER_EffectiveNP_6__1up"  ;
      break;
    case Syst::JET_JER_EffectiveNP_7restTerm:
      m_sysMap[ sysNum ] = "JET_JER_EffectiveNP_7restTerm__1down";
      m_sysMap[ sysNum ] = "JET_JER_EffectiveNP_7restTerm__1up"  ;
      break;
    case Syst::JET_Pileup_OffsetMu:
      m_sysMap[ sysNum   ] = "JET_Pileup_OffsetMu__1down";
      m_sysMap[ sysNum+1 ] = "JET_Pileup_OffsetMu__1up"  ;
      break;
    case Syst::JET_Pileup_OffsetNPV:
      m_sysMap[ sysNum   ] = "JET_Pileup_OffsetNPV__1down";
      m_sysMap[ sysNum+1 ] = "JET_Pileup_OffsetNPV__1up"  ;
      break;
    case Syst::JET_Pileup_PtTerm:
      m_sysMap[ sysNum   ] = "JET_Pileup_PtTerm__1down";
      m_sysMap[ sysNum+1 ] = "JET_Pileup_PtTerm__1up"  ;
      break;
    case Syst::JET_Pileup_RhoTopology:
      m_sysMap[ sysNum   ] = "JET_Pileup_RhoTopology__1down";
      m_sysMap[ sysNum+1 ] = "JET_Pileup_RhoTopology__1up"  ;
      break;
    case Syst::JET_PunchThrough_MC16:
      m_sysMap[ sysNum   ] = "JET_PunchThrough_MC16__1down";
      m_sysMap[ sysNum+1 ] = "JET_PunchThrough_MC16__1up"  ;
      break;
    case Syst::JET_SingleParticle_HighPt:
      m_sysMap[ sysNum   ] = "JET_SingleParticle_HighPt__1down";
      m_sysMap[ sysNum+1 ] = "JET_SingleParticle_HighPt__1up"  ;
      break;
    case Syst::MUON_ID:
      m_sysMap[ sysNum   ] = "MUON_ID__1down";
      m_sysMap[ sysNum+1 ] = "MUON_ID__1up"  ;
      break;
    case Syst::MUON_MS:
      m_sysMap[ sysNum   ] = "MUON_MS__1down";
      m_sysMap[ sysNum+1 ] = "MUON_MS__1up"  ;
      break;
    case Syst::MUON_SAGITTA_RESBIAS:
      m_sysMap[ sysNum   ] = "MUON_SAGITTA_RESBIAS__1down";
      m_sysMap[ sysNum+1 ] = "MUON_SAGITTA_RESBIAS__1up"  ;
      break;
    case Syst::MUON_SAGITTA_RHO:
      m_sysMap[ sysNum   ] = "MUON_SAGITTA_RHO__1down";
      m_sysMap[ sysNum+1 ] = "MUON_SAGITTA_RHO__1up"  ;
      break;
    case Syst::MUON_SCALE:
      m_sysMap[ sysNum   ] = "MUON_SCALE__1down";
      m_sysMap[ sysNum+1 ] = "MUON_SCALE__1up"  ;
      break;
    case Syst::VAR_TH_muR0p5_muF0p5_VBF:
      m_sysMap [ sysNum ] = "Theory_muR0p5_muF0p5_VBF";
      break;
    case Syst::VAR_TH_muR0p5_muF0p5_VH:
      m_sysMap [ sysNum ] = "Theory_muR0p5_muF0p5_VH";
      break;
    case Syst::VAR_TH_muR0p5_muF0p5_ttH:
      m_sysMap [ sysNum ] = "Theory_muR0p5_muF0p5_ttH";
      break;
    case Syst::VAR_TH_muR0p5_muF1p0_VBF:
      m_sysMap [ sysNum ] = "Theory_muR0p5_muF1p0_VBF";
      break;
    case Syst::VAR_TH_muR0p5_muF1p0_VH:
      m_sysMap [ sysNum ] = "Theory_muR0p5_muF1p0_VH";
      break;
    case Syst::VAR_TH_muR0p5_muF1p0_ttH:
      m_sysMap [ sysNum ] = "Theory_muR0p5_muF1p0_ttH";
      break;
    case Syst::VAR_TH_muR0p5_muF2p0_VBF:
      m_sysMap [ sysNum ] = "Theory_muR0p5_muF2p0_VBF";
      break;
    case Syst::VAR_TH_muR0p5_muF2p0_VH:
      m_sysMap [ sysNum ] = "Theory_muR0p5_muF2p0_VH";
      break;
    case Syst::VAR_TH_muR0p5_muF2p0_ttH:
      m_sysMap [ sysNum ] = "Theory_muR0p5_muF2p0_ttH";
      break;
    case Syst::VAR_TH_muR1p0_muF0p5_VBF:
      m_sysMap [ sysNum ] = "Theory_muR1p0_muF0p5_VBF";
      break;
    case Syst::VAR_TH_muR1p0_muF0p5_VH:
      m_sysMap [ sysNum ] = "Theory_muR1p0_muF0p5_VH";
      break;
    case Syst::VAR_TH_muR1p0_muF0p5_ttH:
      m_sysMap [ sysNum ] = "Theory_muR1p0_muF0p5_ttH";
      break;
    case Syst::VAR_TH_muR1p0_muF2p0_VBF:
      m_sysMap [ sysNum ] = "Theory_muR1p0_muF2p0_VBF";
      break;
    case Syst::VAR_TH_muR1p0_muF2p0_VH:
      m_sysMap [ sysNum ] = "Theory_muR1p0_muF2p0_VH";
      break;
    case Syst::VAR_TH_muR1p0_muF2p0_ttH:
      m_sysMap [ sysNum ] = "Theory_muR1p0_muF2p0_ttH";
      break;
    case Syst::VAR_TH_muR2p0_muF0p5_VBF:
      m_sysMap [ sysNum ] = "Theory_muR2p0_muF0p5_VBF";
      break;
    case Syst::VAR_TH_muR2p0_muF0p5_VH:
      m_sysMap [ sysNum ] = "Theory_muR2p0_muF0p5_VH";
      break;
    case Syst::VAR_TH_muR2p0_muF0p5_ttH:
      m_sysMap [ sysNum ] = "Theory_muR2p0_muF0p5_ttH";
      break;
    case Syst::VAR_TH_muR2p0_muF1p0_VBF:
      m_sysMap [ sysNum ] = "Theory_muR2p0_muF1p0_VBF";
      break;
    case Syst::VAR_TH_muR2p0_muF1p0_VH:
      m_sysMap [ sysNum ] = "Theory_muR2p0_muF1p0_VH";
      break;
    case Syst::VAR_TH_muR2p0_muF1p0_ttH:
      m_sysMap [ sysNum ] = "Theory_muR2p0_muF1p0_ttH";
      break;
    case Syst::VAR_TH_muR2p0_muF2p0_VBF:
      m_sysMap [ sysNum ] = "Theory_muR2p0_muF2p0_VBF";
      break;
    case Syst::VAR_TH_muR2p0_muF2p0_VH:
      m_sysMap [ sysNum ] = "Theory_muR2p0_muF2p0_VH";
      break;
    case Syst::VAR_TH_muR2p0_muF2p0_ttH:
      m_sysMap [ sysNum ] = "Theory_muR2p0_muF2p0_ttH";
      break;
    case Syst::VAR_TH_pdf_90400:
      m_sysMap [ sysNum ] = "Theory_pdf_90400";
      break;
    case Syst::VAR_TH_pdf_90401:
      m_sysMap [ sysNum ] = "Theory_pdf_90401";
      break;
    case Syst::VAR_TH_pdf_90402:
      m_sysMap [ sysNum ] = "Theory_pdf_90402";
      break;
    case Syst::VAR_TH_pdf_90403:
      m_sysMap [ sysNum ] = "Theory_pdf_90403";
      break;
    case Syst::VAR_TH_pdf_90404:
      m_sysMap [ sysNum ] = "Theory_pdf_90404";
      break;
    case Syst::VAR_TH_pdf_90405:
      m_sysMap [ sysNum ] = "Theory_pdf_90405";
      break;
    case Syst::VAR_TH_pdf_90406:
      m_sysMap [ sysNum ] = "Theory_pdf_90406";
      break;
    case Syst::VAR_TH_pdf_90407:
      m_sysMap [ sysNum ] = "Theory_pdf_90407";
      break;
    case Syst::VAR_TH_pdf_90408:
      m_sysMap [ sysNum ] = "Theory_pdf_90408";
      break;
    case Syst::VAR_TH_pdf_90409:
      m_sysMap [ sysNum ] = "Theory_pdf_90409";
      break;
    case Syst::VAR_TH_pdf_90410:
      m_sysMap [ sysNum ] = "Theory_pdf_90410";
      break;
    case Syst::VAR_TH_pdf_90411:
      m_sysMap [ sysNum ] = "Theory_pdf_90411";
      break;
    case Syst::VAR_TH_pdf_90412:
      m_sysMap [ sysNum ] = "Theory_pdf_90412";
      break;
    case Syst::VAR_TH_pdf_90413:
      m_sysMap [ sysNum ] = "Theory_pdf_90413";
      break;
    case Syst::VAR_TH_pdf_90414:
      m_sysMap [ sysNum ] = "Theory_pdf_90414";
      break;
    case Syst::VAR_TH_pdf_90415:
      m_sysMap [ sysNum ] = "Theory_pdf_90415";
      break;
    case Syst::VAR_TH_pdf_90416:
      m_sysMap [ sysNum ] = "Theory_pdf_90416";
      break;
    case Syst::VAR_TH_pdf_90417:
      m_sysMap [ sysNum ] = "Theory_pdf_90417";
      break;
    case Syst::VAR_TH_pdf_90418:
      m_sysMap [ sysNum ] = "Theory_pdf_90418";
      break;
    case Syst::VAR_TH_pdf_90419:
      m_sysMap [ sysNum ] = "Theory_pdf_90419";
      break;
    case Syst::VAR_TH_pdf_90420:
      m_sysMap [ sysNum ] = "Theory_pdf_90420";
      break;
    case Syst::VAR_TH_pdf_90421:
      m_sysMap [ sysNum ] = "Theory_pdf_90421";
      break;
    case Syst::VAR_TH_pdf_90422:
      m_sysMap [ sysNum ] = "Theory_pdf_90422";
      break;
    case Syst::VAR_TH_pdf_90423:
      m_sysMap [ sysNum ] = "Theory_pdf_90423";
      break;
    case Syst::VAR_TH_pdf_90424:
      m_sysMap [ sysNum ] = "Theory_pdf_90424";
      break;
    case Syst::VAR_TH_pdf_90425:
      m_sysMap [ sysNum ] = "Theory_pdf_90425";
      break;
    case Syst::VAR_TH_pdf_90426:
      m_sysMap [ sysNum ] = "Theory_pdf_90426";
      break;
    case Syst::VAR_TH_pdf_90427:
      m_sysMap [ sysNum ] = "Theory_pdf_90427";
      break;
    case Syst::VAR_TH_pdf_90428:
      m_sysMap [ sysNum ] = "Theory_pdf_90428";
      break;
    case Syst::VAR_TH_pdf_90429:
      m_sysMap [ sysNum ] = "Theory_pdf_90429";
      break;
    case Syst::VAR_TH_pdf_90430:
      m_sysMap [ sysNum ] = "Theory_pdf_90430";
      break;
    case Syst::VAR_TH_pdf_90431:
      m_sysMap [ sysNum ] = "Theory_pdf_90431";
      break;
    case Syst::VAR_TH_pdf_90432:
      m_sysMap [ sysNum ] = "Theory_pdf_90432";
      break;
    case Syst::VAR_TH_ggF_qcd_2017_pTH120:
      m_sysMap[ sysNum ] = "QCDscale_ggF_pTH120";
      break;
    case Syst::VAR_TH_ggF_qcd_2017_pTH60:
      m_sysMap[ sysNum ] = "QCDscale_ggF_pTH60";
      break;
    case Syst::VAR_TH_qcd_wg1_mig01:
      m_sysMap[ sysNum ] = "QCDscale_ggF_mig01";
      break;
    case Syst::VAR_TH_qcd_wg1_mig12:
      m_sysMap[ sysNum ] = "QCDscale_ggF_mig12";
      break;
    case Syst::VAR_TH_qcd_wg1_mu:
      m_sysMap[ sysNum ] = "QCDscale_ggF_H4l";
      break;
    case Syst::VAR_TH_qcd_wg1_qm_t:
      m_sysMap[ sysNum ] = "QCDscale_ggF_qm_t";
      break;
    case Syst::VAR_TH_qcd_wg1_res:
      m_sysMap[ sysNum ] = "QCDres_ggF";
      break;
    case Syst::VAR_TH_qcd_wg1_vbf2j:
      m_sysMap[ sysNum ] = "QCDscale_ggF_vbf2j";
      break;
    case Syst::VAR_TH_qcd_wg1_vbf3j:
      m_sysMap[ sysNum ] = "QCDscale_ggF_vbf3j";
      break;
    case Syst::VAR_TH_ggF_QCD_pTH_nJ0:
      m_sysMap[ sysNum ] = "QCDScale_ggF_nJ0";
      break;
    case Syst::VAR_TH_Var3c:
      m_sysMap[ sysNum ] = "Theory_Shower_Var3c__1down";
      break;
    case Syst::VAR_TH_Var3c+1:
      m_sysMap[ sysNum ] = "Theory_Shower_Var3c__1up";
      break;
    case Syst::VAR_TH_hard:
      m_sysMap[ sysNum ] = "Theory_Shower_hard__1down";
      break;
    case Syst::VAR_TH_hard+1:
      m_sysMap[ sysNum ] = "Theory_Shower_hard__1up";
      break;
    case Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_0p5:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_0p5_fsrmuRfac_0p5";
      break;
    case Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_1p0:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_0p5_fsrmuRfac_1p0";
      break;
    case Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_2p0:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_0p5_fsrmuRfac_2p0";
      break;
    case Syst::VAR_TH_isrmuRfac_0p625_fsrmuRfac_1p0:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_0p625_fsrmuRfac_1p0";
      break;
    case Syst::VAR_TH_isrmuRfac_0p75_fsrmuRfac_1p0:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_0p75_fsrmuRfac_1p0";
      break;
    case Syst::VAR_TH_isrmuRfac_0p875_fsrmuRfac_1p0:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_0p875_fsrmuRfac_1p0";
      break;
    case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p5:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p5";
      break;
    case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p625:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p625";
      break;
    case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p75:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p75";
      break;
    case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p875:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p875";
      break;
    case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p25:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_1p0_fsrmuRfac_1p25";
      break;
    case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p5:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_1p0_fsrmuRfac_1p5";
      break;
    case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p75:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_1p0_fsrmuRfac_1p75";
      break;
    case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_2p0:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_1p0_fsrmuRfac_2p0";
      break;
    case Syst::VAR_TH_isrmuRfac_1p25_fsrmuRfac_1p0:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_1p25_fsrmuRfac_1p0";
      break;
    case Syst::VAR_TH_isrmuRfac_1p5_fsrmuRfac_1p0:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_1p5_fsrmuRfac_1p0";
      break;
    case Syst::VAR_TH_isrmuRfac_1p75_fsrmuRfac_1p0:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_1p75_fsrmuRfac_1p0";
      break;
    case Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_0p5:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_2p0_fsrmuRfac_0p5";
      break;
    case Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_1p0:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_2p0_fsrmuRfac_1p0";
      break;
    case Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_2p0:
      m_sysMap[ sysNum ] = "Theory_Shower_isrmuRfac_2p0_fsrmuRfac_2p0";
      break;
    case Syst::VAR_TH_Shower_Herwig_Nominal:
      m_sysMap[ sysNum ] = "Theory_Shower_Herwig_Nominal";
      break;
    case Syst::VAR_TH_Shower_Herwig_ggHbbH:
      m_sysMap[ sysNum ] = "Theory_Shower_Herwig_ggHbbH";
      break;
    case Syst::VAR_TH_Shower_Herwig_VBF:
      m_sysMap[ sysNum ] = "Theory_Shower_Herwig_VBF";
      break;
    case Syst::VAR_TH_Shower_Herwig_VH:
      m_sysMap[ sysNum ] = "Theory_Shower_Herwig_VH";
      break;
    case Syst::VAR_TH_Shower_Herwig_ttHtH:
      m_sysMap[ sysNum ] = "Theory_Shower_Herwig_ttHtH";
      break;
    case Syst::SignalMassShift:
      m_sysMap[ sysNum ] = "SignalMassShift__1down";
      m_sysMap[ sysNum ] = "SignalMassShift__1up"  ;
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261000:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261000";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261001:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261001";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261002:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261002";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261003:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261003";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261004:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261004";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261005:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261005";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261006:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261006";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261007:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261007";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261008:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261008";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261009:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261009";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261010:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261010";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261011:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261011";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261012:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261012";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261013:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261013";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261014:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261014";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261015:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261015";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261016:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261016";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261017:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261017";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261018:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261018";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261019:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261019";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261020:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261020";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261021:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261021";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261022:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261022";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261023:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261023";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261024:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261024";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261025:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261025";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261026:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261026";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261027:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261027";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261028:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261028";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261029:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261029";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261030:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261030";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261031:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261031";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261032:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261032";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261033:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261033";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261034:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261034";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261035:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261035";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261036:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261036";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261037:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261037";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261038:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261038";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261039:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261039";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261040:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261040";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261041:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261041";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261042:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261042";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261043:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261043";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261044:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261044";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261045:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261045";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261046:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261046";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261047:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261047";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261048:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261048";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261049:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261049";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261050:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261050";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261051:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261051";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261052:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261052";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261053:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261053";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261054:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261054";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261055:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261055";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261056:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261056";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261057:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261057";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261058:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261058";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261059:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261059";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261060:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261060";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261061:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261061";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261062:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261062";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261063:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261063";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261064:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261064";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261065:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261065";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261066:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261066";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261067:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261067";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261068:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261068";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261069:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261069";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261070:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261070";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261071:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261071";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261072:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261072";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261073:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261073";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261074:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261074";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261075:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261075";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261076:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261076";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261077:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261077";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261078:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261078";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261079:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261079";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261080:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261080";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261081:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261081";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261082:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261082";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261083:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261083";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261084:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261084";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261085:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261085";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261086:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261086";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261087:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261087";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261088:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261088";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261089:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261089";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261090:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261090";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261091:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261091";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261092:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261092";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261093:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261093";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261094:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261094";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261095:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261095";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261096:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261096";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261097:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261097";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261098:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261098";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261099:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261099";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261100:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF1_PDF261100";
      break;
    case Syst::VAR_TH_qqZZ_MUR0p5_MUF0p5_PDF261000:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR0p5_MUF0p5_PDF261000";
      break;
    case Syst::VAR_TH_qqZZ_MUR0p5_MUF1_PDF261000:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR0p5_MUF1_PDF261000";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF0p5_PDF261000:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF0p5_PDF261000";
      break;
    case Syst::VAR_TH_qqZZ_MUR1_MUF2_PDF261000:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR1_MUF2_PDF261000";
      break;
    case Syst::VAR_TH_qqZZ_MUR2_MUF1_PDF261000:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR2_MUF1_PDF261000";
      break;
    case Syst::VAR_TH_qqZZ_MUR2_MUF2_PDF261000:
      m_sysMap[ sysNum ] = "Theory_qqZZ_MUR2_MUF2_PDF261000";
      break;
    case Syst::VAR_TH_qqZZ_Sherpa_CKKW:
      m_sysMap[ sysNum ] = "Theory_qqZZ_CKKW__1down";
      m_sysMap[ sysNum ] = "Theory_qqZZ_CKKW__1up"  ;
      break;
    case Syst::VAR_TH_qqZZ_Sherpa_QSF:
      m_sysMap[ sysNum ] = "Theory_qqZZ_QSF__1down";
      m_sysMap[ sysNum ] = "Theory_qqZZ_QSF__1up"  ;
      break;
    case Syst::VAR_TH_qqZZ_Sherpa_CSSKIN:
      m_sysMap[ sysNum ] = "Theory_qqZZ_CSSKIN";
      break;
    case Syst::VAR_TH_qqZZ_Generator_Powheg:
      m_sysMap[ sysNum ] = "Theory_qqZZ_Generator_Powheg";
      break;
    case Syst::NormSystematics:
      FillNormalizationSystematics(m_sysMap);
      break;
    case Syst::NormPart1Systematics:
      FillNormPart1Systematics(m_sysMap);
      break;
    case Syst::NormPart2Systematics:
      FillNormPart2Systematics(m_sysMap);
      break;
    case Syst::ShapeSystematics:
      FillShapeSystematics(m_sysMap);
      break;
    case Syst::ShapePart1Systematics:
      FillShapePart1Systematics(m_sysMap);
      break;
    case Syst::ShapePart2Systematics:
      FillShapePart2Systematics(m_sysMap);
      break;
    case Syst::ShapePart3Systematics:
      FillShapePart3Systematics(m_sysMap);
      break;
    case Syst::ExperimentalSystematics:
      FillNormalizationSystematics(m_sysMap);
      FillShapeSystematics(m_sysMap);
      break;
    case Syst::SignalTheorySystematics:
      FillSigTheoryScaleSystematics(m_sysMap);
      FillSigTheoryPdfSystematics(m_sysMap);
      FillSigTheoryQcdSystematics(m_sysMap);
      break;
    case Syst::SignalTheoryScaleSystematics:
      FillSigTheoryScaleSystematics(m_sysMap);
      break;
    case Syst::SignalTheoryScalePart1Systematics:
      FillSigTheoryScalePart1Systematics(m_sysMap);
      break;
    case Syst::SignalTheoryScalePart2Systematics:
      FillSigTheoryScalePart2Systematics(m_sysMap);
      break;
    case Syst::SignalTheoryScalePart3Systematics:
      FillSigTheoryScalePart3Systematics(m_sysMap);
      break;
    case Syst::SignalTheoryPdfSystematics:
      FillSigTheoryPdfSystematics(m_sysMap);
      break;
    case Syst::SignalTheoryPdfPart1Systematics:
      FillSigTheoryPdfPart1Systematics(m_sysMap);
      break;
    case Syst::SignalTheoryPdfPart2Systematics:
      FillSigTheoryPdfPart2Systematics(m_sysMap);
      break;
    case Syst::SignalTheoryPdfPart3Systematics:
      FillSigTheoryPdfPart3Systematics(m_sysMap);
      break;
    case Syst::SignalTheoryPdfPart4Systematics:
      FillSigTheoryPdfPart4Systematics(m_sysMap);
      break;
    case Syst::SignalTheoryQcdSystematics:
      FillSigTheoryQcdSystematics(m_sysMap);
      break;
    case Syst::SignalTheoryQcdPart1Systematics:
      FillSigTheoryQcdPart1Systematics(m_sysMap);
      break;
    case Syst::SignalTheoryQcdPart2Systematics:
      FillSigTheoryQcdPart2Systematics(m_sysMap);
      break;
    case Syst::SignalTheoryQcdPart3Systematics:
      FillSigTheoryQcdPart3Systematics(m_sysMap);
      break;
    case Syst::SignalShowerSystematics:
      FillSignalShowerSystematics(m_sysMap);
      break;
    case Syst::SignalShowerPart1Systematics:
      FillSignalShowerPart1Systematics(m_sysMap);
      break;
    case Syst::SignalShowerPart2Systematics:
      FillSignalShowerPart2Systematics(m_sysMap);
      break;
    case Syst::SignalShowerPart3Systematics:
      FillSignalShowerPart3Systematics(m_sysMap);
      break;
    case Syst::SignalShowerHerwigSystematics:
      FillSignalShowerHerwigSystematics(m_sysMap);
      break;
    case Syst::SignalCompositionSystematics:
      FillSignalCompositionSystematics(m_sysMap);
      break;
    case Syst::SignalMassShapeSystematics:
      FillSignalMassShapeSystematics(m_sysMap);
      break;
    case Syst::SignalSystematics:
      FillNormalizationSystematics(m_sysMap);
      FillShapeSystematics(m_sysMap);
      FillSigTheoryPdfSystematics(m_sysMap);
      FillSigTheoryQcdSystematics(m_sysMap);
      m_sysMap[ Syst::VAR_TH_QCD_Scale_VBF        ] = "Theory_QCD_Scale_VBF"       ;
      m_sysMap[ Syst::VAR_TH_QCD_Scale_VH         ] = "Theory_QCD_Scale_VH"        ;
      m_sysMap[ Syst::VAR_TH_QCD_Scale_ttH        ] = "Theory_QCD_Scale_ttH"       ;
      m_sysMap[ Syst::VAR_TH_Var3c                ] = "Theory_Shower_Var3c__1down" ;
      m_sysMap[ Syst::VAR_TH_Var3c+1              ] = "Theory_Shower_Var3c__1up"   ;
      m_sysMap[ Syst::VAR_TH_hard                 ] = "Theory_Shower_hard__1down"  ;
      m_sysMap[ Syst::VAR_TH_hard+1               ] = "Theory_Shower_hard__1up"    ;
      m_sysMap[ Syst::VAR_TH_Shower_ISRFSR        ] = "Theory_Shower_ISRFSR"       ;
      m_sysMap[ Syst::VAR_TH_Shower_Herwig_ggHbbH ] = "Theory_Shower_Herwig_ggHbbH";
      m_sysMap[ Syst::VAR_TH_Shower_Herwig_VBF    ] = "Theory_Shower_Herwig_VBF"   ;
      m_sysMap[ Syst::VAR_TH_Shower_Herwig_VH     ] = "Theory_Shower_Herwig_VH"    ;
      m_sysMap[ Syst::VAR_TH_Shower_Herwig_ttHtH  ] = "Theory_Shower_Herwig_ttHtH" ;
      FillSignalCompositionSystematics(m_sysMap);
      break;
    case Syst::qqZZSystematics:
      FillNormalizationSystematics(m_sysMap);
      FillShapeSystematics(m_sysMap);
      m_sysMap[ Syst::VAR_TH_qqZZ_Sherpa_CKKW   ] = "Theory_qqZZ_CKKW__1down";
      m_sysMap[ Syst::VAR_TH_qqZZ_Sherpa_CKKW+1 ] = "Theory_qqZZ_CKKW__1up"  ;
      m_sysMap[ Syst::VAR_TH_qqZZ_Sherpa_QSF    ] = "Theory_qqZZ_QSF__1down" ;
      m_sysMap[ Syst::VAR_TH_qqZZ_Sherpa_QSF+1  ] = "Theory_qqZZ_QSF__1up"   ;
      m_sysMap[ Syst::VAR_TH_qqZZ_Sherpa_CSSKIN ] = "Theory_qqZZ_CSSKIN"     ;
      m_sysMap[ Syst::VAR_TH_qqZZ_QCD           ] = "Theory_qqZZ_QCD";
      m_sysMap[ Syst::VAR_TH_qqZZ_PDF           ] = "Theory_qqZZ_PDF";
      break;
    case Syst::ggZZSystematics:
      FillNormalizationSystematics(m_sysMap);
      FillShapeSystematics(m_sysMap);
      break;
    case Syst::ZjetsSystematics:
      m_sysMap[ Syst::ZJET_stat_2l2e    ] = "ZJET_stat_2l2e__1down" ;
      m_sysMap[ Syst::ZJET_stat_2l2e+1  ] = "ZJET_stat_2l2e__1up"   ;
      m_sysMap[ Syst::ZJET_syst_2l2e    ] = "ZJET_syst_2l2e__1down" ;
      m_sysMap[ Syst::ZJET_syst_2l2e+1  ] = "ZJET_syst_2l2e__1up"   ;
      m_sysMap[ Syst::ZJET_stat_2l2mu   ] = "ZJET_stat_2l2mu__1down";
      m_sysMap[ Syst::ZJET_stat_2l2mu+1 ] = "ZJET_stat_2l2mu__1up"  ;
      m_sysMap[ Syst::ZJET_syst_2l2mu   ] = "ZJET_syst_2l2mu__1down";
      m_sysMap[ Syst::ZJET_syst_2l2mu+1 ] = "ZJET_syst_2l2mu__1up"  ;
      break;
    case Syst::ZZTheorySystematics:
      FillZZTheorySystematics(m_sysMap);
      break;
    case Syst::ZZTheoryPart1Systematics:
      FillZZTheoryPart1Systematics(m_sysMap);
      break;
    case Syst::ZZTheoryPart2Systematics:
      FillZZTheoryPart2Systematics(m_sysMap);
      break;
    default:
      PRINT_INFO("<MakeSysMap()>:: No valid systematic set selected -> No sys!!");
    }
    
  }
  return m_sysMap;
  
}

void FillNormalizationSystematics(std::map<short int,std::string> &sysMap){

FillNormPart1Systematics(sysMap);
FillNormPart2Systematics(sysMap);

}

void FillNormPart1Systematics(std::map<short int,std::string> &sysMap){
  
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP0                 ] = "EL_EFF_ID_CorrUncertaintyNP0__1down"               ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP0+1               ] = "EL_EFF_ID_CorrUncertaintyNP0__1up"                 ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP1                 ] = "EL_EFF_ID_CorrUncertaintyNP1__1down"               ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP1+1               ] = "EL_EFF_ID_CorrUncertaintyNP1__1up"                 ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP2                 ] = "EL_EFF_ID_CorrUncertaintyNP2__1down"               ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP2+1               ] = "EL_EFF_ID_CorrUncertaintyNP2__1up"                 ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP3                 ] = "EL_EFF_ID_CorrUncertaintyNP3__1down"               ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP3+1               ] = "EL_EFF_ID_CorrUncertaintyNP3__1up"                 ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP4                 ] = "EL_EFF_ID_CorrUncertaintyNP4__1down"               ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP4+1               ] = "EL_EFF_ID_CorrUncertaintyNP4__1up"                 ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP5                 ] = "EL_EFF_ID_CorrUncertaintyNP5__1down"               ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP5+1               ] = "EL_EFF_ID_CorrUncertaintyNP5__1up"                 ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP6                 ] = "EL_EFF_ID_CorrUncertaintyNP6__1down"               ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP6+1               ] = "EL_EFF_ID_CorrUncertaintyNP6__1up"                 ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP7                 ] = "EL_EFF_ID_CorrUncertaintyNP7__1down"               ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP7+1               ] = "EL_EFF_ID_CorrUncertaintyNP7__1up"                 ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP8                 ] = "EL_EFF_ID_CorrUncertaintyNP8__1down"               ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP8+1               ] = "EL_EFF_ID_CorrUncertaintyNP8__1up"                 ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP9                 ] = "EL_EFF_ID_CorrUncertaintyNP9__1down"               ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP9+1               ] = "EL_EFF_ID_CorrUncertaintyNP9__1up"                 ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP10                ] = "EL_EFF_ID_CorrUncertaintyNP10__1down"              ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP10+1              ] = "EL_EFF_ID_CorrUncertaintyNP10__1up"                ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP11                ] = "EL_EFF_ID_CorrUncertaintyNP11__1down"              ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP11+1              ] = "EL_EFF_ID_CorrUncertaintyNP11__1up"                ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP12                ] = "EL_EFF_ID_CorrUncertaintyNP12__1down"              ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP12+1              ] = "EL_EFF_ID_CorrUncertaintyNP12__1up"                ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP13                ] = "EL_EFF_ID_CorrUncertaintyNP13__1down"              ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP13+1              ] = "EL_EFF_ID_CorrUncertaintyNP13__1up"                ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP14                ] = "EL_EFF_ID_CorrUncertaintyNP14__1down"              ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP14+1              ] = "EL_EFF_ID_CorrUncertaintyNP14__1up"                ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP15                ] = "EL_EFF_ID_CorrUncertaintyNP15__1down"              ;
  sysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP15+1              ] = "EL_EFF_ID_CorrUncertaintyNP15__1up"                ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down"  ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0+1  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up"    ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down"  ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1+1  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up"    ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down"  ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2+1  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up"    ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down"  ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3+1  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up"    ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down"  ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4+1  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up"    ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down"  ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5+1  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up"    ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down"  ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6+1  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up"    ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down"  ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7+1  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up"    ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down"  ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8+1  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up"    ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down"  ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9+1  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up"    ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down" ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up"   ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down" ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up"   ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down" ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up"   ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down" ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up"   ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down" ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up"   ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down" ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up"   ;

}

void FillNormPart2Systematics(std::map<short int,std::string> &sysMap){

  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1down" ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1up"   ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1down" ;
  sysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17+1 ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1up"   ;
  sysMap[ Syst::EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR           ] = "EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down"         ;
  sysMap[ Syst::EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR+1         ] = "EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up"           ;
  sysMap[ Syst::EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR          ] = "EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down"        ;
  sysMap[ Syst::EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR+1        ] = "EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up"          ;
  sysMap[ Syst::FT_EFF_Eigen_B_0                             ] = "FT_EFF_Eigen_B_0__1down"                           ;
  sysMap[ Syst::FT_EFF_Eigen_B_0+1                           ] = "FT_EFF_Eigen_B_0__1up"                             ;
  sysMap[ Syst::FT_EFF_Eigen_B_1                             ] = "FT_EFF_Eigen_B_1__1down"                           ;
  sysMap[ Syst::FT_EFF_Eigen_B_1+1                           ] = "FT_EFF_Eigen_B_1__1up"                             ;
  sysMap[ Syst::FT_EFF_Eigen_B_2                             ] = "FT_EFF_Eigen_B_2__1down"                           ;
  sysMap[ Syst::FT_EFF_Eigen_B_2+1                           ] = "FT_EFF_Eigen_B_2__1up"                             ;
  sysMap[ Syst::FT_EFF_Eigen_C_0                             ] = "FT_EFF_Eigen_C_0__1down"                           ;
  sysMap[ Syst::FT_EFF_Eigen_C_0+1                           ] = "FT_EFF_Eigen_C_0__1up"                             ;
  sysMap[ Syst::FT_EFF_Eigen_C_1                             ] = "FT_EFF_Eigen_C_1__1down"                           ;
  sysMap[ Syst::FT_EFF_Eigen_C_1+1                           ] = "FT_EFF_Eigen_C_1__1up"                             ;
  sysMap[ Syst::FT_EFF_Eigen_C_2                             ] = "FT_EFF_Eigen_C_2__1down"                           ;
  sysMap[ Syst::FT_EFF_Eigen_C_2+1                           ] = "FT_EFF_Eigen_C_2__1up"                             ;
  sysMap[ Syst::FT_EFF_Eigen_C_3                             ] = "FT_EFF_Eigen_C_3__1down"                           ;
  sysMap[ Syst::FT_EFF_Eigen_C_3+1                           ] = "FT_EFF_Eigen_C_3__1up"                             ;
  sysMap[ Syst::FT_EFF_Eigen_Light_0                         ] = "FT_EFF_Eigen_Light_0__1down"                       ;
  sysMap[ Syst::FT_EFF_Eigen_Light_0+1                       ] = "FT_EFF_Eigen_Light_0__1up"                         ;
  sysMap[ Syst::FT_EFF_Eigen_Light_1                         ] = "FT_EFF_Eigen_Light_1__1down"                       ;
  sysMap[ Syst::FT_EFF_Eigen_Light_1+1                       ] = "FT_EFF_Eigen_Light_1__1up"                         ;
  sysMap[ Syst::FT_EFF_Eigen_Light_2                         ] = "FT_EFF_Eigen_Light_2__1down"                       ;
  sysMap[ Syst::FT_EFF_Eigen_Light_2+1                       ] = "FT_EFF_Eigen_Light_2__1up"                         ;
  sysMap[ Syst::FT_EFF_Eigen_Light_3                         ] = "FT_EFF_Eigen_Light_3__1down"                       ;
  sysMap[ Syst::FT_EFF_Eigen_Light_3+1                       ] = "FT_EFF_Eigen_Light_3__1up"                         ;
  sysMap[ Syst::FT_EFF_Eigen_Light_4                         ] = "FT_EFF_Eigen_Light_4__1down"                       ;
  sysMap[ Syst::FT_EFF_Eigen_Light_4+1                       ] = "FT_EFF_Eigen_Light_4__1up"                         ;
  sysMap[ Syst::JET_JvtEfficiency 			     ] = "JET_JvtEfficiency__1down"			     ;
  sysMap[ Syst::JET_JvtEfficiency+1 			     ] = "JET_JvtEfficiency__1up"			     ;
  sysMap[ Syst::JET_fJvtEfficiency 			     ] = "JET_fJvtEfficiency__1down"			     ;
  sysMap[ Syst::JET_fJvtEfficiency+1 			     ] = "JET_fJvtEfficiency__1up"			     ;
  sysMap[ Syst::HOEW_QCD_syst                                ] = "HOEW_QCD_syst__1down"                              ;
  sysMap[ Syst::HOEW_QCD_syst+1                              ] = "HOEW_QCD_syst__1up"                                ;
  sysMap[ Syst::HOEW_syst                                    ] = "HOEW_syst__1down"                                  ;
  sysMap[ Syst::HOEW_syst+1                                  ] = "HOEW_syst__1up"                                    ;
  sysMap[ Syst::HOQCD_scale_syst                             ] = "HOQCD_scale_syst__1down"                           ;
  sysMap[ Syst::HOQCD_scale_syst+1                           ] = "HOQCD_scale_syst__1up"                             ;
  sysMap[ Syst::MUON_EFF_ISO_STAT                            ] = "MUON_EFF_ISO_STAT__1down"                          ;
  sysMap[ Syst::MUON_EFF_ISO_STAT+1                          ] = "MUON_EFF_ISO_STAT__1up"                            ;
  sysMap[ Syst::MUON_EFF_ISO_SYS                             ] = "MUON_EFF_ISO_SYS__1down"                           ;
  sysMap[ Syst::MUON_EFF_ISO_SYS+1                           ] = "MUON_EFF_ISO_SYS__1up"                             ;
  sysMap[ Syst::MUON_EFF_RECO_STAT_LOWPT                     ] = "MUON_EFF_RECO_STAT_LOWPT__1down"                   ;
  sysMap[ Syst::MUON_EFF_RECO_STAT_LOWPT+1                   ] = "MUON_EFF_RECO_STAT_LOWPT__1up"                     ;
  sysMap[ Syst::MUON_EFF_RECO_STAT                           ] = "MUON_EFF_RECO_STAT__1down"                         ;
  sysMap[ Syst::MUON_EFF_RECO_STAT+1                         ] = "MUON_EFF_RECO_STAT__1up"                           ;
  sysMap[ Syst::MUON_EFF_RECO_SYS_LOWPT                      ] = "MUON_EFF_RECO_SYS_LOWPT__1down"                    ;
  sysMap[ Syst::MUON_EFF_RECO_SYS_LOWPT+1                    ] = "MUON_EFF_RECO_SYS_LOWPT__1up"                      ;
  sysMap[ Syst::MUON_EFF_RECO_SYS                            ] = "MUON_EFF_RECO_SYS__1down"                          ;
  sysMap[ Syst::MUON_EFF_RECO_SYS+1                          ] = "MUON_EFF_RECO_SYS__1up"                            ;
  sysMap[ Syst::MUON_EFF_TTVA_STAT                           ] = "MUON_EFF_TTVA_STAT__1down"                         ;
  sysMap[ Syst::MUON_EFF_TTVA_STAT+1                         ] = "MUON_EFF_TTVA_STAT__1up"                           ;
  sysMap[ Syst::MUON_EFF_TTVA_SYS                            ] = "MUON_EFF_TTVA_SYS__1down"                          ;
  sysMap[ Syst::MUON_EFF_TTVA_SYS+1                          ] = "MUON_EFF_TTVA_SYS__1up"                            ;
  sysMap[ Syst::PRW_DATASF                                   ] = "PRW_DATASF__1down"                                 ;
  sysMap[ Syst::PRW_DATASF+1                                 ] = "PRW_DATASF__1up"                                   ;
  
}

void FillShapeSystematics(std::map<short int,std::string> &sysMap){

  FillShapePart1Systematics(sysMap);
  FillShapePart2Systematics(sysMap);
  FillShapePart3Systematics(sysMap);
  
}

void FillShapePart1Systematics(std::map<short int,std::string> &sysMap){
  
  sysMap[ Syst::EG_RESOLUTION_ALL                           ] = "EG_RESOLUTION_ALL__1down"                         ;
  sysMap[ Syst::EG_RESOLUTION_ALL+1                         ] = "EG_RESOLUTION_ALL__1up"			   ;
  /* old sys 
     sysMap[ Syst::EG_SCALE_ALLCORR                            ] = "EG_SCALE_ALLCORR__1down"			   ;
     sysMap[ Syst::EG_SCALE_ALLCORR+1		            ] = "EG_SCALE_ALLCORR__1up"			           ;
     sysMap[ Syst::EG_SCALE_E4SCINTILLATOR                     ] = "EG_SCALE_E4SCINTILLATOR__1down"		   ;
     sysMap[ Syst::EG_SCALE_E4SCINTILLATOR+1		    ] = "EG_SCALE_E4SCINTILLATOR__1up"                     ;
  */
  sysMap[ Syst::EG_SCALE_AF2                                ] = "EG_SCALE_AF2__1down"                              ;
  sysMap[ Syst::EG_SCALE_AF2+1                              ] = "EG_SCALE_AF2__1up"                                ;
  sysMap[ Syst::EG_SCALE_ALL                                ] = "EG_SCALE_ALL__1down"			           ;
  sysMap[ Syst::EG_SCALE_ALL+1		                    ] = "EG_SCALE_ALL__1up"			           ;
  /* not used anymore
     sysMap[ Syst::EG_SCALE_LARCALIB_EXTRA2015PRE	    ] = "EG_SCALE_LARCALIB_EXTRA2015PRE__1down"	           ;
     sysMap[ Syst::EG_SCALE_LARCALIB_EXTRA2015PRE+1	    ] = "EG_SCALE_LARCALIB_EXTRA2015PRE__1up"	           ;
     sysMap[ Syst::EG_SCALE_LARTEMPERATURE_EXTRA2015PRE      ] = "EG_SCALE_LARTEMPERATURE_EXTRA2015PRE__1down"      ;
     sysMap[ Syst::EG_SCALE_LARTEMPERATURE_EXTRA2015PRE+1    ] = "EG_SCALE_LARTEMPERATURE_EXTRA2015PRE__1up"	   ;
     sysMap[ Syst::EG_SCALE_LARTEMPERATURE_EXTRA2016PRE	    ] = "EG_SCALE_LARTEMPERATURE_EXTRA2016PRE__1down"      ;
     sysMap[ Syst::EG_SCALE_LARTEMPERATURE_EXTRA2016PRE+1    ] = "EG_SCALE_LARTEMPERATURE_EXTRA2016PRE__1up"	   ;
  */
  sysMap[ Syst::JET_BJES_Response 			    ] = "JET_BJES_Response__1down"			   ;
  sysMap[ Syst::JET_BJES_Response+1			    ] = "JET_BJES_Response__1up"			   ;
  sysMap[ Syst::JET_EffectiveNP_1 			    ] = "JET_EffectiveNP_1__1down"			   ;
  sysMap[ Syst::JET_EffectiveNP_1+1			    ] = "JET_EffectiveNP_1__1up"			   ;
  sysMap[ Syst::JET_EffectiveNP_2 			    ] = "JET_EffectiveNP_2__1down"			   ;
  sysMap[ Syst::JET_EffectiveNP_2+1			    ] = "JET_EffectiveNP_2__1up"			   ;
  sysMap[ Syst::JET_EffectiveNP_3 			    ] = "JET_EffectiveNP_3__1down"			   ;
  sysMap[ Syst::JET_EffectiveNP_3+1			    ] = "JET_EffectiveNP_3__1up"			   ;
  sysMap[ Syst::JET_EffectiveNP_4 			    ] = "JET_EffectiveNP_4__1down"			   ;
  sysMap[ Syst::JET_EffectiveNP_4+1			    ] = "JET_EffectiveNP_4__1up"			   ;
  sysMap[ Syst::JET_EffectiveNP_5 			    ] = "JET_EffectiveNP_5__1down"			   ;
  sysMap[ Syst::JET_EffectiveNP_5+1			    ] = "JET_EffectiveNP_5__1up"			   ;
  sysMap[ Syst::JET_EffectiveNP_6 			    ] = "JET_EffectiveNP_6__1down"			   ;
  sysMap[ Syst::JET_EffectiveNP_6+1			    ] = "JET_EffectiveNP_6__1up"			   ;
  sysMap[ Syst::JET_EffectiveNP_7 			    ] = "JET_EffectiveNP_7__1down"			   ;
  sysMap[ Syst::JET_EffectiveNP_7+1			    ] = "JET_EffectiveNP_7__1up"			   ;
  sysMap[ Syst::JET_EffectiveNP_8restTerm 		    ] = "JET_EffectiveNP_8restTerm__1down"		   ;
  sysMap[ Syst::JET_EffectiveNP_8restTerm+1		    ] = "JET_EffectiveNP_8restTerm__1up"		   ;
  sysMap[ Syst::JET_EtaIntercalibration_Modelling 	    ] = "JET_EtaIntercalibration_Modelling__1down"	   ;
  sysMap[ Syst::JET_EtaIntercalibration_Modelling+1	    ] = "JET_EtaIntercalibration_Modelling__1up"	   ;
  sysMap[ Syst::JET_EtaIntercalibration_NonClosure_highE    ] = "JET_EtaIntercalibration_NonClosure_highE__1down"  ;
  sysMap[ Syst::JET_EtaIntercalibration_NonClosure_highE+1  ] = "JET_EtaIntercalibration_NonClosure_highE__1up"	   ;
  sysMap[ Syst::JET_EtaIntercalibration_NonClosure_negEta   ] = "JET_EtaIntercalibration_NonClosure_negEta__1down" ;
  sysMap[ Syst::JET_EtaIntercalibration_NonClosure_negEta+1 ] = "JET_EtaIntercalibration_NonClosure_negEta__1up"   ;
  sysMap[ Syst::JET_EtaIntercalibration_NonClosure_posEta   ] = "JET_EtaIntercalibration_NonClosure_posEta__1down" ;
  sysMap[ Syst::JET_EtaIntercalibration_NonClosure_posEta+1 ] = "JET_EtaIntercalibration_NonClosure_posEta__1up"   ;
  sysMap[ Syst::JET_EtaIntercalibration_TotalStat 	    ] = "JET_EtaIntercalibration_TotalStat__1down"	   ;
  sysMap[ Syst::JET_EtaIntercalibration_TotalStat+1	    ] = "JET_EtaIntercalibration_TotalStat__1up"	   ;

}

void FillShapePart2Systematics(std::map<short int,std::string> &sysMap){
  
  sysMap[ Syst::JET_JER_DataVsMC                            ] = "JET_JER_DataVsMC__1down"                          ;
  //sysMap[ Syst::JET_JER_DataVsMC+1                          ] = "JET_JER_DataVsMC__1up"                            ;
  sysMap[ Syst::JET_JER_EffectiveNP_1                       ] = "JET_JER_EffectiveNP_1__1down"                     ;
  //sysMap[ Syst::JET_JER_EffectiveNP_1+1                     ] = "JET_JER_EffectiveNP_1__1up"                       ;
  sysMap[ Syst::JET_JER_EffectiveNP_2                       ] = "JET_JER_EffectiveNP_2__1down"                     ;
  //sysMap[ Syst::JET_JER_EffectiveNP_2+1                     ] = "JET_JER_EffectiveNP_2__1up"                       ;
  sysMap[ Syst::JET_JER_EffectiveNP_3                       ] = "JET_JER_EffectiveNP_3__1down"                     ;
  //sysMap[ Syst::JET_JER_EffectiveNP_3+1                     ] = "JET_JER_EffectiveNP_3__1up"                       ;
  sysMap[ Syst::JET_JER_EffectiveNP_4                       ] = "JET_JER_EffectiveNP_4__1down"                     ;
  //sysMap[ Syst::JET_JER_EffectiveNP_4+1                     ] = "JET_JER_EffectiveNP_4__1up"                       ;
  sysMap[ Syst::JET_JER_EffectiveNP_5                       ] = "JET_JER_EffectiveNP_5__1down"                     ;
  //sysMap[ Syst::JET_JER_EffectiveNP_5+1                     ] = "JET_JER_EffectiveNP_5__1up"                       ;
  sysMap[ Syst::JET_JER_EffectiveNP_6                       ] = "JET_JER_EffectiveNP_6__1down"                     ;
  //sysMap[ Syst::JET_JER_EffectiveNP_6+1                     ] = "JET_JER_EffectiveNP_6__1up"                       ;
  sysMap[ Syst::JET_JER_EffectiveNP_7restTerm               ] = "JET_JER_EffectiveNP_7restTerm__1down"             ;
  //sysMap[ Syst::JET_JER_EffectiveNP_7restTerm+1             ] = "JET_JER_EffectiveNP_7restTerm__1up"               ;
  sysMap[ Syst::JET_Pileup_OffsetMu  			    ] = "JET_Pileup_OffsetMu__1down"		           ;
  sysMap[ Syst::JET_Pileup_OffsetMu+1			    ] = "JET_Pileup_OffsetMu__1up"			   ;
  sysMap[ Syst::JET_Pileup_OffsetNPV       		    ] = "JET_Pileup_OffsetNPV__1down"		           ;
  sysMap[ Syst::JET_Pileup_OffsetNPV+1			    ] = "JET_Pileup_OffsetNPV__1up"			   ;
  sysMap[ Syst::JET_Pileup_PtTerm 			    ] = "JET_Pileup_PtTerm__1down"			   ;
  sysMap[ Syst::JET_Pileup_PtTerm+1			    ] = "JET_Pileup_PtTerm__1up"			   ;
  sysMap[ Syst::JET_Pileup_RhoTopology     		    ] = "JET_Pileup_RhoTopology__1down"		           ;
  sysMap[ Syst::JET_Pileup_RhoTopology+1		    ] = "JET_Pileup_RhoTopology__1up"		           ;
  sysMap[ Syst::JET_PunchThrough_MC16     		    ] = "JET_PunchThrough_MC16__1down"		           ;
  sysMap[ Syst::JET_PunchThrough_MC16+1			    ] = "JET_PunchThrough_MC16__1up"		           ;
  sysMap[ Syst::JET_SingleParticle_HighPt 		    ] = "JET_SingleParticle_HighPt__1down"		   ;
  sysMap[ Syst::JET_SingleParticle_HighPt+1		    ] = "JET_SingleParticle_HighPt__1up"		   ;
  sysMap[ Syst::MUON_ID  				    ] = "MUON_ID__1down"				   ;
  sysMap[ Syst::MUON_ID+1				    ] = "MUON_ID__1up"				           ;
  sysMap[ Syst::MUON_MS  				    ] = "MUON_MS__1down"				   ;
  sysMap[ Syst::MUON_MS+1				    ] = "MUON_MS__1up"				           ;
  sysMap[ Syst::MUON_SAGITTA_RESBIAS			    ] = "MUON_SAGITTA_RESBIAS__1down"			   ;
  sysMap[ Syst::MUON_SAGITTA_RESBIAS+1			    ] = "MUON_SAGITTA_RESBIAS__1up"			   ;
  sysMap[ Syst::MUON_SAGITTA_RHO	        	    ] = "MUON_SAGITTA_RHO__1down"			   ;
  sysMap[ Syst::MUON_SAGITTA_RHO+1			    ] = "MUON_SAGITTA_RHO__1up"			           ;
  sysMap[ Syst::MUON_SCALE       			    ] = "MUON_SCALE__1down"			           ;
  sysMap[ Syst::MUON_SCALE+1				    ] = "MUON_SCALE__1up"				   ;
  
}

void FillShapePart3Systematics(std::map<short int,std::string> &sysMap){
  
  sysMap[ Syst::JET_Flavor_Composition_ggHbbH               ] = "JET_Flavor_Composition_ggHbbH__1down"             ;
  sysMap[ Syst::JET_Flavor_Composition_ggHbbH+1             ] = "JET_Flavor_Composition_ggHbbH__1up"               ;
  sysMap[ Syst::JET_Flavor_Composition_VBF                  ] = "JET_Flavor_Composition_VBF__1down"                ;
  sysMap[ Syst::JET_Flavor_Composition_VBF+1                ] = "JET_Flavor_Composition_VBF__1up"                  ;
  sysMap[ Syst::JET_Flavor_Composition_VH                   ] = "JET_Flavor_Composition_VH__1down"                 ;
  sysMap[ Syst::JET_Flavor_Composition_VH+1                 ] = "JET_Flavor_Composition_VH__1up"                   ;
  sysMap[ Syst::JET_Flavor_Composition_ttHtH                ] = "JET_Flavor_Composition_ttHtH__1down"              ;
  sysMap[ Syst::JET_Flavor_Composition_ttHtH+1              ] = "JET_Flavor_Composition_ttHtH__1up"                ;
  sysMap[ Syst::JET_Flavor_Composition_ZZ                   ] = "JET_Flavor_Composition_ZZ__1down"                 ;
  sysMap[ Syst::JET_Flavor_Composition_ZZ+1                 ] = "JET_Flavor_Composition_ZZ__1up"                   ;
  sysMap[ Syst::JET_Flavor_Response_ggHbbH                  ] = "JET_Flavor_Response_ggHbbH__1down"                ;
  sysMap[ Syst::JET_Flavor_Response_ggHbbH+1                ] = "JET_Flavor_Response_ggHbbH__1up"                  ;
  sysMap[ Syst::JET_Flavor_Response_VBF                     ] = "JET_Flavor_Response_VBF__1down"                   ;
  sysMap[ Syst::JET_Flavor_Response_VBF+1                   ] = "JET_Flavor_Response_VBF__1up"                     ;
  sysMap[ Syst::JET_Flavor_Response_VH                      ] = "JET_Flavor_Response_VH__1down"                    ;
  sysMap[ Syst::JET_Flavor_Response_VH+1                    ] = "JET_Flavor_Response_VH__1up"                      ;
  sysMap[ Syst::JET_Flavor_Response_ttHtH                   ] = "JET_Flavor_Response_ttHtH__1down"                 ;
  sysMap[ Syst::JET_Flavor_Response_ttHtH+1                 ] = "JET_Flavor_Response_ttHtH__1up"                   ;
  sysMap[ Syst::JET_Flavor_Response_ZZ                      ] = "JET_Flavor_Response_ZZ__1down"                    ;
  sysMap[ Syst::JET_Flavor_Response_ZZ+1                    ] = "JET_Flavor_Response_ZZ__1up"                      ;
  //sysMap[ Syst::JET_Flavor_Composition    		    ] = "JET_Flavor_Composition__1down"		           ;
  //sysMap[ Syst::JET_Flavor_Composition+1	   	    ] = "JET_Flavor_Composition__1up"		           ;
  //sysMap[ Syst::JET_Flavor_Response			    ] = "JET_Flavor_Response__1down"		           ;
  //sysMap[ Syst::JET_Flavor_Response+1			    ] = "JET_Flavor_Response__1up"			   ;

}

void FillSigTheoryScaleSystematics(std::map<short int,std::string> &sysMap){

  FillSigTheoryScalePart1Systematics(sysMap);
  FillSigTheoryScalePart2Systematics(sysMap);
  FillSigTheoryScalePart3Systematics(sysMap);
  //sysMap[ Syst::VAR_TH_muR0p5_muF0p5       ] = "Theory_muR0p5_muF0p5";
  //sysMap[ Syst::VAR_TH_muR0p5_muF1p0       ] = "Theory_muR0p5_muF1p0";
  //sysMap[ Syst::VAR_TH_muR0p5_muF2p0       ] = "Theory_muR0p5_muF2p0";
  //sysMap[ Syst::VAR_TH_muR1p0_muF0p5       ] = "Theory_muR1p0_muF0p5";
  //sysMap[ Syst::VAR_TH_muR1p0_muF2p0       ] = "Theory_muR1p0_muF2p0";
  //sysMap[ Syst::VAR_TH_muR2p0_muF0p5       ] = "Theory_muR2p0_muF0p5";
  //sysMap[ Syst::VAR_TH_muR2p0_muF1p0       ] = "Theory_muR2p0_muF1p0";
  //sysMap[ Syst::VAR_TH_muR2p0_muF2p0       ] = "Theory_muR2p0_muF2p0";

}

void FillSigTheoryScalePart1Systematics(std::map<short int,std::string> &sysMap){

  sysMap[ Syst::VAR_TH_muR0p5_muF0p5_VBF ] = "Theory_muR0p5_muF0p5_VBF";
  sysMap[ Syst::VAR_TH_muR0p5_muF1p0_VBF ] = "Theory_muR0p5_muF1p0_VBF";
  sysMap[ Syst::VAR_TH_muR0p5_muF2p0_VBF ] = "Theory_muR0p5_muF2p0_VBF";
  sysMap[ Syst::VAR_TH_muR1p0_muF0p5_VBF ] = "Theory_muR1p0_muF0p5_VBF";
  sysMap[ Syst::VAR_TH_muR1p0_muF2p0_VBF ] = "Theory_muR1p0_muF2p0_VBF";
  sysMap[ Syst::VAR_TH_muR2p0_muF0p5_VBF ] = "Theory_muR2p0_muF0p5_VBF";
  sysMap[ Syst::VAR_TH_muR2p0_muF1p0_VBF ] = "Theory_muR2p0_muF1p0_VBF";
  sysMap[ Syst::VAR_TH_muR2p0_muF2p0_VBF ] = "Theory_muR2p0_muF2p0_VBF";
  
}

void FillSigTheoryScalePart2Systematics(std::map<short int,std::string> &sysMap){

  sysMap[ Syst::VAR_TH_muR0p5_muF0p5_VH  ] = "Theory_muR0p5_muF0p5_VH" ;
  sysMap[ Syst::VAR_TH_muR0p5_muF1p0_VH  ] = "Theory_muR0p5_muF1p0_VH" ;
  sysMap[ Syst::VAR_TH_muR0p5_muF2p0_VH  ] = "Theory_muR0p5_muF2p0_VH" ;
  sysMap[ Syst::VAR_TH_muR1p0_muF0p5_VH  ] = "Theory_muR1p0_muF0p5_VH" ;
  sysMap[ Syst::VAR_TH_muR1p0_muF2p0_VH  ] = "Theory_muR1p0_muF2p0_VH" ;
  sysMap[ Syst::VAR_TH_muR2p0_muF0p5_VH  ] = "Theory_muR2p0_muF0p5_VH" ;
  sysMap[ Syst::VAR_TH_muR2p0_muF1p0_VH  ] = "Theory_muR2p0_muF1p0_VH" ;
  sysMap[ Syst::VAR_TH_muR2p0_muF2p0_VH  ] = "Theory_muR2p0_muF2p0_VH" ;
  
}

void FillSigTheoryScalePart3Systematics(std::map<short int,std::string> &sysMap){

  sysMap[ Syst::VAR_TH_muR0p5_muF0p5_ttH ] = "Theory_muR0p5_muF0p5_ttH";
  sysMap[ Syst::VAR_TH_muR0p5_muF1p0_ttH ] = "Theory_muR0p5_muF1p0_ttH";
  sysMap[ Syst::VAR_TH_muR0p5_muF2p0_ttH ] = "Theory_muR0p5_muF2p0_ttH";
  sysMap[ Syst::VAR_TH_muR1p0_muF0p5_ttH ] = "Theory_muR1p0_muF0p5_ttH";
  sysMap[ Syst::VAR_TH_muR1p0_muF2p0_ttH ] = "Theory_muR1p0_muF2p0_ttH";
  sysMap[ Syst::VAR_TH_muR2p0_muF0p5_ttH ] = "Theory_muR2p0_muF0p5_ttH";
  sysMap[ Syst::VAR_TH_muR2p0_muF1p0_ttH ] = "Theory_muR2p0_muF1p0_ttH";
  sysMap[ Syst::VAR_TH_muR2p0_muF2p0_ttH ] = "Theory_muR2p0_muF2p0_ttH";
    
}

void FillSigTheoryPdfSystematics(std::map<short int,std::string> &sysMap){

  FillSigTheoryPdfPart1Systematics(sysMap);
  FillSigTheoryPdfPart2Systematics(sysMap);
  FillSigTheoryPdfPart3Systematics(sysMap);
  FillSigTheoryPdfPart4Systematics(sysMap);

}

void FillSigTheoryPdfPart1Systematics(std::map<short int,std::string> &sysMap){

  sysMap[ Syst::VAR_TH_pdf_90400           ] = "Theory_pdf_90400"    ;
  sysMap[ Syst::VAR_TH_pdf_90401           ] = "Theory_pdf_90401"    ;
  sysMap[ Syst::VAR_TH_pdf_90402           ] = "Theory_pdf_90402"    ;
  sysMap[ Syst::VAR_TH_pdf_90403           ] = "Theory_pdf_90403"    ;
  sysMap[ Syst::VAR_TH_pdf_90404           ] = "Theory_pdf_90404"    ;
  sysMap[ Syst::VAR_TH_pdf_90405           ] = "Theory_pdf_90405"    ;
  sysMap[ Syst::VAR_TH_pdf_90406           ] = "Theory_pdf_90406"    ;
  sysMap[ Syst::VAR_TH_pdf_90407           ] = "Theory_pdf_90407"    ;

}

void FillSigTheoryPdfPart2Systematics(std::map<short int,std::string> &sysMap){
  
  sysMap[ Syst::VAR_TH_pdf_90408           ] = "Theory_pdf_90408"    ;
  sysMap[ Syst::VAR_TH_pdf_90409           ] = "Theory_pdf_90409"    ;
  sysMap[ Syst::VAR_TH_pdf_90410           ] = "Theory_pdf_90410"    ;
  sysMap[ Syst::VAR_TH_pdf_90411           ] = "Theory_pdf_90411"    ;
  sysMap[ Syst::VAR_TH_pdf_90412           ] = "Theory_pdf_90412"    ;
  sysMap[ Syst::VAR_TH_pdf_90413           ] = "Theory_pdf_90413"    ;
  sysMap[ Syst::VAR_TH_pdf_90414           ] = "Theory_pdf_90414"    ;
  sysMap[ Syst::VAR_TH_pdf_90415           ] = "Theory_pdf_90415"    ;
  sysMap[ Syst::VAR_TH_pdf_90416           ] = "Theory_pdf_90416"    ;
  
}

void FillSigTheoryPdfPart3Systematics(std::map<short int,std::string> &sysMap){
  
  sysMap[ Syst::VAR_TH_pdf_90417           ] = "Theory_pdf_90417"    ;
  sysMap[ Syst::VAR_TH_pdf_90418           ] = "Theory_pdf_90418"    ;
  sysMap[ Syst::VAR_TH_pdf_90419           ] = "Theory_pdf_90419"    ;
  sysMap[ Syst::VAR_TH_pdf_90420           ] = "Theory_pdf_90420"    ;
  sysMap[ Syst::VAR_TH_pdf_90421           ] = "Theory_pdf_90421"    ;
  sysMap[ Syst::VAR_TH_pdf_90422           ] = "Theory_pdf_90422"    ;
  sysMap[ Syst::VAR_TH_pdf_90423           ] = "Theory_pdf_90423"    ;
  sysMap[ Syst::VAR_TH_pdf_90424           ] = "Theory_pdf_90424"    ;
  
}

void FillSigTheoryPdfPart4Systematics(std::map<short int,std::string> &sysMap){
  
  sysMap[ Syst::VAR_TH_pdf_90425           ] = "Theory_pdf_90425"    ;
  sysMap[ Syst::VAR_TH_pdf_90426           ] = "Theory_pdf_90426"    ;
  sysMap[ Syst::VAR_TH_pdf_90427           ] = "Theory_pdf_90427"    ;
  sysMap[ Syst::VAR_TH_pdf_90428           ] = "Theory_pdf_90428"    ;
  sysMap[ Syst::VAR_TH_pdf_90429           ] = "Theory_pdf_90429"    ;
  sysMap[ Syst::VAR_TH_pdf_90430           ] = "Theory_pdf_90430"    ;
  sysMap[ Syst::VAR_TH_pdf_90431           ] = "Theory_pdf_90431"    ;
  sysMap[ Syst::VAR_TH_pdf_90432           ] = "Theory_pdf_90432"    ;
  
}

void FillSigTheoryQcdSystematics(std::map<short int,std::string> &sysMap){

  FillSigTheoryQcdPart1Systematics(sysMap);
  FillSigTheoryQcdPart2Systematics(sysMap);
  
}

void FillSigTheoryQcdPart1Systematics(std::map<short int,std::string> &sysMap){
  
  sysMap[ Syst::VAR_TH_ggF_qcd_2017_pTH120 ] = "QCDscale_ggF_pTH120" ;
  sysMap[ Syst::VAR_TH_ggF_qcd_2017_pTH60  ] = "QCDscale_ggF_pTH60"  ;
  sysMap[ Syst::VAR_TH_qcd_wg1_mig01       ] = "QCDscale_ggF_mig01"  ;
  sysMap[ Syst::VAR_TH_qcd_wg1_mig12       ] = "QCDscale_ggF_mig12"  ;
  sysMap[ Syst::VAR_TH_qcd_wg1_mu          ] = "QCDscale_ggF_H4l"    ;
  
}

void FillSigTheoryQcdPart2Systematics(std::map<short int,std::string> &sysMap){

  sysMap[ Syst::VAR_TH_qcd_wg1_qm_t        ] = "QCDscale_ggF_qm_t"   ;
  sysMap[ Syst::VAR_TH_qcd_wg1_res         ] = "QCDres_ggF"          ;
  sysMap[ Syst::VAR_TH_qcd_wg1_vbf2j       ] = "QCDscale_ggF_vbf2j"  ;
  sysMap[ Syst::VAR_TH_qcd_wg1_vbf3j       ] = "QCDscale_ggF_vbf3j"  ;
  sysMap[ Syst::VAR_TH_ggF_QCD_pTH_nJ0     ] = "QCDScale_ggF_nJ0"    ;
  
}

void FillSigTheoryQcdPart3Systematics(std::map<short int,std::string> &sysMap){

  sysMap[ Syst::VAR_TH_QCD_Scale_Nominal_VBF ] = "Theory_QCD_Scale_Nominal_VBF";
  sysMap[ Syst::VAR_TH_QCD_Scale_Nominal_VH  ] = "Theory_QCD_Scale_Nominal_VH" ;
  sysMap[ Syst::VAR_TH_QCD_Scale_Nominal_ttH ] = "Theory_QCD_Scale_Nominal_ttH";
  sysMap[ Syst::VAR_TH_PDF_Nominal           ] = "Theory_PDF_Nominal"          ;
  
}

void FillSignalShowerSystematics(std::map<short int,std::string> &sysMap){

  FillSignalShowerPart1Systematics(sysMap);
  FillSignalShowerPart2Systematics(sysMap);
  FillSignalShowerPart3Systematics(sysMap);
  
}

void FillSignalShowerPart1Systematics(std::map<short int,std::string> &sysMap){
  
  sysMap[ Syst::VAR_TH_Var3c                         ] = "Theory_Shower_Var3c__1down"                 ;
  sysMap[ Syst::VAR_TH_Var3c+1		             ] = "Theory_Shower_Var3c__1up"                   ;
  sysMap[ Syst::VAR_TH_hard                          ] = "Theory_Shower_hard__1down"                  ;
  sysMap[ Syst::VAR_TH_hard+1                        ] = "Theory_Shower_hard__1up"                    ;
  sysMap[ Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_0p5   ] = "Theory_Shower_isrmuRfac_0p5_fsrmuRfac_0p5"  ;
  sysMap[ Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_1p0   ] = "Theory_Shower_isrmuRfac_0p5_fsrmuRfac_1p0"  ;
  sysMap[ Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_2p0   ] = "Theory_Shower_isrmuRfac_0p5_fsrmuRfac_2p0"  ;
  sysMap[ Syst::VAR_TH_isrmuRfac_0p625_fsrmuRfac_1p0 ] = "Theory_Shower_isrmuRfac_0p625_fsrmuRfac_1p0";
  
}

void FillSignalShowerPart2Systematics(std::map<short int,std::string> &sysMap){
  
  sysMap[ Syst::VAR_TH_isrmuRfac_0p75_fsrmuRfac_1p0  ] = "Theory_Shower_isrmuRfac_0p75_fsrmuRfac_1p0" ;
  sysMap[ Syst::VAR_TH_isrmuRfac_0p875_fsrmuRfac_1p0 ] = "Theory_Shower_isrmuRfac_0p875_fsrmuRfac_1p0";
  sysMap[ Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p5   ] = "Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p5"  ;
  sysMap[ Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p625 ] = "Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p625";
  sysMap[ Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p75  ] = "Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p75" ;
  sysMap[ Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p875 ] = "Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p875";
  sysMap[ Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p25  ] = "Theory_Shower_isrmuRfac_1p0_fsrmuRfac_1p25" ;
  sysMap[ Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p5   ] = "Theory_Shower_isrmuRfac_1p0_fsrmuRfac_1p5"  ;
  
}

void FillSignalShowerPart3Systematics(std::map<short int,std::string> &sysMap){

  sysMap[ Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p75  ] = "Theory_Shower_isrmuRfac_1p0_fsrmuRfac_1p75" ;
  sysMap[ Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_2p0   ] = "Theory_Shower_isrmuRfac_1p0_fsrmuRfac_2p0"  ;
  sysMap[ Syst::VAR_TH_isrmuRfac_1p25_fsrmuRfac_1p0  ] = "Theory_Shower_isrmuRfac_1p25_fsrmuRfac_1p0" ;
  sysMap[ Syst::VAR_TH_isrmuRfac_1p5_fsrmuRfac_1p0   ] = "Theory_Shower_isrmuRfac_1p5_fsrmuRfac_1p0"  ;
  sysMap[ Syst::VAR_TH_isrmuRfac_1p75_fsrmuRfac_1p0  ] = "Theory_Shower_isrmuRfac_1p75_fsrmuRfac_1p0" ;
  sysMap[ Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_0p5   ] = "Theory_Shower_isrmuRfac_2p0_fsrmuRfac_0p5"  ;
  sysMap[ Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_1p0   ] = "Theory_Shower_isrmuRfac_2p0_fsrmuRfac_1p0"  ;
  sysMap[ Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_2p0   ] = "Theory_Shower_isrmuRfac_2p0_fsrmuRfac_2p0"  ;
  
}

void FillSignalShowerHerwigSystematics(std::map<short int,std::string> &sysMap){
  
  sysMap[ Syst::VAR_TH_Shower_Herwig_Nominal ] = "Theory_Shower_Herwig_Nominal";
  sysMap[ Syst::VAR_TH_Shower_Herwig_ggHbbH  ] = "Theory_Shower_Herwig_ggHbbH" ;
  sysMap[ Syst::VAR_TH_Shower_Herwig_VBF     ] = "Theory_Shower_Herwig_VBF"    ;
  sysMap[ Syst::VAR_TH_Shower_Herwig_VH      ] = "Theory_Shower_Herwig_VH"     ;
  sysMap[ Syst::VAR_TH_Shower_Herwig_ttHtH   ] = "Theory_Shower_Herwig_ttHtH"  ;
  
}

void FillSignalCompositionSystematics(std::map<short int,std::string> &sysMap){

  sysMap[ Syst::SignalComposition_ggHbbH   ] = "SignalComposition_ggHbbH__1down";
  sysMap[ Syst::SignalComposition_ggHbbH+1 ] = "SignalComposition_ggHbbH__1up"  ;
  sysMap[ Syst::SignalComposition_VBF      ] = "SignalComposition_VBF__1down"   ;
  sysMap[ Syst::SignalComposition_VBF+1    ] = "SignalComposition_VBF__1up"     ;
  sysMap[ Syst::SignalComposition_VH       ] = "SignalComposition_VH__1down"    ;
  sysMap[ Syst::SignalComposition_VH+1     ] = "SignalComposition_VH__1up"      ;
  sysMap[ Syst::SignalComposition_ttHtH    ] = "SignalComposition_ttHtH__1down" ;
  sysMap[ Syst::SignalComposition_ttHtH+1  ] = "SignalComposition_ttHtH__1up"   ;
  
}

void FillSignalMassShapeSystematics(std::map<short int,std::string> &sysMap){

  sysMap[ Syst::SignalMassShift           ] = "SignalMassShift__1down"        ;
  sysMap[ Syst::SignalMassShift+1         ] = "SignalMassShift__1up"          ;
  
}

void FillZZTheorySystematics(std::map<short int,std::string> &sysMap){

  FillZZTheoryPart1Systematics(sysMap);
  FillZZTheoryPart2Systematics(sysMap);
  
}

void FillZZTheoryPart1Systematics(std::map<short int,std::string> &sysMap){

  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261000     ] = "Theory_qqZZ_MUR1_MUF1_PDF261000"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261001     ] = "Theory_qqZZ_MUR1_MUF1_PDF261001"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261002     ] = "Theory_qqZZ_MUR1_MUF1_PDF261002"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261003     ] = "Theory_qqZZ_MUR1_MUF1_PDF261003"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261004     ] = "Theory_qqZZ_MUR1_MUF1_PDF261004"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261005     ] = "Theory_qqZZ_MUR1_MUF1_PDF261005"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261006     ] = "Theory_qqZZ_MUR1_MUF1_PDF261006"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261007     ] = "Theory_qqZZ_MUR1_MUF1_PDF261007"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261008     ] = "Theory_qqZZ_MUR1_MUF1_PDF261008"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261009     ] = "Theory_qqZZ_MUR1_MUF1_PDF261009"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261010     ] = "Theory_qqZZ_MUR1_MUF1_PDF261010"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261011     ] = "Theory_qqZZ_MUR1_MUF1_PDF261011"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261012     ] = "Theory_qqZZ_MUR1_MUF1_PDF261012"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261013     ] = "Theory_qqZZ_MUR1_MUF1_PDF261013"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261014     ] = "Theory_qqZZ_MUR1_MUF1_PDF261014"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261015     ] = "Theory_qqZZ_MUR1_MUF1_PDF261015"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261016     ] = "Theory_qqZZ_MUR1_MUF1_PDF261016"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261017     ] = "Theory_qqZZ_MUR1_MUF1_PDF261017"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261018     ] = "Theory_qqZZ_MUR1_MUF1_PDF261018"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261019     ] = "Theory_qqZZ_MUR1_MUF1_PDF261019"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261020     ] = "Theory_qqZZ_MUR1_MUF1_PDF261020"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261021     ] = "Theory_qqZZ_MUR1_MUF1_PDF261021"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261022     ] = "Theory_qqZZ_MUR1_MUF1_PDF261022"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261023     ] = "Theory_qqZZ_MUR1_MUF1_PDF261023"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261024     ] = "Theory_qqZZ_MUR1_MUF1_PDF261024"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261025     ] = "Theory_qqZZ_MUR1_MUF1_PDF261025"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261026     ] = "Theory_qqZZ_MUR1_MUF1_PDF261026"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261027     ] = "Theory_qqZZ_MUR1_MUF1_PDF261027"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261028     ] = "Theory_qqZZ_MUR1_MUF1_PDF261028"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261029     ] = "Theory_qqZZ_MUR1_MUF1_PDF261029"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261030     ] = "Theory_qqZZ_MUR1_MUF1_PDF261030"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261031     ] = "Theory_qqZZ_MUR1_MUF1_PDF261031"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261032     ] = "Theory_qqZZ_MUR1_MUF1_PDF261032"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261033     ] = "Theory_qqZZ_MUR1_MUF1_PDF261033"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261034     ] = "Theory_qqZZ_MUR1_MUF1_PDF261034"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261035     ] = "Theory_qqZZ_MUR1_MUF1_PDF261035"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261036     ] = "Theory_qqZZ_MUR1_MUF1_PDF261036"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261037     ] = "Theory_qqZZ_MUR1_MUF1_PDF261037"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261038     ] = "Theory_qqZZ_MUR1_MUF1_PDF261038"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261039     ] = "Theory_qqZZ_MUR1_MUF1_PDF261039"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261040     ] = "Theory_qqZZ_MUR1_MUF1_PDF261040"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261041     ] = "Theory_qqZZ_MUR1_MUF1_PDF261041"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261042     ] = "Theory_qqZZ_MUR1_MUF1_PDF261042"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261043     ] = "Theory_qqZZ_MUR1_MUF1_PDF261043"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261044     ] = "Theory_qqZZ_MUR1_MUF1_PDF261044"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261045     ] = "Theory_qqZZ_MUR1_MUF1_PDF261045"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261046     ] = "Theory_qqZZ_MUR1_MUF1_PDF261046"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261047     ] = "Theory_qqZZ_MUR1_MUF1_PDF261047"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261048     ] = "Theory_qqZZ_MUR1_MUF1_PDF261048"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261049     ] = "Theory_qqZZ_MUR1_MUF1_PDF261049"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261050     ] = "Theory_qqZZ_MUR1_MUF1_PDF261050"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261051     ] = "Theory_qqZZ_MUR1_MUF1_PDF261051"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261052     ] = "Theory_qqZZ_MUR1_MUF1_PDF261052"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261053     ] = "Theory_qqZZ_MUR1_MUF1_PDF261053"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261054     ] = "Theory_qqZZ_MUR1_MUF1_PDF261054"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261055     ] = "Theory_qqZZ_MUR1_MUF1_PDF261055"    ;
  
}

void FillZZTheoryPart2Systematics(std::map<short int,std::string> &sysMap){
  
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261056     ] = "Theory_qqZZ_MUR1_MUF1_PDF261056"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261057     ] = "Theory_qqZZ_MUR1_MUF1_PDF261057"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261058     ] = "Theory_qqZZ_MUR1_MUF1_PDF261058"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261059     ] = "Theory_qqZZ_MUR1_MUF1_PDF261059"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261060     ] = "Theory_qqZZ_MUR1_MUF1_PDF261060"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261061     ] = "Theory_qqZZ_MUR1_MUF1_PDF261061"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261062     ] = "Theory_qqZZ_MUR1_MUF1_PDF261062"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261063     ] = "Theory_qqZZ_MUR1_MUF1_PDF261063"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261064     ] = "Theory_qqZZ_MUR1_MUF1_PDF261064"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261065     ] = "Theory_qqZZ_MUR1_MUF1_PDF261065"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261066     ] = "Theory_qqZZ_MUR1_MUF1_PDF261066"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261067     ] = "Theory_qqZZ_MUR1_MUF1_PDF261067"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261068     ] = "Theory_qqZZ_MUR1_MUF1_PDF261068"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261069     ] = "Theory_qqZZ_MUR1_MUF1_PDF261069"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261070     ] = "Theory_qqZZ_MUR1_MUF1_PDF261070"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261071     ] = "Theory_qqZZ_MUR1_MUF1_PDF261071"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261072     ] = "Theory_qqZZ_MUR1_MUF1_PDF261072"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261073     ] = "Theory_qqZZ_MUR1_MUF1_PDF261073"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261074     ] = "Theory_qqZZ_MUR1_MUF1_PDF261074"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261075     ] = "Theory_qqZZ_MUR1_MUF1_PDF261075"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261076     ] = "Theory_qqZZ_MUR1_MUF1_PDF261076"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261077     ] = "Theory_qqZZ_MUR1_MUF1_PDF261077"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261078     ] = "Theory_qqZZ_MUR1_MUF1_PDF261078"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261079     ] = "Theory_qqZZ_MUR1_MUF1_PDF261079"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261080     ] = "Theory_qqZZ_MUR1_MUF1_PDF261080"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261081     ] = "Theory_qqZZ_MUR1_MUF1_PDF261081"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261082     ] = "Theory_qqZZ_MUR1_MUF1_PDF261082"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261083     ] = "Theory_qqZZ_MUR1_MUF1_PDF261083"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261084     ] = "Theory_qqZZ_MUR1_MUF1_PDF261084"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261085     ] = "Theory_qqZZ_MUR1_MUF1_PDF261085"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261086     ] = "Theory_qqZZ_MUR1_MUF1_PDF261086"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261087     ] = "Theory_qqZZ_MUR1_MUF1_PDF261087"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261088     ] = "Theory_qqZZ_MUR1_MUF1_PDF261088"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261089     ] = "Theory_qqZZ_MUR1_MUF1_PDF261089"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261090     ] = "Theory_qqZZ_MUR1_MUF1_PDF261090"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261091     ] = "Theory_qqZZ_MUR1_MUF1_PDF261091"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261092     ] = "Theory_qqZZ_MUR1_MUF1_PDF261092"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261093     ] = "Theory_qqZZ_MUR1_MUF1_PDF261093"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261094     ] = "Theory_qqZZ_MUR1_MUF1_PDF261094"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261095     ] = "Theory_qqZZ_MUR1_MUF1_PDF261095"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261096     ] = "Theory_qqZZ_MUR1_MUF1_PDF261096"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261097     ] = "Theory_qqZZ_MUR1_MUF1_PDF261097"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261098     ] = "Theory_qqZZ_MUR1_MUF1_PDF261098"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261099     ] = "Theory_qqZZ_MUR1_MUF1_PDF261099"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261100     ] = "Theory_qqZZ_MUR1_MUF1_PDF261100"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR0p5_MUF0p5_PDF261000 ] = "Theory_qqZZ_MUR0p5_MUF0p5_PDF261000";
  sysMap[ Syst::VAR_TH_qqZZ_MUR0p5_MUF1_PDF261000   ] = "Theory_qqZZ_MUR0p5_MUF1_PDF261000"  ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF0p5_PDF261000   ] = "Theory_qqZZ_MUR1_MUF0p5_PDF261000"  ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR1_MUF2_PDF261000     ] = "Theory_qqZZ_MUR1_MUF2_PDF261000"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR2_MUF1_PDF261000     ] = "Theory_qqZZ_MUR2_MUF1_PDF261000"    ;
  sysMap[ Syst::VAR_TH_qqZZ_MUR2_MUF2_PDF261000     ] = "Theory_qqZZ_MUR2_MUF2_PDF261000"    ;
  sysMap[ Syst::VAR_TH_qqZZ_Sherpa_CKKW             ] = "Theory_qqZZ_CKKW__1down"            ;
  sysMap[ Syst::VAR_TH_qqZZ_Sherpa_CKKW+1           ] = "Theory_qqZZ_CKKW__1up"              ;
  sysMap[ Syst::VAR_TH_qqZZ_Sherpa_QSF              ] = "Theory_qqZZ_QSF__1down"             ;
  sysMap[ Syst::VAR_TH_qqZZ_Sherpa_QSF+1            ] = "Theory_qqZZ_QSF__1up"               ;
  sysMap[ Syst::VAR_TH_qqZZ_Sherpa_CSSKIN           ] = "Theory_qqZZ_CSSKIN"                 ;
  sysMap[ Syst::VAR_TH_qqZZ_Generator_Powheg        ] = "Theory_qqZZ_Generator_Powheg"       ;
  
}
