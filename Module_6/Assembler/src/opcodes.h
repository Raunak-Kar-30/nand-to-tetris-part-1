// All the valid tokens are described here

// Defines
#define NUM_OF_COMP_FIELDS 28
#define NUM_OF_DEST_FIELDS 8
#define NUM_OF_JUMP_FIELDS 8

const char comp_field[28][5] = {
    "0",
    "1",
    "-1",
    "D",
    "A",
    "M",
    "!D",
    "!A",
    "!M",
    "-D",
    "-A",
    "-M",
    "D+1",
    "A+1",
    "M+1",
    "D-1",
    "A-1",
    "M-1",
    "D+A",
    "D+M",
    "D-A",
    "D-M",
    "A-D",
    "M-D",
    "D&A",
    "D&M",
    "D|A",
    "D|M"};

const char dest_field[8][5] = {
    "\0",
    "M",
    "D",
    "MD",
    "A",
    "AM",
    "AD",
    "AMD"};

const char jump_field[8][5] = {
    "\0",
    "JGT",
    "JEQ",
    "JGE",
    "JLT",
    "JNE",
    "JLE",
    "JMP"};

const char comp_binary[28][10] = {
    "0101010",
    "0111111",
    "0111010",
    "0001100",
    "0110000",
    "1110000",
    "0001101",
    "0110001",
    "1110001",
    "0001111",
    "0110011",
    "1110011",
    "0011111",
    "0110111",
    "1110111",
    "0001110",
    "0110010",
    "1110010",
    "0000010",
    "1000010",
    "0010011",
    "1010011",
    "0000111",
    "1000111",
    "0000000",
    "1000000",
    "0010101",
    "1010101"};

const char dest_binary[8][10] = {
    "000",
    "001",
    "010",
    "011",
    "100",
    "101",
    "110",
    "111"};

const char jump_binary[8][10] = {
    "000",
    "001",
    "010",
    "011",
    "100",
    "101",
    "110",
    "111"};