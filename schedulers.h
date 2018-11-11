//
// Created by squishy on 10/31/15.
//

#ifndef SOLN_SCHEDULERS_H
#define SOLN_SCHEDULERS_H

#define MAX_PROCS_IN_QUEUE 256

#include "proc.h"
#include "time.h"
#include "stdlib.h"

int fcfs(proc_t * procs, const int numprocs, const int ts);
int sjf(proc_t * procs, const int numprocs, const int ts);
int srt(proc_t * procs, const int numprocs, const int ts);
int rr(proc_t * procs, const int numprocs, const int ts);
int rand_sched(proc_t * procs, const int numprocs, const int ts);

#endif //SOLN_SCHEDULERS_H
