project(ffasp)

add_executable(ffasp Term.cpp SpiritProgramParser.cpp SafetyChecker.cpp Rule.cpp Rewrite.cpp Program.cpp ProcessBuff.cpp Literal.cpp Globals.cpp FAnswerSet.cpp Error.cpp DLVResultParser.cpp DLVASPSolver.cpp CLSolver.cpp AtomSet.cpp Atom.cpp ASPTranslate.cpp ASPEval.cpp main.cpp)

install(TARGETS ffasp RUNTIME DESTINATION bin)
