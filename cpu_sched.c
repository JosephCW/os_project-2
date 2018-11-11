/*
 * \file cpu_sched.c
 * \author Nathan Eloe
 * \brief implementation of functions that run the scheduler and print the statistics/rungraphs
 * Modified by:
 */

#include "cpu_sched.h"
#include "proc.h"
#include "stdio.h"

int all_run(proc_t * procs, int numprocs)
{
    int i=0;
    for (;i<numprocs; i++)
        if (!isdone(&(procs[i])))
            return 0;
    return 1;
}

void run_scheduler(proc_t * procs, int numprocs, sched_func sched, const char* name)
{
    int i, to_run, time_slice =0;
    proc_t * p;
    reset_all(procs, numprocs);
    printf("\n===== RUNNING %s =====\n", name);
    while (!all_run(procs, numprocs))
    {
        to_run = sched(procs, numprocs, time_slice);
        for (i=0; i<numprocs; i++)
        {
            p = &(procs[i]);
            if (i == to_run)
                burst(p);
            else if (!running(p, time_slice))
                nop(p);
            else
                wait_p(p);
        }
        time_slice++;
    }
    print_rungraph(procs, numprocs);
    print_stats(procs, numprocs);
}
