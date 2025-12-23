// Includes
#include "assembler.h"
#include "opcodes.h"

// Search for a symbol in the symbol table
// If symbol not found, add it to the symbol table starting from 16 onwards
int get_address(symbol_table *sym_table_ptr, char *symbol)
{
    static int new_sym_address = 16;

    int address = search_sym_table(sym_table_ptr, symbol);

    if(address == (-1))
    {
        add_symbol(sym_table_ptr, symbol, new_sym_address);
        address = new_sym_address;

        new_sym_address = new_sym_address + 1;
    }

    return address;
}

// Search c instruction
char *search_c_field(char *field, int type)
{
    if(type == 1)
    {
        for(int i = 0; i < NUM_OF_COMP_FIELDS; i++) 
        {
            if(!(strcmp(comp_field[i], field))) 
            {
                char *binary = calloc(BIN_WORD_SIZE, sizeof(char));
                strcpy(binary, comp_binary[i]);

                return binary;
            }
        }
    }

    else if(type == 2)
    {
        for(int i = 0; i < NUM_OF_DEST_FIELDS; i++) 
        {
            if(!(strcmp(dest_field[i], field))) 
            {
                char *binary = calloc(BIN_WORD_SIZE, sizeof(char));
                strcpy(binary, dest_binary[i]);

                return binary;
            }
        }
    }

    else if(type == 3)
    {
        for(int i = 0; i < NUM_OF_JUMP_FIELDS; i++) 
        {
            if(!(strcmp(jump_field[i], field))) 
            {
                char *binary = calloc(BIN_WORD_SIZE, sizeof(char));
                strcpy(binary, jump_binary[i]);

                return binary;
            }
        }
    }

    return "\0";
}



// Generates the binary equivalent of a-instruction
char *gen_a_binary(char *instruction, symbol_table *sym_table_ptr)
{
    // Check if '@' present
    if(instruction[0] == '@')
    {
        // Store the binary equivalent of a instruction
        char *binary = calloc(BIN_WORD_SIZE + 1, sizeof(char));
        if(binary == NULL) die("Allocation failed for binary in gen_a_binary()");

        // Store the address
        int address = 0;

        // Store the length of the instruction
        int str_len = strlen(instruction);

        // Store the a value after '@'
        char *value = calloc(str_len, sizeof(char));
        if(value == NULL) die("Allocation failed for value in gen_a_binary()");

        // Is symbol flag
        int is_sym = 0;

        int j = 0;

        // Read the instruction 
        for(int i = 1; i < str_len; i++)
        {
            if((!(isalnum(instruction[i]))) && instruction[i] != '.' && instruction[i] != '_' && instruction[i] != '$' && instruction[i] != ':') return "\0";

            if(!(isdigit(instruction[i]))) is_sym = 1;

            value[j] = instruction[i];
            j = j + 1;
        }

        // Check if value is a symbol
        if(is_sym) address = get_address(sym_table_ptr, value);
        else address = str_to_int(value);

        // Convert the address to binary
        char *bin_addr = dec_to_bin(address);

        // Complete the binary instruction
        strcat(binary, "0");
        strcat(binary, bin_addr);
    
        return binary;
    }

    return "\0";
}

// Generates the binary equivalent of c-instruction -- proud of this function
char *gen_c_binary(char *instruction)
{
    int str_len = strlen(instruction);
    char *field = calloc((str_len + 1), sizeof(char));
    int f = 0;

    char *dest = calloc((str_len + 1), sizeof(char));
    char *comp = calloc((str_len + 1), sizeof(char));
    char *jump = calloc((str_len + 1), sizeof(char));

    for(int i = 0; i < str_len; i++)
    {
        if(instruction[i] == '=')
        {
            strcpy(dest, field);
            f = 0;
            continue;
        }

        else if(instruction[i] == ';')
        {
            strcpy(comp, field);
            f = 0;
            continue;
        }

        field[f] = instruction[i];
        f = f + 1;
    }
    
    if(*comp != '\0') strcpy(jump, field);
    if(*comp == '\0') strcpy(comp, field);

    // Store the binary of c instruction and for the field
    char *binary = calloc(BIN_WORD_SIZE + 1, sizeof(char));
    if(binary == NULL) die("Allocation failed for binary in gen_c_binary()");
    strcat(binary, "111");

    char *field_binary = calloc(BIN_WORD_SIZE, sizeof(char));
    if(binary == NULL) die("Allocation failed for field_binary in gen_c_binary()");

    // Search comp field
    if(*(field_binary = search_c_field(comp, 1)) == '\0') return "\0";
    strcat(binary, field_binary);

    // Search dest field
    if(*(field_binary = search_c_field(dest, 2)) == '\0') return "\0";
    strcat(binary, field_binary);

    // Search jump field
    if(*(field_binary = search_c_field(jump, 3)) == '\0') return "\0";
    strcat(binary, field_binary);

    return binary;
}