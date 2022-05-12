#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
spinlock_acquire(int *lock)
{
 while(__sync_lock_test_and_set(lock, 1) != 0)
    ;
  __sync_synchronize();
}

void
spinlock_release(int *lock)
{
  __sync_synchronize();
  __sync_lock_release(lock);
}

int counter_lock;
int counter;

void
thread(void *arg)
{
    int i;

    printf("I am thread %l\n", (long) arg);

    for (i = 0; i < 1000; i++) 
    {
        spinlock_acquire(&counter_lock);
        counter += 1;
        spinlock_release(&counter_lock);
    }
    exit(0);
}

int 
main(void)
{
    int id1, id2;
    void *stack1, *stack2;

    counter_lock = 0;
    counter = 0;

    stack1 = sbrk(4096);
    id1 = clone(thread, stack1, (void *) 0);

    stack2 = sbrk(4096);
    id2 = clone(thread, stack2, (void *) 1);

    join(id1);
    join(id2);

    printf("counter = %d\n", counter);
    exit(0);
}
