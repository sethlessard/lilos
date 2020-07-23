#include <klibc/kstdbool.h>
#include <klibc/kstdlib.h>

void _reverse(char* str, int length);
void _swap(char* str1, char* str2);

/**
 * Utility function to reverse a string.
 * @param str the string.
 * @param length the length of the string.
 */ 
void _reverse(char* str, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        _swap((str + start), (str + end));
        start++;
        end--;
    }
}

void _swap(char* str1, char* str2) {
    char c = str1[0];
    str1[0] = str2[0];
    str2[0] = c;
}

/**
 * Converts an integer value into a null-terminated string using the specified
 * base and stores the result in the str array.
 * @param value the value to convert.
 * @param str the character buffer to store the null-terminated string.
 * @param base the base of the integer, between 2 and 36.
 */
char* kitoa(int value, char *str, int base) {
    int i = 0;
    bool isNeg = false;

    if (value == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    if (value < 0 && base == 10) {
        isNeg = true;
        value = -value;
    }

    while (value != 0) {
        int rem = value % base;
        str[i++] = (rem > 9) ? (rem-10) + 'a' : rem + '0';
        value = value / base;
    }

    if (isNeg)
        str[i++] = '-';
    str[i] = '\0';
    _reverse(str, i);
    return str;
}
