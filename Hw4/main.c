#include <stdio.h>    /* for printf */
#include <stdlib.h>   /* for string to integer conversion, random numbers */
#include "mem.h"

/*
  The main program will accept four paramemters on the command line.
  The first parameter is the memory size.  The second parameter is the
  duration of the each simulation run.  The third parameter is the
  number of times to repeat each experiment (ie. number of runs). The
  fourth parameter is a random number seed. Here is an example command
  line:

  ./hw7 1000 3000 100 1235

  This means that your program should initialize physical memory to
  1,000 units, perform 100 runs with each run taking 3000 units of
  time, and the random number generator should be seeded (one time)
  with the value 1235.
*/

int main(int argc, char** argv)
{  
	//input 
	int numUnits = atoi(argv[1]);
	int numUnitsTime = atoi(argv[2]);
	int numRuns = atoi(argv[3]);
	int randSeed = atoi(argv[4]);
	
	//array 
	mem_init(numUnits);
	
	//variables for BF
	double avgProbeBF = 0;
	double avgFailedBF = 0;
	double avgFragmentBF = 0;
	
	double numProbesBF = 0;
	double numFailedBF = 0;
	double numFragmentedBF = 0;
	
	//variables for FF
	double avgProbeFF = 0;
	double avgFailedFF = 0;
	double avgFragmentFF = 0;
	
	double numProbesFF = 0;
	double numFailedFF = 0;
	double numFragmentedFF = 0;
	
	//variables for NF
	double avgProbeNF = 0;
	double avgFailedNF = 0;
	double avgFragmentNF = 0;
	
	double numProbesNF = 0;
	double numFailedNF = 0;
	double numFragmentedNF = 0;
	
	//BEST FIT
	srand(randSeed);
	
	mem_clear();
	
	for(int i = 0; i < numRuns; i++) {
		for(int j = 0; j < numUnitsTime; j++) {
			//random numbers 
			int randSize = rand() % (MAX_REQUEST_SIZE - MIN_REQUEST_SIZE);
			int randDura = rand() % (MAX_DURATION - MIN_DURATION);
			
			randSize += MIN_REQUEST_SIZE;
			randDura += MIN_DURATION;
			
			//value for mem_allocate 
			int checker; 
			checker = mem_allocate(BESTFIT, randSize, randDura);
			
			if(checker == -1) {
				numFailedBF += 1;
			}
			else {
				numProbesBF += checker;
			}
			mem_single_time_unit_transpired();
		}
		//fragments
		numFragmentedBF += mem_fragment_count(MIN_REQUEST_SIZE - 1);
		
		mem_clear();
	}
	//averages 
	avgProbeBF = numProbesBF/numRuns;
	avgFailedBF = numFailedBF/numRuns;
	avgFragmentBF = numFragmentedBF/numRuns;
	
	printf("BEST FIT: \n");
	printf("Average number probes for Best Fit %.2f\n", avgProbeBF);
	printf("Average number of failed probes for Best Fit %.2f\n", avgFailedBF);
	printf("Average number of memory fragments for Best Fit %.2f\n", avgFragmentBF);
	
	//FIRST FIT
	srand(randSeed);
	
	mem_clear();
	
	for(int i = 0; i < numRuns; i++) {
		for(int j = 0; j < numUnitsTime; j++) {
			//random numbers 
			int randSize = rand() % (MAX_REQUEST_SIZE - MIN_REQUEST_SIZE);
			int randDura = rand() % (MAX_DURATION - MIN_DURATION);
			
			randSize += MIN_REQUEST_SIZE;
			randDura += MIN_DURATION;
			
			//value for mem_allocate
			int checker; 
			checker = mem_allocate(FIRSTFIT, randSize, randDura);
			
			if(checker == -1){
				numFailedFF += 1; 
			}
			else {
				numProbesFF += checker;
			}
			mem_single_time_unit_transpired();
		}
		//fragments
		numFragmentedFF += mem_fragment_count(MIN_REQUEST_SIZE - 1);
		
		mem_clear();
	}
	//averages
	avgProbeFF = numProbesFF/numRuns;
	avgFailedFF = numFailedFF/numRuns;
	avgFragmentFF = numFragmentedFF/numRuns;
	
	printf("\n");
	printf("FIRST FIT: \n");
	printf("Average number probes for First Fit %.2f\n", avgProbeFF);
	printf("Average number of failed probes for First Fit %.2f\n", avgFailedFF);
	printf("Average number of memory fragments for First Fit %.2f\n", avgFragmentFF);
	
	//NEXT FIT
	srand(randSeed);
	
	mem_clear();
	
	for(int i = 0; i < numRuns; i++){
		for(int j = 0; j < numUnitsTime; j++) {
			//random numbers 
			int randSize = rand() % (MAX_REQUEST_SIZE - MIN_REQUEST_SIZE);
			int randDura = rand() % (MAX_DURATION - MIN_DURATION);
			
			randSize += MIN_REQUEST_SIZE;
			randDura += MIN_DURATION;
			
			//value for mem_allocate
			int checker; 
			checker = mem_allocate(NEXTFIT, randSize, randDura);
			
			if(checker == -1) {
				numFailedNF += 1;
			}
			else {
				numProbesNF += checker;
			}
			mem_single_time_unit_transpired();
		}
		//fragmenta
		numFragmentedNF += mem_fragment_count(MIN_REQUEST_SIZE -1);
		
		mem_clear();
	}
	//averages
	avgProbeNF = numProbesNF/numRuns;
	avgFailedNF = numFailedNF/numRuns;
	avgFragmentNF = numFragmentedNF/numRuns;

	printf("\n");
	printf("NEXT FIT: \n");	
	printf("Average number probes for Next Fit %.2f\n", avgProbeNF);
	printf("Average number of failed probes for Next Fit %.2f\n", avgFailedNF);
	printf("Average number of memory fragments for Next Fit %.2f\n", avgFragmentNF);
	
	mem_free();
	
  	return 0;
}
