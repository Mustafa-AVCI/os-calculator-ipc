/*#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int num1, num2, result;

    // İlk ve ikinci sayıyı oku
    read(STDIN_FILENO, &num1, sizeof(num1));
    read(STDIN_FILENO, &num2, sizeof(num2));

    // Toplama işlemini yap
    result = num1 + num2;

    // Sonucu yaz
    write(STDOUT_FILENO, &result, sizeof(result));

    return 0;
}
*/


/*
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
    int result = num1 + num2;
    write(STDOUT_FILENO, &result, sizeof(result)); // Sonucu stdout üzerinden döner
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
    int result = num1 + num2;

    write(STDOUT_FILENO, &result, sizeof(result));
    return 0;
}
