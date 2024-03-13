#include "TargetInfo/SimTargetInfo.h"
#include "Sim.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheSimTarget() {
  SIM_DUMP_YELLOW
  static Target TheSimTarget;
  return TheSimTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeSimTargetInfo() {
  SIM_DUMP_YELLOW
  RegisterTarget<Triple::sim> X(getTheSimTarget(), "sim",
                                "Simulator target for LLVM course", "SIM");
}
