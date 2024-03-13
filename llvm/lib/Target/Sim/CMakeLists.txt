add_llvm_component_group(Sim)

add_llvm_target(SimCodeGen
  SimTargetMachine.cpp

  LINK_COMPONENTS
  CodeGen
  Core
  Support
  Target
  SimInfo

  ADD_TO_COMPONENT
  Sim
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
