#include <stdio.h>

#define MAXLEN 1000
#define LIMIT 8


unsigned
read_line(char line[], unsigned maxlen);


int main() {
    unsigned line_len;
    char line[MAXLEN];

    while ((line_len = read_line(line, MAXLEN)) > 0) {
        if (line_len > LIMIT) {
            printf("%s", line);
        }
    }

    return 0;
}


unsigned
read_line(char line[], unsigned maxlen)
{
    int c;
    unsigned i;

    for (i = 0; i < maxlen - 1 && (c = getchar()) && c != EOF && c != '\n' ; ++i) {
        line[i] = c;
    }
    if (c == '\n') line[i++] = c;
    line[i] = '\0';

    return i;
}