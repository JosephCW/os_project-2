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
  // Keep track of the earliest to arrive that
  // hasn't completed. that will always be the
  // process needing to be burned down. (run)
  int to_run = -1;
  int earliest_starting_time = -1;
  for (int i = 0; i < numprocs; i++) {
    if (!isdone(&procs[i])) {
      // If it's the first process it has the lowest time.
      if (earliest_starting_time == -1) {
        earliest_starting_time = (&procs[i])->m_arrive;
        to_run = i;
      }
      // see if the next has a lower starting time.
      if ((&procs[i])->m_arrive < earliest_starting_time) {
        earliest_starting_time = (&procs[i])->m_arrive;
        to_run = i;
      }
    }
  }
  
  return to_run;
}

int sjf(proc_t * procs, const int numprocs, const int ts)
{
    // TODO:  Milestone 3
	return 0;
}

int srt(proc_t * procs, const int numprocs, const int ts)
{
//  printf("\n");
  // Loop through all processes
  // If it is not already completed
    // Get process with the lowest time
    // run that process
  int to_run = -1;
  int lowest_time_remaining = -1;
  for (int i = 0; i < numprocs; i++) {
//	printf("\tOn Process: %d\n", i);
//	printf("\t\tProcess remaining time: %d\n", time_remaining(&procs[i]));
    if (!isdone(&procs[i])) {
//	printf("\t\tProcess isn't complete!\n");	
      if (lowest_time_remaining == -1) {
//	printf("\t\t\tLowest time by default: %d\n", time_remaining(&procs[i]));
        to_run = i;
        lowest_time_remaining = time_remaining(&procs[i]);
      }

      if (time_remaining(&procs[i]) < lowest_time_remaining) {
//	printf("\t\t\tLowest time: %d\n", time_remaining(&procs[i]));
        to_run = i;
        lowest_time_remaining = time_remaining(&procs[i]);
      }
    }
  }
 printf("\tReturning the value: %d\n", to_run);
 return to_run;
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
