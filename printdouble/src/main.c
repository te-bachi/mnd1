
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>

typedef enum {
    FORMAT_BINARY      = 2,
    FORMAT_DECIMAL     = 10,
    FORMAT_HEXADECIMAL = 16
} format_t;


typedef union {
    double      a;
    uint64_t    b;
} un_t;

double      create_double(uint8_t sign, int16_t exponent, uint64_t mantisse);
uint64_t    parse(const char *str, format_t format);
void        printdouble(double d);
double      calc_double(uint64_t hex);

/**
 * Create a double with input values "sign", "exponent" and "mantisse".
 
 * @param   sign        0 = positive, 1 = negative
 * @param   exponent    exponent from -1022 to +1023
 * @param   mantisse    numerical value
 * @return  returns the newly created double
 */
double
create_double(uint8_t sign, int16_t exponent, uint64_t mantisse)
{
    un_t un;
    
    exponent += 1023;
    
    un.b = ((((uint64_t) sign)     << 63) & 0x8000000000000000);
    un.b = ((((uint64_t) exponent) << 52) & 0x7ff0000000000000) | un.b;
    un.b = ((((uint64_t) mantisse) >>  1) & 0x000fffffffffffff) | un.b;
    
    return un.a;
}

/**
 * Parse a character string writes it into an unsigned integer (64-bit).
 
 * @param   str         character string
 * @param   format      what type of input string is it: FORMAT_BINARY, FORMAT_DECIMAL or FORMAT_HEXADECIMAL
 * @return  returns the newly created unsigned integer (64-bit)
 */
uint64_t
parse(const char *str, format_t format)
{
    uint64_t result;
    char     chr;
    int      length;
    int      i;
    int      negative;
    
    result   = 0;
    i        = 0;
    negative = 1;
    length   = strlen(str);
    
    if (length > 0) {
        if (length > 2 && str[0] == '0' &&
           (str[1] == 'x' || str[1] == 'X')) {
            i += 2;
        } else if (str[0] == '-') {
            negative = -1;
            i += 1;
        } else if (str[0] == '+') {
            i += 1;
        }
        
        for (; i < length; i++) {
            chr = str[i];
            
            if (chr >= '0' && chr <= '9') {
                chr -= '0';
            } else if (chr >= 'A' && chr <= 'Z') {
                chr -= 'A' - 10;
            } else if (chr >= 'a' && chr <= 'z') {
                chr -= 'a' - 10;
            } else {
                break;
            }
            
            result *= format;
            result += chr;
        }
    }
    
    return (negative * result);
}

/**
 * Print double precision value
 *
 * @param   d           double value to print
 */
void
printdouble(double d)
{
    uint8_t idx;
    uint8_t tmp;
    un_t    un;
    
    un.a = d;
    for (idx = 0; idx < 64; idx++) {
        tmp = (un.b >> (63 - idx)) & 0x1;
        printf("%" PRIu8, tmp);
        if (idx == 0 || (63 - idx) % 8 == 0) {
            printf(" ");
        }
    }
     printf("\n");
}

/**
 * Converts integer to double
 *
 * @param   hex         integer value
 * @return  returns a double
 */
double
calc_double(uint64_t hex)
{
    un_t    un;
    
    un.b = hex;
    
    return un.a;
}

/**
 * Main function
 */
int
main(int argc, char *argv[])
{
    int i;
    un_t un;
    
    /*
    uint64_t input[5] = {
        0x3ff0000000000000,
        0x3fd0000000000000,
        0xbfb9999999999999,
        0x4090006666666666,
        0xbffc5bf891b4ef6a
    };
    */
    char input[5][65] = {
        "0011111111110000000000000000000000000000000000000000000000000000",
        "0011111111010000000000000000000000000000000000000000000000000000",
        "1011111110111001100110011001100110011001100110011001100110011001",
        "0100000010010000000000000110011001100110011001100110011001100110",
        "1011111111111100010110111111100010010001101101001110111101101010"
    };
    
    /*   1.0000 = 0 0111111 11110000 00000000 00000000 00000000 00000000 00000000 00000000 */
    un.a = 1.0;
    printf("%60.49f = ", un.a);
    printdouble(un.a);
    
    /*  -1.0000 = 1 0111111 11110000 00000000 00000000 00000000 00000000 00000000 00000000 */
    un.a = -1.0;
    printf("%60.49f = ", un.a);
    printdouble(un.a);
    
    /*   1.1000 = 0 0111111 11110001 10011001 10011001 10011001 10011001 10011001 10011010 */
    un.a = 1.1;
    printf("%60.49f = ", un.a);
    printdouble(un.a);
    
    /*   0.1000 = 0 0111111 10111001 10011001 10011001 10011001 10011001 10011001 10011010 */
    un.a = 0.1;
    printf("%60.49f = ", un.a);
    printdouble(un.a);
    
    printf("\n\n*******************\n\n");
    
    for (i = 0; i < (sizeof(input)/sizeof(input[0])); i++) {
        //un.a = calc_double(input[i]);
        un.b = parse(input[i], FORMAT_BINARY);
        printf("%60.49f = ", un.a);
        printdouble(un.a);
    }
    
    printf("\n\n*******************\n\n");
    un.b = parse("0011111110111001100110011001100110011001100110011001100110011010", FORMAT_BINARY);
    printf("%60.49e = ", un.a);
    printdouble(un.a);
    
    un.a = create_double(0, -1022, 1);
    printf("%60.49e = ", un.a);
    printdouble(un.a);
    
    un.a = create_double(0, 1023, 1);
    printf("%60.49e = ", un.a);
    printdouble(un.a);
    
    un.a = create_double(0, 0, 1);
    printf("%60.49e = ", un.a);
    printdouble(un.a);
    
    un.a = create_double(0, 1, 1);
    printf("%60.49e = ", un.a);
    printdouble(un.a);
    
    un.a = create_double(0, 2, 1);
    printf("%60.49e = ", un.a);
    printdouble(un.a);
    
    un.a = create_double(0, -1, 1);
    printf("%60.49e = ", un.a);
    printdouble(un.a);
    
    un.a = create_double(0, 0, 2);
    printf("%60.49e = ", un.a);
    printdouble(un.a);
    
    un.a = create_double(0, 0, 4);
    printf("%60.49e = ", un.a);
    printdouble(un.a);
    
    un.a = create_double(0, 0, 6);
    printf("%60.49e = ", un.a);
    printdouble(un.a);
    
    un.a = create_double(0, 1, 6);
    printf("%60.49e = ", un.a);
    printdouble(un.a);
    
    return 0;
}
