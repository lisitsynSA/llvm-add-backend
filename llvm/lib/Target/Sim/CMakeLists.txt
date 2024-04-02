add_llvm_component_group(Sim)

set(LLVM_TARGET_DEFINITIONS Sim.td)

tablegen(LLVM SimGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM SimGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM SimGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM SimGenCallingConv.inc -gen-callingconv)
tablegen(LLVM SimGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM SimGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM SimGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM SimGenMCCodeEmitter.inc -gen-emitter)

add_public_tablegen_target(SimCommonTableGen)

add_llvm_target(SimCodeGen
  SimTargetMachine.cpp
  SimRegisterInfo.cpp
  SimInstrInfo.cpp
  SimSubtarget.cpp
  SimAsmPrinter.cpp
  SimFrameLowering.cpp
  SimISelDagToDag.cpp
  SimISelLowering.cpp
  SimMCInstLower.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  Core
  MC
  SimDesc
  SelectionDAG
  Support
  Target
  SimInfo
  GlobalISel

  ADD_TO_COMPONENT
  Sim
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
