/*
    Consists of other helper functions for supplementing the main functions
*/

#include "assembler.h"

FILE *get_file(char *arg)
{
    if(arg == NULL) 
    {
        die("No file provided\nProvide a file with extension .asm");
        return NULL;
    }

    else
    {
        int str_len = strlen(arg);

        int index = str_len - 1;

        if(arg[index - 3] == '.' && arg[index - 2] == 'a' && arg[index - 1] == 's' && arg[index] == 'm')
        {
            FILE *file_ptr = fopen(arg, "r");
            if(file_ptr == NULL) die("File not found in provided directory");

            return file_ptr;
        }

        else 
        {
            die("Invalid filetype\nFile must be of type .asm (HACK Assembler)");
            return NULL;
        }
    }
}

FILE *get_bin_file(char *arg)
{
    int str_len = strlen(arg);

    char *bin_filename = calloc((str_len + 2), sizeof(char));
    
    strcpy(bin_filename, arg);

    int l_index = (str_len + 2) - 2;

    bin_filename[l_index - 3] = 'h';
    bin_filename[l_index - 2] = 'a';
    bin_filename[l_index - 1] = 'c';
    bin_filename[l_index] = 'k';

    FILE *bin_file_ptr = fopen(bin_filename, "w");
    if(bin_file_ptr == NULL) die("Could not open binary (.hack) file");

    return bin_file_ptr;
}

// String to integer conversion
int str_to_int(char *string)
{
    int str_len = strlen(string);

    int integer = 0;

    for(int i = 0; i < str_len; i++)
    {
        integer = (10 * integer) + ((int) string[i] - 48);
    }

    return integer;
}

// Decimal to binary
char *dec_to_bin(int decimal)
{
    char *binary = calloc(BIN_WORD_SIZE, sizeof(char));
    if(binary == NULL) die("Allocation failed for binary");

    // Initialize every character with 0
    for(int i = 0; i < (BIN_WORD_SIZE - 1); i++) binary[i] = '0';

    int i = BIN_WORD_SIZE - 2;
    while(decimal > 0)
    {
        int c = decimal % 2;
        decimal = decimal / 2;

        binary[i] = (char) (c + 48);

        i = i - 1;
    }

    return binary;
}