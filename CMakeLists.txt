project(ffasp)

set(CMAKE_BUILD_TYPE RELEASE)
#set(CMAKE_BUILD_TYPE DEBUG)
add_executable(ffasp Term.cpp SpiritProgramParser.cpp SafetyChecker.cpp Rule.cpp Rewrite.cpp Program.cpp ProcessBuff.cpp Literal.cpp Globals.cpp FAnswerSet.cpp Error.cpp CLSolver.cpp AtomSet.cpp Atom.cpp ASPTranslate.cpp ASPEval.cpp AtomNode.cpp AtomFactory.cpp Component.cpp GraphBuilder.cpp Registry.cpp ComponentFinder.cpp BoostComponentFinder.cpp DependencyGraph.cpp EvalComp.cpp main.cpp)

install(TARGETS ffasp RUNTIME DESTINATION bin)
