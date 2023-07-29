#include <stdio.h>

int main() {
    while (1) {
        printf("Enter a value (or 'q' to quit): ");
        char input[10];
        fgets(input, sizeof(input), stdin);

        if (input[0] == 'q')
            break;
    }

    return 0;
}

