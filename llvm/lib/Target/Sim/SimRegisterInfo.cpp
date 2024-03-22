#include "SimRegisterInfo.h"
#include "Sim.h"
#include "SimFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

using namespace llvm;

#define GET_REGINFO_TARGET_DESC
#include "SimGenRegisterInfo.inc"

SimRegisterInfo::SimRegisterInfo() : SimGenRegisterInfo(Sim::R0) {
  SIM_DUMP_GREEN
}