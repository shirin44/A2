#include "../kernel/include/mbox.h"
#include "../kernel/include/uart_config.h"
#include "../kernel/include/colors.h"
#include "../uart/uart0.h"
#include "../kernel/include/string_utils.h"
#include "../kernel/include/commands.h"

#define MAX_CMD_SIZE 100
#define MAX_COMMANDS 6 // Increased to accommodate all commands
#define MAX_HISTORY_SIZE 100
#define OS_NAME "Shirin_A2"

// History buffer to store command history
char history[MAX_HISTORY_SIZE][MAX_CMD_SIZE];
int historyCount = 0;
int currentHistoryIndex = 0;

const char *commands[MAX_COMMANDS] = {"help", "clear", "setcolor", "showinfo", "setbaudrate", "setdatabits", "setstopbit", "setparity", "sethandshake"};

// Function prototypes
void tokenizeAndExecuteCommand(char *buffer);
void cli();

char *tab_handler(char *cli_buffer)
{
    int i;
    int num_completions = 0;
    int last_matching_index = -1;
    int partial_length = custom_strlen(cli_buffer);

    // Convert input buffer to lowercase for case-insensitive comparison
    char lowercase_buffer[MAX_CMD_SIZE];
    custom_strcpy(lowercase_buffer, cli_buffer);
    for (i = 0; i < partial_length; i++)
    {
        lowercase_buffer[i] = custom_tolower(lowercase_buffer[i]);
    }

    // Find completions and last matching index
    for (i = 0; i < MAX_COMMANDS; ++i)
    {
        // Compare the partial command with the current command (case-insensitive)
        if (custom_strncmp(commands[i], lowercase_buffer, partial_length) == 0)
        {
            // Partial match found, increment the number of completions
            num_completions++;
            last_matching_index = i;
        }
    }

    // If there's only one completion
    if (num_completions == 1)
    {
        // Return the completed command
        return commands[last_matching_index];
    }
    else if (num_completions > 1)
    { // If there are multiple completions
        uart_puts("\nMultiple matches: ");
        for (i = 0; i < MAX_COMMANDS; i++)
        {
            // Print all matched commands
            if (custom_strncmp(commands[i], lowercase_buffer, partial_length) == 0)
            {
                uart_puts(commands[i]);
                uart_puts(" ");
            }
        }
        uart_puts("\n");
    }
    else
    { // No match found
        // Delete the partial command and replace it with an empty buffer
        for (i = 0; i < partial_length; i++)
        {
            uart_puts("\b \b"); // Move cursor back, print space to erase, move cursor back again
        }
        cli_buffer[0] = '\0'; // Reset the buffer
    }

    // Return an empty string if no completion or multiple completions
    return "";
}

void tokenizeAndExecuteCommand(char *buffer)
{
    // Tokenize the command
    char *command_name = custom_strtok(buffer, " ");

    if (*command_name != '\0')
    {
        // Execute the command
        if (custom_strcmp(command_name, "help") == 0)
        {
            char *argument = custom_strtok('\0', " ");
            help_command(argument);
        }
        else if (custom_strcmp(command_name, "clear") == 0)
        {
            clear_command();
        }
        else if (custom_strcmp(command_name, "setcolor") == 0)
        {
            char *color_name = custom_strtok('\0', " ");
            setcolor_command(color_name);
        }
        else if (custom_strcmp(command_name, "showinfo") == 0)
        {
            showinfo_command();
        }
        else if (custom_strcmp(command_name, "setbaudrate") == 0)
        {
            configureBaudrate();
        }
        else if (custom_strcmp(command_name, "setdatabits") == 0)
        {
            char *databits_str = custom_strtok('\0', " ");
            configureDatabit(databits_str);
        }
        else if (custom_strcmp(command_name, "setstopbit") == 0)
        {
            char *stopbits_str = custom_strtok('\0', " ");
            int stopbits = custom_atoi(stopbits_str);
            configureStopbit(stopbits);
        }
        else if (custom_strcmp(command_name, "setparity") == 0)
        {
            char *parity_str = custom_strtok('\0', " ");
            int parity = custom_atoi(parity_str);
            configureParity(parity);
        }
        else if (custom_strcmp(command_name, "sethandshake") == 0)
        {
            configureHandshaking();
        }
        else
        {
            uart_puts("\nUnknown command: ");
            uart_puts(command_name);
            uart_puts("\n");
        }
    }
    uart_puts("\n");
}

void cli()
{
    static int index = 0;
    char c = uart_getc();
    uart_sendc(c);

    static char cli_buffer[MAX_CMD_SIZE]; // Buffer to store user input

    if (c == '\n')
    {
        // Handle newline character
        cli_buffer[index] = '\0'; // Terminate the buffer

        // Copy the completed command from cli_buffer to history array after execution
        custom_strncpy(history[historyCount % MAX_HISTORY_SIZE], cli_buffer, MAX_CMD_SIZE);
        historyCount++;
        currentHistoryIndex = historyCount;

        // Process the completed command from cli_buffer
        tokenizeAndExecuteCommand(cli_buffer);

        // Reset index for the next command
        index = 0;

        // Print prompt
        uart_puts("\n");
        uart_puts(OS_NAME);
        uart_puts("> ");
    }
    else if (c == '\t')
    {
        // Handle tab key press for tab completion
        char *completed_command = tab_handler(cli_buffer);
        if (*completed_command != '\0')
        {
            // Print the completion
            uart_puts(completed_command);
            uart_puts(" ");

            // Copy the completed command into cli_buffer
            cli_buffer[0] = '\0'; // Clear existing content if necessary
            custom_strcpy(cli_buffer, completed_command);

            // Move the cursor to the end of the completed command
            index = custom_strlen(cli_buffer);
        }
    }
    else if (c == 127)
    {
        // Handle backspace character
        if (index > 0)
        {
            uart_puts("\b \b");
            index--;
        }
    }
    else if (c == 45 || c == 61)
    {
        // Handle arrow key for history navigation
        if (c == 45 && currentHistoryIndex > 0)
        {
            currentHistoryIndex--;
        }
        else if (c == 61 && currentHistoryIndex < historyCount)
        {
            currentHistoryIndex++;
        }
        if (currentHistoryIndex < historyCount)
        {
            // Clear current input line
            while (index > 0)
            {
                uart_puts("\b \b");
                index--;
            }
            // Copy history command to input buffer
            custom_strncpy(cli_buffer, history[currentHistoryIndex % MAX_HISTORY_SIZE], MAX_CMD_SIZE);
            index = custom_strlen(cli_buffer);
            // Print history command
            uart_puts(cli_buffer);
        }
    }
    else if (index < MAX_CMD_SIZE - 1)
    {
        // Store character in input buffer
        cli_buffer[index++] = c;
    }
}

void main()
{
    // set up serial console
    uart_init();
    uart_puts(" #     #                                                    \n");
    uart_puts(" #  #  # ###### #       ####   ####  #    # ######          \n");
    uart_puts(" #  #  # #      #      #    # #    # ##  ## #               \n");
    uart_puts(" #  #  # #####  #      #      #    # # ## # #####           \n");
    uart_puts(" #  #  # #      #      #      #    # #    # #               \n");
    uart_puts(" #  #  # #      #      #    # #    # #    # #               \n");
    uart_puts("  ## ##  ###### ######  ####   ####  #    # ######          \n");
    uart_puts("                                                            \n");
    uart_puts("                                                            \n");
    uart_puts("                                                            \n");

    uart_puts("                                                            \n");
    uart_puts(" #####  ####                                                \n");
    uart_puts("   #   #    #                                               \n");
    uart_puts("   #   #    #                                               \n");
    uart_puts("   #   #    #                                               \n");
    uart_puts("   #   #    #                                               \n");
    uart_puts("   #    ####                                                \n");
    uart_puts("                                                            \n");
    uart_puts("                                                            \n");

    uart_puts("                                                            \n");
    uart_puts(" ####### ####### #######  #####  #        #####    ###      \n");
    uart_puts(" #       #          #    #     # #    #  #     #  #   #     \n");
    uart_puts(" #       #          #          # #    #  #     # #     #    \n");
    uart_puts(" #####   #####      #     #####  #    #   ###### #     #    \n");
    uart_puts(" #       #          #    #       #######       # #     #    \n");
    uart_puts(" #       #          #    #            #  #     #  #   #     \n");
    uart_puts(" ####### #######    #    #######      #   #####    ###      \n");
    uart_puts("                                                            \n");
    uart_puts("                                                            \n");
    uart_puts("                                                            \n");

    uart_puts(" ######     #    ######  #######    #######  #####          \n");
    uart_puts(" #     #   # #   #     # #          #     # #     #         \n");
    uart_puts(" #     #  #   #  #     # #          #     # #               \n");
    uart_puts(" ######  #     # ######  #####      #     #  #####          \n");
    uart_puts(" #     # ####### #   #   #          #     #       #         \n");
    uart_puts(" #     # #     # #    #  #          #     # #     #         \n");
    uart_puts(" ######  #     # #     # #######    #######  #####         \n");
    uart_puts("                                                            \n");
    uart_puts("                                                            \n");
    uart_puts("DEVELOPED BY <SHIRIN SHUJAA> ID: S3983427");
  

    // Print OS line
    uart_puts("\n");
    uart_puts(OS_NAME);
    uart_puts("> ");

    // echo everything back
    while (1)
    {

        cli();
    }
}
