//---------------------------------------------------------------------------------------------------------------------------------------
// Assembler code for HACK assembler of Nand to Tetris
// Fun and exciting experiment and project

// The aim of this program is to translate any HACK assembly (.asm) file into the HACK binary file (.hack)

// Plan : 
//  Contains two functions - first pass and second pass
//  The first pass function goes through the program and creates a symbol table containing all the labels from the program and the pre-defined symbols
//  The second part then goes through the program once again which replaces every symbol from the symbol table 
//  and simultaneously converts the assembly code to the binary code

// Goals : 
//  1. Should only read a file with extension .hka (hack assembly)
//  2. Should be able to read multiple files and convert them to hack all at once (into distinct files)
//  3. Program finally outputs 3 things : The symbol table, the raw asm file (without labels, symbols and comments and redundant spaces), and the binary file

// Author : Raunak Kar
// Assignment of : Nand to Tetris Part 1, Module 6

//---------------------------------------------------------------------------------------------------------------------------------------

#include "assembler.h"

int main(int argc, char **argv)
{
    // Creation of symbol table
    symbol_table *sym_table_ptr = create_sym_table();

    // Get the source file
    FILE *file_ptr = get_file(argv[1]);

    // First pass
    first_pass(file_ptr, sym_table_ptr);

    // Get binary file
    FILE *bin_file_ptr = get_bin_file(argv[1]);

    // Second pass
    second_pass(file_ptr, bin_file_ptr, sym_table_ptr);
    //disp_sym_table(sym_table_ptr);

    return 0;
}

// The first pass function
void first_pass(FILE *file_ptr, symbol_table *sym_table_ptr)
{
    int line_number = 0;
    int instr_number = -1;

    while(1)
    {
        if(feof(file_ptr)) break;

        char *line = read_line(file_ptr);
        line_number = line_number + 1;

        char *instruction = get_instruction(line);
        if(*instruction != '\0')
        {
            // Check if label
            char *label = get_label(instruction);
            if(*label != '\0') 
            {
                int address = 0;
                if((address = search_sym_table(sym_table_ptr, label)) == (-1)) add_symbol(sym_table_ptr, label, (instr_number + 1));
                
                else error("Symbol redefined", line_number);
            }

            // If not label, increment the instruction number
            else instr_number  = instr_number + 1;
        }
        
        free(instruction);
        free(line);
    }

    // Move the file pointer to the beginning of the file
    fseek(file_ptr, 0, SEEK_SET);
}

// The second pass function
void second_pass(FILE *file_ptr, FILE *bin_file_ptr, symbol_table *sym_table_ptr)
{
    int line_number = 0;
    int instr_number = -1;

    while(1)
    {
        if(feof(file_ptr)) break;

        char *line = read_line(file_ptr);
        line_number = line_number + 1;

        char *binary = calloc((BIN_WORD_SIZE + 1), sizeof(char));
        if(binary == NULL) die("Allocation failed for binary");

        char *instruction = get_instruction(line);
        if(*instruction != '\0')
        {
            // Check if label
            if(*get_label(instruction) != '\0') continue;

            // Check for a instruction
            else if(*(binary = gen_a_binary(instruction, sym_table_ptr)) != '\0')
            {
                instr_number = instr_number + 1;
                fprintf(bin_file_ptr, "%s\n", binary);
            }

            else if(*(binary = gen_c_binary(instruction)) != '\0')
            {
                instr_number  = instr_number + 1;
                fprintf(bin_file_ptr, "%s\n", binary);
            }

            else error("Invalid instruction", line_number);
        }
        
        free(instruction);
        free(line);
        free(binary);
    }

    // close the files
    fclose(file_ptr);
    fclose(bin_file_ptr);
}