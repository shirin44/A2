#ifndef COMMANDS_H
#define COMMANDS_H

// Include necessary headers
#include "mbox.h"
#include "colors.h"
#include "../../uart/uart0.h"
#include "string_utils.h"

// Declarations of command handling functions
void help_command(char *command_name);
void clear_command();
void setcolor_command(char *color_name);
void showinfo_command();
void printBoardRevision(const unsigned int *mac); 



#endif // COMMANDS_H
