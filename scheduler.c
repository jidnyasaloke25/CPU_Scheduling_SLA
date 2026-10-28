/*
 CPU Process Scheduling Simulator - C implementation
 Algorithms: SJF (non-preemptive) and SRTF (preemptive)
 Compile: gcc scheduler.c -o scheduler
 Run:     ./scheduler       (Windows: scheduler.exe)
*/
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX 100
typedef struct {
    char id[16];
    int at, bt, remaining, ct, tat, wt, rt, done;
} Process;

void print_results(Process p[], int n, const char *algorithm) {
    double avg_wt = 0, avg_tat = 0;
    int end = 0, busy = 0;
    printf("\n=== %s RESULTS ===\n", algorithm);
    printf("%-10s %-8s %-8s %-12s %-12s %-10s %-10s\n",
           "Process", "Arrival", "Burst", "Completion", "Turnaround", "Waiting", "Response");
    for (int i = 0; i < n; i++) {
        printf("%-10s %-8d %-8d %-12d %-12d %-10d %-10d\n",
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
        if (p[i].ct > end) end = p[i].ct;
        busy += p[i].bt;
    }
    printf("Average waiting time: %.2f\n", avg_wt / n);
    printf("Average turnaround time: %.2f\n", avg_tat / n);
    printf("CPU utilization: %.2f%%\n", end ? 100.0 * busy / end : 0.0);
}

void sjf(Process original[], int n) {
    Process p[MAX];
    memcpy(p, original, n * sizeof(Process));
    int time = 0, completed = 0;
    while (completed < n) {
        int best = -1;
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time &&
                (best == -1 || p[i].bt < p[best].bt ||
                 (p[i].bt == p[best].bt && p[i].at < p[best].at))) best = i;
        }
        if (best == -1) {
            int next = INT_MAX;
            for (int i = 0; i < n; i++)
                if (!p[i].done && p[i].at < next) next = p[i].at;
            time = next;
            continue;
        }
        Process *x = &p[best];
        x->rt = time - x->at;
        time += x->bt;
        x->ct = time; x->tat = x->ct - x->at; x->wt = x->tat - x->bt;
        x->done = 1; completed++;
    }
    print_results(p, n, "SJF");
}

void srtf(Process original[], int n) {
    Process p[MAX];
    memcpy(p, original, n * sizeof(Process));
    int time = 0, completed = 0;
    while (completed < n) {
        int best = -1;
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time &&
                (best == -1 || p[i].remaining < p[best].remaining ||
                 (p[i].remaining == p[best].remaining && p[i].at < p[best].at))) best = i;
        }
        if (best == -1) {
            int next = INT_MAX;
            for (int i = 0; i < n; i++)
                if (!p[i].done && p[i].at < next) next = p[i].at;
            time = next;
            continue;
        }
        if (p[best].rt == -1) p[best].rt = time - p[best].at;
        p[best].remaining--;
        time++;
        if (p[best].remaining == 0) {
            p[best].done = 1;
            p[best].ct = time;
            p[best].tat = p[best].ct - p[best].at;
            p[best].wt = p[best].tat - p[best].bt;
            completed++;
        }
    }
    print_results(p, n, "SRTF");
}

int main(void) {
    Process p[MAX];
    int n;
    printf("CPU Process Scheduling Simulator (SJF / SRTF)\n");
    printf("Enter number of processes (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid process count.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        printf("\nProcess ID (no spaces): ");
        scanf("%15s", p[i].id);
        printf("Arrival time: ");
        scanf("%d", &p[i].at);
        printf("Burst time: ");
        scanf("%d", &p[i].bt);
        if (p[i].at < 0 || p[i].bt < 1) {
            printf("Arrival must be >= 0 and burst must be >= 1.\n");
            return 1;
        }
        p[i].remaining = p[i].bt;
        p[i].ct = p[i].tat = p[i].wt = 0;
        p[i].rt = -1;
        p[i].done = 0;
    }
    sjf(p, n);
    srtf(p, n);
    return 0;
}
