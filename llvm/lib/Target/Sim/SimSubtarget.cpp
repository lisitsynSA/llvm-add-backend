#include "SimSubtarget.h"
#include "Sim.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;

#define DEBUG_TYPE "sim-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "SimGenSubtargetInfo.inc"

SimSubtarget::SimSubtarget(const StringRef &CPU, const StringRef &TuneCPU,
                           const StringRef &FS, const TargetMachine &TM)
    : SimGenSubtargetInfo(TM.getTargetTriple(), CPU, TuneCPU, FS) {
  SIM_DUMP_CYAN
}