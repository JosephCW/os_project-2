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
//  printf("\tReturning the value: %d\n", to_run);
  return to_run;
}

int sjf(proc_t * procs, const int numprocs, const int ts)
{
  // Notes in the docs are wrong for variables.
      // m_timeburst - how many already done
      // m_burst - how many needed to burst
      // m_arrive - ts when it arrived

  int to_run = -1;
  int shortest_burst_time = -1;
//  for (int i = 0; i < numprocs; i++) {
//    printf("Process %d \n\t isComplete %d\n\t timeburst %d\n\t burst/ burndown %d\n\t arrived %d\n", i, isdone(&procs[i]), (&procs[i])->m_timeburst, (&procs[i])->m_burst, (&procs[i])->m_arrive);
//  }

  // If we're on step zero, we need to choose one that arrived at zero.
  if (ts == 0) {
    printf("TS is Zero!");
    for (int i = 0; i < numprocs; i++) {
      if ((&procs[i])->m_arrive == 0) {
//	printf("Process arrived at zero! %d\n", i);
        if (to_run == -1) {
//          printf("Process is set as active by default %d\n", i);
          shortest_burst_time = (&procs[i])->m_timeburst;
          to_run = i;
        } else {
          if ((&procs[i])->m_timeburst < shortest_burst_time) {
//            printf("Process is set as active %d\n", i);
            shortest_burst_time = (&procs[i])->m_timeburst;
            to_run = i;
          }
        }
      }
    }
  }
  
  // If there ws a process already going, finish off that process.  
  for (int i = 0; i < numprocs; i++) {
      if ((&procs[i])->m_timeburst != 0 && 
            !isdone(&procs[i])) {
        // If bursting has started but not completing
//        printf("Process is not done and has already begun bursting: %d\n", i);
        to_run = i;
      } else {
//        printf("Process %d is either done, or has not begun bursing\n", i);
      }
    }
    

  // If there isn't a process that was already started
  // and we're not on timestamp zero,
  // pick a process based on which has the least remaining burst time.
  if (to_run == -1) {
    // 
    for (int i = 0;i < numprocs; i++) {
      if (!isdone(&procs[i])) {
        // Default of -1
        if (to_run == -1) {
//          printf("Defaulting to %d with remaining time %d\n", i, (&procs[i])->m_burst);
          shortest_burst_time = (&procs[i])->m_burst;
          to_run = i;
        }
        // non default, see if less than current.
        if ((&procs[i])->m_burst < shortest_burst_time) {
//          printf("New shortest time: process %d, burst remaining %d", i, (&procs[i])->m_burst);
          shortest_burst_time = (&procs[i])->m_burst;
          to_run = i;
        }
      }
    }
  }
//  printf("\tReturning the value: %d\n", to_run);
  return to_run;
}

int srt(proc_t * procs, const int numprocs, const int ts)
{
  int to_run = -1;
  int lowest_time_remaining = -1;
  // if on timestamp zero, we need to only pull from 
  // processes that have already arrived.
  if (ts == 0) {
    for (int i = 0; i < numprocs; i++) {
      if ((&procs[i])->m_arrive == 0) {
        // Default to first one.
        if (to_run == -1) {
          to_run = i;
          lowest_time_remaining = time_remaining(&procs[i]); 
        }
        if (time_remaining(&procs[i]) < lowest_time_remaining) {
          to_run = i;
          lowest_time_remaining = time_remaining(&procs[i]);
        }
      }
    } 
  }

  if (to_run == -1) {
    for (int i = 0; i < numprocs; i++) {
//  	  printf("\tOn Process: %d\n", i);
//  	  printf("\t\tProcess remaining time: %d\n", time_remaining(&procs[i]));
      if (!isdone(&procs[i])) {
//  	  printf("\t\tProcess isn't complete!\n");	
        if (lowest_time_remaining == -1) {
//	  printf("\t\t\tLowest time by default: %d\n", time_remaining(&procs[i]));
          to_run = i;
          lowest_time_remaining = time_remaining(&procs[i]);
        }

        if (time_remaining(&procs[i]) < lowest_time_remaining) {
//	  printf("\t\t\tLowest time: %d\n", time_remaining(&procs[i]));
          to_run = i;
          lowest_time_remaining = time_remaining(&procs[i]);
        }
      }
    }
  }
 //printf("\tReturning the value: %d\n", to_run);
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
