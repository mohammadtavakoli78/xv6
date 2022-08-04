#include "types.h"
#include "stat.h"
#include "user.h"
 
 
 
 
int stdout = 1;
int main()
{
    int pid = fork();
    if(pid < 0){
        printf(1, "Error. \n");
    }
    else if (pid == 0){
        printf(1, "This is process %d and the parent is %d\n", getpid(), getParentID())   ;
    }
    else{
        wait();
        pid = fork();
        if(pid < 0){
            printf(1, "Error. \n");
        }
        else if (pid == 0){
            printf(1, "This is process %d and the parent is %d\n", getpid(), getParentID())   ;
        }
        else{
            while(wait() != -1){}
            sleep(1);
            printf(1, "This is process %d and the parent is %d\n", getpid(), getParentID())   ;
        
        }   
    }
    exit();
}