add_llvm_component_library(LLVMSimDesc
  SimMCTargetDesc.cpp
  SimMCAsmInfo.cpp
  SimInstPrinter.cpp
  SimMCCodeEmitter.cpp
  SimAsmBackend.cpp
  SimELFObjectWriter.cpp

  LINK_COMPONENTS
  MC
  Support
  SimInfo

  ADD_TO_COMPONENT
  Sim
 )
