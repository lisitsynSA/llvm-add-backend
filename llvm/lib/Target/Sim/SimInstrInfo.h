#ifndef LLVM_LIB_TARGET_SIM_SIMINSTRINFO_H
#define LLVM_LIB_TARGET_SIM_SIMINSTRINFO_H

#include "SimRegisterInfo.h"
#include "MCTargetDesc/SimInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "SimGenInstrInfo.inc"

namespace llvm {

class SimSubtarget;

class SimInstrInfo : public SimGenInstrInfo {
public:
  SimInstrInfo();

};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_SIM_SIMINSTRINFO_H
