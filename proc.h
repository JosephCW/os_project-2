/*
 * \file proc.h
 * \author Nathan Eloe
 * \brief declares functionality to create and modify process information structures
 * Modified by:
 */

#ifndef SOLN_PROC_H
#define SOLN_PROC_H

typedef struct _repnode {
    char action;
    struct _repnode *next;
} repnode_t;

typedef struct _process {
    char m_procname;
    int m_burst;
    int m_arrive;
    int m_timeburst;
    int m_totalwait;
    repnode_t *head, *tail;
} proc_t;

/*
 * \brief creates a new node with the specified action and a NULL next pointer
 * \return the newly created node
 */
repnode_t new_node(char action);

/*
 * \brief Deallocates the linked list of action repnodes recursively
 * \pre the linked list that begins at the node start must be terminated by a node that points to NULL as it's next
 * \pre start has not been previously freed
 * \post the memory of all nodes in the chain is freed
 * \post the memory for the node start is freed
 * \return None
 */
void free_nodes(repnode_t *start);

/*
 * \brief Allocates a CPU burst to a process
 * \pre proc is a pointer to an allocated process (not been freed, out of scope, etc)
 * \post proc's timeburst is incremented
 * \post A repnode containing 'B' is added to the processes representation linked list
 */
void burst(proc_t * proc);
/*
 * \brief Tells a process to wait
 * \pre proc is a pointer to an allocated process (not been freed, out of scope, etc)
 * \post proc's timewait is incremented
 * \post A repnode containing 'W' is added to the processes representation linked list
 */
void wait_p(proc_t * proc);
/*
 * \brief Tells a process to take no action (has finished or not started yet)
 * \pre proc is a pointer to an allocated process (not been freed, out of scope, etc)
 * \post A repnode containing ' ' is added to the processes representation linked list
 */
void nop(proc_t * proc);
/*
 * \brief Adds a repnode with the specified action to the process' linked list of repnodes
 * \pre proc is a pointer to an allocated process (not been freed, out of scope, etc)
 * \post A repnode containing ac is added to the processes representation linked list
 */
void add_action(proc_t * proc, char act);
/*
 * \brief Determines whether a process has finished executing (has received all required CPU burst)
 * \pre proc is a pointer to an allocated process (not been freed, out of scope, etc)
 * \return 1 if process has completed execution, 0 otherwise
 */
int isdone(proc_t * proc);
/*
 * \brief Determines whether a process has already started, but has not finished
 * \pre proc is a pointer to an allocated process (not been freed, out of scope, etc)
 * \return 1 if process has started but not completed execution, 0 otherwise
 */
int running(proc_t * proc, int ts);
/*
 * \brief Resets the stats of the process (0 timewait, 0 timeburst, nothing in the representation LL)
 * \pre proc is a pointer to an allocated process (not been freed, out of scope, etc)
 * \post the process is returned to it's original, unrun state.
 */
void reset(proc_t * proc);
/*
 * \brief Resets all processes in the array of processes
 * \pre numprocs >= 0
 * \pre the procs array has been allocated with at least numprocs spaces
 * \post all processes in the array are reset
 */
void reset_all(proc_t * procs, int numprocs);
/*
 * \brief Prints the statistics about a process
 * \pre proc is a pointer to an allocated process (not been freed, out of scope, etc)
 * \post Process statistics are print to stdout
 */
void print_process(proc_t * proc);
/*
 * \brief Determines the amount of burst time the process needs to finish executing
 * \pre proc is a pointer to an allocated process (not been freed, out of scope, etc)
 * \return the amount of required burst time to complete execution
 */
int time_remaining(proc_t * proc);
/*
 * \brief Formats and prints the rungraph to the screen
 * \pre numprocs >= 0
 * \pre the procs array has been allocated with at least numprocs spaces
 * \post the rungraph is formatted and printed to the screen
 */
void print_rungraph(proc_t * procs, int numprocs);
/*
 * \brief Calculates and prints the average statistics to the screen
 * \pre numprocs >= 0
 * \pre the procs array has been allocated with at least numprocs spaces
 * \post the rungraph is formatted and printed to the screen
 */
void print_stats(proc_t * procs, int numprocs);

/*
 * \brief Reads the file and loads an array of processes
 * \pre None
 * \post opens the file, reads process information, and closes the file
 * \post stores the length of the process array in the variable
 */
proc_t * read_file(const char* fname, int * numprocs);
#endif //SOLN_PROC_H
