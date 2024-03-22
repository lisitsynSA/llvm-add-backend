#ifndef LLVM_LIB_TARGET_SIM_SIMREGISTERINFO_H
#define LLVM_LIB_TARGET_SIM_SIMREGISTERINFO_H

#define GET_REGINFO_HEADER
#include "SimGenRegisterInfo.inc"

namespace llvm {

struct SimRegisterInfo : public SimGenRegisterInfo {
public:
  SimRegisterInfo();
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_SIM_SIMREGISTERINFO_H