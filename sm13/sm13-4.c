#include <stdio.h>


int main() {

    size_t sz = 0;
    unsigned int left, right;

    while (scanf("%x-%x %*[^\n]%*c", &left, &right) != EOF) {
    	sz += right;
    	sz -= left;
    }
    printf("%lu", sz);
    return 0;
}

// В задаче не нужны 64-битные типы
