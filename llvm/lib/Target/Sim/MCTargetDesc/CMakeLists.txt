add_llvm_component_library(LLVMSimDesc
  SimMCTargetDesc.cpp
  SimMCAsmInfo.cpp
  SimInstPrinter.cpp

  LINK_COMPONENTS
  MC
  Support
  SimInfo

  ADD_TO_COMPONENT
  Sim
 )
