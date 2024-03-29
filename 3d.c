#include <stdio.h>
struct Process
{
    int pid; // Process ID
    int burst_time;
};
void calculateTimes(struct Process processes[], int n)
{
    int waiting_time[n], turnaround_time[n];
    int total_waiting_time = 0, total_turnaround_time = 0;
    waiting_time[0] = 0;
    for (int i = 1; i < n; i++)
    {
        waiting_time[i] = waiting_time[i - 1] + processes[i - 1].burst_time;
        total_waiting_time += waiting_time[i];
    }
    for (int i = 0; i < n; i++)
    {
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
        total_turnaround_time += turnaround_time[i];
    }
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time,
               waiting_time[i], turnaround_time[i]);
    }
    double avg_waiting_time = (double)total_waiting_time / n;
    double avg_turnaround_time = (double)total_turnaround_time / n;
    printf("\nAverage Waiting Time: %.2lf\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2lf\n", avg_turnaround_time);
}
int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }
    calculateTimes(processes, n);
    return 0;
}