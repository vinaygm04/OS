#include <stdio.h>

typedef struct {
    int pid;
    int period;     
    int burst;     
    int remaining; 
} Task;

void sortByPeriod(Task tasks[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (tasks[i].period > tasks[j].period) {
                Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
        tasks[i].remaining = tasks[i].burst;
    }
}

void rateMonotonic(Task tasks[], int n, int sim_time) {
    printf("\nRate-Monotonic Scheduling:\n");
    printf("Time\tTask\n");
   
    sortByPeriod(tasks, n);
   
    for (int time = 0; time < sim_time; time++) {
        int scheduled = -1;
       
        
        for (int i = 0; i < n; i++) {
            if (time % tasks[i].period == 0) {
                tasks[i].remaining = tasks[i].burst;
            }
        }
       
      
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0) {
                scheduled = i;
                break;
            }
        }
     
        if (scheduled != -1) {
            tasks[scheduled].remaining--;
            printf("%d\tT%d\n", time, tasks[scheduled].pid);
        } else {
            printf("%d\tIdle\n", time);
        }
    }
}

int main() {
    int n, sim_time;
    printf("Enter number of tasks: ");
    scanf("%d", &n);
   
    Task tasks[n];
    for (int i = 0; i < n; i++) {
        tasks[i].pid = i+1;
        printf("Enter period and burst time for task T%d: ", i+1);
        scanf("%d %d", &tasks[i].period, &tasks[i].burst);
    }
   
    printf("Enter simulation time: ");
    scanf("%d", &sim_time);
   
    rateMonotonic(tasks, n, sim_time);
   
    return 0;
}
