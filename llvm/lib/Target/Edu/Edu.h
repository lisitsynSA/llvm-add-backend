#ifndef LLVM_LIB_TARGET_Edu_Edu_H
#define LLVM_LIB_TARGET_Edu_Edu_H

#include "llvm/Support/raw_ostream.h"

// #define EDU_STACKTRACE
#ifdef EDU_STACKTRACE
#define BOOST_STACKTRACE_LINK
// libboost-stacktrace-dev should be installed
// and -lboost_stacktrace_backtrace should be added
#include <boost/stacktrace.hpp>
#define EDU_DUMP_STACKTRACE                                                    \
  {                                                                            \
    llvm::errs() << boost::stacktrace::to_string(                              \
        boost::stacktrace::stacktrace());                                      \
  }
#else
#define EDU_DUMP_STACKTRACE
#endif

#define EDU_DUMP(Color)                                                        \
  {                                                                            \
    llvm::errs().changeColor(Color)                                            \
        << __func__ << "\n\t\t" << __FILE__ << ":" << __LINE__ << "\n";        \
    llvm::errs().changeColor(llvm::raw_ostream::WHITE);                        \
    EDU_DUMP_STACKTRACE                                                        \
  }
// #define EDU_DUMP(Color) {}

#define EDU_DUMP_RED EDU_DUMP(llvm::raw_ostream::RED)
#define EDU_DUMP_GREEN EDU_DUMP(llvm::raw_ostream::GREEN)
#define EDU_DUMP_YELLOW EDU_DUMP(llvm::raw_ostream::YELLOW)
#define EDU_DUMP_CYAN EDU_DUMP(llvm::raw_ostream::CYAN)
#define EDU_DUMP_MAGENTA EDU_DUMP(llvm::raw_ostream::MAGENTA)

#endif // LLVM_LIB_TARGET_Edu_Edu_H
