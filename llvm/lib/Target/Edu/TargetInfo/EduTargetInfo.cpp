#include "EduTargetInfo.h"
#include "Edu.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheEduTarget() {
  static Target TheEduTarget;
  return TheEduTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeEduTargetInfo() {
  EDU_DUMP_RED
  RegisterTarget<Triple::edu> X(getTheEduTarget(), "edu",
                                "Educational target for LLVM course", "EDU");
}
