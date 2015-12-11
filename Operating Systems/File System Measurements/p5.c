#define _GNU_SOURCE
#include <sched.h> // sched_affinity()
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // uint64_t
#include <sys/time.h> // gettimeofday()
// open()
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>
// close()
#include <unistd.h>
// fstatvfs()
#include <sys/statvfs.h>

static inline uint64_t RDTSC()
{
  unsigned int hi, lo;
  __asm__ volatile("rdtsc" : "=a" (lo), "=d" (hi));
  return ((uint64_t)hi << 32) | lo;
}

void TimerAccuracy()
{
   // gettimeofday
	struct timeval first;
	struct timeval last;

   // RDTSC
   uint64_t start = 0;
   uint64_t end = 0;
   
   double seconds_rdtsc = 0;
   double seconds_gettimeofday = 0;

   // timer accuracy comparison
   const int trials = 10;
   int i = 0;
   while (i < trials)
   {
      gettimeofday (&first, NULL);
      start = RDTSC();
      sleep(1);
      end = RDTSC();
      gettimeofday (&last, NULL);
      
      seconds_rdtsc += (double)(end - start) / 3393.0E6; // frequency is specific to C4Lab09 (Intel i7-2600K)
      seconds_gettimeofday += (last.tv_sec - first.tv_sec) + ((last.tv_usec - first.tv_usec)/1E6);

      i++;
   }
   printf ("Comparing Timer Accuracy For 1 Second . . .\n");
   printf ("RDTSC:\n");
   printf ("seconds elapsed: %f\n", seconds_rdtsc / trials);
   printf ("Gettimeofday:\n");
   printf ("seconds elapsed: %f\n", seconds_gettimeofday / trials);
   printf ("\n");
}

int FileBlockSize()
{
   // rdtsc
   uint64_t start = 0;
   uint64_t end = 0;

   struct statvfs fs;
   unsigned long block_size = 0;
   double nanoseconds = 0;
   int offset[7] = {512, 128, 1024, 16, 2048, 256, 4096};
   char buffer[1];
   int fd = 0;
   int i = 0;

   printf ("Measuring File Block Size . . .\n");

   // Actual file system block size **REFERENCE**
   fd = open ("/tmp/os/imgA.jpg", O_RDONLY, S_IRUSR);
   fstatvfs(fd, &fs); // update statvfs struct with file system info
   block_size  = fs.f_bsize; // assign file system block size
   close (fd);
   printf ("Actual file system block size: %lu bytes (%dKB) \n", block_size, (int)block_size / 1024);

   // create a 4KB file based off the actual file system block size 
   fd = open ("/tmp/os/blocksize.txt", O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR); // open or create file if necessary
   while (i < 4096)
   {
      write (fd, "a", 1); // append single byte to file
      i++;
   }

   // perform measurements
   i = 0;
   while (i < 7) 
   {
      lseek (fd, offset[i], SEEK_SET); // set the inode pointer to desired location from beginning of file

      start = RDTSC();
      read (fd, buffer, 1); // read a single byte of data pointed to by 'fd'
      end = RDTSC();
      nanoseconds =  ((double)(end - start) / 3393.0E6) * 1E9; // frequency is specific to C4Lab09 (Intel i7-2600K)

      printf ("Byte %d read time: %f ns\n", offset[i], nanoseconds);
      nanoseconds = 0;
      i++;
   }
   close (fd);
   printf ("Results show the file system block size is indeed 4096 bytes (4KB).\n");
   printf ("\n");

   return (int)block_size;
}

void PrefetchingSize(int arg)
{
   // rdtsc
   uint64_t start = 0;
   uint64_t end = 0;

   double nanoseconds = 0;
   const int blocks = 128; // # blocks to visit (prefetch buffer size)
   int block_size = arg; // fs block size
   int fd = 0;
   int i = 0;
   char buffer[1];

   printf ("Measuring Prefetching Buffer Size . . .\n");

   // fill the cache with irrelevant data (first inode)
   // essentially clearing the cache from previous execution
   fd = open ("/tmp/os/imgB.jpg", O_RDONLY, S_IRUSR);
   while (i < 8388608) // read 8MB of data (L3 cache for i7-2600K)
   {
      read (fd, buffer, 1);
      i++;
   }
   close(fd);

   // perform measurements (second inode) 
   i = 0;
   fd = open ("/tmp/os/imgA.jpg", O_RDONLY, S_IRUSR); // open file, set as read only for user
   while (i < blocks) // read block after block from cache
   {
      lseek (fd, block_size - 1, SEEK_CUR); // set the inode pointer to offset from current location
      start = RDTSC();
      read (fd, buffer, 1); // read a single byte of data from block pointed to by 'fd'
      end = RDTSC();
      nanoseconds =  ((double)(end - start) / 3393.0E6) * 1E9; // seconds = cycles / frequency
      printf ("Block %d read time: %f ns\n", i + 1, nanoseconds);

      i++;
   }
   close (fd);
   printf ("\n");
}

void FileCacheSize(int arg)
{
   // rdtsc
   uint64_t start = 0;
   uint64_t end = 0;

   double nanoseconds = 0;
   char buffer[1];
   int block_size = arg;
   int fd = 0;
   int i = 0;

   printf ("Measuring File Cache Size . . .\n");

   // Fill cache with data from large file
   fd = open ("/tmp/os/imgB.jpg", O_RDONLY, S_IRUSR);
   while (i < block_size * 2048) // read 8MB of data (L3 cache for i7-2600K)
   {
      read (fd, buffer, 1);
      i++;
   }

   // perform measurements
   lseek (fd, block_size - 1, SEEK_SET); // set the inode pointer to first block
   start = RDTSC();
   read (fd, buffer, 1); // read a single byte of data pointed to by 'fd'
   end = RDTSC();
   nanoseconds =  ((double)(end - start) / 3393.0E6) * 1E9; // frequency is specific to C4Lab09 (Intel i7-2600K)
   printf ("Block 1 read time: %f ns\n", nanoseconds);

   // set the inode pointer to cache size + prefetch size to avoid worst case scenario 
   // of the last block (2048)from the file prefetching another 128 blocks 
   lseek (fd, (2048 * block_size) + 128, SEEK_SET);  
   start = RDTSC();
   read (fd, buffer, 1); // read a single byte of data pointed to by 'fd'
   end = RDTSC();
   nanoseconds =  ((double)(end - start) / 3393.0E6) * 1E9; // frequency is specific to C4Lab09 (Intel i7-2600K)
   printf ("Block 2176 (cache + prefetch) read time: %f ns\n", nanoseconds);

   // this read should be greater than the first read to block 1; cache miss
   lseek (fd, block_size - 1, SEEK_SET); // set the inode pointer to first block
   start = RDTSC();
   read (fd, buffer, 1); // read a single byte of data pointed to by 'fd'
   end = RDTSC();
   nanoseconds =  ((double)(end - start) / 3393.0E6) * 1E9; // frequency is specific to C4Lab09 (Intel i7-2600K)
   printf ("Block 1 read time: %f ns\n", nanoseconds);

   close (fd);
   printf ("\n");
}

void DirectPointers(int arg)
{
   // rdtsc
   uint64_t start = 0;
   uint64_t end = 0;
   
   double nanoseconds = 0;
   int block_size = arg;
   int file_size = (256 * block_size); // 1MB file
   int writes = 16; // assumed value larger than # of direct pointers for file system
   int fd = 0;
   int i = 0;

   printf ("Calculating Number Of Direct Pointers . . .\n");

   // create a 1MB file 
   fd = open ("/tmp/os/directptrs.txt", O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR); // open or create file if necessary
   while (i < file_size)
   {
      write (fd, "a", 1); // append single byte to file
      i++;
   }

   // perform measurements
   i = 0;
   while (i < writes)
   {
      lseek (fd, block_size - 1, SEEK_CUR); // write to adjacent blocks
      start = RDTSC();
      write (fd, "X", 1);
      fsync (fd);
      end = RDTSC();
      nanoseconds =  ((double)(end - start) / 3393.0E6) * 1E9; // frequency is specific to C4Lab09 (Intel i7-2600K)
      printf ("Block %d write time: %f ns\n", i + 1, nanoseconds);

      i++;
   }
   close (fd);
   printf ("\n");
}

int main()
{
   // cpu affinity
   cpu_set_t mask; 
	CPU_ZERO (&mask); 
	CPU_SET (0, &mask);   
	sched_setaffinity (0, sizeof(cpu_set_t), &mask);  

   // perform file system measurements
   TimerAccuracy();
   int bsize = 0;
   bsize = FileBlockSize ();
   PrefetchingSize (bsize);
   FileCacheSize (bsize);
   DirectPointers (bsize);

   return 0;
}
