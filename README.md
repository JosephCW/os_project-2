# Project 02: CPU Scheduling Policies

## 44-550: Operating Systems

## 40 points

For this project, you must implement the four mechanisms for CPU schedling specified in class: FCFS, SJF, SRT, and RR.

### Milestones

1. Put required header in the `schedulers.c` file (this is the file you will be modifying)
2. Implement the FCFS scheduler (`int fcfs(proc_t * procs, const int numprocs, const int ts)`) and uncomment the appropriate line in `main.c`
3. Implement the SJF scheduler (`int SJF(proc_t * procs, const int numprocs, const int ts)`) and uncomment the appropriate line in `main.c`
4. Implement the SRT scheduler (`int SJF(proc_t * procs, const int numprocs, const int ts)`) and uncomment the appropriate line in `main.c`
5. Implement the RR scheduler (`int SJF(proc_t * procs, const int numprocs, const int ts)`) and uncomment the appropriate line in `main.c`

### Grading

* There are 8 unit tests associated with this project; each is worth 3 points (total of 24)
* 4 points will be allocated to your code not havin*g memory leaks (0.5 pts per valgrind test, total of 4)
* Having at least one unique commit for milestones 2 through 5 are worth 2 points each (total of 8)
* Correctly completing milestone 1 with a unique commit is worth 3 points (total of 3)
* Having a consistent and clean coding standard in `schedulers.c` is worth 1 point

**Total**: 40 points

### Running the code

#### If you have make on your PATH

You can compile the tests by running `make test`, and run all the tests with `./test`.
You can run an individual test by running `./test nameOfTest`; `./test FCFtestprocs`.
You can see the list of available tests by running `./test --list`

You can compile the graph generator by running `make driver`, and run the generator with `./driver nameOfFile`.  For example: `./driver testprocs.txt`

#### If make is not on your PATH

You can compile the tests by running `gcc cpu_sched.c  test.c  proc.c  schedulers.c -o test`.

You can compile the graph generator by running `gcc cpu_sched.c  main.c  proc.c  schedulers.c -o driver`.

Run the code as above.

### Helper Code

There are many helper functions that have been written for you as part of the framework.  You can see the documentation in `proc.h` for these functions that operate on a struct of type `proc_t`.  Specific functions you may want to look at:

* `isdone`
* `running`
* `time_remaining`: returns `m_timeburst - m_burst`

Additionally, you will need to use some information in the `proc_t` struct, including

* `m_arrive`: the time when a process arrived
* `m_timeburst`: amount of time a process needs to burst
* `m_burst`: amount of time a process has already bursted

### Hints/tricks/tips

Remember that these policy functions are NOT designed to determine the complete ordering of processes to run.  They only need to figure out what process to run at a given timestep.

You are encouraged to try to apply your knowledge of how the schedulers work to build your own solution.  However, pseudocode/descriptions of how to choose the next process to run will be provided on the course website if you choose to use it.

A simple random scheduler that chooses a random process that has arrived but not yet finished has been provided with this skeleton.  You can use it as a mechanism to see how each scheduler should work (specifically determine which process should be executed and return its index).

We will discuss a cool way to do a "static" "queue" in class; you may want to use that.  The process struct has a quick and dirty linked list based struct that is associated with it to keep track of the operations that keeps track of the operations to preform next if you want to use that as an example for writing your own _actual_ queue.

### Sample I/O (driver/graph generator)

```bash
$./driver testprocs.txt
Process A: arrive: 0 required: 8 time spent: 0 wait: 0
Process B: arrive: 2 required: 5 time spent: 0 wait: 0
Process C: arrive: 3 required: 1 time spent: 0 wait: 0
Process D: arrive: 5 required: 1 time spent: 0 wait: 0
Process E: arrive: 1 required: 9 time spent: 0 wait: 0

===== RUNNING FCFS =====
   == RUN GRAPH ==
A |>B   B   B   B   B   B   B   B<                                                                 
B |        >W   W   W   W   W   W   W   W   W   W   W   W   W   W   W   B   B   B   B   B<         
C |            >W   W   W   W   W   W   W   W   W   W   W   W   W   W   W   W   W   W   W   B<     
D |                    >W   W   W   W   W   W   W   W   W   W   W   W   W   W   W   W   W   W   B< 
E |    >W   W   W   W   W   W   W   B   B   B   B   B   B   B   B   B<                             
---------------------------------------------------------------------------------------------------
  |000|001|002|003|004|005|006|007|008|009|010|011|012|013|014|015|016|017|018|019|020|021|022|023|
-- Stats --
  Avg. Response Time (Avg. Wait): 11.800000
  Avg. Turnaround Time          : 16.600000

===== RUNNING SJF =====
   == RUN GRAPH ==
A |>B   B   B   B   B   B   B   B<                                                                 
B |        >W   W   W   W   W   W   W   W   B   B   B   B   B<                                     
C |            >W   W   W   W   W   B<                                                             
D |                    >W   W   W   W   B<                                                         
E |    >W   W   W   W   W   W   W   W   W   W   W   W   W   W   B   B   B   B   B   B   B   B   B< 
---------------------------------------------------------------------------------------------------
  |000|001|002|003|004|005|006|007|008|009|010|011|012|013|014|015|016|017|018|019|020|021|022|023|
-- Stats --
  Avg. Response Time (Avg. Wait): 6.200000
  Avg. Turnaround Time          : 11.000000

===== RUNNING SRT =====
   == RUN GRAPH ==
A |>B   B   W   W   W   W   W   W   W   B   B   B   B   B   B<                                     
B |        >B   W   B   W   B   B   B<                                                             
C |            >B                                                                                  
D |                    >B                                                                          
E |    >W   W   W   W   W   W   W   W   W   W   W   W   W   W   B   B   B   B   B   B   B   B   B< 
---------------------------------------------------------------------------------------------------
  |000|001|002|003|004|005|006|007|008|009|010|011|012|013|014|015|016|017|018|019|020|021|022|023|
-- Stats --
  Avg. Response Time (Avg. Wait): 4.600000
  Avg. Turnaround Time          : 9.400000

===== RUNNING RR =====
   == RUN GRAPH ==
A |>B   W   B   W   W   W   B   W   W   W   B   W   W   B   W   W   B   W   W   B   W   B<         
B |        >W   B   W   W   W   B   W   W   W   B   W   W   B   W   W   B<                         
C |            >W   W   B<                                                                         
D |                    >W   W   W   B<                                                             
E |    >B   W   W   B   W   W   W   W   B   W   W   B   W   W   B   W   W   B   W   B   W   B   B< 
---------------------------------------------------------------------------------------------------
  |000|001|002|003|004|005|006|007|008|009|010|011|012|013|014|015|016|017|018|019|020|021|022|023|
-- Stats --
  Avg. Response Time (Avg. Wait): 8.800000
  Avg. Turnaround Time          : 13.600000

===== RUNNING RANDOM =====
   == RUN GRAPH ==
A |>B   B   B   W   W   W   W   W   W   W   W   B   W   B   W   W   B   W   W   W   B   W   W   B< 
B |        >W   B   B   B   W   B   B<                                                             
C |            >W   W   W   W   W   W   W   B<                                                     
D |                    >W   B<                                                                     
E |    >W   W   W   W   W   W   W   W   B   W   W   B   W   B   B   W   B   B   B   W   B   B<     
---------------------------------------------------------------------------------------------------
  |000|001|002|003|004|005|006|007|008|009|010|011|012|013|014|015|016|017|018|019|020|021|022|023|
-- Stats --
  Avg. Response Time (Avg. Wait): 7.800000
  Avg. Turnaround Time          : 12.600000
```