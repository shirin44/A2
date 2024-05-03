#include "../kernel/include/commands.h"



void help_command(char *command_name) {
    uart_puts("\nReceived command name in help_command: ");
    uart_puts(command_name);

    if (command_name == '\0') {
        uart_puts("\nCommands:\n");
        uart_puts("---------------------------------------------------------------------\n");
        uart_puts("| No. | Command              | Usage                                 |\n");
        uart_puts("---------------------------------------------------------------------\n");
        uart_puts("| 1.  | help                 | Show brief information of all commands|\n");
        uart_puts("| 2.  | help <command_name>  | Show full information of the command  |\n");
        uart_puts("| 3.  | clear                | Clear screen                          |\n");
        uart_puts("| 4.  | setcolor             | Set text and/or background color      |\n");
        uart_puts("| 5.  | showinfo             | Show board revision and MAC address   |\n");
        uart_puts("| 6.  | uart_config          | Display UART configuration commands   |\n");
        uart_puts("------------------------------------------------------------------\n");
    }
    else {
        if (custom_strcmp(command_name, "help") == 0) {
            uart_puts("\nFull information of the command 'help':\n");
            uart_puts("help - Display brief information or full information of commands\n");
            uart_puts("Usage: help [command_name]\n");
            uart_puts("If no command_name provided, displays brief information about all commands.\n");
            uart_puts("If command_name provided, displays full information about the specified command.\n");
        }
        else if (custom_strcmp(command_name, "clear") == 0) {
            uart_puts("\nFull information of the command 'clear':\n");
            uart_puts("clear - Clear the screen\n");
            uart_puts("Usage: clear\n");
            uart_puts("Clears the screen and moves the cursor to the top-left corner.\n");
        }
        else if (custom_strcmp(command_name, "setcolor") == 0) {
            uart_puts("\nFull information of the command 'setcolor':\n");
            uart_puts("setcolor - Set text and/or background color\n");
            uart_puts("Usage: setcolor -t <text_color> -b <background_color> -a <both> \n");
            uart_puts("Options:\n");
            uart_puts("  -t: Set text color\n");
            uart_puts("  -b: Set background color\n");
            uart_puts("  -a: Set both text and background color\n");
            uart_puts("Choose color (black, red, green, yellow, blue, magenta, cyan, white): ");
            uart_puts("Options for colors:\n");
            uart_puts("  -b: Set color to black\n");
            uart_puts("  -r: Set color to red\n");
            uart_puts("  -g: Set color to green\n");
            uart_puts("  -y: Set color to yellow\n");
            uart_puts("  -l: Set color to blue\n");
            uart_puts("  -m: Set color to magenta\n");
            uart_puts("  -c: Set color to cyan\n");
            uart_puts("  -w: Set color to white\n");
            uart_puts("Example: setcolor -t text -b black\n");
        }
        else if (custom_strcmp(command_name, "showinfo") == 0) {
            uart_puts("\nFull information of the command 'showinfo':\n");
            uart_puts("showinfo - Show board revision and MAC address\n");
            uart_puts("Usage: showinfo\n");
            uart_puts("This command displays the board revision and MAC address.\n");
        }
        else if (custom_strcmp(command_name, "uart_config") == 0) {
            // Call uart_config_help function
            uart_config_help();
        }
        else {
            uart_puts("\nUnknown command: ");
            uart_puts(command_name);
            uart_puts("\n");
        }
    }
}


void clear_command(){
    // Implement clear screen functionality
    uart_puts("\033[2J"); // ANSI escape sequence to clear screen
}

void setcolor_command(char *color_name){
    uart_puts("\nChoose which color(s) to change (t = text, b = background, or a = both): ");
    char choice = uart_getc(); // Read a single character from user input

    // Define variables to store the ANSI escape sequences for text and background colors
    char *text_color = "";
    char *bg_color = "";

    switch (choice)
    {
    case 't':
        // Change text color
        uart_puts("Choose text color (black, red, green, yellow, blue, magenta, cyan, white): ");
        choice = uart_getc(); // Read a single character from user input
        switch (choice)
        {
        case 'b':
            text_color = COLOR_BLACK; // Set text color to black
            break;
        case 'r':
            text_color = COLOR_RED; // Set text color to red
            break;
        case 'g':
            text_color = COLOR_GREEN; // Set text color to green
            break;
        case 'y':
            text_color = COLOR_YELLOW; // Set text color to yellow
            break;
        case 'l':
            text_color = COLOR_BLUE; // Set text color to blue
            break;
        case 'm':
            text_color = COLOR_MAGENTA; // Set text color to magenta
            break;
        case 'c':
            text_color = COLOR_CYAN; // Set text color to cyan
            break;
        case 'w':
            text_color = COLOR_WHITE; // Set text color to white
            break;
        default:
            uart_puts("Invalid text color. Please choose again.");
            return;
        }
        break;
    case 'b':
        // Change background color
        uart_puts("Choose background color (black, red, green, yellow, blue, magenta, cyan, white): ");
        choice = uart_getc(); // Read a single character from user input
        switch (choice)
        {
        case 'b':
            bg_color = BG_BLACK; // Set background color to black
            break;
        case 'r':
            bg_color = BG_RED; // Set background color to red
            break;
        case 'g':
            bg_color = BG_GREEN; // Set background color to green
            break;
        case 'y':
            bg_color = BG_YELLOW; // Set background color to yellow
            break;
        case 'l':
            bg_color = BG_BLUE; // Set background color to blue
            break;
        case 'm':
            bg_color = BG_MAGENTA; // Set background color to magenta
            break;
        case 'c':
            bg_color = BG_CYAN; // Set background color to cyan
            break;
        case 'w':
            bg_color = BG_WHITE; // Set background color to white
            break;
        default:
            uart_puts("Invalid background color. Please choose again.");
            return;
        }
        break;
    case 'a':
        // Change both text and background colors
        uart_puts("Choose text color (black, red, green, yellow, blue, magenta, cyan, white): ");
        choice = uart_getc(); // Read a single character from user input
        switch (choice)
        {
        case 'b':
            text_color = COLOR_BLACK; // Set text color to black
            break;
        case 'r':
            text_color = COLOR_RED; // Set text color to red
            break;
        case 'g':
            text_color = COLOR_GREEN; // Set text color to green
            break;
        case 'y':
            text_color = COLOR_YELLOW; // Set text color to yellow
            break;
        case 'l':
            text_color = COLOR_BLUE; // Set text color to blue
            break;
        case 'm':
            text_color = COLOR_MAGENTA; // Set text color to magenta
            break;
        case 'c':
            text_color = COLOR_CYAN; // Set text color to cyan
            break;
        case 'w':
            text_color = COLOR_WHITE; // Set text color to white
            break;
        default:
            uart_puts("Invalid text color. Please choose again.");
            return;
        }

        uart_puts("Choose background color (black, red, green, yellow, blue, magenta, cyan, white): ");
        choice = uart_getc(); // Read a single character from user input
        switch (choice)
        {
        case 'b':
            bg_color = BG_BLACK; // Set background color to black
            break;
        case 'r':
            bg_color = BG_RED; // Set background color to red
            break;
        case 'g':
            bg_color = BG_GREEN; // Set background color to green
            break;
        case 'y':
            bg_color = BG_YELLOW; // Set background color to yellow
            break;
        case 'l':
            bg_color = BG_BLUE; // Set background color to blue
            break;
        case 'm':
            bg_color = BG_MAGENTA; // Set background color to magenta
            break;
        case 'c':
            bg_color = BG_CYAN; // Set background color to cyan
            break;
        case 'w':
            bg_color = BG_WHITE; // Set background color to white
            break;
        default:
            uart_puts("Invalid background color. Please choose again.");
            return;
        }
        break;
    default:
        // Invalid choice
        uart_puts("Invalid choice. Please select 't', 'b', or 'a'.");
        return;
    }

    // Apply the chosen colors
    uart_puts(text_color);
    uart_puts(bg_color);
}

void showinfo_command(){
   // Note: Board model and Board serial may give 0 values on QEMU.
            mBuf[0] = 30 * 4;       // Message Buffer Size in bytes
            mBuf[1] = MBOX_REQUEST; // Message Request Code

            mBuf[2] = 0x00030002; // TAG Identifier: Get clock rate (ARM clock)
            mBuf[3] = 8;          // Value buffer size in bytes
            mBuf[4] = 0;          // REQUEST CODE = 0
            mBuf[5] = 3;          // clock id: ARM system clock
            mBuf[6] = 0;          // clear output buffer (response data are mBuf[5] & mBuf[6])

            mBuf[7] = 0x00000001; // TAG Identifier: Get firmware revision
            mBuf[8] = 4;          // Value buffer size in bytes
            mBuf[9] = 0;          // REQUEST CODE = 0
            mBuf[10] = 0;         // clear output buffer (response data are mBuf[10])

            mBuf[11] = 0x00030002; // TAG Identifier: Get clock rate (UART clock)
            mBuf[12] = 8;          // Value buffer size in bytes
            mBuf[13] = 0;          // REQUEST CODE = 0
            mBuf[14] = 2;          // clock id: UART clock
            mBuf[15] = 0;          // clear output buffer (response data are mBuf[14] & mBuf[15])

            mBuf[16] = 0x00010002; // TAG Identifier: Get board revision
            mBuf[17] = 4;          // Value buffer size in bytes
            mBuf[18] = 0;          // REQUEST CODE = 0
            mBuf[19] = 0;          // clear output buffer (response data are mBuf[19])

            mBuf[20] = 0x00010003; // TAG Identifier: Get board MAC address
            mBuf[21] = 6 * 2;      // Value buffer size in bytes
            mBuf[22] = 0;          // REQUEST CODE = 0
            mBuf[23] = 0;          // clear output buffer (response data are mBuf[23])

            mBuf[24] = MBOX_TAG_LAST;

            if (mbox_call(ADDR(mBuf), MBOX_CH_PROP))
            {
                uart_puts("\nDATA: board revision = ");
                printBoardRevision(&mBuf[19]);

                uart_puts("\n+ Response Code in Message TAG (Board MAC address): ");
                uart_hex(mBuf[22]);
                uart_puts("\nDATA: board MAC address = ");
                printBoardRevision((unsigned char *)&mBuf[23]);
            }
            else
            {
                uart_puts("Unable to query!\n");
            }
}
void printBoardRevision(const unsigned int *mac)
{
    if (*mac == 0x00A02082)
    {
        uart_puts("rpi-3B BCM2837 1GiB Sony UK");
    }
    else if (*mac == 0x00900092)
    {
        uart_puts("rpi-Zero BCM2835 512MB Sony UK");
    }
    else if (*mac == 0x00000010)
    {
        uart_puts("rpi-1B+ BCM2835");
    }
    else if (*mac == 0x00a01041)
    {
        uart_puts("rpi-2B BCM2836 1GiB Sony UK");
    }
    else
    {
        uart_puts("rpi-4B BCM2711 2GiB Sony UK");
    }
}

