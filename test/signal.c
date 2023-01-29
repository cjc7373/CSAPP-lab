#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int cnt = 0;

void sigint_handler(int sig) {
    printf("Caught SIGINT!\n");
    exit(0);
}

void sigtstp_handler(int sig) {
    printf("Caught SIGTSTP!\n");
    cnt = 1;
}

int main() {
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        printf("ERR\n");
        exit(0);
    }

    if (signal(SIGTSTP, sigtstp_handler) == SIG_ERR) {
        printf("ERR\n");
        exit(0);
    }

    sigset_t mask, prev_mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    // sigprocmask(SIG_BLOCK, &mask, &prev_mask);

    // for (int i = 0; i < 5; i++) {
    //     printf("%d\n", i);
    //     sleep(1);
    // }

    // printf("SIGINT unblocked!\n");
    // sigprocmask(SIG_SETMASK, &prev_mask, NULL);

    for (int i = 0; i < 50; i++) {
        printf("cnt=%d\n", cnt);
        sleep(1);
    }

    return 0;
}
