### csv_tool_read_column_header_line_c
df.head() type file inspector in C language

# Cheatsheet

#### Step 1:  Download Executable
click or save-as this link:
https://github.com/lineality/csv_tool_read_column_header_line_c/blob/main/dfhead.exe?raw=true 

#### Step 2: setup to be able to run the file on your system
```
$ sudo chmod +x ./dfhead.exe
```

#### Step 3: setup to be able to run the file on your system
```
$ ./dfhead.exe NAME_OF_YOUR_FILE_TO_READ STARTING_ROW END_ROW 
```

This repo contains:
- the source code to compile yourself, and/or 
- the .exe to download and run

### Two Versions
1. all command line, automation friendly
2. Q&A input, human executable friendly

# C dfhead.exe

This is a C program that you can use 
to read from a row you specify 
to a row you specify in a .csv file.

E.g. if you want it to mimic the pandas operation: df.head(), then you can input (in the all command line version): 
```
path/this_file.csv 0 5
```
or (in the user Q&A prompt version)
```
Q: "Enter the filepath and name of the .csv you want to read:"
A: path/this_file.csv

Q: Enter an integer: What data_row to start reading from?
A: 0 

Q: Enter an integer: What data_row to read to? (where to end)
A: 5
```
To: 
- print the column headers
- print the 5 rows of data (from zero to five, as specified)



#### df_head.py mimics the pandas operation: df.head()

# Instructions To Compile Code Yourself
## Simple gcc compile & run steps:

#### Step 1: Compile
```
$ gcc -o executable_file_name source_file_name.c
$ gcc -o dfhead.exe dfhead.c
```
#### Step 2: Run
Remember: Three inputs are passed when you call this file:
1. The name of the .csv (or whatever) file you want it to read.
2. Row number you want it to start reading from.
3. Row number you want it to end at.
```
$ ./dfhead.exe NAME_OF_YOUR_FILE_TO_READ STARTING_ROW END_ROW 
```

# Version One Source Code: all on command line

```
/* 
x86 executable reads .csv file, offset and end.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// some csv files have long rows
#define MAX_LINE_LENGTH 3000

int main(int argc, char **argv)
{
    // variables
    char *path;// file path to (and name of) csv file, input as argument
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int line_count = 0;
    int read_from_here;
    int read_to_here;
    
      ///////////////////////////
     // Check and Set Variables
    ///////////////////////////
    
    // check length of input
    if (argc < 3){
    	// Error message in English
        printf("incorrect number of input arguments: 1. file name 2. read_from_here row 3. read_to_here row");
        return EXIT_FAILURE;
        }
        
    // first input is the file path (including file name)
    path = argv[1];
    
    // second input is the starting row to read
    //pseudocode: read_from_here = argv[2];
    sscanf(argv[2], "%d", &read_from_here);
    
    // third input is the ending row to read
    //pseudocode: read_to_here = argv[3];
    sscanf(argv[3], "%d", &read_to_here);
    
    
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


```



# Version Two Source Code: user Q&A prompt guided
```
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


```
