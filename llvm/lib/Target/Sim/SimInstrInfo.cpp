#include "SimInstrInfo.h"
#include "Sim.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "SimGenInstrInfo.inc"

#define DEBUG_TYPE "Sim-inst-info"

SimInstrInfo::SimInstrInfo() : SimGenInstrInfo() { SIM_DUMP_GREEN }
