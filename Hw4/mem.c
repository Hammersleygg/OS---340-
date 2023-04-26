#include <stdio.h>    /* for printf statements when debugging */
#include <stdlib.h>   /* for malloc() and free() */
#include "mem.h"

/*
  Physical memory array. This is a static global array for all
  functions in this file.  An element in the array with a value of
  zero represents a free unit of memory.
*/
static dur_t* memory;

/*
 The size (i.e. number of units) of the physical memory array. This is
 a static global variable used by functions in this file.
 */
static int mem_size;


/*
 The last_placement_position variable contains the end position of the
 last allocated unit used by the next fit placement algorithm.
 */
static int last_placement_position;

/*
  Using the memory placement algorithm, strategy, allocate size
  units of memory that will reside in memory for duration time units.

  If successful, this function returns the number of contiguous blocks
  (a block is a contiguous "chuck" of units) of free memory probed while 
  searching for a suitable block of memory according to the placement 
  strategy specified.  If unsuccessful, return -1.

  If a suitable contiguous block of memory is found, the first size
  units of this block must be set to the value, duration.
 */
int mem_allocate(mem_strats_t strategy, int size, dur_t duration)
{
	int counter = 0;
	
	//best fit 
	if(strategy == 0){
		int i = 0;
		int smallestSize = mem_size + 1;
		int maybeInsert;
		int bestFitI;
		
		while(i < mem_size) {
			while(memory[i] != 0 && i < mem_size) {
				i++;
			}
			
			int zeros;
			int j = i;
			maybeInsert = i;
			
			if(memory[i] == 0) {
				counter++;
			}
			
			while(memory[j] == 0 && j < mem_size) {
				j++;
				zeros = j - i;
			}
			
			if(zeros == size) {
				for(int k = maybeInsert; k < maybeInsert + size; k++) {
					memory[k] = duration; 
				}
				return counter;
			}
			
			if(smallestSize > zeros && zeros >= size) {
				smallestSize = zeros;
				bestFitI = maybeInsert;
			}
			
			i = j;
		}
		
		if(smallestSize == mem_size + 1) {
			return -1;
		}
		else {
			for(int k = bestFitI; k < bestFitI + size; k++){
				memory[k] = duration;
			}
			
			return counter;
		}
	}
	//first fit
	else if(strategy == 1) {
		int i = 0;
		//int zeros = 0;
		
		while(i < mem_size) {
			while(memory[i] != 0) { 
				i++;
			}
			
			int j = i;
			int maybeInsert;
			
			if(memory[i] == 0) {
				counter++;
				maybeInsert = i;
			}
			
			while(memory[j] == 0) {
				j++;
				int zeros = j - i;
				//zeros = j - i;
				
				if(zeros >= size && j < mem_size) {
					for(int  k = maybeInsert; k < maybeInsert + size; k++) {
						memory[k] = duration;
					}
					return counter;
				}
			}
			i = j;
		}
		return -1;
	}
	//next fit
	else if(strategy == 2) {
		//int zeros = 0;
		int i = last_placement_position;
		int j;
		int maybeInsert;
		
		while(i < mem_size) {
			while(memory[i] != 0 && i < mem_size) {
				i++;
			}
			
			if(memory[i] == 0) {
				counter++;
				maybeInsert = i;
			}
			
			j = i;
			
			while(memory[j] == 0 && j < mem_size) {
				j++;
				int zeros = j - i;
				//zeros = j - i;
				
				if(zeros >= size && j < mem_size) {
					for(int k = maybeInsert; k < maybeInsert + size; k++) {
						memory[k] = duration;
					}
					
					last_placement_position = j;
					return counter;
				}
			}
			i = j;
		}
		
		if(i == mem_size && last_placement_position != 0) {
			i = 0;
			
			while(i < last_placement_position) {
				while(memory[i] != 0 && i < last_placement_position) {
					i++; 
				}
				
				if(memory[i] == 0) {
					counter++;
					maybeInsert = i;
				}
				
				j = i;
				
				while(memory[j] == 0 && j < last_placement_position) {
					j++;
					int zeros = j - i;
					//zeros = j - i;
					
					if(zeros >= size && j < mem_size) {
						for(int k = maybeInsert; k < maybeInsert + size; k++) {
							memory[k] = duration;
						}
						
						last_placement_position = j;
						
						return counter;
					}
				}
				i = j;
			}
		}
		
		return -1;
	}
	
	return -1;
}

/*
  Go through all of memory and decrement all positive-valued entries.
  This simulates one unit of time having transpired.  NOTE: when a
  memory cell is decremented to zero, it becomes "unallocated".
 */
int mem_single_time_unit_transpired()
{
	for(int i = 0; i < mem_size; i++){
		if(memory[i] != 0){
			memory[i] = memory[i] - 1;
		}
	}
	return -1;
}

/*
  Return the number of fragments in memory.  A fragment is a
  contiguous free block of memory of size less than or equal to
  frag_size.
 */
int mem_fragment_count(int frag_size)
{
	int counter = 0;
	int i = 0;
	
	while(i < mem_size){
		while(memory[i] != 0){
			i++;
		}
		
		int j = 0;
		
		while(memory[i] == 0 && i < mem_size) {
			j++;
			i++;
		}
		
		int size = j - i;
		
		if(size <= frag_size){
			counter += 1;
		}
	}
	return counter;
}

/*
  Set the value of zero to all entries of memory.
 */
void mem_clear()
{
	for(int i = 0; i < mem_size; i++){
		memory[i] = 0;
	}
}

/*
 Allocate physical memory to size. This function should 
 only be called once near the beginning of your main function.
 */
void mem_init(int size)
{
  memory = malloc(sizeof(dur_t)*size);
  mem_size = size;
}

/*
 Deallocate physical memory. This function should 
 only be called once near the end of your main function.
 */
void mem_free()
{
  free(memory);
}

/*
  Print memory for testing/debugging purposes.  This is an optional
  routine to write, but highly recommended!  You will need to test and
  debug your allocation algorithms.  Calling this routine in your
  main() after every allocation (successful or not) will help in this
  endeavor.  NOTE: you should print the memory contents in contiguous
  blocks, rather than single units; otherwise, the output will be very
  long.
 */
void mem_print()
{
	int i = 0;
	int index = 0;
	
	while(i < mem_size) {
		while(memory[index] == memory[index + 1] && index < mem_size - 1){
			printf("%i-", memory[index]);
			index++;
		}
		
		index++;
		i = index;
		
		printf("\n");
	}
}


