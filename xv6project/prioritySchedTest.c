#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
    changepolicy(2);

    int allCBT[30] = {0};        
    int allTurnAroundTime[30] = {0}; 
    int allPriority[30] = {0};  
    int allWaitingTime[30] = {0};    

    
    int numberOfChild = -1;

    int priority = -1;

    int parent_id = getpid();


    for (int k=0; k<30; ++k) {
        printf(1, "CHILD %d \n", k);
    }


    for (int i=0; i<30; ++i) {
        if (fork() == 0) {
            wait();
            numberOfChild = i + 1;
            if(0<=i && i<=4) {
                priority = 1;
            }
            if(5<=i && i<=9) {
                priority = 2;
            }
            if(10<=i && i<=14) {
                priority = 3;
            }
            if(15<=i && i<=19) {
                priority = 4;
            }
            if(20<=i && i<=24) {
                priority = 5;
            }
            if(25<=i && i<=29) {
                priority = 6;
            }
            setperiority(priority);
            break;
        }
    }

    if (getpid() != parent_id) {

        for (int i=1; i<=250; ++i) {
            printf(1, "childNumber is /%d/ : /%d/\n", numberOfChild, i);
        }

    } else {

        wait();
        printf(1, "\n === CBT WAT TAT Times for all children === \n");

        int *processTime = malloc(4 * sizeof(int));

        int i = 0;

        while (wait2(processTime) > 0) {
            int chTurnAroundTime = processTime[0];
            int chWaitingTime = processTime[1];
            int chCBT = processTime[2];
            int chPeriority = processTime[3];

            allWaitingTime[i] = chWaitingTime;
            allTurnAroundTime[i] = chTurnAroundTime;
            allCBT[i] = chCBT;
            allPriority[i] = chPeriority;
            
            ++i;
        }

        printf(1, "\n === CBT WAT TAT Times for all children === \n");

        for (int j=0; j<30; ++j) {
            wait();
            printf(1, "*** priority %d ==> TurnAroundTime: %d, WaitingTime: %d, CBT: %d ***\n", allPriority[j], allTurnAroundTime[j], allWaitingTime[j], allCBT[j]);
        }

        printf(1, "\n\n === Average of CBT WAT TAT for every class === \n\n");

        int cbtOfClasses[6] = {0};
        int waitingTimeOfClasses[6] = {0};
        int turnAroundTimeOfClasses[6] = {0};

        for (int j=0; j<30; ++j) {
            int chPeriority = allPriority[j];
            cbtOfClasses[chPeriority - 1] += allCBT[j];
            waitingTimeOfClasses[chPeriority - 1] += allWaitingTime[j];
            turnAroundTimeOfClasses[chPeriority - 1] += allTurnAroundTime[j];
        }

        for (int j=0; j<6; ++j) {
            printf(1, "Priority class: %d HAVE ==> AVG Turnaround: %d, AVG Waiting: %d, AVG CBT: %d\n", j + 1, turnAroundTimeOfClasses[j] / 5, waitingTimeOfClasses[j] / 5, cbtOfClasses[j] / 5);
        }

        printf(1, "\n\n\n*****AVG Times in total*****\n");

        int sumOfCBT = 0;
        int sumOfTurnAroundTime = 0;
        int sumOfWaitingTime = 0;

        for (int j=0; j<30; ++j) {
            sumOfCBT += allCBT[j];
            sumOfWaitingTime += allWaitingTime[j];
            sumOfTurnAroundTime  += allTurnAroundTime[j];
        }

        printf(1, "Total Of CBT WAT TAT is ==> Average of ThurnAroundTime is : %d, Average of WaitingTime is : %d, Average of CBT is : %d\n", sumOfTurnAroundTime/30, sumOfWaitingTime/30, sumOfCBT/30);
    }

    for(int k=0; k<30; ++k) {
        ++k;
    }

    while(wait() != -1) {};

    exit();
}