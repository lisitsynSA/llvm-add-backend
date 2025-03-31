#include "Sim.h"
#include "clang/Basic/Builtins.h"
#include "clang/Basic/MacroBuilder.h"

using namespace clang;
using namespace clang::targets;

void SimTargetInfo::getTargetDefines(const LangOptions &Opts,
                                     MacroBuilder &Builder) const {
  Builder.defineMacro("__sim__");
}

ArrayRef<Builtin::Info> SimTargetInfo::getTargetBuiltins() const {
  return std::nullopt;
}
