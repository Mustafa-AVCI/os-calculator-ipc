/*

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s num1 num2\n", argv[0]);
        return 1;
    }

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);

    if (num2 == 0) {
        fprintf(stderr, "Division by zero error\n");
        return 1;
    }

    int result = num1 / num2;

    write(STDOUT_FILENO, &result, sizeof(result));
    return 0;
}


*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s num1 num2\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    if (num2 == 0) {
        fprintf(stderr, "Error: Division by zero is not allowed.\n");
        exit(EXIT_FAILURE);
    }
    int result = num1 / num2;
    write(STDOUT_FILENO, &result, sizeof(result)); 
    return 0;
}
