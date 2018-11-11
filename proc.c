/*
 * \file proc.c
 * \author Nathan Eloe
 * \brief implements functionality to create and modify process information structures
 * Modified by:
 */
#include "proc.h"
#include <stdlib.h>
#include <stdio.h>

repnode_t new_node(char action)
{
    repnode_t val = {action, NULL};
    return val;
}

void free_nodes(repnode_t * start)
{
    if (start)
    {
        free_nodes(start->next);
        free(start);
    }
}

void add_action(proc_t * proc, char act)
{
    repnode_t * newnode = malloc(sizeof(repnode_t));
    *newnode = new_node(act);
    if (proc->tail)
    {
        proc->tail->next = newnode;
    }
    else
        proc->head = newnode;
    proc->tail = newnode;
}

void burst(proc_t * proc)
{
    proc->m_timeburst += 1;
    add_action(proc, 'B');
}

void wait_p(proc_t * proc)
{
    proc->m_totalwait += 1;
    add_action(proc, 'W');
}

void nop(proc_t * proc)
{
    add_action(proc, ' ');
}

int isdone(proc_t * proc)
{
    return proc->m_timeburst == proc->m_burst;
}

int running(proc_t * proc, int ts)
{
    return ts >= proc->m_arrive && !isdone(proc);
}

void reset(proc_t * proc)
{
    proc->m_timeburst = 0;
    proc->m_totalwait = 0;
    free_nodes(proc->head);
    proc->head = NULL;
    proc->tail = NULL;
}

void reset_all(proc_t * procs, int numprocs)
{
    int i;
    for (i=0; i<numprocs; i++)
        reset(&(procs[i]));
}

void print_process(proc_t * proc)
{
    printf("Process %c: arrive: %d required: %d time spent: %d wait: %d\n", proc->m_procname, proc->m_arrive, proc->m_burst,
           proc->m_timeburst, proc->m_totalwait);
}

void print_rungraph(proc_t * procs, int numprocs)
{
    int i, count=0;
    repnode_t * curr;
    printf("   == RUN GRAPH ==\n");
    for (i=0; i<numprocs; i++)
    {
        count = 0;
        printf("%c |", procs[i].m_procname);
        curr = procs[i].head;
        while (curr)
        {
            if (count == procs[i].m_arrive)
                printf(">%c  ", curr->action);
            else if (count == procs[i].m_arrive + procs[i].m_timeburst + procs[i].m_totalwait -1)
                printf(" %c< ", curr->action);
            else
                printf(" %c  ", curr->action);
            curr = curr->next;
            count ++;
        }
        printf("\n");
    }
    printf("---");
    for (i=0; i<count; i++)
    {
        printf("----");
    }
    printf("\n  |");
    for (i=0; i<count; i++)
    {
        printf("%.3d|", i);
    }
    printf("\n");
    return;
}

void print_stats(proc_t * procs, int numprocs)
{
    int i = 0;\
    double t_wait = 0, t_turnaround = 0;
    for (; i<numprocs; i++)
    {
        t_wait += procs[i].m_totalwait;
        t_turnaround += procs[i].m_totalwait + procs[i].m_timeburst;
    }
    printf("-- Stats --\n");
    printf("  Avg. Response Time (Avg. Wait): %f\n", t_wait / numprocs);
    printf("  Avg. Turnaround Time          : %f\n", t_turnaround / numprocs);
    return;
}

int time_remaining(proc_t * proc)
{
    return proc->m_burst - proc->m_timeburst;
}

proc_t * read_file(const char* fname, int * numprocs)
{
    proc_t * processes;
    int i;
    FILE * procfile = fopen(fname, "r");
    if (!procfile)
    {
        printf("Cannot open file %s for reading; exiting", fname);
        exit(1);
    }
    fscanf(procfile, "%d\n", numprocs);

    processes = calloc(*numprocs, sizeof(proc_t));
    for (i=0; i<*numprocs; i++)
    {
        fscanf(procfile, "%c %d %d\n", &(processes[i].m_procname), &(processes[i].m_burst),
                                     &(processes[i].m_arrive));
    }
    fclose(procfile);
    return processes;
}
