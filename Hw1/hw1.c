// these are the ONLY library header files that can be used. UNDER NO
// CIRCUMSTANCES can additional library headers be included!

#include <stdio.h>	// I/O functions
#include <stdlib.h> 	// atof() function
#include <math.h>	// math functions (eg. sin(), cos(), sqrt())

#include "utils.h"	// user defined functions, constants, and data types
// ----------------------------------------------
// define constants
// define constants
#define PI 3.1415926535  // constant Pi
#define TOTAL_LINES 10   // constant that defines the total number
                         // of line_t values that can be handled
// -----------------------------------
// Main function 
// parameters:	argc --- number of arguments suppled by user on command-line
//		argv --- array of command-line argument values
int main(int argc, char** argv)
{	

	int numLines; 
	double mag; 
	double degrees; 
	double dir; 
	if(argc < 2){
		printf("USAGE: %s lines.txt\n", argv[0]);
		return 1;
	}
	line_t* line_arr = (line_t*) malloc(sizeof(line_t)*TOTAL_LINES);
	numLines = read_lines(argv[1], line_arr, TOTAL_LINES);
	
	for(int i = 0; i < numLines; i++){
		mag = calc_magnitude(line_arr + i);
		dir = calc_direction(line_arr + i);
		degrees = (dir * (180/PI));

		printf("%.2f,%.2f,%.2f,(%.2f, %.2f),(%.2f, %.2f)\n", mag, dir, degrees,line_arr[i].p0.x, line_arr[i].p0.y, line_arr[i].p1.x, line_arr[i].p1.y);
	}
	
	//frees line_arr
	free(line_arr);

	
  /*
    steps to be performed
        1. declare needed variables

	2. allocate DYNAMIC MEMORY for your line array of size
	   TOTAL_LINES. NOTE: you MUST use dynamic memory.  points will
	   be taken off if you do not.

	3. check argc and make sure the program is being called with
	   one (extra) command-line parameter.  For example, from the
	   command-line, the user would enter:

	   $ ./hw1 lines.txt

	4. using the read_lines() function described in utils.h, read
  	   lines from the text file specified in argv[1].  Again, the
  	   location of the text file (eg lines.txt) MUST BE specified
  	   in argv[1].

    	4. Loop through the array of line_t structs and for each line:

	  - compute the magnitude using calc_magnitude()
	  - compute the direction angle in radians using calc_direction()
	  - convert the direction angle to degrees, place in new variable
	  - print the following valus on one line, separated by a comma:
	    * line magnitude (using only 2 decimal places)
  	    * line direction in radians (using only 2 decimal places)
  	    * line direction in degrees (using only 2 decimal places)
	    * (x, y) value of P0 endpoint (using only 2 decimal places)
  	    * (x, y) value of P1 endpoint (using only 2 decimal places)
  
  	    FOR EXAMPLE, for the following two lines of input:
	    0,0,1,1
	    -1, 1, 1, -1

	    THE following two lines would be the corresponding output:
	    1.41,0.79,45.00,(0.00,0.00),(1.00,1.00)
	    2.83,-0.79,-45.00,(-1.00,1.00),(1.00,-1.00)
  */
  return 0;   // main must return an int --- zero means "no errors"
}
