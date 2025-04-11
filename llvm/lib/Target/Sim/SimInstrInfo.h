#ifndef LLVM_LIB_TARGET_SIM_SIMINSTRINFO_H
#define LLVM_LIB_TARGET_SIM_SIMINSTRINFO_H

#include "MCTargetDesc/SimInfo.h"
#include "SimRegisterInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "SimGenInstrInfo.inc"

namespace llvm {

class SimSubtarget;

class SimInstrInfo : public SimGenInstrInfo {
public:
  SimInstrInfo();
  void copyPhysReg(MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI,
                   const DebugLoc &DL, MCRegister DestReg, MCRegister SrcReg,
                   bool KillSrc, bool RenamableDest = false,
                   bool RenamableSrc = false) const override;

  void storeRegToStackSlot(MachineBasicBlock &MBB,
                           MachineBasicBlock::iterator I, Register SrcReg,
                           bool IsKill, int FI, const TargetRegisterClass *RC,
                           const TargetRegisterInfo *TRI, Register VReg,
                           MachineInstr::MIFlag Flags) const override {};
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_SIM_SIMINSTRINFO_H
