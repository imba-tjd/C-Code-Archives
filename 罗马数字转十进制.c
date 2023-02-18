#include <stdio.h>

static int RomanNum[] = {['I'] = 1, ['V'] = 5, ['X'] = 10, ['L'] = 50, ['C'] = 100, ['D'] = 500, ['M'] = 1000};

int roman2dec(const char* romans) {
    int dec = 0;
    int ndx = 0;

    while (romans[ndx] != '\0')
        if (romans[ndx + 1] == '\0' || (romans[ndx + 1] != '\0' && RomanNum[(int)romans[ndx]] >= RomanNum[(int)romans[ndx + 1]]))
            dec += RomanNum[(int)romans[ndx++]];
        else
            dec += -RomanNum[(int)romans[ndx]] + RomanNum[(int)romans[ndx + 1]], ndx += 2;

    return dec;
}

#define PRINT1(a) printf("%d\n", roman2dec(a))
#define PRINT2(a, b) printf("%d %d\n", roman2dec(a), roman2dec(b))
#define PRINT3(a, b, c) printf("%d %d %d\n", roman2dec(a), roman2dec(b), roman2dec(c))
#define PRINT4(a, b, c, d) printf("%d %d %d %d\n", roman2dec(a), roman2dec(b), roman2dec(c), roman2dec(d))

int main() {
    PRINT3("I", "II", "III");
    PRINT1("IV");
    PRINT4("V", "VI", "VII", "VIII");
    PRINT1("IX");
    PRINT4("X", "XI", "XII", "XIII");
    PRINT1("XIV");
    PRINT4("XV", "XVI", "XVII", "XVIII");
    PRINT1("XIX");
    PRINT1("XX");

    PRINT4("MV", "MCD", "MDC", "MCM");                           // 1100 1400 1600 1900
    PRINT4("XCIX", "IC", "CMXCIX", "IM");                        // 99 99 999 999
    PRINT4("MDCLXVI", "MDCCCLXXXVIII", "MDCCCXCIX", "MDCCCIC");  // 1666 1888 1899 1899
}
