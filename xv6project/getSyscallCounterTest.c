#include "types.h"
#include "stat.h"
#include "user.h"
 

int main(int argc, char **argv)
{
    if(argc > 2){
        for (int i=1; i < argc; i++)
        printf(1, "syscall counter is : %d\n", getSyscallCounter(atoi(argv[i])));
    } 
    exit();
}