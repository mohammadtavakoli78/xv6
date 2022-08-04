#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_setperiority(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  return setperiority(n);
}

int
sys_changepolicy(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  return changepolicy(n);
}
int
sys_getParentID(void)
{
  int pid = myproc()->pid;

  return getParentID(pid);
}
int 
sys_getChildren(void)
{
  int * children;
  if(argptr(0, (void*)&children,sizeof(*children)) < 0)
    return -1;
  return getChildren(children);
}
int 
sys_getSyscallCounter(void){
  int syscall;
  if(argint(0, &syscall) < 0)
    return -1;
  int pid = myproc()->pid;
  return getSyscallCounter(syscall, pid);
}
int
sys_getCBT(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return getCBT(pid);
}

int
sys_getWaitingTime(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return getWaitingTime(pid);
}

int
sys_getTurnAroundTime(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return getTurnAroundTime(pid);
}

int
sys_getTotalCBT(void)
{
  return getTotalCBT();
}

int
sys_getTotalWaitingTime(void)
{
  return getTotalWaitingTime();
}

int
sys_getTotalTurnAroundTime(void)
{
  return getTotalTurnAroundTime();
}

int
sys_wait2(void)
{
  int* processTimes;
  if (argptr(0, (void *)&processTimes, sizeof(*processTimes)) < 0)
  {
    return -1;
  }
  else
  {
    return wait2(processTimes);
  }
}