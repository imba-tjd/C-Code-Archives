// 此程序可以将输入的UTF8文本解转义，例如手动输入 1\n2 这四个字符，可以输出 1(换行)2
/* 测试用例：
hello, world\n
\u0068\u0065\u006c\u006c\u006f\u002c\u0020\u0077\u006f\u0072\u006c\u0064\u000a
\u4F60\u597D\t\u4E16\u754C\n
\uD869\uDEA5\n

\uqwer\u1234
\u0068\uqwer
a\uDFFFa
a\uD800a
\y\m
\uD800\u0068
\uD800\uqwer
*/

#include <stdio.h>
#include <stdlib.h>

#define movenext(ch, p) (ch = *p++)
void Parse(const char *p);
int ParseUnicode(const char **pp);
int ParseHex(const char *num);
static unsigned int GetCodePointFromSurrogatePare(unsigned short high, unsigned short low);
void EncodeUTF8(unsigned codePoint);

int main(void) {
    char input[BUFSIZ];
    printf("$>");
    while (fgets(input, BUFSIZ, stdin) != NULL) { // 读到EOF时返回NULL
        Parse(input);
        printf("\n$>");
    }
}

#define HandleEscape(ch, escaped) \
    case ch:                      \
        putchar(escaped);         \
        break
void Parse(const char *p) {
    char ch;
    while (movenext(ch, p) != '\0') {
        switch (ch) {
        case '\\': // 需要转义
            switch (movenext(ch, p)) {
            HandleEscape('\"', '\"');
            HandleEscape('\\', '\\');
            HandleEscape('b', '\b');
            HandleEscape('f', '\f');
            HandleEscape('n', '\n');
            HandleEscape('r', '\r');
            HandleEscape('t', '\t');
            // case '/': // 斜杠的转义是可选的

            case 'u': {
                int codePoint = ParseUnicode(&p);
                if (codePoint == -1) { // ParseHex失败
                    printf("\nError!");
                    return;
                }
                EncodeUTF8(codePoint);
                break;
            }
            default: // 不支持的转义
                // putchar('\\');
                putchar(ch);
                break;
            }
            break;
        default: // 无需转义
            putchar(ch);
            break;
        }
    }
}

static inline int IsHighSurrogate(unsigned short surrogate) { return surrogate >= 0xD800 && surrogate <= 0xDBFF; }
static inline int IsLowSurrogate(unsigned short surrogate) { return surrogate >= 0xDC00 && surrogate <= 0xDFFF; }
int ParseUnicode(const char **pp) {
    const char *p = *pp;
    int high = ParseHex(p); // 跳过字符u
    unsigned codePoint;
    if (high == -1) // 解析失败
        return -1;

    // 解析成功
    p += 4; // 移过xxxx
    codePoint = high;

    if (IsHighSurrogate(high) && (*p) == '\\' && (*(p + 1)) == 'u') { // 解析低代理项
        int low = ParseHex(p + 2); // 移过\u
        if (IsLowSurrogate(low)) { // ParseHex失败或不是低代理项时仍编码当前码点，其余的留给下一轮解析
            p += 6; // 移过\uxxxx
            codePoint = GetCodePointFromSurrogatePare(high, low);
        }
    }

    *pp = p;
    return codePoint;
}

int ParseHex(const char *num) { // 解析\uxxxx中的4个16进制字符
    int hex = 0; // 本来用ushort即可，但出错时需要返回-1

    for (int i = 0; i < 4; i++) { // 只解析xxxx
        char ch = *num++;
        hex <<= 4;
        if (ch >= '0' && ch <= '9')
            hex |= ch - '0';
        else if (ch >= 'A' && ch <= 'F')
            hex |= ch - 'A' + 10;
        else if (ch >= 'a' && ch <= 'f')
            hex |= ch - 'a' + 10;
        else
            return -1; // 非16进制字符
    }
    return hex;
}

static inline unsigned int GetCodePointFromSurrogatePare(unsigned short high, unsigned short low) {
    return 0x10000 + (high - 0xD800) * 0x400 + (low - 0xDC00);
}

void EncodeUTF8(unsigned codePoint) {
    if (codePoint <= 0x007F)
        putchar((char)(codePoint));
    else if (codePoint <= 0x07FF) {
        putchar((char)(0xC0 | ((codePoint >> 6) & 0xFF)));
        putchar((char)(0x80 | (codePoint & 0x3F)));
    }
    else if (codePoint <= 0xFFFF) {
        putchar((char)(0xE0 | ((codePoint >> 12) & 0xFF)));
        putchar((char)(0x80 | ((codePoint >> 6) & 0x3F)));
        putchar((char)(0x80 | (codePoint & 0x3F)));
    }
    else if (codePoint <= 0x10FFFF) {
        putchar((char)(0xF0 | ((codePoint >> 18) & 0xFF)));
        putchar((char)(0x80 | ((codePoint >> 12) & 0x3F)));
        putchar((char)(0x80 | ((codePoint >> 6) & 0x3F)));
        putchar((char)(0x80 | (codePoint & 0x3F)));
    }
    else
        exit(EXIT_FAILURE); // 不可能发生
}
