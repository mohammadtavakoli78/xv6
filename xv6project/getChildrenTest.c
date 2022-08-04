#include "types.h"
#include "stat.h"
#include "user.h"
 
 
 int main(){
     int pid1 = fork();
     int pid2 = fork();
     int pid3 = fork();
     int pid4 = fork();
    if(pid1 > 0 && pid2 > 0 && pid3 > 0 && pid4 > 0){
        int * children = (int*)malloc(sizeof(int)*24);
        getChildren(children);
        printf(1, "this process is %d and the children are", getpid());
        for (int i=0; i<24; i++){
            if(children[i] > 0)
                printf(1,"%d ", children[i]);
        }
        printf(1,"\n");
    }
    while (wait() != -1){}
    sleep(1);
    exit();
 }
