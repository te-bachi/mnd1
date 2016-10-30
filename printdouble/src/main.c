
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
void        printdouble(char format, double d);
double      calc_double(uint64_t hex);
void        sum_double(double x, double y);
void        sqrt_print(double x, double y);
double      calc_relative_rounding_error(double input);
void        calc_exponential_effacement(void);
void        calc_exponential_non_effacement(void);

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
printdouble(char format, double d)
{
    char    fmt[16];
    uint8_t idx;
    uint8_t tmp;
    un_t    un;
    
    un.a = d;
    sprintf(fmt, "%%60.49%c = ", format);
    printf(fmt, un.a);
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
 * Sum and print two double values
 *
 * @param   x       first summand
 * @param   x       second summand
 */
void
sum_double(double x, double y)
{
    printf("%f + %f = %f\n",x, y, x + y);
    printdouble('f', x);
    printdouble('f', y);
    printdouble('f', x + y);
    printf("\n");
}


void
sqrt_print(double x, double y)
{
    double x_sqrt       = sqrt(x);
    double y_sqrt       = sqrt(y);
    double difference   = x_sqrt - y_sqrt;
    
    printf("sqrt(%f) - sqrt(%f) = %f\n\n", x, y, difference);
    
    /* print x, y */
    printf("x\n");
    printdouble('f',x);
    printf("\n");
    
    printf("y\n");
    printdouble('f', y);
    printf("\n");
    
    /* print sqrt(x), sqrt(y) */
    printf("sqrt(x)\n");
    printdouble('f', sqrt(x));
    printf("\n");
    
    printf("sqrt(y)\n");
    printdouble('f', sqrt(y));
    printf("\n");
    
    /* print difference */
    printf("sqrt(x) - sqrt(y)\n");
    printdouble('f', difference);
    printf("\n");
}

double
calc_relative_rounding_error(double input)
{
    double rel_eps = input;
    
    do {
        rel_eps /= 2.0;
    } while ((input + (rel_eps / 2.0)) != input);
    return rel_eps;
}

void
calc_exponential_effacement(void)
{
    
    double x;
    double y;
    double t;
    double k;
    
    printf("%-3s\t%-32s\t%-32s\t%-25s\n" ,"x" , "y", "exp(x)", "y / exp(x) - 1");
    
    //for (x = 24.0; x >= -25.0; x--) {
    x = -25.0;
    
        y = 1.0;
        t = 1.0;
        k = 1.0;
        
        printf("\t%-32s\t%-32s\t%-32s\n" ,"t" , "y", "k");
        printf("\t%32.19f\t%32.19f\t%32.19f\n" ,t, y, k);
        
        while (y != (y + ((t * x) / k))) {
            t /= k;
            t *= x;
            y += t;
            printf("\t%37.24f\t%32.19f\t%32.19f\n" ,t, y, k);
            k += 1;
        }
        printf("%-3s\t%-32s\t%-32s\t%-25s\n" ,"x" , "y", "exp(x)", "y / exp(x) - 1");
        printf("%3.0f\t%32.19f\t%32.19f\t%25.19f\n" ,x , y, exp(x), y / exp(x) - 1.0);
        printf("=================================\n");
    //}
    
    double k_fak = 1.0;
    double x_exp = 1.0;
    
    /*
    y = 1.0;
    t = 1.0;
    k = 1.0;
    while (y != (y + ((t * x) / k))) {
        t /= k;
        t *= x;
        k_fak = 1.0;
        x_exp = 1.0;
        for (double i = 1.0; i <= k; i++) {
            k_fak *= i;
            x_exp *= x;
            //printf("%32.19f\t%32.19f\t%32.19f\n", k_fak, x_exp, x_exp / k_fak);
        }
        y += x_exp / k_fak;
        printf("%32.19f\t%32.19f\n", x_exp / k_fak, y);
        k += 1;
    }
    printf("k!  = %e\n", k_fak);
    printf("x^k = %e\n", x_exp);
    printf("a   = %32.19f\n", x_exp / k_fak);
    
    printf("%3.0f\t%32.19f\t%32.19f\t%25.19f\n" ,x , y, exp(x), y / exp(x) - 1.0);
    */
    return 0.0;
}

void
calc_exponential_non_effacement(void)
{
    
}

/**
 * Main function
 */
int
main(int argc, char *argv[])
{
    int i;
    un_t un;
    
    char input[5][65] = {
        "0011111111110000000000000000000000000000000000000000000000000000",
        "0011111111010000000000000000000000000000000000000000000000000000",
        "1011111110111001100110011001100110011001100110011001100110011001",
        "0100000010010000000000000110011001100110011001100110011001100110",
        "1011111111111100010110111111100010010001101101001110111101101010"
    };
    
    printf("\n\n*******************\n");
    printf("Aufgabe 1.3\n\n");
    
    for (i = 0; i < (sizeof(input)/sizeof(input[0])); i++) {
        un.b = parse(input[i], FORMAT_BINARY);
        printdouble('f', un.a);
    }
    
    printf("\n\n*******************\n");
    printf("Aufgabe 1.4\n\n");
    
    sum_double(0.1, 0.15);
    sum_double(1.0, 2.0);
    sum_double(M_PI, M_E);
    
    
    printf("\n\n*******************\n");
    printf("Aufgabe 1.5\n\n");
    
    //print_epsilon(1.0);
    //print_epsilon(0.1);
    //print_epsilon(0.001);
    printdouble('f', calc_relative_rounding_error(1000.0));
    printdouble('f', calc_relative_rounding_error(1.0));
    printdouble('f', calc_relative_rounding_error(0.001));
    
    /*   0.1000 = 0 0111111 10111001 10011001 10011001 10011001 10011001 10011001 10011010 */
    
    printf("0.1\n");
    un.a = 0.1;
    printdouble('f', un.a);
    printf("\n");
    
    printf("0.1 + epsilon\n");
    un.b = parse("0011111110111001100110011001100110011001100110011001100110011011", FORMAT_BINARY);
    printdouble('f', un.a);
    printf("\n");
    
    printf("0.1 - epsilon\n");
    un.b = parse("0011111110111001100110011001100110011001100110011001100110011001", FORMAT_BINARY);
    printdouble('f', un.a);
    printf("\n");
    
    printf("\n\n*******************\n");
    printf("Aufgabe 1.6\n\n");
    sqrt_print(1234567891.0, 1234567890.0);
    
    printf("\n\n*******************\n\n");
    
    /*
    un.b = parse("0011111110111001100110011001100110011001100110011001100110011010", FORMAT_BINARY);
    printdouble('e', un.a);
    
    un.a = create_double(0, -1022, 1);
    printdouble('e', un.a);
    
    un.a = create_double(0, 1023, 1);
    printdouble('e', un.a);
    
    un.a = create_double(0, 0, 1);
    printdouble('e', un.a);
    
    un.a = create_double(0, 1, 1);
    printdouble('e', un.a);
    
    un.a = create_double(0, 2, 1);
    printdouble('e', un.a);
    
    un.a = create_double(0, -1, 1);
    printdouble('e', un.a);
    
    un.a = create_double(0, 1, 2);
    printdouble('e', un.a);
    
    un.a = create_double(0, 0, 4);
    printdouble('e', un.a);
    
    un.a = create_double(0, 0, 6);
    printdouble('e', un.a);
    
    un.a = create_double(0, 1, 6);
    printdouble('e', un.a);
    
    un.a = create_double(0, 1, 6);
    printdouble('e', un.a);
    */
    
    
    un.a = create_double(0, 0, 1);
    printdouble('e', un.a);
    un.a = create_double(0, 0, 2);
    printdouble('e', un.a);
    un.a = create_double(0, 0, 4);
    printdouble('e', un.a);
    un.a = create_double(0, 0, 8);
    
    un.a = create_double(0, 1, 1);
    printdouble('e', un.a);
    un.a = create_double(0, 1, 2);
    printdouble('e', un.a);
    un.a = create_double(0, 1, 4);
    printdouble('e', un.a);
    un.a = create_double(0, 1, 8);
    printdouble('e', un.a);
    
    un.b = parse("0000000000000110011001100110011001100110011001100110", FORMAT_BINARY);
    printf("mantisse = %" PRIu64 "\n", un.b);
    
    
    un.a = 18.4;
    printf("test\n", un.a);
    printdouble('e', un.a);
    
    un.a = 18.2;
    printf("test\n", un.a);
    printdouble('e', un.a);
    
    un.a = 18.0;
    printf("test\n", un.a);
    printdouble('e', un.a);
    
    un.a = 20.12345;
    printf("test\n", un.a);
    printdouble('e', un.a);
    
    un.a = 19.12345;
    printf("test\n", un.a);
    printdouble('e', un.a);
    
    un.a = 18.12345;
    printf("test\n", un.a);
    printdouble('e', un.a);
    
    un.a = 7.12345;
    printf("test\n", un.a);
    printdouble('e', un.a);
    
    un.a = 4.50;
    printf("test\n", un.a);
    printdouble('e', un.a);
    
    un.a = 4.55;
    printf("test\n", un.a);
    printdouble('e', un.a);
    
    calc_exponential_effacement();
    
    return 0;
}
