# alejandro_mozqueda_proj3

In the first and second programming projects, the code processed commands from a text file
and displayed the results of each command. In part 3 of this project, ALU
functions from part 2 are used to process commands in assembly language format.

Two registers or an immediate value will be used in some operation in hexadecimal format. The hexadecimal prefix is ”0x” and is not to be considered in any conversion process. The uint32t data type in C/C++ is being used to store the number as an unsigned 32-bit number. The provided text file is used as an example input. This program reads various commands, and it will perform the operation between the two hexadecimal numbers. The result of the operation is displayed to the terminal and build environment.
The following are the list of acceptable commands:
ADD
AND
ASR
LSR
LSL
NOT
ORR
SUB
XOR 
MOV

Every operation uses unsigned 32-bit values except the ASR operation. For ASR, the values are 
treated as signed 32-bit values. Using the provided text file as an example input. The results 
output is printed in the same order as the text input file as the value in 32 bits.
This program implements the registers r0-r7. These registers are initialized to 0x0 
before the code begins reading input.
Changes made to a register by one instruction remain the same and available in subsequent
instructions.
