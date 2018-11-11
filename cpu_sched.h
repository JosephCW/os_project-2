/*
 * \file cpu_sched.h
 * \author Nathan Eloe
 * \brief declaration of functions to run the cpu scheduler simulator
 * Modified by:
 */
#ifndef SOLN_CPU_SCHED_H
#define SOLN_CPU_SCHED_H

#include "proc.h"

typedef int (*sched_func)(proc_t *, const int, const int);

/*
 * \brief Determines whether all processes in the array have completed their required burst times
 * \pre numprocs >= 0
 * \pre the procs array has been allocated with at least numprocs spaces
 * \return 0 if any process has not completed, 1 otherwise
 */
int all_run(proc_t * procs, int numprocs);

/*
 * \brief Runs the cpu scheduler on the supplied process information and outputs the rungraph and statistics
 * \pre numprocs >= 0
 * \pre the procs array has been allocated with at least numprocs spaces
 * \pre the string specified by name is null terminated
 * \post though procs is modified through the execution of the function, it is reset to a starting state at the end
 * \post prints the rungraph after the simulation has completed
 * \post prints the average turnaround and wait time of the scheduling mechanism
 */
void run_scheduler(proc_t * procs, int numprocs, sched_func sched, const char* name);
#endif //SOLN_CPU_SCHED_H
