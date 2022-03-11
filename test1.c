#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int x = 5;

void handler(int sig) {
    x += 3;
    fprintf(stderr, "inside %d ", x);
}

int main() {
    fprintf(stderr, "start ");
    //                             POSITION A
    struct sigaction act;
    act.sa_handler = handler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGINT,&act,NULL);

    //                             POSITION B
    kill(getpid(),SIGINT);
    fprintf(stderr,"\n");
    x += 2;

    //                             POSITION C
    fprintf(stderr, "outside %d", x);

    return 0;
}

