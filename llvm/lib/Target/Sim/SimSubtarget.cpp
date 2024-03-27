#include "SimSubtarget.h"
#include "Sim.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define DEBUG_TYPE "Sim-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "SimGenSubtargetInfo.inc"

void SimSubtarget::anchor() {}

SimSubtarget::SimSubtarget(const Triple &TT, const std::string &CPU,
                             const std::string &FS, const TargetMachine &TM)
    : SimGenSubtargetInfo(TT, CPU, /*TuneCPU=*/CPU, FS), InstrInfo(),
      FrameLowering(*this), TLInfo(TM, *this) {}
