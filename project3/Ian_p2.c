#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int TUPLE_SIZE = 1000;

struct Tuple {
    int processID, arrivalTime, burstTime;
};

void add(struct Tuple *tuple) {
    tuple->arrivalTime = (rand() % (1000 - 1 + 1)) + 1;
    tuple->burstTime = (rand() % (100 - 1 + 1)) + 1;
    tuple->processID = (rand() % (999 - 100 + 1)) + 100;
}

double FCFS(struct Tuple *tuple) {

    double awt = 0;

    for (int i = 0; i < TUPLE_SIZE; i++) {
        if(i == 0) {
            awt = 0;
        }
        else {
            awt = awt + tuple[i - 1].burstTime;
        }
    }

    return awt / TUPLE_SIZE;
}

int main() {

    srand(time(NULL));

    printf("Average waiting time for FCFS\n", NULL);

    for (int j = 0; j < TUPLE_SIZE ; ++j) {
        struct Tuple tuple[TUPLE_SIZE];

        // Generate 1000 entries in the table
        for (int i = 0; i < TUPLE_SIZE; ++i) {
            add(&tuple[i]);
        }

        // First Come First Serve
        double awt = FCFS((struct Tuple *) &tuple);
        printf("%.1f\n", awt);
    }

    return 0;
}