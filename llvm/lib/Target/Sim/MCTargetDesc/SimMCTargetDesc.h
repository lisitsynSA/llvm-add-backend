#ifndef LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMMCTARGETDESC_H
#define LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMMCTARGETDESC_H

#include <memory>

namespace llvm {
class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCTargetOptions;
class Target;

MCCodeEmitter *createSimMCCodeEmitter(const MCInstrInfo &MCII, MCContext &Ctx);
MCAsmBackend *createSimAsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                  const MCRegisterInfo &MRI,
                                  const MCTargetOptions &Options);
std::unique_ptr<MCObjectTargetWriter> createSimELFObjectWriter(bool Is64Bit,
                                                               uint8_t OSABI);
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
