#include "types.h"
#include "stat.h"
#include "user.h"

int turnAroundTime = 0;
int waitingTime = 0;
int cputBurstTime = 0;

int main()
{

    changepolicy(1);

    printf(1, "*** This is RoundRobinTest ***\n");

    int parentID = getpid();

    for (int i=0; i<10; i++)
    {
        if (fork() > 0)
            break;
    }

    if (parentID != 0)
    {
        wait();
        for (int i=0; i<1000; i++) {
            printf(1, "/%d/: %d\n", getpid(), i);
            wait();
        }

        int tat = getTurnAroundTime(getpid());
        int wat = getWaitingTime(getpid());
        int cbt = getCBT(getpid());
        
        turnAroundTime += tat;
        waitingTime += wat;
        cputBurstTime += cbt;

        wait();

        printf(1, "*** turnAroundTime for process %d is : %d ***\n", getpid(), tat);
        printf(1, "*** waitingTime for process %d is : %d\n ***", getpid(), wat);
        printf(1, "*** CBT for process %d is : %d\n ***", getpid(), cbt);
        printf(1, "\n\n\n");

    }

    printf(1, "*** AVERAGE of turnAroundTime is : %d *** \n", getTotalTurnAroundTime()/10);
    printf(1, "*** AVERAGE of waitingTime %d *** \n", getTotalWaitingTime()/10);
    printf(1, "*** AVERAGE of CBT %d\n *** ", getTotalCBT()/10);

    while (wait() != -1);

    exit();
}