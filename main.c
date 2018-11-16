/*
 * \file main.c
 * \author Nathan Eloe
 * \brief runs the simulations of different CPU scheduler policies
 * Modified by:
 */

#include "proc.h"
#include "cpu_sched.h"
#include "schedulers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
    srand(time(NULL));
    proc_t * processes;
    int numprocs;
    if (argc != 2)
    {
        printf("You must specify a file containing the process descriptions");
        exit(1);
    }
    processes = read_file(argv[1], &numprocs);
    for (int i=0; i<numprocs; i++)
        print_process(&processes[i]);

    // TODO: Uncomment these when you have implemented the scheduler policy
    
    run_scheduler(processes, numprocs, fcfs, "FCFS");
    run_scheduler(processes, numprocs, sjf, "SJF");
    run_scheduler(processes, numprocs, srt, "SRT");
    run_scheduler(processes, numprocs, rr, "RR");
    run_scheduler(processes, numprocs, rand_sched, "RANDOM");
    //reset_all frees the memory the processes take (since they have a LL of nodes...)
    reset_all(processes, numprocs);
    free(processes);
    return 0;
}
