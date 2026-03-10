add_llvm_component_group(Edu)

add_llvm_target(EduCodeGen
  EduTargetMachine.cpp

  ADD_TO_COMPONENT
  Edu
)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
