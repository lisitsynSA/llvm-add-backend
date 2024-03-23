include "llvm/Target/Target.td"
include "SimRegisterInfo.td"
include "SimInstrInfo.td"

def SimInstrInfo : InstrInfo;
def Sim : Target {
  let InstructionSet = SimInstrInfo;
}
