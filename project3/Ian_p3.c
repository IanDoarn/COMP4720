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

void sort(struct Tuple* tuple, int n)
{
    int i, j;

    for (i = 1; i < n; i++)
    {
        for (j = 0; j < n; j++)
            if (tuple[j].burstTime > tuple[j + 1].burstTime) {
                struct Tuple temp = tuple[j];
                tuple[j] = tuple[j + 1];
                tuple[j + 1] = temp;
            }
    }
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

double SJF(struct Tuple *tuple) {

    // sort tuples by shortest burst time
    sort(tuple, TUPLE_SIZE);

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

    printf("FCFS\tSJF\n", NULL);

    for (int j = 0; j < TUPLE_SIZE; ++j) {

        struct Tuple tuple[TUPLE_SIZE];

        // Generate 1000 entries in the table
        for (int i = 0; i < TUPLE_SIZE; ++i) {
            add(&tuple[i]);
        }

        // First Come First Serve
        double awt1 = FCFS((struct Tuple *) &tuple);

        // Shortest Job First
        double awt2 = SJF((struct Tuple *) &tuple);

        printf("%0.1f\t%0.1f\n", awt1, awt2);

    }
    return 0;
}
