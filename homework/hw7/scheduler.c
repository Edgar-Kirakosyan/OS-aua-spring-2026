//The scheduler based on the esamples given by the homework, this uses basic insertion sorting algorithm.
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;              /* Process ID */
    int arrival_time;     /* Time the process arrives in the system */
    int burst_time;       /* CPU burst time required */
    int turnaround_time;  /* Completion time - arrival time */
    int waiting_time;     /* Turnaround time - burst time */
    int response_time;    /* First run time - arrival time (= waiting time for non-preemptive) */
} Process;

static int runs_before(const Process *a, const Process *b) {
    if (a->arrival_time != b->arrival_time){
        return a->arrival_time < b->arrival_time;
    }
    return a->pid < b->pid;
}

void sort_by_arrival(Process processes[], int n) {
    for (int i = 1; i < n; i++) {
        Process key = processes[i];
        int j = i - 1;
        while (j >= 0 && runs_before(&key, &processes[j])) {
            processes[j + 1] = processes[j];
            j--;
        }
        processes[j + 1] = key;
    }
}

void fcfs(Process processes[], int n) {
    int current_time = 0;

    sort_by_arrival(processes, n);

    for (int i = 0; i < n; i++) {
        Process *p = &processes[i];

        if (current_time < p->arrival_time)
            current_time = p->arrival_time;

        int start_time = current_time;
        int completion_time = start_time + p->burst_time;

        p->response_time = start_time - p->arrival_time;
        p->waiting_time = start_time - p->arrival_time;
        p->turnaround_time = completion_time - p->arrival_time;

        current_time = completion_time;
    }
}

static int shorter_first(const Process *a, const Process *b) {
    if (a->burst_time != b->burst_time){
        return a->burst_time < b->burst_time;
    }
    if (a->arrival_time != b->arrival_time){
        return a->arrival_time < b->arrival_time;
    }
    return a->pid < b->pid;
}

void sort_by_burst(Process processes[], int n) {
    for (int i = 1; i < n; i++) {
        Process key = processes[i];
        int j = i - 1;
        while (j >= 0 && shorter_first(&key, &processes[j])) {
            processes[j + 1] = processes[j];
            j--;
        }
        processes[j + 1] = key;
    }
}

void sjf(Process processes[], int n) {
    int current_time = 0;

    sort_by_burst(processes, n);

    for (int i = 0; i < n; i++) {
        int earliest = processes[i].arrival_time;
        for (int k = i + 1; k < n; k++) {
            if (processes[k].arrival_time < earliest)
                earliest = processes[k].arrival_time;
        }
        if (current_time < earliest)
            current_time = earliest;

        int chosen = i;
        while (processes[chosen].arrival_time > current_time)
            chosen++;

        Process next = processes[chosen];
        for (int k = chosen; k > i; k--) {
            processes[k] = processes[k - 1];
        }
        processes[i] = next;

        Process *p = &processes[i];

        int start_time = current_time;
        int completion_time = start_time + p->burst_time;

        p->response_time = start_time - p->arrival_time;
        p->waiting_time = start_time - p->arrival_time;
        p->turnaround_time = completion_time - p->arrival_time;

        current_time = completion_time;
    }
}

#define CELL 6

static void print_cell(const char *label) {
    int len = 0;
    while (label[len] != '\0')
        len++;
    int left = (CELL - len) / 2;
    int right = CELL - len - left;
    printf("|%*s%s%*s", left, "", label, right, "");
}

void print_gantt(const Process processes[], int n) {
    char label[16];
    int time = 0;

    printf("Gantt Chart: ");
    for (int i = 0; i < n; i++) {
        const Process *p = &processes[i];
        int start_time = p->arrival_time + p->waiting_time;
        if (start_time > time)
            print_cell("IDLE");
        snprintf(label, sizeof(label), "P%d", p->pid);
        print_cell(label);
        time = start_time + p->burst_time;
    }
    printf("|\n");

    printf("%13s", "");
    time = 0;
    for (int i = 0; i < n; i++) {
        const Process *p = &processes[i];
        int start_time = p->arrival_time + p->waiting_time;
        if (start_time > time) {
            printf("%-*d", CELL + 1, time);
            time = start_time;
        }
        printf("%-*d", CELL + 1, time);
        time = start_time + p->burst_time;
    }
    printf("%d\n", time);
}

void print_results(const char *title, const Process processes[], int n) {
    double total_wt = 0, total_tat = 0, total_rt = 0;

    printf("\n=== %s ===\n", title);
    print_gantt(processes, n);

    printf("PID     AT     BT     WT     TAT    RT\n");
    for (int i = 0; i < n; i++) {
        const Process *p = &processes[i];
        printf("%-8d%-7d%-7d%-7d%-7d%d\n",
               p->pid, p->arrival_time, p->burst_time,
               p->waiting_time, p->turnaround_time, p->response_time);
        total_wt += p->waiting_time;
        total_tat += p->turnaround_time;
        total_rt += p->response_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Response Time: %.2f\n", total_rt / n);
}

int main(void) {
    int n;

    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    Process *fcfs_list = malloc(n * sizeof(Process));
    Process *sjf_list = malloc(n * sizeof(Process));
    if (fcfs_list == NULL || sjf_list == NULL) {
        printf("Out of memory.\n");
        free(fcfs_list);
        free(sjf_list);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        Process *p = &fcfs_list[i];
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        if (scanf("%d %d", &p->arrival_time, &p->burst_time) != 2
                || p->arrival_time < 0 || p->burst_time <= 0) {
            printf("Invalid input: arrival time must be >= 0 and burst time > 0.\n");
            free(fcfs_list);
            free(sjf_list);
            return 1;
        }
        p->pid = i + 1;
        p->turnaround_time = 0;
        p->waiting_time = 0;
        p->response_time = 0;

        sjf_list[i] = *p;   
    }

    fcfs(fcfs_list, n);
    print_results("First Come First Served (FCFS)", fcfs_list, n);

    sjf(sjf_list, n);
    print_results("Shortest Job First (SJF)", sjf_list, n);

    free(fcfs_list);
    free(sjf_list);
    return 0;
}
