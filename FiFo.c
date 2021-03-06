// FiFo.c
// Runs on LM4F120/TM4C123
// Provide functions that implement the Software FiFo Buffer
// Last Modified: 4/12/2016 
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly

#include <stdint.h>
// Declare state variables for FiFo
//        size, buffer, put and get indexes
#define FIFO_SIZE 200
int32_t PutI; // Index to put new
int32_t GetI; // Index of oldest 
int32_t Fifo[FIFO_SIZE];


// *********** FiFo_Init**********
// Initializes a software FIFO of a
// fixed size and sets up indexes for
// put and get operations
void FiFo_Init() {
	PutI = GetI = 0;
}

// *********** FiFo_Put**********
// Adds an element to the FIFO
// Input: Character to be inserted
// Output: 1 for success and 0 for failure
//         failure is when the buffer is full
uint32_t FiFo_Put(char data) {
   if ( (PutI+1)%FIFO_SIZE == GetI) {
          return(0);
   }
   Fifo[PutI] = data;
   PutI = (PutI+1)%FIFO_SIZE;
   return(1);

}

// *********** FiFo_Get**********
// Gets an element from the FIFO
// Input: Pointer to a character that will get the character read from the buffer
// Output: 1 for success and 0 for failure
//         failure is when the buffer is empty
uint32_t FiFo_Get(char *datapt)
{
   if (GetI == PutI) {
          return(0);
   }
   *datapt = Fifo[GetI];
   GetI = (GetI+1)%FIFO_SIZE;
   return(1);
}



