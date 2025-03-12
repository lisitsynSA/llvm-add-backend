#ifndef LLVM_LIB_TARGET_SIM_SIMTARGETSTREAMER_H
#define LLVM_LIB_TARGET_SIM_SIMTARGETSTREAMER_H

#include "llvm/MC/MCStreamer.h"

namespace llvm {

class SimTargetStreamer : public MCTargetStreamer {
public:
  SimTargetStreamer(MCStreamer &S);
  ~SimTargetStreamer() override;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_SIM_SIMTARGETSTREAMER_H