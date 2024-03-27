#ifndef LLVM_LIB_TARGET_Sim_Sim_H
#define LLVM_LIB_TARGET_Sim_Sim_H

#include "MCTargetDesc/SimMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Support/raw_ostream.h"

#define SIM_DUMP(Color)                                                        \
  {                                                                            \
    llvm::errs().changeColor(Color)                                            \
        << __func__ << "\n\t\t" << __FILE__ << ":" << __LINE__ << "\n";        \
    llvm::errs().changeColor(llvm::raw_ostream::WHITE);                        \
  }
// #define SIM_DUMP(Color) {}

#define SIM_DUMP_RED SIM_DUMP(llvm::raw_ostream::RED)
#define SIM_DUMP_GREEN SIM_DUMP(llvm::raw_ostream::GREEN)
#define SIM_DUMP_YELLOW SIM_DUMP(llvm::raw_ostream::YELLOW)
#define SIM_DUMP_CYAN SIM_DUMP(llvm::raw_ostream::CYAN)
#define SIM_DUMP_MAGENTA SIM_DUMP(llvm::raw_ostream::MAGENTA)
#define SIM_DUMP_WHITE SIM_DUMP(llvm::raw_ostream::WHITE)

namespace llvm {
class SimTargetMachine;
class FunctionPass;
class SimSubtarget;
class AsmPrinter;
class InstructionSelector;
class MCInst;
class MCOperand;
class MachineInstr;
class MachineOperand;
class PassRegistry;

bool lowerSimMachineInstrToMCInst(const MachineInstr *MI, MCInst &OutMI,
                                    AsmPrinter &AP);
bool LowerSimMachineOperandToMCOperand(const MachineOperand &MO,
                                         MCOperand &MCOp, const AsmPrinter &AP);

FunctionPass *createSimISelDag(SimTargetMachine &TM);

} // namespace llvm

#endif // LLVM_LIB_TARGET_Sim_Sim_H