Repo link: https://github.com/Edgar-Kirakosyan/OS-aua-spring-2026/tree/main/homework/hw7

Enter the number of processes, then the arrival time and burst time of each one.

Example run:

Enter the number of processes: 3
Enter the arrival time and burst time for process 1: 1 2
Enter the arrival time and burst time for process 2: 3 2
Enter the arrival time and burst time for process 3: 2 5

=== First Come First Served (FCFS) ===
Gantt Chart: | IDLE |  P1  |  P3  |  P2  |
             0      1      3      8      10
PID     AT     BT     WT     TAT    RT
1       1      2      0      2      0
3       2      5      1      6      1
2       3      2      5      7      5

Average Waiting Time: 2.00
Average Turnaround Time: 5.00
Average Response Time: 2.00

=== Shortest Job First (SJF) ===
Gantt Chart: | IDLE |  P1  |  P2  |  P3  |
             0      1      3      5      10
PID     AT     BT     WT     TAT    RT
1       1      2      0      2      0
2       3      2      0      2      0
3       2      5      3      8      3

Average Waiting Time: 1.00
Average Turnaround Time: 4.00
Average Response Time: 1.00
