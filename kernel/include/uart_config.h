#ifndef UART_CONFIG_H
#define UART_CONFIG_H

// Include necessary headers
#include "mbox.h"
#include "colors.h"
#include "../../uart/uart0.h"
#include "string_utils.h"


// Function prototypes
void configureBaudrate();
void configureDatabit();
void configureStopbit();
void configureParity();
void configureHandshaking();
void uart_config_help();

#endif // UART_CONFIG_H
