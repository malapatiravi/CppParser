################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/LexicalAnalysis.cpp \
../src/Lines.cpp \
../src/Object.cpp \
../src/SemiExp.cpp \
../src/Special.cpp \
../src/SyntaxAnalysis.cpp \
../src/Tokenizer.cpp \
../src/test.cpp 

OBJS += \
./src/LexicalAnalysis.o \
./src/Lines.o \
./src/Object.o \
./src/SemiExp.o \
./src/Special.o \
./src/SyntaxAnalysis.o \
./src/Tokenizer.o \
./src/test.o 

CPP_DEPS += \
./src/LexicalAnalysis.d \
./src/Lines.d \
./src/Object.d \
./src/SemiExp.d \
./src/Special.d \
./src/SyntaxAnalysis.d \
./src/Tokenizer.d \
./src/test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


