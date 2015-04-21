#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "pcps.h"
#include "pcps_sigthread/pcps_sigthread.h"
#include "pcps_threadinit/pcps_threadinit.h"


PCPS_RET main(int argc, char *argv[])
{
    int produ_num = 0;
    int consu_num = 0;
    int pcps_err = 0;
    int i = 0;

    pthread_t *produ_tid = NULL;
    pthread_t *consu_tid = NULL;

    if(argc != 3) {
        fprintf(stderr, "Usage: %s producers consumers\n", argv[0]);
        return PCPS_FAIL;
    }

    produ_num = atoi(argv[1]);
    consu_num = atoi(argv[2]);

    if((produ_num <= 0) || (consu_num) <= 0) {
        fprintf(stderr, "Type correct numbers of threads\n");
        return PCPS_FAIL;
    }

    if(pcps_err = pcps_sigthreadinit(SIGUSR1)) {
        fprintf(stderr, "Failed to init signal thread\n");
        return PCPS_FAIL;
    }


    fprintf(stdout, "Process %ld will run until SIGUSR1(%d) catched\n",
            (long )getpid(), SIGUSR1);

    if((produ_tid = (pthread_t *)calloc(produ_num, sizeof(pthread_t))) == NULL)
        return PCPS_FAIL;

    if((consu_tid = (pthread_t *)calloc(consu_num, sizeof(pthread_t))) == NULL)
        return PCPS_FAIL;

    for(i = 0; i < produ_num; i++) {

        if(pcps_err = producerinit(produ_tid + i)) {
            fprintf(stderr, "Failed to init consumer %d: %s\n", i, strerror(pcps_err));
            return PCPS_FAIL;
        }
    }

    return PCPS_OK;
}
