#include "MCTargetDesc/SimInfo.h"
#include "Sim.h"
#include "TargetInfo/SimTargetInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "SimGenRegisterInfo.inc"

#define GET_INSTRINFO_MC_DESC
#include "SimGenInstrInfo.inc"

static MCRegisterInfo *createSimMCRegisterInfo(const Triple &TT) {
  SIM_DUMP_MAGENTA
  MCRegisterInfo *X = new MCRegisterInfo();
  InitSimMCRegisterInfo(X, Sim::R0);
  return X;
}

static MCInstrInfo *createSimMCInstrInfo() {
  SIM_DUMP_MAGENTA
  MCInstrInfo *X = new MCInstrInfo();
  InitSimMCInstrInfo(X);
  return X;
}

// We need to define this function for linking succeed
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeSimTargetMC() {
  SIM_DUMP_MAGENTA
  Target &TheSimTarget = getTheSimTarget();
  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheSimTarget, createSimMCRegisterInfo);
  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheSimTarget, createSimMCInstrInfo);
}
