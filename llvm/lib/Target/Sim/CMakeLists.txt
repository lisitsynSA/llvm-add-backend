add_llvm_component_group(Sim)

set(LLVM_TARGET_DEFINITIONS Sim.td)

tablegen(LLVM SimGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM SimGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM SimGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(SimCommonTableGen)

add_llvm_target(SimCodeGen
  SimTargetMachine.cpp
  SimRegisterInfo.cpp
  SimInstrInfo.cpp
  SimSubtarget.cpp

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
