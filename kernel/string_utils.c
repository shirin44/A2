#include "../kernel/include/string_utils.h"

// Define custom_strncpy function
char *custom_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }
    for (; i < n; i++)
    {
        dest[i] = '\0';
    }
    return dest;
}

// Custom strcmp function
int custom_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        ++s1;
        ++s2;
    }
    return *s1 - *s2;
}
// Custom strncmp function
int custom_strncmp(const char *s1, const char *s2, int n)
{
    while (n > 0 && *s1 && *s2 && *s1 == *s2)
    {
        ++s1;
        ++s2;
        --n;
    }
    if (n == 0)
    {
        return 0; // Reached the comparison limit
    }
    return *s1 - *s2;
}

// Custom custom_strlen function
int custom_strlen(const char *str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

// Custom tolower function
char custom_tolower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');
    return c;
}

// Custom strcpy function
void custom_strcpy(char *dest, const char *src)
{
    while (*src)
    {
        *dest++ = *src++;
    }
    *dest = '\0';
}

void custom_strcat(char *dest, const char *src){
    while (*dest != '\0')
    {
        dest++;
    }
    while (*src != '\0')
    {
        *dest++ = *src++;
    }
    *dest = '\0';
}

// Custom strtok function
char *custom_strtok(char *str, const char *delim){
    static char *p = '\0';
    if (str != '\0')
        p = str;

    if (p == '\0' || *p == '\0')
        return '\0';

    char *start = p;

    while (*p != '\0')
    {
        const char *d = delim;
        while (*d != '\0')
        {
            if (*p == *d)
            {
                *p = '\0';
                ++p;
                if (*p == '\0')
                    p = '\0';
                return start;
            }
            ++d;
        }
        ++p;
    }

    return start;
}
int parse_int_from_str(const char* str) {
    int result = 0;  // Initialize result
    int sign = 1;    // Initialize sign as positive
    int index = 0;   // Initialize index of first digit

    // Check if number is negative
    if (str[0] == '-') {
        sign = -1;
        index++;  // Update index of first digit
    }

    // Iterate through all digits and update the result
    for (; str[index] != '\0'; ++index) {
        if (str[index] >= '0' && str[index] <= '9') {
            result = result * 10 + (str[index] - '0');
        } else {
            // Handle invalid characters if necessary
            // For simplicity, this example assumes all characters are digits
            // You may add error handling here for non-digit characters
        }
    }

    // Return result with sign
    return sign * result;
}
// Custom function to convert a string to an integer
int custom_atoi(const char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    // Handle leading whitespace
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i++;

    // Handle sign
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }

    // Process digits
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    // Apply sign
    return sign * result;
}
char* custom_itoa(int num) {
    static char buffer[12]; // Maximum number of digits in a 32-bit integer + 1 for null terminator
    int i = 0;
    int is_negative = 0;

    // Handle negative numbers
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    // Handle special case of 0
    if (num == 0) {
        buffer[i++] = '0';
    } else {
        // Extract digits in reverse order
        while (num != 0) {
            int digit = num % 10;
            buffer[i++] = '0' + digit; // Convert digit to character
            num /= 10;
        }

        // Add '-' for negative numbers
        if (is_negative) {
            buffer[i++] = '-';
        }

        // Reverse the string
        int start = 0;
        int end = i - 1;
        while (start < end) {
            char temp = buffer[start];
            buffer[start] = buffer[end];
            buffer[end] = temp;
            start++;
            end--;
        }
    }

    // Null terminate the string
    buffer[i] = '\0';

    return buffer;
}
