#include "iostream"
#include <TObject.h>

// need to define errors cose instead of exiting everytime with 0
// it will be easier to debug

/* ----------------------------------------- */
/*    Color scheme usded for cout:           */
/*      print          -> shell default      */
/*      error          -> red	             */
/*      fatal          -> bold red	     */
/*      begin function -> bold blue          */
/*      end function   -> shell default      */
/*      debug          -> shell default      */
/*      debug function -> bold violet        */
/*      sys function   -> bold green         */
/*      info           -> bold shell default */
/*      warning        -> violet             */
/* ----------------------------------------- */

bool m_isDebug, m_isVerbose, m_isInfo;

void SetDebugLevel(bool debug){

  m_isDebug = debug;
#ifdef DEBUG
  m_isDebug = true;
#endif
  
}

void SetInfoLevel(bool info){

  m_isInfo = info;
#ifdef DEBUG
  m_isInfo = true;
#endif
  
}

void PRINT(std::string field){
  
  std::cout << field << std::endl;
  
}

void PRINT_DEBUG(std::string field){

  if( !m_isDebug ) return;
  std::cout << "DEBUG:: " << field << std::endl;
  
}

void PRINT_DEBUG(std::string field1, std::string field2){

  if( !m_isDebug ) return;
  std::cout << "DEBUG:: " << field1 << field2 << std::endl;
  
}

void PRINT_VERBOSE(std::string field){

#ifdef DEBUG
  std::cout << "VERBOSE:: " << field << std::endl;
#endif
  
}

void PRINT_VALUES(std::string field){

  if(!m_isInfo) return;
  std::cout << "VERBOSE:: " << field << std::endl;
  
}

void PRINT_VERBOSE(std::string field1, std::string field2){

#ifdef DEBUG
  std::cout << "VERBOSE:: " << field1 << field2 << std::endl;
#endif
  
}

void PRINT_SYS(std::string field){
  
  std::cout<< "\033[1;32m SYS:: " << field <<  "\033[0m" <<std::endl;
  
}

void PRINT_INFO(std::string field){
  
  std::cout << "\e[1m INFO:: " << field <<  "\e[0m" << std::endl;
  
}

void PRINT_DEBUG_FUNCTION(std::string field){

  if( !m_isDebug ) return;
  std::cout << "\033[1;35m DEBUG:: " << field <<  "\033[0m" << std::endl;
  
}

void PRINT_FATAL(std::string field){
  
  std::cout << "\033[1;31m FATAL:: " << field << " \033[0m" << std::endl;
  
}

void PRINT_ERROR(std::string field){

  std::cout << "\033[0;31m ERROR:: " << field << " \033[0m" << std::endl;
  
}

void PRINT_BEGIN_FUNCTION(std::string field){

  std::cout << "\033[1;34m " << field << " \033[0m" << std::endl;
  
}

void PRINT_END_FUNCTION(std::string field){

  std::cout << field << " :: done! " << std::endl;
  
}

void PRINT_WARNING(std::string field){

  std::cout << "\033[0;35m WARNING:: " << field <<  "\033[0m" << std::endl;
  
}

void PRINT_DEBUG_OBJECT(TObject *o, int v = 0){

  if( !m_isDebug ) return;
  if( v == 0 )     o->Print();
  if( v == 1 )     o->Print("v");
  
}
