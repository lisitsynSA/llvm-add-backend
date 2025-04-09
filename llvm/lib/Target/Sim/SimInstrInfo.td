//===----------------------------------------------------------------------===//
// Sim profiles and nodes
//===----------------------------------------------------------------------===//

def SDT_SimBrCC  : SDTypeProfile<0, 2, [ SDTCisVT<0, i32>,
                                         SDTCisVT<1, OtherVT>]>;

def sim_brcc     : SDNode<"SimISD::BR_CC", SDT_SimBrCC,
                            [SDNPHasChain]>;

def sim_ret      : SDNode<"SimISD::RET", SDTNone,
                            [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

//===----------------------------------------------------------------------===//
// Instruction format superclass
//===----------------------------------------------------------------------===//

include "SimInstrFormats.td"

//===----------------------------------------------------------------------===//
// Sim Operand, Complex Patterns and Transformations Definitions.
//===----------------------------------------------------------------------===//

class SImmAsmOperand<int width> : AsmOperandClass {
  let Name = "SImm" # width;
  let RenderMethod = "addImmOperands";
  let DiagnosticType = !strconcat("Invalid", Name);
}

def simm16 : Operand<i32>, ImmLeaf<i32, [{return isUInt<16>(Imm);}]> {
  let ParserMatchClass = SImmAsmOperand<16>;
  let EncoderMethod = "getSImm16OpValue";
  let DecoderMethod = "decodeSImmOperand<16>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (MCOp.evaluateAsConstantImm(Imm))
      return isInt<16>(Imm);
    return MCOp.isBareSymbolRef();
  }];
  let OperandType = "OPERAND_SIMM16";
  let OperandNamespace = "SimOp";
}

def btarget16 : Operand<OtherVT> {
  let ParserMatchClass = SImmAsmOperand<16>;
  let PrintMethod = "printBranchOperand";
  let EncoderMethod = "getBranchTarget16OpValue";
  let DecoderMethod = "decodeSImmOperand<16>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (MCOp.evaluateAsConstantImm(Imm))
      return isInt<16>(Imm);
    return MCOp.isBareSymbolRef();
  }];
  let OperandType = "OPERAND_PCREL";
}

def LI16 : SDNodeXForm<imm, [{
  return CurDAG->getTargetConstant((uint64_t)N->getZExtValue() & 0xffff,
                                  SDLoc(N), MVT::i32);
}]>;

def HI16 : SDNodeXForm<imm, [{
  return CurDAG->getTargetConstant((uint64_t)N->getZExtValue() >> 16, SDLoc(N),
                                  MVT::i32);
}]>;
//===----------------------------------------------------------------------===//
// Instructions specific format
//===----------------------------------------------------------------------===//

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
class IncCCi<bits<8> op>
    : SimInst<op, (outs GPR:$r1, GPR:$r2_), (ins GPR:$r2, simm16:$r3_imm),
              NAME#" $r1 $r2 $r3_imm", []>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
multiclass Arithm<bits<8> opcode, SDPatternOperator op> {
    def NAME  : SimInst<opcode, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                         NAME#" $r1 $r2 $r3_imm",
                         [(set GPR:$r1, (op GPR:$r2, GPR:$r3_imm))]>;
    def NAME#I : SimInst<!add(opcode,0x10), (outs GPR:$r1), (ins GPR:$r2, simm16:$r3_imm),
                         NAME#"i $r1 $r2 $r3_imm",
                         [(set GPR:$r1, (op GPR:$r2, simm16:$r3_imm))]>;
}

//===----------------------------------------------------------------------===//
// Sim Instructions
//===----------------------------------------------------------------------===//


let hasSideEffects = 0, mayLoad = 0, mayStore = 0, isBarrier = 1, isBranch = 1, isTerminator = 1, r1 = 0, r2 = 0 in
def B : SimInst<0xB0, (outs), (ins btarget16:$r3_imm), "B $r3_imm",
                [(br bb:$r3_imm)]>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, isCall = 1, isBranch = 1, isTerminator = 1, r2 = 0, r3_imm = 0 in
def BR : SimInst<0xBB, (outs), (ins GPR:$r1), "BR $r1",
                 [(brind GPR:$r1)]>;

let isBarrier = 1, isReturn = 1, isTerminator = 1 in
def PseudoRET : SimPseudoInst<(outs), (ins), "# PseudoRET",
                [(sim_ret)]>,
                PseudoInstExpansion<(BR R0)>;

let isBranch = 1, isTerminator = 1, r2 = 0 in
def BR_COND : SimInst<0xBC, (outs), (ins GPR:$r1, btarget16:$r3_imm),
                      "BR_COND $r1 $r3_imm", [(sim_brcc GPR:$r1, bb:$r3_imm)]>;

// movli
let isAsCheapAsAMove = 1, isCodeGenOnly = 1, isReMaterializable = 1, r2 = 0 in
def MOVLI : SimInst<0xAA, (outs GPR:$r1), (ins simm16:$r3_imm),
                    "MOVli $r1 $r3_imm",
                    [(set GPR:$r1, simm16:$r3_imm)]>;
// movhi
let isAsCheapAsAMove = 1, isCodeGenOnly = 1, isReMaterializable = 1, r2 = 0  in
def MOVHI : SimInst<0xAF, (outs GPR:$r1), (ins simm16:$r3_imm),
                    "MOVhi $r1 $r3_imm", []>;

def INC_EQi  : IncCCi<0x90>;
def INC_NEi  : IncCCi<0x91>;
def INC_LEi  : IncCCi<0x92>;
def INC_LTi  : IncCCi<0x93>;
def INC_GEi  : IncCCi<0x94>;
def INC_GTi  : IncCCi<0x95>;

defm ADD : Arithm<0x30, add>;
defm SUB : Arithm<0x31, sub>;
defm MUL : Arithm<0x32, mul>;
defm DIV : Arithm<0x33, sdiv>;
defm OR  : Arithm<0x34, or>;
defm AND : Arithm<0x35, and>;
defm XOR : Arithm<0x36, xor>;

// flush
let r1 = 0, r2 = 0, r3_imm = 0 in
def FLUSH : SimInst<0xFF, (outs), (ins), "FLUSH", [(int_sim_flush)]>;

// putpixel
def PUTPIXEL : SimInst<0xEE, (outs), (ins GPR:$r1, GPR:$r2, GPR:$r3_imm),
                      "PUTPIXEL $r1 $r2 $r3_imm", [(int_sim_putpixel GPR:$r1, GPR:$r2, GPR:$r3_imm)]>;

//===----------------------------------------------------------------------===//
// Sim Other patterns
//===----------------------------------------------------------------------===//

def i32hi16 : Operand<i32>, PatLeaf<(i32 imm), [{
    // i32hi16 predicate - true if the 32-bit immediate has only leftmost 16
    // bits set.
    return ((N->getZExtValue() & 0xFFFF0000UL) == N->getZExtValue());}], HI16> {
}

// i32 imm
def : Pat<(i32 imm:$r3_imm), (ORI (MOVHI (HI16 imm:$r3_imm)), (LI16 imm:$r3_imm))>;
def : Pat<(i32 i32hi16:$r3_imm), (MOVHI i32hi16:$r3_imm)>;
