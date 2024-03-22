include "llvm/Target/Target.td"
include "SimRegisterInfo.td"
include "SimInstrInfo.td"

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;

def SimInstrInfo : InstrInfo;
def Sim : Target {
  let InstructionSet = SimInstrInfo;
}
