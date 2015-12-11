#include <stdio.h>
#include <semaphore.h>
#include "rwlock.h"

typedef struct rwlock_t
{
   sem_t write_mutex; // mutual exclusion for 'writers' var
   sem_t read_mutex; // mutual exclusion for 'readers' var
   sem_t writelock; // refuse thread(s) from altering critical section
   sem_t readlock; // refuse thread(s) from accessing critical section
   int writers; // number of threads writing
   int readers; // number of threads reading
} rwlock_t;

struct rwlock_t rw;

void rwlock_init ()
{
   // initialize semaphores and vars
   sem_init (&rw.write_mutex, 0, 1);
   sem_init (&rw.read_mutex, 0, 1);
   sem_init (&rw.writelock, 0, 1);
   sem_init (&rw.readlock, 0, 1); 
   rw.writers = 0;
   rw.readers = 0;
}

void acquire_readlock ()
{
   sem_wait (&rw.readlock); // wait if thread is writing
   sem_wait (&rw.read_mutex); // protect 'readers' var
   rw.readers ++;
   if (rw.readers == 1)
      sem_wait (&rw.writelock); // block thread(s) from writing
   sem_post (&rw.read_mutex); 
   sem_post (&rw.readlock); 
}

void release_readlock ()
{
   sem_wait (&rw.read_mutex); // protect 'readers' var
   rw.readers --;
   if (rw.readers == 0)
      sem_post (&rw.writelock); // allow thread(s) to write
   sem_post (&rw.read_mutex);
}

void acquire_writelock ()
{
   sem_wait (&rw.write_mutex); // protect 'writers' var
   rw.writers ++;
   if (rw.writers == 1)
      sem_wait (&rw.readlock); // block new thread(s) from reading
   sem_post (&rw.write_mutex);
   sem_wait (&rw.writelock); // single thread starts writing 
}

void release_writelock ()
{
   sem_post (&rw.writelock); // single thread completes writing
   sem_wait (&rw.write_mutex); // protect 'writers' var
   rw.writers --;
   if (rw.writers == 0)
      sem_post (&rw.readlock); // allow thread(s) to read
   sem_post (&rw.write_mutex); 
}
