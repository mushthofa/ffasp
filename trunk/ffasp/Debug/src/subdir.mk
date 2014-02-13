################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Atom.cpp \
../src/Error.cpp \
../src/ExprNode.cpp \
../src/Literal.cpp \
../src/ProcessBuff.cpp \
../src/Term.cpp \
../src/ffasp.cpp 

OBJS += \
./src/Atom.o \
./src/Error.o \
./src/ExprNode.o \
./src/Literal.o \
./src/ProcessBuff.o \
./src/Term.o \
./src/ffasp.o 

CPP_DEPS += \
./src/Atom.d \
./src/Error.d \
./src/ExprNode.d \
./src/Literal.d \
./src/ProcessBuff.d \
./src/Term.d \
./src/ffasp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


