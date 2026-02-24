#include <stdio.h>

int main() {
    int i;
    char msg[] = "Done";  
    int d = 1;
    for (i = 1; i <= 10; i++) {      // loop
        if (i % 2 == 0 && !d) {            // decision
            printf("%d is Even\n", i);
        } else {
            printf("%d is Odd\n", i);
            d -= 1;
        }
    }
    printf("%s", msg);
    return 0;
}
