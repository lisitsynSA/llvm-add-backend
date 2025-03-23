add_llvm_component_group(Sim)

set(LLVM_TARGET_DEFINITIONS Sim.td)

tablegen(LLVM SimGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM SimGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM SimGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM SimGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM SimGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM SimGenCallingConv.inc -gen-callingconv)
tablegen(LLVM SimGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM SimGenMCCodeEmitter.inc -gen-emitter)

add_public_tablegen_target(SimCommonTableGen)

add_llvm_target(SimCodeGen
  SimTargetMachine.cpp
  SimRegisterInfo.cpp
  SimInstrInfo.cpp
  SimSubtarget.cpp
  SimAsmPrinter.cpp
  SimISelDagToDag.cpp
  SimISelLowering.cpp
  SimMCInstLower.cpp

  LINK_COMPONENTS
  CodeGen
  Core
  Support
  Target
  SimInfo
  AsmPrinter
  SelectionDAG

  ADD_TO_COMPONENT
  Sim
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
