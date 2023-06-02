#include <stdio.h>

int main() {
    int n;
    int i,int w1 = 0, w2 = 1, wynik;
    printf("Wprowadz ilosc wyrazów: ");
    scanf("%d", &n);
    printf("%d %d ", w1, w2);


    for (i = 0; i < n; i++) {
        wynik = w1 + w2;
        printf("%d ", wynik);
        w1 = w2;
        w2 = wynik;
    }
    return 0;
}
