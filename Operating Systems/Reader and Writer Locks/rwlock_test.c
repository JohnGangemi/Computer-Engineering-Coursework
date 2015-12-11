#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "rwlock.h"

int critical_var = 100; // variable used in critical section

void *write ()
{
   printf ("\nThread %ld wants to write.", pthread_self());
   acquire_writelock ();
   // critical section
   printf ("\nThread %ld entered critical section and wrote: %d", pthread_self(), critical_var += 100);
   //
   release_writelock ();

   return NULL;
}

void *read ()
{
   printf ("\nThread %ld wants to read.", pthread_self());
   acquire_readlock ();
   // critical section
   printf ("\nThread %ld entered critical section and reads: %d", pthread_self(), critical_var);
   //
   release_readlock ();
   
   return NULL;
}

int main(int argc, char *argv[])
{
   // validate command-line arguments
   if (argc < 3 || argc > 3)
   {
      printf ("Invalid number of arguments.\n");
      exit(0);
   }

   int max_readers = 0;
   max_readers = atoi (argv[1]);
   int max_writers = 0;
   max_writers = atoi (argv[2]);

   printf ("\n**Shared resource is initialized to %d**", critical_var);
   printf ("\n**Writers increment shared resource by 100**");
   printf ("\n  Readers: %d / Writers: %d\n", max_readers, max_writers);

   // initialize rwlock_t struct data members
   rwlock_init();

   // define readers and writers arrays
   pthread_t readers[max_readers];
   pthread_t writers[max_writers];

   // create threads to read and write
   int i = 0;
   if (max_readers >= max_writers)
   {
      while ( i < max_readers)
      {
         pthread_create (&readers[i], NULL, read, NULL);
         if (i < max_writers)
             pthread_create (&writers[i], NULL, write, NULL);
         i++;
      }
   }
   else
   {
      while ( i < max_writers)
      {
         pthread_create (&writers[i], NULL, write, NULL);
         if (i < max_readers)
            pthread_create (&readers[i], NULL, read, NULL);
         i++;
      }
   }

   // allow all threads to complete
   int k = 0;
   while ( k < max_readers)
   {
      pthread_join (readers[k], NULL);
      k++;
   }
   
   int l = 0;
   while ( l < max_writers)
   {
      pthread_join (writers[l], NULL);
      l++;
   }

   printf("\n");
   return 0;
}
