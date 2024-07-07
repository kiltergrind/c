#include <stdio.h>

#define MAXLINE 50



unsigned long long
get_line(char line[], unsigned long long maxline);

void
copy_str(char to[], char from[]);



int main(void)
{
    unsigned long long current_len;
    unsigned long long found_max_len;
    char line[MAXLINE], longest[MAXLINE];

    found_max_len = 0;
    while ((current_len = get_line(line, MAXLINE)) > 0) {
        if (current_len > found_max_len) {
            found_max_len = current_len;
            copy_str(longest, line);
        }
    }

    if (found_max_len > 0) {
        printf("\n\n\n---------------"
               "\nLongest string length: %llu"
               "\n---------------"
               "\nLongest string: %s"
               "\n---------------",
               found_max_len, longest);
    }

    return 0;
}


unsigned long long
get_line(char line[], unsigned long long maxline)
{
    int c;
    unsigned long long i;
    
    for (i = 0; i < maxline && (c = getchar()) != '\n' && c != EOF; ++i)
        line[i] = c;
    
    // This is really unnecessary
    // if (c == '\n') {
    //     line[i] = c;
    //     ++i;
    // }

    line[i] = '\0';

    while (c != '\n' && c != EOF) {
        ++i;
        c = getchar();
    }

    return i;
}


void
copy_str(char to[], char from[])
{
    unsigned i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}