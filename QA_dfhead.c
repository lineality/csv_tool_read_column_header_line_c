/* 
x86 executable reads .csv file, offset and end.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// some csv files have long rows
#define MAX_LINE_LENGTH 3000

int main()
{
    // variables
    char *path;// file path to (and name of) csv file, input as argument
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int line_count = 0;
    int read_from_here;
    int read_to_here;
    
      /////////////////////////
     // Get and Set Variables
    /////////////////////////
    
    // ask user to type in a number:
    printf("Enter the filepath and name of the .csv you want to read:\n");
    // read in the user input
    scanf("%s", path);

    // ask user to type in a number:
    printf("Enter an integer: What data_row to start reading from?\n");
    // second input is the starting row to read
    scanf("%d", &read_from_here);

    // ask user to type in a number:
    printf("Enter an integer: What data_row to read to? (where to end)\n");   
    // third input is the ending row to read
    scanf("%d", &read_to_here);
    
    
      ///////////////////////
     // Open and Check File
    ///////////////////////
    
    // Open file (use the file name given in first input)
    FILE *file = fopen(path, "r");
    
    // if there is no file, exit to an error message
    if (!file){
	// Error message in English
        printf("specify your file: dfhead.exe YOUR_FILE_NAME");

	// return machine error message
        perror(path);
        
        // fully exit probram
        return EXIT_FAILURE;
    }
    
    /* Terminal Print */
    printf("read_from_here: %d, read_to_here: %d\n", read_from_here, read_to_here);
    
      /////////////////////////
     // Read File: From -> To
    /////////////////////////
    
    /* Get each line until there are none left */
    while (fgets(line, MAX_LINE_LENGTH, file) && (line_count <= read_to_here+1)){
    
    	// read only in the range specified in input
        if (line_count >= read_from_here){
	    /* Test Print */
	    //printf("line_count %d, read_from_here %d, read_to_here %d\n", line_count, read_from_here, read_to_here);
	    
	    /* Print each line
	    The 'row' of data starts at zero after the header-row, 
	    so the first row is kind of row "-2"
	    The data-science dataframe row numbers are important to use here.
	    */
	    printf("data_row[%d]: %s", ++line_count-2, line);
		
	    /* Add a trailing newline to lines that don't already have one */
	    if (line[strlen(line) - 1] != '\n'){
	        printf("\n");
	        }// inner if
	        
	}// main if
	
	// If ("else") the start point is not the beginning, advance to that point.
	else {
	++line_count;
	}
	
    }// end while
    
    
      ////////////////////
     // Tidy Up & Finish
    ////////////////////
    
    /* Close file */
    if (fclose(file)){
        // Error message in English
        printf("error when closing the file");

        return EXIT_FAILURE;
        perror(path);
    }
    
    
    //final exit of program
    return 0;
}

