#include "Edu.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeEduTargetInfo() {
  EDU_DUMP_RED
}
