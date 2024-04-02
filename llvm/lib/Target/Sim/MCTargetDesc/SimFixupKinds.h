#ifndef LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMFIXUPKINDS_H
#define LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMFIXUPKINDS_H

#include "llvm/MC/MCFixup.h"

namespace llvm {
namespace Sim {
  // Although most of the current fixup types reflect a unique relocation
  // one can have multiple fixup types for a given relocation and thus need
  // to be uniquely named.
  //
  // This table *must* be in the same order of
  // MCFixupKindInfo Infos[Sim::NumTargetFixupKinds]
  // in SimAsmBackend.cpp.
  //
  enum Fixups {
    fixup_Sim_PC16 = FirstTargetFixupKind,
    // Marker
    LastTargetFixupKind,
    NumTargetFixupKinds = LastTargetFixupKind - FirstTargetFixupKind
  };
} // namespace Sim
} // namespace llvm


#endif