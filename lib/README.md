# Library Directory
This directory is intended for project specific (private) libraries.
PlatformIO will compile them to static libraries and link into the executable file.

The source code of each library should be placed in a separate directory
("lib/your_library_name/[Code]").

Current Project Directory:

lib/  
├── AppCore/  
│   └── AppCore.h  
│
├── Boards/  
│   └── PrestoBoard.h
│   └── PrestoJrBoard.h
│   └── SensorBoard.h  
│  
├── Estop/  
│   └── Estop.h  
│   └── LeakSensor.h (planned)  
│   └── WatchdogEstop.h (planned)
│   └── InternalEstop.h (planned)
│  
├── LEDMux/  
│   ├── led_mux.pio  
│   ├── led_mux.pio.h  
│   ├── LEDMux.cpp  
│   └── LEDMux.h  
│  
├── MotorControl/  
│   ├── MotorController.cpp  
│   └── MotorController.h  
|
├── NeoPixel/  
│   ├── StatusLight.h  
|
├── PIO/  
│   └── (PIO assembly scripts)  
├── PIOExamples/  
│   └── (example PIO code and experiments)    
├── PIOFiles/  
│   └── (Wrapper .c and .h files for PIO usage) 
├── PIOInterfaces/  
│   └── (our PIO interfaces for SPI, DMA, and/or I2C) - deprecated
│  
├── Proto/  
│   └── (Protobuf message definitions) 
├── ProtoFiles/  
│   └── (Protobuf message packers and senders) 
├── ProtoHandlers/  
│   └── (Protobuf message packers and senders) 
├── ProtoSim/  
│   └── (Python simulators for testing Protobuf) 
│  
├── Sensors/  
│   ├── DOFStick.cpp  
│   ├── DOFStick.h  
│   ├── TempSensor.cpp  
│   └── TempSensor.h  
│  
├── VariableBlink/  
│   ├── blink_input.pio  
│   ├── blink_input.pio.h  
│   ├── LEDPIO.cpp  
│   └── LEDPIO.h  
│  
├── README --> THIS FILE  
└── README copy  (the original PlatformIO REadME)  

# Project Modules 
This repository is organized into modular components, separating hardware abstractions, core logic, and reference implementations.


## AppCore

Contains the central application interfaces.  
Defines logical flow of the application

## Boards

An alternative to AppCore, this makes our central application interfaces board specific.  
Defines logical flow of each individual board, meaning we need less build flags.
Need to add optionality between RTOS and superloop.

## Estop

Module to handle emergency stop via interrupts  
Provides critical interfaces for immediately halting system operations in response to safety triggers.
Additional File for handling leak sensors, since this also has it's own EStop situation, but remarkably similar since they're both just GPIO signals that we can just have 2 Estop objects.

## MotorControl

Implementation for motor drivers and other controlled outputs  
Encapsulates the control logic for movement and actuation.

## Sensors

Drivers and abstractions for environmental and input data.  
Interfacing via SPI or I2C in the main CPU context.

### DOFStick 
Interface for multi-axis input devices.  

### TempSensor 
Support for temperature and humidity measurement and monitoring.

## PIO (Programmable I/O) Implementations
Due to the fact that LDF only searches top-level folders, these are individually stored in their own folders

### LEDMux

High-performance LED multiplexing using the PIO peripheral.  

Uses .pio files for assembly-level timing and .cpp/.h for the high-level C++ API.

### VariableBlink

A practical example of input-driven timing using PIO peripheral.

Demonstrates real-time integration between C++ logic and PIO state machines.

# Protobuf and PIO
This section is dedicated solely to explaining the structure of our PIO and Protobuf files since they are generated during build through scripts in the main directory.

## Programmable IO Implementations
### PIO
Store the raw PIO Assembly scripts here

### PIOExamples
These are examples pulled from the internet to test, so basically a collection of experimental and reference implementations for developers to use as a sandbox. 

### PIOFiles
Generated PIO Wrapper files are stored here. These are the .c and .h files that enable us to interact with the PIO state machines.

### PIO Interfaces
These are the fancy PIO Handlers specifically focused on communication protocols and not a specific module, which is why they are stored here.
Inital focus will be PIO I2C interface and PIO DMA controller

## Protobuf Implementations
### Proto
This is where the protobuf messages are stored

### ProtoFiles
This is where the wrapper files generated for the protobuf messages are stored.

### ProtoHandlers
This is where we will store Protobuf Handlers that send and receive messages. Might take some work to figure out how to have each of the modules be able to send, but this might just be a pass Serial reference thing.

### ProtoSim
These are python scripts for testing and simulating Protobuf. For instance, the ProtoReceiver.py reads and decodes the Protobuf messages from your COM port when connected via USB.




  
  
# Library Dependency Finder

The PlatformIO Library Dependency Finder will find automatically dependent
libraries by scanning project source files.

More information about PlatformIO Library Dependency Finder
- https://docs.platformio.org/page/librarymanager/ldf.html

