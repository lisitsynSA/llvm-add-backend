#include "llvm/MC/TargetRegistry.h"
#include "Edu.h"

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeEduTarget() {
  // Register the target.
  EDU_DUMP_RED
}
