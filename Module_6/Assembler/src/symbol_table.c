/*
    Source code for symbol table creation, addition and searching
*/

#include "assembler.h"

// Initialize the table
symbol_table *init_sym_table(int len)
{
    if(len > 0)
    {
        symbol_table *sym_table_ptr = calloc(1, sizeof(symbol_table));
        if(sym_table_ptr == NULL) die("Allocation failed for symbol table struct");

        sym_table_ptr->symbol = calloc(len, sizeof(char*));
        if(sym_table_ptr->symbol == NULL) die("Allocation failed for symbol array in symbol table");

        for(int i = 0; i < len; i++)
        {
            sym_table_ptr->symbol[i] = calloc(SYM_BUFF_SIZE, sizeof(char));
            if(sym_table_ptr->symbol[i] == NULL) die("Allocation failed for symbols in the symbol table");
        }

        sym_table_ptr->address = calloc(len, sizeof(int));
        if(sym_table_ptr->address == NULL) die("Allocation failed for address array in symbol table");

        sym_table_ptr->table_len = 0;
        sym_table_ptr->table_size = len;

        return sym_table_ptr;
    }

    else
    {
        die("Invalid length for symbol table allocation");
        return NULL;
    }
}

void resize_sym_table(symbol_table *sym_table_ptr, int len)
{
    if((sym_table_ptr != NULL) && (len > 0))
    {
        int sym_table_len = (sym_table_ptr)->table_size;

        (sym_table_ptr)->symbol = realloc((sym_table_ptr)->symbol, sizeof(char*) * len);
        if((sym_table_ptr)->symbol == NULL) die("Reallocation failed for symbol array in symbol table");

        for(int i = sym_table_len; i < len; i++)
        {
            (sym_table_ptr)->symbol[i] = calloc(SYM_BUFF_SIZE, sizeof(char));
            if((sym_table_ptr)->symbol[i] == NULL) die("Rellocation failed for symbols in the symbol table");
        }

        (sym_table_ptr)->address = realloc((sym_table_ptr)->address, sizeof(int) * len);
        if((sym_table_ptr)->address == NULL) die("Reallocation failed for address array in symbol table");

        (sym_table_ptr)->table_size = len;
    }

    else if(sym_table_ptr == NULL) die("Null pointer cannot be resized");

    else die("Invalid length for symbol table reallocation");
}


// Create the default symbol table
symbol_table *create_sym_table(void)
{
    symbol_table *sym_table_ptr = init_sym_table(20);

    add_symbol(sym_table_ptr, "R0", 0);
    add_symbol(sym_table_ptr, "R1", 1);
    add_symbol(sym_table_ptr, "R2", 2);
    add_symbol(sym_table_ptr, "R3", 3);
    add_symbol(sym_table_ptr, "R4", 4);
    add_symbol(sym_table_ptr, "R5", 5);
    add_symbol(sym_table_ptr, "R6", 6);
    add_symbol(sym_table_ptr, "R7", 7);
    add_symbol(sym_table_ptr, "R8", 8);
    add_symbol(sym_table_ptr, "R9", 9);
    add_symbol(sym_table_ptr, "R10", 10);
    add_symbol(sym_table_ptr, "R11", 11);
    add_symbol(sym_table_ptr, "R12", 12);
    add_symbol(sym_table_ptr, "R13", 13);
    add_symbol(sym_table_ptr, "R14", 14);
    add_symbol(sym_table_ptr, "R15", 15);
    add_symbol(sym_table_ptr, "SCREEN", 16384);
    add_symbol(sym_table_ptr, "KBD", 24576);
    add_symbol(sym_table_ptr, "SP", 0);
    add_symbol(sym_table_ptr, "LCL", 1);
    add_symbol(sym_table_ptr, "ARG", 2);
    add_symbol(sym_table_ptr, "THIS", 3);
    add_symbol(sym_table_ptr, "THAT", 4);

    return sym_table_ptr;
}

// Add symbols to the symbol table
void add_symbol(symbol_table *sym_table_ptr, char *symbol, int address)
{
    sym_table_ptr->table_len = sym_table_ptr->table_len + 1;

    int sym_table_len = sym_table_ptr->table_len;
    int index = sym_table_len- 1;

    int sym_len = strlen(symbol);

    if(sym_len > SYM_BUFF_SIZE)
    {
        sym_table_ptr->symbol[index] = realloc(sym_table_ptr->symbol[index], sizeof(char) * sym_len);
    }

    strcpy(sym_table_ptr->symbol[index], symbol);
    sym_table_ptr->address[index] = address;

    if(sym_table_ptr->table_len == sym_table_ptr->table_size) resize_sym_table(sym_table_ptr, (2 * sym_table_len));
}

// Search the symbol table
int search_sym_table(symbol_table *sym_table_ptr, char *symbol)
{
    // Get the current length of the symbol table
    int sym_table_len = sym_table_ptr->table_len;

    // Search the table and return the index if found
    for(int i = 0; i < sym_table_len; i++) if(!(strcmp(sym_table_ptr->symbol[i], symbol))) return sym_table_ptr->address[i];

    return (-1);
}

// Diplay the table -- temporary function
void disp_sym_table(symbol_table *sym_table_ptr)
{
    int len = sym_table_ptr->table_len;

    for(int i = 0; i < len; i++) printf("%s\t\t%d\n", sym_table_ptr->symbol[i], sym_table_ptr->address[i]);
}