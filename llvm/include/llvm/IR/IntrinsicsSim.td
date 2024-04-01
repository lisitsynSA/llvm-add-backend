
let TargetPrefix = "sim" in {  // All intrinsics start with "llvm.sim.".

def int_sim_putpixel: ClangBuiltin<"simPutPixel">,
  Intrinsic<[], [llvm_i32_ty, llvm_i32_ty, llvm_i32_ty], [IntrNoMem, IntrHasSideEffects]>;

def int_sim_flush: ClangBuiltin<"simFlush">,
  Intrinsic<[], [], [IntrNoMem, IntrHasSideEffects]>;

} // TargetPrefix = "sim"
