#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef OPTIMIZED_LOWER

void lower(char *s) {
    size_t i;
    size_t len = strlen(s);
    for (i = 0; i < len; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') s[i] -= ('A' - 'a');
    }
}

#else

void lower(char *s) {
    size_t i;
    for (i = 0; i < strlen(s); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') s[i] -= ('A' - 'a');
    }
}

#endif

int main(int argc, char **argv) {
    clock_t start_t, end_t;
    double total_t;

    for (int i = 1000; i <= 200000; i += 8000) {
        char *s = malloc(i);
        memset(s, 0, i);
        memset(s, 'a', i - 1);
        start_t = clock();
        // printf("Starting of the program, start_t = %ld\n", start_t);
        lower(s);
        // printf("Going to scan a big loop, start_t = %ld\n", start_t);
        end_t = clock();
        // printf("End of the big loop, end_t = %ld\n", end_t);

        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("%d %f\n", i, total_t);
        free(s);
    }

    return 0;
}
