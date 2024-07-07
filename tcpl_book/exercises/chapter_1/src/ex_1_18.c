#include <stdio.h>

#define MAXLEN 1000
#define LIMIT 8


unsigned long long
read_line(char line[], unsigned maxlen);

unsigned long long
trim_line(char line[], unsigned long long len);


int main() {
    unsigned long long line_len;
    char line[MAXLEN];

    while ((line_len = read_line(line, MAXLEN)) > 0) {
        printf("LL: %llu\n", line_len);
        if (trim_line(line, line_len) != 0)
            printf("%s", line);
    }

    return 0;
}


/*! Reads line from user input.
 *
 *  Character by character from stdin and stores through pointer into string.
 *  
 * @param { char[] } line pointer to string to remove trailing blanks for
 * @param maxlen string length ("pos" name used is for internal use)
 * @return Length of string that was scanned
 */
unsigned long long
read_line(char line[], unsigned maxlen)
{
    int c;
    unsigned long long i;

    for (i = 0; i < maxlen - 1 && (c = getchar()) != EOF && c != '\n' ; ++i) {
        line[i] = c;
    }
    
    if (c == '\n') line[i++] = c;
    line[i] = '\0';

    return i;
}


/* Function: trim_line
 * ----------------------------------------------------------------------------
 * > This function removes trailing characters that appear to be "blank",
 * > such as newline('\n'), tab('\t'), space(' ')
 * ----------------------------------------------------------------------------
 * @param { char[] } line
 *  - pointer to string to remove trailing blanks for
 * @param { ull }    pos
 *  - string length ("pos" name used is for internal use)
 * ----------------------------------------------------------------------------
 * @returns { llu }
 *  - removed blanks count
 *****************************************************************************/
unsigned long long
trim_line(char line[], unsigned long long pos)
{
    // Change to long long if large trailing sequences are expected
    unsigned char blank_count;

    if (pos == 0) {
        return 0;
    }

    --pos;
    blank_count = 1;
    while (blank_count-- > 0 && pos >= 0) {
        // printf("\nL: %d P: %llu\n", line[pos] == '\t', pos);
        if (line[pos] == ' ' || line[pos] == '\t' || line[pos] == '\n') {
            line[pos--] = 0; 
            blank_count += 2;
        }
    }

    return blank_count;
}