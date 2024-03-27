//===----------------------------------------------------------------------===//
//
// Implements the info about Sim target spec.
//
//===----------------------------------------------------------------------===//

#include "SimTargetMachine.h"
#include "Sim.h"
//#include "SimTargetTransformInfo.h"
#include "TargetInfo/SimTargetInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetOptions.h"

#define DEBUG_TYPE "Sim"

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeSimTarget() {
  // Register the target.
  SIM_DUMP_CYAN
  RegisterTargetMachine<SimTargetMachine> A(getTheSimTarget());
}

SimTargetMachine::SimTargetMachine(const Target &T, const Triple &TT,
                                   StringRef CPU, StringRef FS,
                                   const TargetOptions &Options,
                                   std::optional<Reloc::Model> RM,
                                   std::optional<CodeModel::Model> CM,
                                   CodeGenOptLevel OL, bool JIT)
    : LLVMTargetMachine(T, "e-m:e-p:32:32-i8:8:32-i16:16:32-i64:64-n32", TT,
                        CPU, FS, Options, Reloc::Static,
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, std::string(CPU), std::string(FS), *this) {
  initAsmInfo();
}

SimTargetMachine::~SimTargetMachine() = default;

namespace {

/// Sim Code Generator Pass Configuration Options.
class SimPassConfig : public TargetPassConfig {
public:
  SimPassConfig(SimTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  SimTargetMachine &getSimTargetMachine() const {
    return getTM<SimTargetMachine>();
  }

  bool addInstSelector() override;
};

} // end anonymous namespace

TargetPassConfig *SimTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new SimPassConfig(*this, PM);
}

bool SimPassConfig::addInstSelector() {
  addPass(createSimISelDag(getSimTargetMachine()));
  return false;
}
