// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

// Initializing i (loop counter to 0)
    @0
    D=A
    @i      // Storing the value in D=RAM[0] in i
    M=D

// Initiliazing R2 to 0 as well (since it will hold the multiplication value)
    @0
    D=A
    @R2
    M=D

// Main loop for the multiplication
(LOOP)
    // Loop check condition
    @i
    D=M     // Storing the value of i in D
    @R1
    D=D-M   // Subtracting the value of M from D (this should result in a negative number if i < R[1])
    @END
    D;JGE   // If D = i - RAM[1] >= 0 (meaning i >= RAM[1], since i starts from 0) then goto END labeded instructions

    // Multiplication
    @R0
    D=M     // Storing the value of RAM[0] in D
    @R2     // Adding RAM[0] to the value in RAM[2]
    M=D+M

    // Increment i
    @i
    M=M+1

    // Jump back to the LOOP beginning
    @LOOP
    0;JMP

// End loop
(END)
    @END
    0;JMP
