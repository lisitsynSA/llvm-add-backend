#include "SimMCTargetDesc.h"
#include "Sim.h"
#include "SimInfo.h"
#include "SimInstPrinter.h"
#include "SimMCAsmInfo.h"
#include "SimTargetStreamer.h"
#include "TargetInfo/SimTargetInfo.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "SimGenRegisterInfo.inc"

#define GET_INSTRINFO_MC_DESC
#include "SimGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "SimGenSubtargetInfo.inc"

static MCRegisterInfo *createSimMCRegisterInfo(const Triple &TT) {
  SIM_DUMP_MAGENTA
  MCRegisterInfo *X = new MCRegisterInfo();
  InitSimMCRegisterInfo(X, Sim::R0);
  return X;
}

static MCInstrInfo *createSimMCInstrInfo() {
  SIM_DUMP_MAGENTA
  MCInstrInfo *X = new MCInstrInfo();
  InitSimMCInstrInfo(X);
  return X;
}

static MCSubtargetInfo *createSimMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU, StringRef FS) {
  SIM_DUMP_MAGENTA
  return createSimMCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
}

static MCAsmInfo *createSimMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TT,
                                     const MCTargetOptions &Options) {
  SIM_DUMP_MAGENTA
  MCAsmInfo *MAI = new SimELFMCAsmInfo(TT);
  unsigned SP = MRI.getDwarfRegNum(Sim::R1, true);
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, SP, 0);
  MAI->addInitialFrameState(Inst);
  return MAI;
}

static MCInstPrinter *createSimMCInstPrinter(const Triple &T,
                                             unsigned SyntaxVariant,
                                             const MCAsmInfo &MAI,
                                             const MCInstrInfo &MII,
                                             const MCRegisterInfo &MRI) {
  return new SimInstPrinter(MAI, MII, MRI);
}

SimTargetStreamer::SimTargetStreamer(MCStreamer &S) : MCTargetStreamer(S) {}
SimTargetStreamer::~SimTargetStreamer() = default;

static MCTargetStreamer *createTargetAsmStreamer(MCStreamer &S,
                                                 formatted_raw_ostream &OS,
                                                 MCInstPrinter *InstPrint,
                                                 bool isVerboseAsm) {
  return new SimTargetStreamer(S);
}

// We need to define this function for linking succeed
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeSimTargetMC() {
  SIM_DUMP_MAGENTA
  Target &TheSimTarget = getTheSimTarget();
  RegisterMCAsmInfoFn X(TheSimTarget, createSimMCAsmInfo);
  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheSimTarget, createSimMCRegisterInfo);
  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheSimTarget, createSimMCInstrInfo);
  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheSimTarget,
                                          createSimMCSubtargetInfo);
  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheSimTarget, createSimMCInstPrinter);
  TargetRegistry::RegisterAsmTargetStreamer(TheSimTarget,
                                            createTargetAsmStreamer);
  // Register the MC Code Emitter.
  TargetRegistry::RegisterMCCodeEmitter(TheSimTarget, createSimMCCodeEmitter);
  // Register the asm backend.
  TargetRegistry::RegisterMCAsmBackend(TheSimTarget, createSimAsmBackend);
}
