#ifndef LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMMCTARGETDESC_H
#define LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMMCTARGETDESC_H

namespace llvm {
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;

MCCodeEmitter *createSimMCCodeEmitter(const MCInstrInfo &MCII, MCContext &Ctx);
} // namespace llvm

// Defines symbolic names for Sim registers.  This defines a mapping from
// register name to register number.
//
#define GET_REGINFO_ENUM
#include "SimGenRegisterInfo.inc"

// Defines symbolic names for the Sim instructions.
#define GET_INSTRINFO_ENUM
#include "SimGenInstrInfo.inc"

#endif // LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMMCTARGETDESC_H
