#include <stdio.h>
#include <stdlib.h>

int main(void) {
    for (int i = 0; i < 5; i++) {
        void *p = malloc(16);
        printf("할당된 주소 %d: %p\n", i, p);
    }
    return 0;
}
