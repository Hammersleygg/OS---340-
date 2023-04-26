// -----------------------------------
// CSCI 340 - Operating Systems I 
// Spring 2023 (Anthony Leclerc)
// utils.c implementation file
// Homework Assignment 1
//
// -----------------------------------

// these are the ONLY library header files that can be used. Under no
// circumstances can additional library header files be included.  In
// particular, this restriction means you CANNOT USE any function
// declared in <string.h>, which includes functions such as: strtok(),
// strchr(), strstr(), strlen(), index(), and others.

// NOTE: when you compile, DO NOT IGNORE WARNINGS!  These warnings are
// likely indicating you are doing something wrong, such as using a
// library function that you are not allowed to use or passing the
// wrong type of argument into a function.

#include <stdio.h>	// standard I/O functions
#include <stdlib.h> 	// atof()
#include <math.h>	// math functions

#include "utils.h"	// user defined functions

// see utils.h for the required function prototypes and specifications

// NOTE: you may add any "helper" functions you need to get the job done.
//       for example, if you need to determine the length of a string.

// put your IMPLEMENTATION of the function prototypes below:
int read_lines(char* filename, line_t* line_arr, int n){
	//Reading in the file 
	FILE* myFile;
	myFile = fopen(filename, "r");
	
	
	//if the file isn't found
	if(myFile == NULL){
		printf("File not found.\n");
	}
	
	char myArray[128];
	int lineNum = 0;
	
	while(fgets(myArray, 80, myFile)){
		char buffer[128];
		int iterator = 0;
		int lineCounter = 0;
	
		point_t p0;
		point_t p1;
		line_t line;
	
		double vals[4];
		int valIterator = 0;
	
		while(myArray[lineCounter] != '\0'){
			if(myArray[lineCounter] == ',' || myArray[lineCounter] == '\n') {
				buffer[iterator + 1] = '\0';
				vals[valIterator] = atof(buffer);
				
				//sets the buffer array to 0
				for(int i = 0; i < 128; i++){
					buffer[i] = 0;
				}
				
				iterator = 0;
				valIterator++; 
			}
			else {
				buffer[iterator] = myArray[lineCounter];
				iterator++;
			}
			lineCounter++;
		}
		p0.x = vals[0];
		p0.y = vals[1];
		p1.x = vals[2];
		p1.y = vals[3];
	
		line.p0 = p0;
		line.p1 = p1;
	
		line_arr[lineNum] = line;
		lineNum++;	
	}
	//printf("total lines: %d\n", lineNum);
	return lineNum;
	}



double calc_direction(line_t* line_ptr){

	double angle = 0;
	
	double x0 = line_ptr -> p0.x;
	double y0 = line_ptr -> p0.y;
	
	double x1 = line_ptr -> p1.x;
	double y1 = line_ptr -> p1.y;
	
	
	//angle
	angle = atan2(y1 - y0, x1 - x0);
	//printf("Direction: %f\n", angle);
	
	return angle;
}

double calc_magnitude(line_t* line_ptr){
	
	double magnitude = 0;
	
	double x0 = line_ptr -> p0.x;
	double y0 = line_ptr -> p0.y;
	
	double x1 = line_ptr -> p1.x;
	double y1 = line_ptr -> p1.y;
	
	
	//magnitude
	magnitude = sqrt(((x1 - x0)*(x1 - x0)) + ((y1 - y0) * (y1 - y0)));
	//printf("Magnitude: %f\n", magnitude);
	
	return magnitude; 
}






