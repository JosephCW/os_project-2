/**
 * Joseph Watts
 * Operating Systems Fall 2018
 * This class will return the correct process to run
 * based on several different schedueling algorithms
*/

#include <stdio.h>
#include <stdlib.h>
#include "schedulers.h"
#include "proc.h"

int fcfs(proc_t * procs, const int numprocs, const int ts)
{
  // Loop through all of the processes to see if one is running.
    // If a process is already running
      // it needs to continue running.
  // Start the one that arrived first that doesn't have a status of completed
  int to_run = -1;
  for (int i = 0; i < numprocs; i++) {
    if (running(&procs[i], ts)) {
      printf("There is a process running on %d\n", i);
      // There shouldn't be any instance where
      // more than one is running at a time in FCFS.
      to_run = i;
    }
  }
  // If there are no currently running processes,
  // return the first to arrive that isn't finished
  // get the index of the first to arrive
  // return that index.
  /*int earliest_arrival_time = -1;
  if (to_run == -1) {
    printf("To run has a value of -1!");
    for (int i = 0; i < numprocs; i++) {
      // By default set it to the first process.
      if (earliest_arrival_time == -1) {
        earliest_arrival_time = (&procs[i])->m_arrive;
        to_run = i;
      } else {
        // If this process arrived earlier than the previous ones
        // set it as the next process to run.
        if ((&procs[i])->m_arrive < earliest_arrival_time) {
          earliest_arrival_time = (&procs[i])->m_arrive;
          to_run = i;
        }
      }
    }
  }
*/
  return to_run;
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
