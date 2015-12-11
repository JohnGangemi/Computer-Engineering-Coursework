#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 8 hex value address = 32 bit address 
// 2^32 bits virtual address / 2^12 bits page size = 2^20 pages = 1048576 pages
#define NUM_PTE 1048576

// defines features of a page 
struct pageTableEntry
{
   int valid_bit;
   int dirty_bit;
   int page_number;
   int occurence;
};

// simulated page table of type pageTableEntry
struct pageTableEntry pageTable[NUM_PTE];

int hits = 0; // count total hits in memory
int misses = 0; // count total page faults

void ran (int *mem, int page_num, int frames, int *read, int *write);
void fifo (int *queue, int pages, int page_num, int frames, int *read, int *write);
void lfu (int *mem, int pages, int page_num, int frames, int *read, int *write);
void mfu (int *mem, int pages, int page_num, int frames, int *read, int *write);
void lru (int *mem, int pages, int page_num, int frames, int *read, int *write);
void opt (); // not implemented

int main(int argc, char *argv[])
{
   cpu_set_t mask;   // holds bit pattern for cpu mask  
	CPU_ZERO(&mask);   // sets bit pattern to all zeros
	CPU_SET(0, &mask);   // set appropriate bit to 1 for core 1
	sched_setaffinity(0, sizeof(cpu_set_t), &mask);   // call function to pin the process to the cpu core set by mask struct

   ///////////////////////////////////////////////////////////////////////
   // command line validation ////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////
   if (argc < 5 || argc > 5)
   {
      printf ("Invalid number of arguments.\n");
      exit(0);
   }

   if (strcmp(argv[1], "bzip.trace") != 0 && strcmp(argv[1], "gcc.trace") != 0 && strcmp(argv[1], "swim.trace") != 0 
      && strcmp(argv[1], "sixpack.trace") != 0)
   {
      printf ("Invalid file name.\n");
      exit(0);
   }
   char *fname;
   fname = argv[1];

   int nframes = 0;
   nframes = atoi(argv[2]);

   if (strcmp(argv[3], "rand") != 0 && strcmp(argv[3], "fifo") != 0 && strcmp(argv[3], "lru") != 0 && strcmp(argv[3], "lfu") != 0 
      && strcmp(argv[3], "mfu") != 0 && strcmp(argv[3], "opt") != 0 )
   {
      printf ("Invalid page replacement policy.\n");
      exit(0);
   }
   char *algorithm;
   algorithm = argv[3];

   if (strcmp(argv[4], "debug") != 0 && strcmp(argv[4], "quiet"))
   {
      printf ("Invalid output description.\n");
      exit(0);
   }  
   char *output;
   output = argv[4];
   ///////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////

   // variable declarations
   int reads = 0;
   int writes = 0;
   unsigned addr;
   char rw;
   int iter = 1;
   FILE *fp;

   // create dynamic array for simulated frames of memory
   int *memory;
   memory = malloc (nframes * sizeof(int));
   if (memory == NULL)
   {
      printf ("Error: could not allocate memory\n");
      exit(0);
   }
   
   // instantiate page table entries
   int i = 0;
   for (i = 0; i < NUM_PTE; i++)
   {
      pageTable[i].valid_bit = 0;
      pageTable[i].dirty_bit = 0;
      pageTable[i].page_number = i;
      pageTable[i].occurence = 0;
   }

   // instantiate frames of memory
   int j = 0;
   for (j = 0; j < nframes; j++)
   {
      // mark all unused frames with -1 for debugging purpose
      memory[j] = -1;
   }   

   // open trace file
   fp = fopen (fname, "r");

   // read each line from trace file
   while (fscanf (fp, "%x %c", &addr, &rw) != EOF)
   {
      // use first 5 hex values (20 bits) from hex address to find page number
      addr = addr >> 12;

      // assign dirty bit if necessary
      if (rw == 'W' || rw == 'w')
         pageTable[addr].dirty_bit = 1;

      // page replacement policies
      if (strcmp(algorithm, "rand") == 0)
      {
         ran (memory, addr, nframes, &reads, &writes);
      }
      else if (strcmp(algorithm, "fifo") == 0)
      {
         fifo (memory, iter, addr, nframes, &reads, &writes);
      }
      else if (strcmp(algorithm, "lfu") == 0)
      {
         lfu (memory, iter, addr, nframes, &reads, &writes);
      }
      else if (strcmp(algorithm, "lru") == 0)
      {
         lru (memory, iter, addr, nframes, &reads, &writes);
      }
      else if (strcmp(algorithm, "mfu") == 0)
      {
         mfu (memory, iter, addr, nframes, &reads, &writes);
      }
      else 
         opt ();
      
      /*if (strcmp(output, "debug") == 0)
      {
         printf ("memory: ");
         int q = 0;
         for (q = 0; q < nframes; q++)
         {
            printf ("%d ", memory[q]);
         }
         printf ("\nreads: %d and writes: %d\n", reads, writes);
         printf ("\n");
      }*/

      iter++;
   }   

   if (strcmp(output, "debug") == 0)
   {
      if (hits ==0 && misses == 0)
      {
         printf ("Hit rate could not be calculated\n");
      }
      else
      {
         printf ("hits: %d and misses: %d \n", hits, misses);

         double hit_rate = 0.00;
         hit_rate = (double)hits / (double)(hits + misses);
         hit_rate *= 100;
         printf ("Hit rate: %f percent\n", hit_rate);
      }
   }

   if (strcmp(output, "quiet") == 0)
   {
      printf ("total memory frames: %d\n", nframes);
      printf ("events in trace: %d\n", iter - 1);
      printf ("total disk reads: %d\n", reads);
      printf ("total disk writes: %d\n", writes);
   }

   // handle program resources
   fclose (fp);
   free (memory);

   return 0;
}

/////////////////////////////////////////////////////////////////////
// high level function blocks ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////

void ran (int *mem, int page_num, int frames, int *read, int *write)
{
    // seed rand()
    srand((unsigned)time(NULL));

   // assign vpn to random frame in memory
   if (pageTable[page_num].valid_bit == 0)
   {
      misses++;

      int temp = 0;
      temp = rand() % frames;

      // check if page to be evicted is dirty
      if (pageTable[mem[temp]].dirty_bit == 1)
      {
         // write page to disk and read in new page
         *write += 1; 
         *read += 1;
         
         // change dirty bit for evicted page
         pageTable[mem[temp]].dirty_bit = 0;
      }
      else
         *read += 1; 
      
      // set valid bit for evicted page
      pageTable[mem[temp]].valid_bit = 0;

      mem[temp] = page_num;
      pageTable[page_num].valid_bit = 1;
   }
   else
      hits++;
}

void fifo (int *queue, int pages, int page_num, int frames, int *read, int *write)
{
   unsigned int empty_frame = 0; // flag if empty frame in memory

   if (pages > frames)
   {         
      if (pageTable[page_num].valid_bit == 0)
      {
         misses++;

         // fill queue before evicting pages
         int i = 0;
         for (i = 0; i < frames; i++)
         {
            if (queue[i] == -1 && empty_frame == 0)
            {
              queue[i] = page_num;
              pageTable[page_num].valid_bit = 1;
              *read += 1;
              empty_frame = 1; // set flag 
            } 
         }      
         
         // shift contents and evict first page in memory
         if (!empty_frame)
         {
            int j = 0;
            
            // check if page to be evicted is dirty
            if (pageTable[queue[j]].dirty_bit == 1)
            {
               // write page to disk and read in new page
               *write += 1; 
               *read += 1;
               
               // change dirty bit for evicted page
               pageTable[queue[j]].dirty_bit = 0;
            }
            else
               *read += 1;            

            // set valid bit for evicted page
            pageTable[queue[j]].valid_bit = 0;            

            // check for single element queue (no shifting)
            if (frames > 1)
            {
               for (j = 0; j < frames - 1; j++)
               {
                  // shift element left
                  int temp = 0;
                  temp = queue[j+1];
                  queue[j] = temp;

                  // check when i references 2nd to last element
                  if (j+1 < frames - 1)
                     queue[j+1] = -1; 
                  else
                  {
                     queue[j+1] = page_num; 
                     pageTable[page_num].valid_bit = 1;
                  }
               }
            }
            else
            {
               queue[j] = page_num;
               pageTable[page_num].valid_bit = 1;
            }
         }
      }
      else
         hits++;
   }     
   else
   {
      if (pageTable[page_num].valid_bit == 0)
      {
         misses++;

         // fill queue 
         int i = 0;
         for (i = 0; i < pages; i++)
         {
            if (queue[i] == -1 && empty_frame == 0)
            {            
              queue[i] = page_num;
              pageTable[page_num].valid_bit = 1;
              *read += 1;
              empty_frame = 1; // set flag
            } 
         } 
      }
      else
         hits++;
   }
}

void lfu (int *mem, int pages, int page_num, int frames, int *read, int *write)
{
   if (pages > frames)
   {
      if (pageTable[page_num].valid_bit == 1)
      {
         hits++;
         pageTable[page_num].occurence += 1;
      }
      else
      {
         misses++;

         // find page in memory with smallest occurence value
         int least = pageTable[mem[0]].occurence;
         int index = 0;
         int j = 0;
         for (j = 0; j < frames; j++)
         {
            if (least > pageTable[mem[j]].occurence)
            {
               least = pageTable[mem[j]].occurence;
               index = j;
            }
         }
         
          // check if page to be evicted is dirty
         if (pageTable[mem[index]].dirty_bit == 1)
         {
            // write page to disk and read in new page
            *write += 1; 
            *read += 1;
            
            // change dirty bit for evicted page
            pageTable[mem[index]].dirty_bit = 0;
         }
         else
            *read += 1;

         // set valid bit for evicted page
         pageTable[mem[index]].valid_bit = 0;

         // location of lfu frame is replaced
         mem[index] = page_num;
         pageTable[page_num].occurence = 1;
         pageTable[page_num].valid_bit = 1;
      }
   }
   else
   {
      unsigned int empty_frame = 0; // flag if empty frame in memory

      if (pageTable[page_num].valid_bit == 1)
      {
         hits++;
         pageTable[page_num].occurence += 1;
      }
      else
      {
         misses++;

         int i = 0;
         for (i = 0; i < pages; i++)
         {
            if (mem[i] == -1 && empty_frame == 0)
            {            
              mem[i] = page_num;
              pageTable[page_num].valid_bit = 1;
              pageTable[page_num].occurence = 1;
              *read += 1;
              empty_frame = 1; // set flag
            } 
         } 
      }
   }
}

void mfu (int *mem, int pages, int page_num, int frames, int *read, int *write)
{
   if (pages > frames)
   {
      if (pageTable[page_num].valid_bit == 1)
      {
         hits++;
         pageTable[page_num].occurence += 1;
      }
      else
      {
         misses++;

         // find page in memory with largest occurence value
         int most = pageTable[mem[0]].occurence;
         int index = 0;
         int j = 0;
         for (j = 0; j < frames; j++)
         {
            if (most < pageTable[mem[j]].occurence)
            {
               most = pageTable[mem[j]].occurence;
               index = j;
            }
         }
         
          // check if page to be evicted is dirty
         if (pageTable[mem[index]].dirty_bit == 1)
         {
            // write page to disk and read in new page
            *write += 1; 
            *read += 1;
            
            // change dirty bit for evicted page
            pageTable[mem[index]].dirty_bit = 0;
         }
         else
            *read += 1;

         // set valid bit for evicted page
         pageTable[mem[index]].valid_bit = 0;

         // location of lfu frame is replaced
         mem[index] = page_num;
         pageTable[page_num].occurence = 1;
         pageTable[page_num].valid_bit = 1;
      }
   }
   else
   {
      unsigned int empty_frame = 0; // flag if empty frame in memory

      if (pageTable[page_num].valid_bit == 1)
      {
         hits++;
         pageTable[page_num].occurence += 1;
      }
      else
      {
         misses++;

         int i = 0;
         for (i = 0; i < pages; i++)
         {
            if (mem[i] == -1 && empty_frame == 0)
            {            
              mem[i] = page_num;
              pageTable[page_num].valid_bit = 1;
              pageTable[page_num].occurence = 1;
              *read += 1;
              empty_frame = 1; // set flag   
            } 
         } 
      }
   }
}

void lru (int *mem, int pages, int page_num, int frames, int *read, int *write)
{
   if (pages > frames)
   {       
      if (pageTable[page_num].valid_bit == 1)
      {
         hits++;
         pageTable[page_num].occurence = pages;
      }
      else
      {
         misses++;

         // find page in memory with smallest occurence value
         int least = pageTable[mem[0]].occurence;
         int index = 0;
         int j = 0;
         for (j = 0; j < frames; j++)
         {
            if (least > pageTable[mem[j]].occurence)
            {
               least = pageTable[mem[j]].occurence;
               index = j;
            }
         }
         
          // check if page to be evicted is dirty
         if (pageTable[mem[index]].dirty_bit == 1)
         {
            // write page to disk and read in new page
            *write += 1; 
            *read += 1;
            
            // change dirty bit for evicted page
            pageTable[mem[index]].dirty_bit = 0;
         }
         else
            *read += 1;

         // set valid bit for evicted page
         pageTable[mem[index]].valid_bit = 0;

         // location of lfu frame is replaced
         mem[index] = page_num;
         pageTable[page_num].occurence = pages;
         pageTable[page_num].valid_bit = 1;
      }
   }
   else
   {
      unsigned int empty_frame = 0; // flag if empty frame in memory

      if (pageTable[page_num].valid_bit == 1)
      {
         hits++;
         pageTable[page_num].occurence = pages;
      }
      else
      {
         misses++;

         int i = 0;
         for (i = 0; i < pages; i++)
         {
            if (mem[i] == -1 && empty_frame == 0)
            {            
              mem[i] = page_num;
              pageTable[page_num].valid_bit = 1;
              pageTable[page_num].occurence = pages;
              *read += 1;
              empty_frame = 1; // set flag
            } 
         } 
      }
   }
}

void opt ()
{
}
