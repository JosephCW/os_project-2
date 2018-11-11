#include "acutest.h"
#include "proc.h"
#include "schedulers.h"

int FCFS1[] = {0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 2, 3};
int SJF1[]  = {0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4};
int SRT1[]  = {0, 0, 1, 2, 1, 3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4};
int RR1[]   = {0, 4, 0, 1, 4, 2, 0, 1, 3, 4, 0, 1, 4, 0, 1, 4, 0, 1, 4, 0, 4, 0, 4, 4};

int FCFS2[] = {0, 0, 0, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3};
int SJF2[]  = {0, 0, 0, 1, 3, 3, 3, 3, 2, 2, 2, 2, 2};
int SRT2[]  = {0, 1, 0, 0, 3, 3, 3, 3, 2, 2, 2, 2, 2};
int RR2[]   = {0, 1, 0, 2, 3, 0, 2, 3, 2, 3, 2, 3, 2};

void _test_sched(const char * fname, int (*sched) (proc_t *, int, int), const int expected[], const int num_expected)
{
    int numprocs;
    proc_t * procs = read_file(fname, &numprocs);
    proc_t * p;
    for (int j=0; j<num_expected; j++)
    {
        int to_run = sched(procs, numprocs, j);
        TEST_CHECK(to_run == expected[j]);
        for (int i=0; i<numprocs; i++)
        {
            p = &(procs[i]);
            if (i == to_run)
                burst(p);
            else if (!running(p, j))
                nop(p);
            else
                wait_p(p);
        }
    }
    reset_all(procs, numprocs);
    free(procs);
}

void fcfs_testprocs()
{
    _test_sched("testprocs.txt", fcfs, FCFS1, 24);
}

void sjf_testprocs()
{
    _test_sched("testprocs.txt", sjf, SJF1, 24);
}

void srt_testprocs()
{
    _test_sched("testprocs.txt", srt, SRT1, 24);
}

void rr_testprocs()
{
    _test_sched("testprocs.txt", rr, RR1, 24);
}
// --- 
void fcfs_aprocs()
{
    _test_sched("aprocs.txt", fcfs, FCFS2, 13);
}

void sjf_aprocs()
{
    _test_sched("aprocs.txt", sjf, SJF2, 13);
}

void srt_aprocs()
{
    _test_sched("aprocs.txt", srt, SRT2, 13);
}

void rr_aprocs()
{
    _test_sched("aprocs.txt", rr, RR2, 13);
}

TEST_LIST = {
    {"FCFStestprocs", fcfs_testprocs},
    {"SJFtestprocs", sjf_testprocs},
    {"SRTtestprocs", srt_testprocs},
    {"RRtestprocs", rr_testprocs},
    {"FCFSaprocs", fcfs_aprocs},
    {"SJFaprocs", sjf_aprocs},
    {"SRTaprocs", srt_aprocs},
    {"RRaprocs", rr_aprocs},
    {NULL, NULL}
};
