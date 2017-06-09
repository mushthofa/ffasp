##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=ffasp
ConfigurationName      :=Debug
WorkspacePath          := "/home/creep/GitHub/ffasp"
ProjectPath            := "/home/creep/GitHub/ffasp"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Mushthofa
Date                   :=09/06/17
CodeLitePath           :="/home/creep/.codelite"
LinkerName             :=/usr/bin/x86_64-linux-gnu-g++
SharedObjectLinkerName :=/usr/bin/x86_64-linux-gnu-g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="ffasp.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)glpk $(LibrarySwitch)Cbc $(LibrarySwitch)Cgl $(LibrarySwitch)CbcSolver $(LibrarySwitch)Clp $(LibrarySwitch)CoinUtils $(LibrarySwitch)OsiCbc $(LibrarySwitch)OsiClp 
ArLibs                 :=  "glpk" "Cbc" "Cgl" "CbcSolver" "Clp" "CoinUtils" "OsiCbc" "OsiClp" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/lib/x86_64-linux-gnu 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/x86_64-linux-gnu-ar rcu
CXX      := /usr/bin/x86_64-linux-gnu-g++
CC       := /usr/bin/x86_64-linux-gnu-gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/x86_64-linux-gnu-as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/ASPEval.cpp$(ObjectSuffix) $(IntermediateDirectory)/ASPTranslate.cpp$(ObjectSuffix) $(IntermediateDirectory)/Atom.cpp$(ObjectSuffix) $(IntermediateDirectory)/AtomFactory.cpp$(ObjectSuffix) $(IntermediateDirectory)/AtomNode.cpp$(ObjectSuffix) $(IntermediateDirectory)/AtomSet.cpp$(ObjectSuffix) $(IntermediateDirectory)/BoostComponentFinder.cpp$(ObjectSuffix) $(IntermediateDirectory)/CLSolver.cpp$(ObjectSuffix) $(IntermediateDirectory)/Component.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/ComponentFinder.cpp$(ObjectSuffix) $(IntermediateDirectory)/DependencyGraph.cpp$(ObjectSuffix) $(IntermediateDirectory)/Error.cpp$(ObjectSuffix) $(IntermediateDirectory)/EvalComp.cpp$(ObjectSuffix) $(IntermediateDirectory)/FAnswerSet.cpp$(ObjectSuffix) $(IntermediateDirectory)/Globals.cpp$(ObjectSuffix) $(IntermediateDirectory)/GraphBuilder.cpp$(ObjectSuffix) $(IntermediateDirectory)/GraphProcessor.cpp$(ObjectSuffix) $(IntermediateDirectory)/Literal.cpp$(ObjectSuffix) $(IntermediateDirectory)/MIPMinCheck.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/ProcessBuff.cpp$(ObjectSuffix) $(IntermediateDirectory)/Program.cpp$(ObjectSuffix) $(IntermediateDirectory)/Registry.cpp$(ObjectSuffix) $(IntermediateDirectory)/Rewrite.cpp$(ObjectSuffix) $(IntermediateDirectory)/Rule.cpp$(ObjectSuffix) $(IntermediateDirectory)/SafetyChecker.cpp$(ObjectSuffix) $(IntermediateDirectory)/SpiritProgramParser.cpp$(ObjectSuffix) $(IntermediateDirectory)/Term.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/ASPEval.cpp$(ObjectSuffix): ASPEval.cpp $(IntermediateDirectory)/ASPEval.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/ASPEval.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ASPEval.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ASPEval.cpp$(DependSuffix): ASPEval.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ASPEval.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ASPEval.cpp$(DependSuffix) -MM "ASPEval.cpp"

$(IntermediateDirectory)/ASPEval.cpp$(PreprocessSuffix): ASPEval.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ASPEval.cpp$(PreprocessSuffix) "ASPEval.cpp"

$(IntermediateDirectory)/ASPTranslate.cpp$(ObjectSuffix): ASPTranslate.cpp $(IntermediateDirectory)/ASPTranslate.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/ASPTranslate.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ASPTranslate.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ASPTranslate.cpp$(DependSuffix): ASPTranslate.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ASPTranslate.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ASPTranslate.cpp$(DependSuffix) -MM "ASPTranslate.cpp"

$(IntermediateDirectory)/ASPTranslate.cpp$(PreprocessSuffix): ASPTranslate.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ASPTranslate.cpp$(PreprocessSuffix) "ASPTranslate.cpp"

$(IntermediateDirectory)/Atom.cpp$(ObjectSuffix): Atom.cpp $(IntermediateDirectory)/Atom.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/Atom.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Atom.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Atom.cpp$(DependSuffix): Atom.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Atom.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Atom.cpp$(DependSuffix) -MM "Atom.cpp"

$(IntermediateDirectory)/Atom.cpp$(PreprocessSuffix): Atom.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Atom.cpp$(PreprocessSuffix) "Atom.cpp"

$(IntermediateDirectory)/AtomFactory.cpp$(ObjectSuffix): AtomFactory.cpp $(IntermediateDirectory)/AtomFactory.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/AtomFactory.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/AtomFactory.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/AtomFactory.cpp$(DependSuffix): AtomFactory.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/AtomFactory.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/AtomFactory.cpp$(DependSuffix) -MM "AtomFactory.cpp"

$(IntermediateDirectory)/AtomFactory.cpp$(PreprocessSuffix): AtomFactory.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/AtomFactory.cpp$(PreprocessSuffix) "AtomFactory.cpp"

$(IntermediateDirectory)/AtomNode.cpp$(ObjectSuffix): AtomNode.cpp $(IntermediateDirectory)/AtomNode.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/AtomNode.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/AtomNode.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/AtomNode.cpp$(DependSuffix): AtomNode.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/AtomNode.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/AtomNode.cpp$(DependSuffix) -MM "AtomNode.cpp"

$(IntermediateDirectory)/AtomNode.cpp$(PreprocessSuffix): AtomNode.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/AtomNode.cpp$(PreprocessSuffix) "AtomNode.cpp"

$(IntermediateDirectory)/AtomSet.cpp$(ObjectSuffix): AtomSet.cpp $(IntermediateDirectory)/AtomSet.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/AtomSet.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/AtomSet.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/AtomSet.cpp$(DependSuffix): AtomSet.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/AtomSet.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/AtomSet.cpp$(DependSuffix) -MM "AtomSet.cpp"

$(IntermediateDirectory)/AtomSet.cpp$(PreprocessSuffix): AtomSet.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/AtomSet.cpp$(PreprocessSuffix) "AtomSet.cpp"

$(IntermediateDirectory)/BoostComponentFinder.cpp$(ObjectSuffix): BoostComponentFinder.cpp $(IntermediateDirectory)/BoostComponentFinder.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/BoostComponentFinder.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/BoostComponentFinder.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/BoostComponentFinder.cpp$(DependSuffix): BoostComponentFinder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/BoostComponentFinder.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/BoostComponentFinder.cpp$(DependSuffix) -MM "BoostComponentFinder.cpp"

$(IntermediateDirectory)/BoostComponentFinder.cpp$(PreprocessSuffix): BoostComponentFinder.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/BoostComponentFinder.cpp$(PreprocessSuffix) "BoostComponentFinder.cpp"

$(IntermediateDirectory)/CLSolver.cpp$(ObjectSuffix): CLSolver.cpp $(IntermediateDirectory)/CLSolver.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/CLSolver.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CLSolver.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CLSolver.cpp$(DependSuffix): CLSolver.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CLSolver.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/CLSolver.cpp$(DependSuffix) -MM "CLSolver.cpp"

$(IntermediateDirectory)/CLSolver.cpp$(PreprocessSuffix): CLSolver.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CLSolver.cpp$(PreprocessSuffix) "CLSolver.cpp"

$(IntermediateDirectory)/Component.cpp$(ObjectSuffix): Component.cpp $(IntermediateDirectory)/Component.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/Component.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Component.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Component.cpp$(DependSuffix): Component.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Component.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Component.cpp$(DependSuffix) -MM "Component.cpp"

$(IntermediateDirectory)/Component.cpp$(PreprocessSuffix): Component.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Component.cpp$(PreprocessSuffix) "Component.cpp"

$(IntermediateDirectory)/ComponentFinder.cpp$(ObjectSuffix): ComponentFinder.cpp $(IntermediateDirectory)/ComponentFinder.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/ComponentFinder.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ComponentFinder.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ComponentFinder.cpp$(DependSuffix): ComponentFinder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ComponentFinder.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ComponentFinder.cpp$(DependSuffix) -MM "ComponentFinder.cpp"

$(IntermediateDirectory)/ComponentFinder.cpp$(PreprocessSuffix): ComponentFinder.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ComponentFinder.cpp$(PreprocessSuffix) "ComponentFinder.cpp"

$(IntermediateDirectory)/DependencyGraph.cpp$(ObjectSuffix): DependencyGraph.cpp $(IntermediateDirectory)/DependencyGraph.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/DependencyGraph.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DependencyGraph.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DependencyGraph.cpp$(DependSuffix): DependencyGraph.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/DependencyGraph.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/DependencyGraph.cpp$(DependSuffix) -MM "DependencyGraph.cpp"

$(IntermediateDirectory)/DependencyGraph.cpp$(PreprocessSuffix): DependencyGraph.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DependencyGraph.cpp$(PreprocessSuffix) "DependencyGraph.cpp"

$(IntermediateDirectory)/Error.cpp$(ObjectSuffix): Error.cpp $(IntermediateDirectory)/Error.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/Error.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Error.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Error.cpp$(DependSuffix): Error.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Error.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Error.cpp$(DependSuffix) -MM "Error.cpp"

$(IntermediateDirectory)/Error.cpp$(PreprocessSuffix): Error.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Error.cpp$(PreprocessSuffix) "Error.cpp"

$(IntermediateDirectory)/EvalComp.cpp$(ObjectSuffix): EvalComp.cpp $(IntermediateDirectory)/EvalComp.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/EvalComp.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/EvalComp.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EvalComp.cpp$(DependSuffix): EvalComp.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/EvalComp.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/EvalComp.cpp$(DependSuffix) -MM "EvalComp.cpp"

$(IntermediateDirectory)/EvalComp.cpp$(PreprocessSuffix): EvalComp.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/EvalComp.cpp$(PreprocessSuffix) "EvalComp.cpp"

$(IntermediateDirectory)/FAnswerSet.cpp$(ObjectSuffix): FAnswerSet.cpp $(IntermediateDirectory)/FAnswerSet.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/FAnswerSet.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FAnswerSet.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FAnswerSet.cpp$(DependSuffix): FAnswerSet.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FAnswerSet.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/FAnswerSet.cpp$(DependSuffix) -MM "FAnswerSet.cpp"

$(IntermediateDirectory)/FAnswerSet.cpp$(PreprocessSuffix): FAnswerSet.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FAnswerSet.cpp$(PreprocessSuffix) "FAnswerSet.cpp"

$(IntermediateDirectory)/Globals.cpp$(ObjectSuffix): Globals.cpp $(IntermediateDirectory)/Globals.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/Globals.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Globals.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Globals.cpp$(DependSuffix): Globals.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Globals.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Globals.cpp$(DependSuffix) -MM "Globals.cpp"

$(IntermediateDirectory)/Globals.cpp$(PreprocessSuffix): Globals.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Globals.cpp$(PreprocessSuffix) "Globals.cpp"

$(IntermediateDirectory)/GraphBuilder.cpp$(ObjectSuffix): GraphBuilder.cpp $(IntermediateDirectory)/GraphBuilder.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/GraphBuilder.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GraphBuilder.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GraphBuilder.cpp$(DependSuffix): GraphBuilder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GraphBuilder.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GraphBuilder.cpp$(DependSuffix) -MM "GraphBuilder.cpp"

$(IntermediateDirectory)/GraphBuilder.cpp$(PreprocessSuffix): GraphBuilder.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GraphBuilder.cpp$(PreprocessSuffix) "GraphBuilder.cpp"

$(IntermediateDirectory)/GraphProcessor.cpp$(ObjectSuffix): GraphProcessor.cpp $(IntermediateDirectory)/GraphProcessor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/GraphProcessor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GraphProcessor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GraphProcessor.cpp$(DependSuffix): GraphProcessor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GraphProcessor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GraphProcessor.cpp$(DependSuffix) -MM "GraphProcessor.cpp"

$(IntermediateDirectory)/GraphProcessor.cpp$(PreprocessSuffix): GraphProcessor.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GraphProcessor.cpp$(PreprocessSuffix) "GraphProcessor.cpp"

$(IntermediateDirectory)/Literal.cpp$(ObjectSuffix): Literal.cpp $(IntermediateDirectory)/Literal.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/Literal.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Literal.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Literal.cpp$(DependSuffix): Literal.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Literal.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Literal.cpp$(DependSuffix) -MM "Literal.cpp"

$(IntermediateDirectory)/Literal.cpp$(PreprocessSuffix): Literal.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Literal.cpp$(PreprocessSuffix) "Literal.cpp"

$(IntermediateDirectory)/MIPMinCheck.cpp$(ObjectSuffix): MIPMinCheck.cpp $(IntermediateDirectory)/MIPMinCheck.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/MIPMinCheck.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MIPMinCheck.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MIPMinCheck.cpp$(DependSuffix): MIPMinCheck.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MIPMinCheck.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MIPMinCheck.cpp$(DependSuffix) -MM "MIPMinCheck.cpp"

$(IntermediateDirectory)/MIPMinCheck.cpp$(PreprocessSuffix): MIPMinCheck.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MIPMinCheck.cpp$(PreprocessSuffix) "MIPMinCheck.cpp"

$(IntermediateDirectory)/ProcessBuff.cpp$(ObjectSuffix): ProcessBuff.cpp $(IntermediateDirectory)/ProcessBuff.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/ProcessBuff.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ProcessBuff.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ProcessBuff.cpp$(DependSuffix): ProcessBuff.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ProcessBuff.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ProcessBuff.cpp$(DependSuffix) -MM "ProcessBuff.cpp"

$(IntermediateDirectory)/ProcessBuff.cpp$(PreprocessSuffix): ProcessBuff.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ProcessBuff.cpp$(PreprocessSuffix) "ProcessBuff.cpp"

$(IntermediateDirectory)/Program.cpp$(ObjectSuffix): Program.cpp $(IntermediateDirectory)/Program.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/Program.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Program.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Program.cpp$(DependSuffix): Program.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Program.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Program.cpp$(DependSuffix) -MM "Program.cpp"

$(IntermediateDirectory)/Program.cpp$(PreprocessSuffix): Program.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Program.cpp$(PreprocessSuffix) "Program.cpp"

$(IntermediateDirectory)/Registry.cpp$(ObjectSuffix): Registry.cpp $(IntermediateDirectory)/Registry.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/Registry.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Registry.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Registry.cpp$(DependSuffix): Registry.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Registry.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Registry.cpp$(DependSuffix) -MM "Registry.cpp"

$(IntermediateDirectory)/Registry.cpp$(PreprocessSuffix): Registry.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Registry.cpp$(PreprocessSuffix) "Registry.cpp"

$(IntermediateDirectory)/Rewrite.cpp$(ObjectSuffix): Rewrite.cpp $(IntermediateDirectory)/Rewrite.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/Rewrite.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Rewrite.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Rewrite.cpp$(DependSuffix): Rewrite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Rewrite.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Rewrite.cpp$(DependSuffix) -MM "Rewrite.cpp"

$(IntermediateDirectory)/Rewrite.cpp$(PreprocessSuffix): Rewrite.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Rewrite.cpp$(PreprocessSuffix) "Rewrite.cpp"

$(IntermediateDirectory)/Rule.cpp$(ObjectSuffix): Rule.cpp $(IntermediateDirectory)/Rule.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/Rule.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Rule.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Rule.cpp$(DependSuffix): Rule.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Rule.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Rule.cpp$(DependSuffix) -MM "Rule.cpp"

$(IntermediateDirectory)/Rule.cpp$(PreprocessSuffix): Rule.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Rule.cpp$(PreprocessSuffix) "Rule.cpp"

$(IntermediateDirectory)/SafetyChecker.cpp$(ObjectSuffix): SafetyChecker.cpp $(IntermediateDirectory)/SafetyChecker.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/SafetyChecker.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SafetyChecker.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SafetyChecker.cpp$(DependSuffix): SafetyChecker.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SafetyChecker.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SafetyChecker.cpp$(DependSuffix) -MM "SafetyChecker.cpp"

$(IntermediateDirectory)/SafetyChecker.cpp$(PreprocessSuffix): SafetyChecker.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SafetyChecker.cpp$(PreprocessSuffix) "SafetyChecker.cpp"

$(IntermediateDirectory)/SpiritProgramParser.cpp$(ObjectSuffix): SpiritProgramParser.cpp $(IntermediateDirectory)/SpiritProgramParser.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/SpiritProgramParser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SpiritProgramParser.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SpiritProgramParser.cpp$(DependSuffix): SpiritProgramParser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SpiritProgramParser.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SpiritProgramParser.cpp$(DependSuffix) -MM "SpiritProgramParser.cpp"

$(IntermediateDirectory)/SpiritProgramParser.cpp$(PreprocessSuffix): SpiritProgramParser.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SpiritProgramParser.cpp$(PreprocessSuffix) "SpiritProgramParser.cpp"

$(IntermediateDirectory)/Term.cpp$(ObjectSuffix): Term.cpp $(IntermediateDirectory)/Term.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/creep/GitHub/ffasp/Term.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Term.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Term.cpp$(DependSuffix): Term.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Term.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Term.cpp$(DependSuffix) -MM "Term.cpp"

$(IntermediateDirectory)/Term.cpp$(PreprocessSuffix): Term.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Term.cpp$(PreprocessSuffix) "Term.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


