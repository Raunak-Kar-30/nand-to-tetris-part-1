/*
    Reads a line
    Gets the instruction from the line
    Breaks the entire instruction in the line into instructions and checks the validity of the instructions
*/

#include "assembler.h"

// Read one line from the file
char *read_line(FILE *file_ptr)
{
    if(file_ptr == NULL) die("NULL file provided");

    int buff_size = LINE_BUFF_SIZE;
    char *line = calloc(buff_size, sizeof(char));
    if(line == NULL) die("Allocation failed for line in read_line()");

    int len = 0;    // Accounts for the total length of the line read
    char c = ' ';

    while((c = fgetc(file_ptr)) != '\n' && c != EOF)
    {
        len = len + 1;

        line[len - 1] = c;

        if(len == buff_size)
        {
            line = realloc(line, sizeof(char) * (2 * buff_size));
            if(line == NULL) die("Reallocation failed for line in read_line()");

            buff_size = 2 * buff_size;
        }
    }

    if(c == '\n') line[len] = '\0';

    else if(c == EOF) line[len] = '\0';

    return line;
}

// Get the instruction from the line
char *get_instruction(char *line)
{
    // Store the max len
    int instr_size = INSTR_BUFF_SIZE;
    
    // Store the instruction
    char *instruction = calloc(instr_size, sizeof(char));
    if(instruction == NULL) die("Allocation failed for instruction in get_instruction()");

    // Set the index and read the line
    int i = 0;
    int j = 0;

    while(line[i] != '\0')
    {
        if(isspace(line[i]))
        {
            i = i + 1;
            continue;
        }

        else if(line[i] == '/' && line[i+1] == '/') break;

        else
        {
            instruction[j] = line[i];

            if((j + 1) == instr_size)
            {
                instruction = realloc(instruction, sizeof(char) * (instr_size * 2));
                if(instruction == NULL) die("Reallocation failed for instruction in get_instruction()");

                instr_size = 2 * instr_size;
            }

            j = j + 1;
        }

        i = i + 1;
    }

    return instruction;
}

// Checks if an instruction is a label, if so - returns the label
char *get_label(char *instruction)
{
    // Store the max size of label
    int len = strlen(instruction);

    if(instruction[0] == '(' && instruction[len - 1] == ')')
    {
        // Store the label
        char *label = calloc(len, sizeof(char));
        if(label == NULL) die("Allocation failed for label in get_label()");

        int i = 0;
        int l = 0;

        
        while(instruction[++i] != ')')
        {
            if((!(isalnum(instruction[i]))) && instruction[i] != '.' && instruction[i] != '_' && instruction[i] != '$' && instruction[i] != ':') return "\0";

            label[l] = instruction[i];
            l = l + 1;
        }

        return label;
    }

    return "\0";
}
