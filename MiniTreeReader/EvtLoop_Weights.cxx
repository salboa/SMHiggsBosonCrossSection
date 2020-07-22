#include "EventLoop.h"

Double_t EventLoop::GetWeight(){

  PRINT_VERBOSE("<EventLoop::GetWeight()>:: retrieving reco event weight ...");

  Double_t m_w = weight;

  if(m_removeLepWeight) m_w = weight/w_lepEff;
  
  switch(m_SystNum){
    /* Normalization weights */
  case Syst::EL_EFF_ID_CorrUncertaintyNP0                 : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP0__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP0+1               : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP0__1up                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP1                 : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP1__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP1+1               : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP1__1up                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP2                 : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP2__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP2+1               : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP2__1up                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP3                 : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP3__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP3+1               : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP3__1up                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP4                 : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP4__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP4+1               : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP4__1up                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP5                 : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP5__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP5+1               : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP5__1up                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP6                 : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP6__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP6+1               : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP6__1up                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP7                 : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP7__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP7+1               : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP7__1up                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP8                 : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP8__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP8+1               : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP8__1up                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP9                 : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP9__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP9+1               : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP9__1up                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP10                : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP10__1down              ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP10+1              : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP10__1up                ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP11                : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP11__1down              ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP11+1              : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP11__1up                ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP12                : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP12__1down              ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP12+1              : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP12__1up                ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP13                : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP13__1down              ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP13+1              : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP13__1up                ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP14                : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP14__1down              ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP14+1              : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP14__1up                ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP15                : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP15__1down              ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP15+1              : m_w *= wgt_EL_EFF_ID_CorrUncertaintyNP15__1up                ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0    : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0+1  : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up    ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1    : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1+1  : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up    ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2    : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2+1  : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up    ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3    : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3+1  : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up    ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4    : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4+1  : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up    ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5    : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5+1  : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up    ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6    : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6+1  : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up    ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7    : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7+1  : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up    ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8    : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8+1  : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up    ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9    : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9+1  : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up    ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10   : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10+1 : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up   ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11   : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11+1 : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up   ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12   : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12+1 : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up   ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13   : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13+1 : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up   ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14   : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14+1 : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up   ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15   : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15+1 : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up   ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16   : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1down ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16+1 : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1up   ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17   : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1down ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17+1 : m_w *= wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1up   ; break;
  case Syst::EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR           : m_w *= wgt_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down         ; break;
  case Syst::EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR+1         : m_w *= wgt_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up           ; break;
  case Syst::EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR          : m_w *= wgt_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down        ; break;
  case Syst::EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR+1        : m_w *= wgt_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up          ; break;
  case Syst::FT_EFF_Eigen_B_0                             : m_w *= wgt_FT_EFF_Eigen_B_0__1down                           ; break;
  case Syst::FT_EFF_Eigen_B_0+1                           : m_w *= wgt_FT_EFF_Eigen_B_0__1up                             ; break;
  case Syst::FT_EFF_Eigen_B_1                             : m_w *= wgt_FT_EFF_Eigen_B_1__1down                           ; break;
  case Syst::FT_EFF_Eigen_B_1+1                           : m_w *= wgt_FT_EFF_Eigen_B_1__1up                             ; break;
  case Syst::FT_EFF_Eigen_B_2                             : m_w *= wgt_FT_EFF_Eigen_B_2__1down                           ; break;
  case Syst::FT_EFF_Eigen_B_2+1                           : m_w *= wgt_FT_EFF_Eigen_B_2__1up                             ; break;
  case Syst::FT_EFF_Eigen_C_0                             : m_w *= wgt_FT_EFF_Eigen_C_0__1down                           ; break;
  case Syst::FT_EFF_Eigen_C_0+1                           : m_w *= wgt_FT_EFF_Eigen_C_0__1up                             ; break;
  case Syst::FT_EFF_Eigen_C_1                             : m_w *= wgt_FT_EFF_Eigen_C_1__1down                           ; break;
  case Syst::FT_EFF_Eigen_C_1+1                           : m_w *= wgt_FT_EFF_Eigen_C_1__1up                             ; break;
  case Syst::FT_EFF_Eigen_C_2                             : m_w *= wgt_FT_EFF_Eigen_C_2__1down                           ; break;
  case Syst::FT_EFF_Eigen_C_2+1                           : m_w *= wgt_FT_EFF_Eigen_C_2__1up                             ; break;
  case Syst::FT_EFF_Eigen_C_3                             : m_w *= wgt_FT_EFF_Eigen_C_3__1down                           ; break;
  case Syst::FT_EFF_Eigen_C_3+1                           : m_w *= wgt_FT_EFF_Eigen_C_3__1up                             ; break;
  case Syst::FT_EFF_Eigen_Light_0                         : m_w *= wgt_FT_EFF_Eigen_Light_0__1down                       ; break;
  case Syst::FT_EFF_Eigen_Light_0+1                       : m_w *= wgt_FT_EFF_Eigen_Light_0__1up                         ; break;
  case Syst::FT_EFF_Eigen_Light_1                         : m_w *= wgt_FT_EFF_Eigen_Light_1__1down                       ; break;
  case Syst::FT_EFF_Eigen_Light_1+1                       : m_w *= wgt_FT_EFF_Eigen_Light_1__1up                         ; break;
  case Syst::FT_EFF_Eigen_Light_2                         : m_w *= wgt_FT_EFF_Eigen_Light_2__1down                       ; break;
  case Syst::FT_EFF_Eigen_Light_2+1                       : m_w *= wgt_FT_EFF_Eigen_Light_2__1up                         ; break;
  case Syst::FT_EFF_Eigen_Light_3                         : m_w *= wgt_FT_EFF_Eigen_Light_3__1down                       ; break;
  case Syst::FT_EFF_Eigen_Light_3+1                       : m_w *= wgt_FT_EFF_Eigen_Light_3__1up                         ; break;
  case Syst::FT_EFF_Eigen_Light_4                         : m_w *= wgt_FT_EFF_Eigen_Light_4__1down                       ; break;
  case Syst::FT_EFF_Eigen_Light_4+1                       : m_w *= wgt_FT_EFF_Eigen_Light_4__1up                         ; break;
  case Syst::JET_JvtEfficiency                            : m_w *= wgt_JET_JvtEfficiency__1down                          ; break;
  case Syst::JET_JvtEfficiency+1                          : m_w *= wgt_JET_JvtEfficiency__1up                            ; break;
  case Syst::JET_fJvtEfficiency                           : m_w *= wgt_JET_fJvtEfficiency__1down                         ; break;
  case Syst::JET_fJvtEfficiency+1                         : m_w *= wgt_JET_fJvtEfficiency__1up                           ; break;
  case Syst::HOEW_QCD_syst                                : m_w *= wgt_HOEW_QCD_syst__1down                              ; break;
  case Syst::HOEW_QCD_syst+1                              : m_w *= wgt_HOEW_QCD_syst__1up                                ; break;
  case Syst::HOEW_syst                                    : m_w *= wgt_HOEW_syst__1down                                  ; break;
  case Syst::HOEW_syst+1                                  : m_w *= wgt_HOEW_syst__1up                                    ; break;
  case Syst::HOQCD_scale_syst                             : m_w *= wgt_HOQCD_scale_syst__1down                           ; break;
  case Syst::HOQCD_scale_syst+1                           : m_w *= wgt_HOQCD_scale_syst__1up                             ; break;
  case Syst::MUON_EFF_ISO_STAT                            : m_w *= wgt_MUON_EFF_ISO_STAT__1down                          ; break;
  case Syst::MUON_EFF_ISO_STAT+1                          : m_w *= wgt_MUON_EFF_ISO_STAT__1up                            ; break;
  case Syst::MUON_EFF_ISO_SYS                             : m_w *= wgt_MUON_EFF_ISO_SYS__1down                           ; break;
  case Syst::MUON_EFF_ISO_SYS+1                           : m_w *= wgt_MUON_EFF_ISO_SYS__1up                             ; break;
  case Syst::MUON_EFF_RECO_STAT_LOWPT                     : m_w *= wgt_MUON_EFF_RECO_STAT_LOWPT__1down                   ; break;
  case Syst::MUON_EFF_RECO_STAT_LOWPT+1                   : m_w *= wgt_MUON_EFF_RECO_STAT_LOWPT__1up                     ; break;
  case Syst::MUON_EFF_RECO_STAT                           : m_w *= wgt_MUON_EFF_RECO_STAT__1down                         ; break;
  case Syst::MUON_EFF_RECO_STAT+1                         : m_w *= wgt_MUON_EFF_RECO_STAT__1up                           ; break;
  case Syst::MUON_EFF_RECO_SYS_LOWPT                      : m_w *= wgt_MUON_EFF_RECO_SYS_LOWPT__1down                    ; break;
  case Syst::MUON_EFF_RECO_SYS_LOWPT+1                    : m_w *= wgt_MUON_EFF_RECO_SYS_LOWPT__1up                      ; break;
  case Syst::MUON_EFF_RECO_SYS                            : m_w *= wgt_MUON_EFF_RECO_SYS__1down                          ; break;
  case Syst::MUON_EFF_RECO_SYS+1                          : m_w *= wgt_MUON_EFF_RECO_SYS__1up                            ; break;
  case Syst::MUON_EFF_TTVA_STAT                           : m_w *= wgt_MUON_EFF_TTVA_STAT__1down                         ; break;
  case Syst::MUON_EFF_TTVA_STAT+1                         : m_w *= wgt_MUON_EFF_TTVA_STAT__1up                           ; break;
  case Syst::MUON_EFF_TTVA_SYS                            : m_w *= wgt_MUON_EFF_TTVA_SYS__1down                          ; break;
  case Syst::MUON_EFF_TTVA_SYS+1                          : m_w *= wgt_MUON_EFF_TTVA_SYS__1up                            ; break;
  case Syst::PRW_DATASF                                   : m_w *= wgt_PRW_DATASF__1down                                 ; break;
  case Syst::PRW_DATASF+1                                 : m_w *= wgt_PRW_DATASF__1up                                   ; break;
    /* Signal Theory weights */
  case Syst::VAR_TH_muR0p5_muF0p5_VBF:
    if(m_IntProdMode==Process::VBF) m_w *= wgt_var_th_muR0p5_muF0p5;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR0p5_muF0p5_VH:
    if(m_IntProdMode==Process::WH || m_IntProdMode==Process::ZH || m_IntProdMode==Process::ggZH) m_w *= wgt_var_th_muR0p5_muF0p5;
    else                                                                                         m_w *= 1;
    break;
  case Syst::VAR_TH_muR0p5_muF0p5_ttH:
    if(m_IntProdMode==Process::ttH) m_w *= wgt_var_th_muR0p5_muF0p5;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR0p5_muF1p0_VBF:
    if(m_IntProdMode==Process::VBF) m_w *= wgt_var_th_muR0p5_muF1p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR0p5_muF1p0_VH:
    if(m_IntProdMode==Process::WH || m_IntProdMode==Process::ZH || m_IntProdMode==Process::ggZH) m_w *= wgt_var_th_muR0p5_muF1p0;
    else                                                                                         m_w *= 1;
    break;
  case Syst::VAR_TH_muR0p5_muF1p0_ttH:
    if(m_IntProdMode==Process::ttH) m_w *= wgt_var_th_muR0p5_muF1p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR0p5_muF2p0_VBF:
    if(m_IntProdMode==Process::VBF) m_w *= wgt_var_th_muR0p5_muF2p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR0p5_muF2p0_VH:
    if(m_IntProdMode==Process::WH || m_IntProdMode==Process::ZH || m_IntProdMode==Process::ggZH) m_w *= wgt_var_th_muR0p5_muF2p0;
    else                                                                                         m_w *= 1;
    break;
  case Syst::VAR_TH_muR0p5_muF2p0_ttH:
    if(m_IntProdMode==Process::ttH) m_w *= wgt_var_th_muR0p5_muF2p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR1p0_muF0p5_VBF:
    if(m_IntProdMode==Process::VBF) m_w *= wgt_var_th_muR1p0_muF0p5;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR1p0_muF0p5_VH:
    if(m_IntProdMode==Process::WH || m_IntProdMode==Process::ZH || m_IntProdMode==Process::ggZH) m_w *= wgt_var_th_muR1p0_muF0p5;
    else                                                                                         m_w *= 1;
    break;
  case Syst::VAR_TH_muR1p0_muF0p5_ttH:
    if(m_IntProdMode==Process::ttH) m_w *= wgt_var_th_muR1p0_muF0p5;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR1p0_muF2p0_VBF:
    if(m_IntProdMode==Process::VBF) m_w *= wgt_var_th_muR1p0_muF2p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR1p0_muF2p0_VH:
    if(m_IntProdMode==Process::WH || m_IntProdMode==Process::ZH || m_IntProdMode==Process::ggZH) m_w *= wgt_var_th_muR1p0_muF2p0;
    else                                                                                         m_w *= 1;
    break;
  case Syst::VAR_TH_muR1p0_muF2p0_ttH:
    if(m_IntProdMode==Process::ttH) m_w *= wgt_var_th_muR1p0_muF2p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR2p0_muF0p5_VBF:
    if(m_IntProdMode==Process::VBF) m_w *= wgt_var_th_muR2p0_muF0p5;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR2p0_muF0p5_VH:
    if(m_IntProdMode==Process::WH || m_IntProdMode==Process::ZH || m_IntProdMode==Process::ggZH) m_w *= wgt_var_th_muR2p0_muF0p5;
    else                                                                                         m_w *= 1;
    break;
  case Syst::VAR_TH_muR2p0_muF0p5_ttH:
    if(m_IntProdMode==Process::ttH) m_w *= wgt_var_th_muR2p0_muF0p5;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR2p0_muF1p0_VBF:
    if(m_IntProdMode==Process::VBF) m_w *= wgt_var_th_muR2p0_muF1p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR2p0_muF1p0_VH:
    if(m_IntProdMode==Process::WH || m_IntProdMode==Process::ZH || m_IntProdMode==Process::ggZH) m_w *= wgt_var_th_muR2p0_muF1p0;
    else                                                                                         m_w *= 1;
    break;
  case Syst::VAR_TH_muR2p0_muF1p0_ttH:
    if(m_IntProdMode==Process::ttH) m_w *= wgt_var_th_muR2p0_muF1p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR2p0_muF2p0_VBF:
    if(m_IntProdMode==Process::VBF) m_w *= wgt_var_th_muR2p0_muF2p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR2p0_muF2p0_VH:
    if(m_IntProdMode==Process::WH || m_IntProdMode==Process::ZH || m_IntProdMode==Process::ggZH) m_w *= wgt_var_th_muR2p0_muF2p0;
    else                                                                                         m_w *= 1;
    break;
  case Syst::VAR_TH_muR2p0_muF2p0_ttH:
    if(m_IntProdMode==Process::ttH) m_w *= wgt_var_th_muR2p0_muF2p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90400:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90400;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90401:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90401;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90402:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90402;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90403:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90403;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90404:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90404;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90405:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90405;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90406:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90406;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90407:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90407;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90408:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90408;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90409:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90409;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90410:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90410;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90411:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90411;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90412:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90412;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90413:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90413;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90414:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90414;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90415:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90415;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90416:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90416;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90417:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90417;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90418:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90418;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90419:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90419;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90420:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90420;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90421:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90421;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90422:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90422;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90423:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90423;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90424:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90424;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90425:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90425;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90426:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90426;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90427:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90427;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90428:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90428;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90429:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90429;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90430:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90430;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90431:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90431;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90432:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90432;
    else                                                                                           m_w *= 1;
    break;
  //case Syst::VAR_TH_QCD_Scale_Nominal:
  //  if(m_IntProdMode!=Process::ggH && m_IntProdMode!=Process::bbH &&
  //     m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb ) m_w *= wgt_var_th_nominal;
  //  else                                                             m_w *= 1;
  //  break;
  case Syst::VAR_TH_QCD_Scale_Nominal_VBF:
    if(m_IntProdMode==Process::VBF) m_w *= wgt_var_th_nominal;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_QCD_Scale_Nominal_VH:
    if(m_IntProdMode==Process::WH || m_IntProdMode==Process::ZH || m_IntProdMode==Process::ggZH) m_w *= wgt_var_th_nominal;
    else                                                                                         m_w *= 1; 
    break;
  case Syst::VAR_TH_QCD_Scale_Nominal_ttH:
    if(m_IntProdMode==Process::ttH) m_w *= wgt_var_th_nominal;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_PDF_Nominal:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= wgt_var_th_pdf_90400;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_ggF_qcd_2017_pTH120:
    if(m_IntProdMode==Process::ggH) m_w *= wgt_var_th_ggF_qcd_2017_pTH120;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_ggF_qcd_2017_pTH60:
    if(m_IntProdMode==Process::ggH) m_w *= wgt_var_th_ggF_qcd_2017_pTH60;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_ggF_QCD_pTH_nJ0:
    if(m_IntProdMode==Process::ggH) m_w *= wgt_var_th_ggF_qcd_nJ0;
    else                            m_w *= 1; 
    break;
  case Syst::VAR_TH_qcd_wg1_mig01:
    if(m_IntProdMode==Process::ggH) m_w *= wgt_var_th_qcd_wg1_mig01;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_qcd_wg1_mig12:
    if(m_IntProdMode==Process::ggH) m_w *= wgt_var_th_qcd_wg1_mig12;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_qcd_wg1_mu:
    if(m_IntProdMode==Process::ggH) m_w *= wgt_var_th_qcd_wg1_mu;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_qcd_wg1_qm_t:
    if(m_IntProdMode==Process::ggH) m_w *= wgt_var_th_qcd_wg1_qm_t;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_qcd_wg1_res:
    if(m_IntProdMode==Process::ggH) m_w *= wgt_var_th_qcd_wg1_res;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_qcd_wg1_vbf2j:
    if(m_IntProdMode==Process::ggH) m_w *= wgt_var_th_qcd_wg1_vbf2j;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_qcd_wg1_vbf3j:
    if(m_IntProdMode==Process::ggH) m_w *= wgt_var_th_qcd_wg1_vbf3j;
    else                            m_w *= 1;
    break;
    //case Syst::VAR_TH_Shower_Herwig:
    //if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_Herwig;
    //else                                                                                           m_w *= 1;
    //break;
  case Syst::VAR_TH_Var3c:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_Var3cDown;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_Var3c+1:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_Var3cUp;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_hard:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_hardLo;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_hard+1:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_hardHi;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_0p5:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_0p5_fsrmuRfac_0p5;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_1p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_0p5_fsrmuRfac_1p0;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_2p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_0p5_fsrmuRfac_2p0;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_0p625_fsrmuRfac_1p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_0p625_fsrmuRfac_1p0;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_0p75_fsrmuRfac_1p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_0p75_fsrmuRfac_1p0;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_0p875_fsrmuRfac_1p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_0p875_fsrmuRfac_1p0;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p5:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p5;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p625:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p625;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p75:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p75;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p875:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p875;
    else                                                                                           m_w *= 1;
    break;  
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p25:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p25;
    else                                                                                           m_w *= 1;
    break;  
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p5:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p5;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p75:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p75;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_2p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_1p0_fsrmuRfac_2p0;
    else                                                                                           m_w *= 1;
    break;  
  case Syst::VAR_TH_isrmuRfac_1p25_fsrmuRfac_1p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_1p25_fsrmuRfac_1p0;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_1p5_fsrmuRfac_1p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_1p5_fsrmuRfac_1p0;
    else                                                                                           m_w *= 1;
    break;  
  case Syst::VAR_TH_isrmuRfac_1p75_fsrmuRfac_1p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_1p75_fsrmuRfac_1p0;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_0p5:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_2p0_fsrmuRfac_0p5;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_1p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_2p0_fsrmuRfac_1p0;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_2p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= wgt_var_th_isrmuRfac_2p0_fsrmuRfac_2p0;
    else                                                                                           m_w *= 1;
    break;
    /* qqZZ Theory weights */
  case Syst::VAR_TH_qqZZ_Sherpa_CKKW:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_Sherpa_CKKW__1down;
    else                             m_w *= 1;
    break;
  case Syst::VAR_TH_qqZZ_Sherpa_CKKW+1:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_Sherpa_CKKW__1up;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_Sherpa_CSSKIN:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_Sherpa_CSSKIN__1up;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_Sherpa_QSF:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_Sherpa_QSF__1down;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_Sherpa_QSF+1:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_Sherpa_QSF__1up;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261000:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261000;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261001:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261001;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261002:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261002;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261003:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261003;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261004:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261004;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261005:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261005;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261006:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261006;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261007:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261007;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261008:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261008;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261009:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261009;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261010:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261010;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261011:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261011;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261012:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261012;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261013:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261013;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261014:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261014;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261015:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261015;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261016:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261016;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261017:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261017;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261018:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261018;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261019:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261019;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261020:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261020;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261021:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261021;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261022:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261022;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261023:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261023;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261024:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261024;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261025:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261025;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261026:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261026;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261027:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261027;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261028:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261028;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261029:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261029;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261030:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261030;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261031:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261031;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261032:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261032;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261033:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261033;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261034:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261034;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261035:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261035;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261036:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261036;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261037:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261037;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261038:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261038;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261039:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261039;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261040:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261040;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261041:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261041;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261042:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261042;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261043:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261043;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261044:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261044;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261045:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261045;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261046:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261046;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261047:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261047;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261048:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261048;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261049:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261049;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261050:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261050;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261051:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261051;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261052:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261052;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261053:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261053;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261054:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261054;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261055:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261055;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261056:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261056;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261057:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261057;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261058:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261058;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261059:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261059;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261060:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261060;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261061:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261061;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261062:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261062;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261063:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261063;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261064:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261064;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261065:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261065;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261066:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261066;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261067:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261067;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261068:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261068;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261069:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261069;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261070:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261070;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261071:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261071;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261072:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261072;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261073:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261073;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261074:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261074;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261075:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261075;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261076:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261076;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261077:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261077;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261078:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261078;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261079:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261079;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261080:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261080;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261081:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261081;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261082:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261082;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261083:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261083;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261084:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261084;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261085:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261085;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261086:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261086;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261087:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261087;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261088:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261088;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261089:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261089;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261090:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261090;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261091:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261091;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261092:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261092;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261093:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261093;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261094:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261094;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261095:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261095;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261096:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261096;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261097:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261097;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261098:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261098;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261099:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261099;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261100:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF1_PDF261100;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR0p5_MUF0p5_PDF261000:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR0p5_MUF0p5_PDF261000;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR0p5_MUF1_PDF261000:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR0p5_MUF1_PDF261000;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF0p5_PDF261000:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF0p5_PDF261000;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR1_MUF2_PDF261000:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR1_MUF2_PDF261000;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR2_MUF1_PDF261000:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR2_MUF1_PDF261000;
    else                             m_w *= 1;
    break;			      
  case Syst::VAR_TH_qqZZ_MUR2_MUF2_PDF261000:
    if(m_IntProdMode==Process::qqZZ) m_w *= wgt_var_th_MUR2_MUF2_PDF261000;
    else                             m_w *= 1;
    break;			      
  default: m_w *= 1; break;
  }
  return m_w;
  
}

Double_t EventLoop::GetTruthWeight(){

  PRINT_VERBOSE("<EventLoop::GetTruthWeight()>:: retrieving truth event weight ...");

  Double_t m_w = thweight;
  
  switch(m_SystNum){
    /* theory weights */
  case Syst::VAR_TH_muR0p5_muF0p5_VBF:
    if(m_IntProdMode==Process::VBF) m_w *= thwgt_var_th_muR0p5_muF0p5;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR0p5_muF0p5_VH:
    if(m_IntProdMode==Process::WH || m_IntProdMode==Process::ZH || m_IntProdMode==Process::ggZH) m_w *= thwgt_var_th_muR0p5_muF0p5;
    else                                                                                         m_w *= 1;
    break;
  case Syst::VAR_TH_muR0p5_muF0p5_ttH:
    if(m_IntProdMode==Process::ttH) m_w *= thwgt_var_th_muR0p5_muF0p5;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR0p5_muF1p0_VBF:
    if(m_IntProdMode==Process::VBF) m_w *= thwgt_var_th_muR0p5_muF1p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR0p5_muF1p0_VH:
    if(m_IntProdMode==Process::WH || m_IntProdMode==Process::ZH || m_IntProdMode==Process::ggZH) m_w *= thwgt_var_th_muR0p5_muF1p0;
    else                                                                                         m_w *= 1;
    break;
  case Syst::VAR_TH_muR0p5_muF1p0_ttH:
    if(m_IntProdMode==Process::ttH) m_w *= thwgt_var_th_muR0p5_muF1p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR0p5_muF2p0_VBF:
    if(m_IntProdMode==Process::VBF) m_w *= thwgt_var_th_muR0p5_muF2p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR0p5_muF2p0_VH:
    if(m_IntProdMode==Process::WH || m_IntProdMode==Process::ZH || m_IntProdMode==Process::ggZH) m_w *= thwgt_var_th_muR0p5_muF2p0;
    else                                                                                         m_w *= 1;
    break;
  case Syst::VAR_TH_muR0p5_muF2p0_ttH:
    if(m_IntProdMode==Process::ttH) m_w *= thwgt_var_th_muR0p5_muF2p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR1p0_muF0p5_VBF:
    if(m_IntProdMode==Process::VBF) m_w *= thwgt_var_th_muR1p0_muF0p5;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR1p0_muF0p5_VH:
    if(m_IntProdMode==Process::WH || m_IntProdMode==Process::ZH || m_IntProdMode==Process::ggZH) m_w *= thwgt_var_th_muR1p0_muF0p5;
    else                                                                                         m_w *= 1;
    break;
  case Syst::VAR_TH_muR1p0_muF0p5_ttH:
    if(m_IntProdMode==Process::ttH) m_w *= thwgt_var_th_muR1p0_muF0p5;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR1p0_muF2p0_VBF:
    if(m_IntProdMode==Process::VBF) m_w *= thwgt_var_th_muR1p0_muF2p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR1p0_muF2p0_VH:
    if(m_IntProdMode==Process::WH || m_IntProdMode==Process::ZH || m_IntProdMode==Process::ggZH) m_w *= thwgt_var_th_muR1p0_muF2p0;
    else                                                                                         m_w *= 1;
    break;
  case Syst::VAR_TH_muR1p0_muF2p0_ttH:
    if(m_IntProdMode==Process::ttH) m_w *= thwgt_var_th_muR1p0_muF2p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR2p0_muF0p5_VBF:
    if(m_IntProdMode==Process::VBF) m_w *= thwgt_var_th_muR2p0_muF0p5;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR2p0_muF0p5_VH:
    if(m_IntProdMode==Process::WH || m_IntProdMode==Process::ZH || m_IntProdMode==Process::ggZH) m_w *= thwgt_var_th_muR2p0_muF0p5;
    else                                                                                         m_w *= 1;
    break;
  case Syst::VAR_TH_muR2p0_muF0p5_ttH:
    if(m_IntProdMode==Process::ttH) m_w *= thwgt_var_th_muR2p0_muF0p5;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR2p0_muF1p0_VBF:
    if(m_IntProdMode==Process::VBF) m_w *= thwgt_var_th_muR2p0_muF1p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR2p0_muF1p0_VH:
    if(m_IntProdMode==Process::WH || m_IntProdMode==Process::ZH || m_IntProdMode==Process::ggZH) m_w *= thwgt_var_th_muR2p0_muF1p0;
    else                                                                                         m_w *= 1;
    break;
  case Syst::VAR_TH_muR2p0_muF1p0_ttH:
    if(m_IntProdMode==Process::ttH) m_w *= thwgt_var_th_muR2p0_muF1p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR2p0_muF2p0_VBF:
    if(m_IntProdMode==Process::VBF) m_w *= thwgt_var_th_muR2p0_muF2p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_muR2p0_muF2p0_VH:
    if(m_IntProdMode==Process::WH || m_IntProdMode==Process::ZH || m_IntProdMode==Process::ggZH) m_w *= thwgt_var_th_muR2p0_muF2p0;
    else                                                                                         m_w *= 1;
    break;
  case Syst::VAR_TH_muR2p0_muF2p0_ttH:
    if(m_IntProdMode==Process::ttH) m_w *= thwgt_var_th_muR2p0_muF2p0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90400:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90400;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90401:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90401;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90402:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90402;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90403:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90403;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90404:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90404;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90405:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90405;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90406:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90406;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90407:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90407;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90408:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90408;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90409:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90409;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90410:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90410;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90411:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90411;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90412:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90412;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90413:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90413;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90414:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90414;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90415:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90415;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90416:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90416;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90417:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90417;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90418:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90418;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90419:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90419;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90420:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90420;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90421:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90421;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90422:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90422;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90423:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90423;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90424:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90424;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90425:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90425;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90426:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90426;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90427:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90427;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90428:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90428;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90429:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90429;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90430:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90430;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90431:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90431;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_pdf_90432:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90432;
    else                                                                                           m_w *= 1;
    break;
  //case Syst::VAR_TH_QCD_Scale_Nominal:
  //  if(m_IntProdMode!=Process::ggH && m_IntProdMode!=Process::bbH &&
  //     m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb ) m_w *= thwgt_var_th_nominal;
  //  else                                                             m_w *= 1;
  //  break;
  case Syst::VAR_TH_QCD_Scale_Nominal_VBF:
    if(m_IntProdMode==Process::VBF) m_w *= thwgt_var_th_nominal;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_QCD_Scale_Nominal_VH:
    if(m_IntProdMode==Process::WH || m_IntProdMode==Process::ZH || m_IntProdMode==Process::ggZH) m_w *= thwgt_var_th_nominal;
    else                                                                                         m_w *= 1; 
    break;
  case Syst::VAR_TH_QCD_Scale_Nominal_ttH:
    if(m_IntProdMode==Process::ttH) m_w *= thwgt_var_th_nominal;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_PDF_Nominal:
    if(m_IntProdMode!=Process::bbH && m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb) m_w *= thwgt_var_th_pdf_90400;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_ggF_qcd_2017_pTH120:
    if(m_IntProdMode==Process::ggH) m_w *= thwgt_var_th_ggF_qcd_2017_pTH120;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_ggF_qcd_2017_pTH60:
    if(m_IntProdMode==Process::ggH) m_w *= thwgt_var_th_ggF_qcd_2017_pTH60;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_ggF_QCD_pTH_nJ0:
    if(m_IntProdMode==Process::ggH) m_w *= thwgt_var_th_ggF_qcd_nJ0;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_qcd_wg1_mig01:
    if(m_IntProdMode==Process::ggH) m_w *= thwgt_var_th_qcd_wg1_mig01;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_qcd_wg1_mig12:
    if(m_IntProdMode==Process::ggH) m_w *= thwgt_var_th_qcd_wg1_mig12;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_qcd_wg1_mu:
    if(m_IntProdMode==Process::ggH) m_w *= thwgt_var_th_qcd_wg1_mu;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_qcd_wg1_qm_t:
    if(m_IntProdMode==Process::ggH) m_w *= thwgt_var_th_qcd_wg1_qm_t;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_qcd_wg1_res:
    if(m_IntProdMode==Process::ggH) m_w *= thwgt_var_th_qcd_wg1_res;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_qcd_wg1_vbf2j:
    if(m_IntProdMode==Process::ggH) m_w *= thwgt_var_th_qcd_wg1_vbf2j;
    else                            m_w *= 1;
    break;
  case Syst::VAR_TH_qcd_wg1_vbf3j:
    if(m_IntProdMode==Process::ggH) m_w *= thwgt_var_th_qcd_wg1_vbf3j;
    else                            m_w *= 1;
    break;
    //case Syst::VAR_TH_Shower_Herwig:
    //if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_Herwig;
    //else                                                                                           m_w *= 1;
    //break;
  case Syst::VAR_TH_Var3c:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_Var3cDown;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_Var3c+1:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_Var3cUp;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_hard:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_hardLo;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_hard+1:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_hardHi;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_0p5:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_0p5;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_1p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_1p0;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_2p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_2p0;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_0p625_fsrmuRfac_1p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_0p625_fsrmuRfac_1p0;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_0p75_fsrmuRfac_1p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_0p75_fsrmuRfac_1p0;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_0p875_fsrmuRfac_1p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_0p875_fsrmuRfac_1p0;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p5:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p5;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p625:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p625;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p75:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p75;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p875:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p875;
    else                                                                                           m_w *= 1;
    break;  
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p25:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p25;
    else                                                                                           m_w *= 1;
    break;  
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p5:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p5;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p75:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p75;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_2p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_2p0;
    else                                                                                           m_w *= 1;
    break;  
  case Syst::VAR_TH_isrmuRfac_1p25_fsrmuRfac_1p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_1p25_fsrmuRfac_1p0;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_1p5_fsrmuRfac_1p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_1p5_fsrmuRfac_1p0;
    else                                                                                           m_w *= 1;
    break;  
  case Syst::VAR_TH_isrmuRfac_1p75_fsrmuRfac_1p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_1p75_fsrmuRfac_1p0;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_0p5:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_0p5;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_1p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_1p0;
    else                                                                                           m_w *= 1;
    break;
  case Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_2p0:
    if(m_IntProdMode!=Process::tWH && m_IntProdMode!=Process::tHqb && m_IntProdMode!=Process::bbH) m_w *= thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_2p0;
    else                                                                                           m_w *= 1;
    break;
  default: m_w *= 1; break;
  }
  return m_w;
  
}
