#include <stdio.h>


int main() {
    int ch = getchar();
    printf("| Is EOF | -> %s\n", ch == EOF ? "true" : "false");
    printf("| getchar() != EOF | ->  %d\n", ch != 0);
    printf("| Value | -> %c\n", ch);

    return 0;
}