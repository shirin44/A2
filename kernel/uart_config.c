// Include necessary headers
#include "../kernel/include/uart_config.h"
#include "../uart/uart0.h"
#include "../kernel/include/string_utils.h"

//function to configure baudrate 
void configureBaudrate()
{
    uart_puts("\nEnter baudrate: ");
    static char baud_buffer[10];
    static int baud_index = 0;
    static char baud_char;
    do
    {
        baud_char = uart_getc();
        uart_sendc(baud_char); // echo the character
        if (baud_char != '\n' && baud_char != '\r')
        {
            baud_buffer[baud_index] = baud_char;
            baud_index++;
        }
    } while (baud_char != '\n' && baud_char != '\r' && baud_index < sizeof(baud_buffer) - 1);
    baud_buffer[baud_index] = '\0';                 // null-terminate the string
    int baudrate = parse_int_from_str(baud_buffer); // convert string to integer
    uart_puts("-----------------------");
    uart_puts("\nIBRD before baudrate configuration: ");
    uart_hex(UART0_IBRD); // print the IBRD (it should be UART0_IBRD)
    uart_puts("\nFBRD before baudrate configuration: ");
    uart_hex(UART0_FBRD); // print the FBRD
    set_baudrate(baudrate);
    uart_init();
    uart_puts("\n\nIBRD after baudrate configuration: ");
    uart_hex(UART0_IBRD);
    uart_puts("\nFBRD after baudrate configuration: ");
    uart_hex(UART0_FBRD);
    uart_puts("\n");
    uart_puts("-----------------------\n");
    for (int i = 0; i < 10; i++)
    { // reset buffer
        baud_buffer[i] = 0;
    }
    baud_index = 0;
}

// Function to configure data bit
void configureDatabit()
{
    uart_puts("\nEnter data bit (5,6,7,8): ");
    static char databit_buffer[2];
    static int databit_index = 0;
    static char databit_char;
    do
    {
        databit_char = uart_getc();
        if (databit_char != '\n' && databit_char != '\r')
        {
            uart_sendc(databit_char); // echo the character
            databit_buffer[databit_index] = databit_char;
            databit_index++;
        }
    } while (databit_char != '\n' && databit_char != '\r' && databit_index < sizeof(databit_buffer) - 1);
    databit_buffer[databit_index] = '\0';
    int databit = parse_int_from_str(databit_buffer);
    if (databit != 5 && databit != 6 && databit != 7 && databit != 8)
    {
        uart_puts("\n\u274CWarning: You entered a number other than 5, 6, 7, or 8.\n");
    }
    else
    {
        uart_puts("\n");
        uart_puts("-----------------------\n");
        uart_puts("\n");
        uart_puts("\nSetting data bit to ");
        uart_puts(databit_buffer); // Print the chosen data bit
        uart_puts("\nLCRH before data bit configuration: ");
        uart_hex(UART0_LCRH);
        set_databit(databit);
        uart_init();
        uart_puts("\nLCRH after data bit configuration: ");
        uart_hex(UART0_LCRH);
        uart_puts("\nData bit configuration ended\n");
        uart_puts("-----------------------\n");
    }
    for (int i = 0; i < 2; i++)
    { // reset buffer
        databit_buffer[i] = 0;
    }
    databit_index = 0;
}


// Function to configure stop bit
void configureStopbit()
{
    uart_puts("\nEnter stop bit (1,2): ");
    static char stopbit_buffer[2];// Buffer to store user input
    static int stopbit_index = 0;
    static char stopbit_char;
    do
    {
        stopbit_char = uart_getc();
        if (stopbit_char != '\n' && stopbit_char != '\r')
        {
            uart_sendc(stopbit_char); // echo the character
            stopbit_buffer[stopbit_index] = stopbit_char;
            stopbit_index++;
        }
    } while (stopbit_char != '\n' && stopbit_char != '\r' && stopbit_index < sizeof(stopbit_buffer) - 1);
    stopbit_buffer[stopbit_index] = '\0';
    int stopbit = parse_int_from_str(stopbit_buffer);
    uart_puts("\n-----------------------");
    if (stopbit != 1 && stopbit != 2)
    {
        uart_puts("\n\u274CWarning: You entered a number other than 1 or 0.\n");
    }
    else
    {
        uart_puts("\nLCRH before stop bit configuration: ");
        uart_hex(UART0_LCRH);
        set_stopbit(stopbit);
        uart_init();
        uart_puts("\nLCRH after stop bit configuration: ");
        uart_hex(UART0_LCRH);
        uart_puts("\n");
        uart_puts("-----------------------\n");
    }
    for (int i = 0; i < 2; i++)
    { // reset buffer
        stopbit_buffer[i] = 0;
    }
    stopbit_index = 0;
}


// Function to configure parity
void configureParity()
{
    uart_puts("\nEnter parity choice (none, even, odd): ");
    static char parity_buffer[5];// Buffer to store user input
    static int parity_index = 0;
    static char parity_char;
    do
    {
        parity_char = uart_getc();
        if (parity_char != '\n' && parity_char != '\r')
        {
            uart_sendc(parity_char); // echo the character
            parity_buffer[parity_index] = parity_char;
            parity_index++;
        }
    } while (parity_char != '\n' && parity_char != '\r' && parity_index < sizeof(parity_buffer) - 1);
    parity_buffer[parity_index] = '\0';
    if (custom_strcmp(parity_buffer, "none") != 0 && custom_strcmp(parity_buffer, "odd") != 0 && custom_strcmp(parity_buffer, "even") != 0)
    {
        uart_puts("\n\u274CWarning: You entered a string other than 'none', 'odd', or 'even'.\n");
    }
    uart_puts("\n-----------------------");
    uart_puts("\nParity set to: ");
    uart_puts(parity_buffer);
    int parity_choice = 0;
    if (custom_strcmp(parity_buffer, "none") == 0)
    {
        parity_choice = 1;
    }
    else if (custom_strcmp(parity_buffer, "odd") == 0)
    {
        parity_choice = 2;
    }
    else
    {
        parity_choice = 3; // even
    }
    uart_puts("\nLCRH before parity configuration: ");
    uart_hex(UART0_LCRH);
    set_parity(parity_choice);
    uart_init();
    uart_puts("\nLCRH after parity configuration: ");
    uart_hex(UART0_LCRH);
    uart_puts("\n-----------------------");
    uart_puts("\n");
    
    for (int i = 0; i < 5; i++)
    { // reset buffer
        parity_buffer[i] = 0;
    }
    parity_index = 0;
}

// Function to configure handshaking
void configureHandshaking()
{
    uart_puts("\nEnter handshaking choice (none, enable): ");
    static char hs_buffer[7];// Buffer to store user input
    static int hs_index = 0;
    static char hs_char;
    do
    {
        hs_char = uart_getc();
        if (hs_char != '\n' && hs_char != '\r')
        {
            uart_sendc(hs_char); // echo the character
            hs_buffer[hs_index] = hs_char;
            hs_index++;
        }
    } while (hs_char != '\n' && hs_char != '\r' && hs_index < sizeof(hs_buffer) - 1);
    hs_buffer[hs_index] = '\0';
    if (custom_strcmp(hs_buffer, "none") != 0 && custom_strcmp(hs_buffer, "enable") != 0)
    {
        uart_puts("\n\u274CWarning: You entered a string other than 'none' or 'enable'.\n");
    }
    uart_puts("\n-----------------------");
    uart_puts("\nHandshaking mode: ");
    uart_puts(hs_buffer);
    int hs_choice = 0;
    if (custom_strcmp(hs_buffer, "enable") == 0)
    {
        hs_choice = 1;
    }
    configure_handshaking(hs_choice);
    uart_puts("\nCR after handshaking configuration: ");
    uart_hex(UART0_CR);
    uart_puts("\n");
    for (int i = 0; i < 7; i++)
    { // reset buffer
        hs_buffer[i] = 0;
    }
    hs_index = 0;
}

// Function to display UART configuration commands
void uart_config_help()
{
    uart_puts("\nUART Configuration Commands:\n");
    uart_puts("+----------------------+--------------------------------------------------------+\n");
    uart_puts("| Command              | Description                                            |\n");
    uart_puts("+----------------------+--------------------------------------------------------+\n");
    uart_puts("| setbaudrate          | Set the UART baud rate (e.g., 1, 115200).           |\n");
    uart_puts("| setdatabits <datab>  | Set the number of data bits (5, 6, 7, or 8).           |\n");
    uart_puts("| setstopbits <stopb>  | Set the number of stop bits (1 or 2).                  |\n");
    uart_puts("| setparity <parity>   | Set the parity mode (none, even, or odd).              |\n");
    uart_puts("| sethandshake <mode>  | Enable or disable CTS/RTS handshaking control (on/off).|\n");
    uart_puts("+----------------------+--------------------------------------------------------+\n");
}
