/**
 * Joseph Watts
 * Operating Systems Fall 2018
 * This class will return the correct process to run
 * based on several different schedueling algorithms
*/

#include "schedulers.h"

int fcfs(proc_t * procs, const int numprocs, const int ts)
{
    // TODO: Milestone 2
	return 0;
}

int sjf(proc_t * procs, const int numprocs, const int ts)
{
    // TODO: Milestone 3
	return 0;
}
int srt(proc_t * procs, const int numprocs, const int ts)
{
    // TODO:  Milestone 4
	return 0;
}

int rr(proc_t * procs, const int numprocs, const int ts)
{
    // TODO: Milestone 5
	return 0;
}

int rand_sched(proc_t * procs, const int numprocs, const int ts)
{
    int * running_procs = malloc(sizeof(int) * numprocs);
    int numrunning = 0;
    int i;
    int rand_idx;
    int to_run;
    for (i=0; i<numprocs; i++)
    {
        if (running(&procs[i], ts))
        {
            running_procs[numrunning] = i;
            numrunning ++;
        }
    }
    rand_idx = rand() % numrunning;
    to_run = running_procs[rand_idx];
    free(running_procs);
    return to_run;
}
