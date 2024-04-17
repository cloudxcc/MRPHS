# MRPHS v0.1

MRPHS compiles PDVL code into SystemVerilog (MRPHS_D) code.

The project is still under construction !!!

The project is licensed under the Apache License, Version 2.0 (the “License”).

## Installing

Download the tool from github:

git clone https://github.com/cloudxcc/MRPHS.git

## Documentation/Doxygen 

The Doxygen enhanced code overview can be found here:

MRPHS/v0.1/doxygen/doc/htm/index.html

In order to update the Doxygen based docu, go to MRPHS/v0.1/work and execute:

make doxygen

## Compiling PDVL to SystemVerilog:

Go to MRPHS/v0.1/work and execute:

make MRPHS_D

The MRPHS_D.exe file can be found in the bin directory.

## MRPHS options:

The following options apply to MRPHS_D: 

   -h, --help:  Display this text and exit  
   
   -rl:         Report level            
   
   -s:          Source file (list)     
   
   -top:        Top level name (optional)
   
   -o:          Output directory



