#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct Tuple {
    int processID, arrivalTime, burstTime;
};

void add(struct Tuple *tuple) {
    tuple->arrivalTime = (rand() % (1000 - 1 + 1)) + 1;
    tuple->burstTime = (rand() % (100 - 1 + 1)) + 1;
    tuple->processID = (rand() % (999 - 100 + 1)) + 100;
}

int main() {

    srand(time(NULL));

    struct Tuple tuple[1000];

    for (int i = 0; i < 1000; ++i) {
        add(&tuple[i]);
    }

    printf("processID\tarrivalTime\tburstTime\n", NULL);

    for (int j = 0; j < 1000; ++j) {
        printf("%d\t\t\t%d\t\t\t%d\n", tuple[j].arrivalTime, tuple[j].burstTime, tuple[j].processID);
    }

    return 0;
}