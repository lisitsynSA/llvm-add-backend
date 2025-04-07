#include "MCTargetDesc/SimFixupKinds.h"
#include "MCTargetDesc/SimMCTargetDesc.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCFixupKindInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCValue.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/EndianStream.h"

using namespace llvm;

namespace {
class SimAsmBackend : public MCAsmBackend {
protected:
  const Target &TheTarget;

public:
  SimAsmBackend(const Target &T)
      : MCAsmBackend(llvm::endianness::little), TheTarget(T) {}

  unsigned getNumFixupKinds() const override {
    return Sim::NumTargetFixupKinds;
  }
  const MCFixupKindInfo &getFixupKindInfo(MCFixupKind Kind) const override {

    const static MCFixupKindInfo InfosLE[Sim::NumTargetFixupKinds] = {
        // name                offset bits  flags
        {"fixup_Sim_PC16", 0, 16, MCFixupKindInfo::FKF_IsPCRel},
    };

    // Fixup kinds from .reloc directive are like R_SPARC_NONE. They do
    // not require any extra processing.
    if (Kind >= FirstLiteralRelocationKind)
      return MCAsmBackend::getFixupKindInfo(FK_NONE);

    if (Kind < FirstTargetFixupKind)
      return MCAsmBackend::getFixupKindInfo(Kind);

    assert(unsigned(Kind - FirstTargetFixupKind) < getNumFixupKinds() &&
           "Invalid kind!");
    return InfosLE[Kind - FirstTargetFixupKind];
  }

  bool writeNopData(raw_ostream &OS, uint64_t Count,
                    const MCSubtargetInfo *STI) const override {
    // Cannot emit NOP with size not multiple of 32 bits.
    if (Count % 4 != 0)
      return false;

    uint64_t NumNops = Count / 4;
    for (uint64_t i = 0; i != NumNops; ++i)
      support::endian::write<uint32_t>(OS, 0x01000000, Endian);

    return true;
  }
};

class ELFSimAsmBackend : public SimAsmBackend {
  Triple::OSType OSType;

public:
  ELFSimAsmBackend(const Target &T, Triple::OSType OSType)
      : SimAsmBackend(T), OSType(OSType) {}

  void applyFixup(const MCAssembler &Asm, const MCFixup &Fixup,
                  const MCValue &Target, MutableArrayRef<char> Data,
                  uint64_t Value, bool IsResolved,
                  const MCSubtargetInfo *STI) const override {
    unsigned NumBytes = 0;
    switch (Fixup.getKind()) {
    default:
      return;
    case Sim::fixup_Sim_PC16:
      // Forcing a signed division because Value can be negative.
      Value /= 4;
      NumBytes = 2;
      break;
    }

    unsigned Offset = Fixup.getOffset();
    // For each byte of the fragment that the fixup touches, mask in the bits
    // from the fixup value. The Value has been "split up" into the
    // appropriate bitfields above.
    for (unsigned i = 0; i != NumBytes; ++i) {
      Data[Offset + i] |= uint8_t((Value >> (i * 8)) & 0xff);
    }
    return;
  }

  std::unique_ptr<MCObjectTargetWriter>
  createObjectTargetWriter() const override {
    uint8_t OSABI = MCELFObjectTargetWriter::getOSABI(OSType);
    return createSimELFObjectWriter(false, OSABI);
  }
};

} // end anonymous namespace

MCAsmBackend *llvm::createSimAsmBackend(const Target &T,
                                        const MCSubtargetInfo &STI,
                                        const MCRegisterInfo &MRI,
                                        const MCTargetOptions &Options) {
  return new ELFSimAsmBackend(T, STI.getTargetTriple().getOS());
}