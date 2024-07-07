#include <stdio.h>




void
fahr_to_cels(unsigned lower, unsigned upper, unsigned step);

void
cels_to_fahr(unsigned lower, unsigned upper, unsigned step);



int main(void)
{
    unsigned lower = 0, upper = 300, step = 20;

    printf("Celsius to Fahrenheit\n-------------\n");
    fahr_to_cels(lower, upper, step);

    printf("Fahrenheit to Celsius\n-------------\n");
    cels_to_fahr(lower, upper, step);

    return 0;
}


void
fahr_to_cels(unsigned lower, unsigned upper, unsigned step)
{
    float fahr, celsius;

    fahr = lower;

    printf("%3s %6s\n", "Fahr", "Celsius");
    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    printf("\n");
}


void
cels_to_fahr(unsigned lower, unsigned upper, unsigned step)
{
    float fahr, celsius;

    celsius = lower;

    printf("%6s %3s\n", "Celsius", "Fahr");
    while (celsius <= upper) {
        fahr = 9.0 / 5 * celsius + 32;
        printf("%6.1f %3.0f\n", celsius, fahr);
        celsius = celsius + step;
    }
    printf("\n");
}
