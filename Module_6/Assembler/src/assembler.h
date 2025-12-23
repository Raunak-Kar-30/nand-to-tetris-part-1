// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Defines
#define SYM_BUFF_SIZE   50
#define INSTR_BUFF_SIZE 50
#define LINE_BUFF_SIZE  250
#define BIN_WORD_SIZE   16      

// ----------------------------------------------------------------------------------------------------
// Data structures
// // The e-flag denotes that the last element in the allocated array has reached
// The table holds the key value pair
typedef struct
{
    char **symbol;
    int *address;
    int table_len;
    int table_size;
} symbol_table;

// ----------------------------------------------------------------------------------------------------
// Function declarations
// Table and data functions
symbol_table *init_sym_table(int len);
void resize_sym_table(symbol_table *sym_table_ptr, int len);
symbol_table *create_sym_table(void);
void add_symbol(symbol_table *sym_table_ptr, char *symbol, int address);
int search_sym_table(symbol_table *sym_table_ptr, char *symbol);
void disp_sym_table(symbol_table *sym_table_ptr);       // Temp function

// Control functions
void first_pass(FILE *file_ptr, symbol_table *sym_table_ptr);
void second_pass(FILE *file_ptr, FILE *bin_file_ptr, symbol_table *sym_table_ptr);

// Analyzer functions
char *read_line(FILE *file_ptr);
char *get_instruction(char *line);
char *get_label(char *instruction);

// Generator functions
int get_address(symbol_table *sym_table_ptr, char *symbol);
char *gen_a_binary(char *instruction, symbol_table *sym_table_ptr);
char *gen_c_binary(char *instruction);
char *search_c_field(char *field, int type);

// Misc functions
FILE *get_file(char *arg);
FILE *get_bin_file(char *arg);
int str_to_int(char *string);
char *dec_to_bin(int decimal);

// Error functions
void error(char *message, int line_number);
void die(char *message);

