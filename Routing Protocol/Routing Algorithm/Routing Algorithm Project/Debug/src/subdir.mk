################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/edge.cpp \
../src/graph.cpp \
../src/graphColoring.cpp \
../src/hNode.cpp \
../src/kruskal.cpp \
../src/longestPath.cpp \
../src/scenicRouting.cpp 

OBJS += \
./src/edge.o \
./src/graph.o \
./src/graphColoring.o \
./src/hNode.o \
./src/kruskal.o \
./src/longestPath.o \
./src/scenicRouting.o 

CPP_DEPS += \
./src/edge.d \
./src/graph.d \
./src/graphColoring.d \
./src/hNode.d \
./src/kruskal.d \
./src/longestPath.d \
./src/scenicRouting.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


