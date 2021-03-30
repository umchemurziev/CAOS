#include <stdio.h>
int main() {

    unsigned long long sz = 0;
    unsigned int left, right;

    while (scanf("%x-%x %*[^\n]%*c", &left, &right) != EOF) {
    	sz += right;
    	sz -= left;
    }
    printf("%llu", sz);
    return 0;
}
