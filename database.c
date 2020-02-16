/*****************************************************************
//
//  NAME:		Ehsan Kourkchi
//
//  HOMEWORK:		Project 1
//
//  CLASS:		ICS 212
//
//  INSTRUCTOR:		Ravi Narayan
//
//  DATE:		October 20, 2013           
//
//  FILE:		database.c        
//
//  DESCRIPTION:	This file contains the user-interface and functions 
//			to handle a database [Project 1] 
//
//****************************************************************/
// To compile the program:
// $ make all
// $ ./database
//****************************************************************/


#define RED "\033[1;31m"
#define GREEN "\033[1;32m" 
#define BLUE "\033[1;34m" 
// background: blue foeground: cyan
#define CYAN "\033[44;1;36m"
// "\033[K" clears the end of Line
#define DEFCOLOR "\033[0m\033[K"
#define YELLOW "\033[44;1;33m"

# include <stdio.h>
# include <string.h>
# include  <stdlib.h>
# include "record.h"
# include "databaseio.h"
#include "database_functions.h"


 
 // Display header
 // Main Menu
 // Program Arguments Handling
 void header(void);
 int main_menu(int numberOfRecords);
 int arguments(int argc, char * argv[]);
 
 // UserInterface to ask a user to input the data
 int getfield(char * input_string, char string_name[], int mode, int maxSize);
 int get_address(char * address, char string[], int maxSize);
 int get_name(char * name, char string[], int maxSize);
 int get_int(int * number, int lower, int upper);
 void get_int_txt(int * year, int lower, int upper, char text []);
 
 // User Interface to handle the database
 int getdata(struct record ** start);
 int printdata(struct record * start);
 int modifydata(struct record * start);
 int removedata(struct record ** start);
 
 // Some additonal functions
 int string_equality(char a [], char b []);
 void StringColorPrint(char * string, char color[]);


/*****************************************************************/
// GLOBAL VARIABLES */

 int debugmode = 0;

/****************************************************************/


int main(int argc, char *argv[])
{
  
  //char address[80];
  //char name[25];
  //char telephone[15];
  //int  yearofbirth;
  int i;
  char filename[25];
  int check, menu;
  int goto_main_menu=1, exit_program=0;
  int numberOfRecords = 0;
  struct record *start = NULL, *current, *temp;
  
  
  
header(); // program main header
  
strcpy(filename, "Database.txt");  // naming the database i/o file

numberOfRecords = readfile(&start, filename); // reading in the database from disk
 
if (arguments(argc, argv) == 1) return 1;


do {
  
menu = main_menu(numberOfRecords);
switch (menu)
{
  case 1: // add
    check = getdata(&start);
    if (check == 100) numberOfRecords++;
    if (check == 0) exit_program=1;
    else  goto_main_menu=1;
    break;
  case 4:  // print
    check = printdata(start);
    if (check == 0) exit_program=1;
    else  goto_main_menu=1;
    break;
  case 2: // modify
    check = modifydata(start);
    if (check == 0) exit_program=1;
    else  goto_main_menu=1;
    break;
  case 5: // print all
    printAllRecords(start);
    goto_main_menu=1;
    break;
  case 3:  // remove
    check = removedata(&start);
    if (check == -1) exit_program=1;
    else  {goto_main_menu=1;  numberOfRecords-= check;}
    break;
  case 6:  // exit
    exit_program=1;
    break;
}
 

} while(exit_program == 0 && goto_main_menu==1) ;
 
 

printf("\n\n The database is available in \"Database.txt\"  ...\n Goodbye ....\n\n");


writefile(start, filename);  // writing out into the file
 

/** Releasing memory */
current = start;
while(current != NULL) 
{ 
  temp = current->next;
  free(current);
  current = temp;
}
 

fflush(stdout);
return 0; 

} /** The end of main program */

/*****************************************************************/
/*****************************************************************/
/*****************************************************************/

/*****************************************************************
//
//  Function name:		get_address  
//
//  DESCRIPTION:		a function to get address like strings 
				the input string may have new_line (i.e. '\n')
				
//  Parameters:			char *address: The pointer to the string which will be entered by user
//				char string[]: The name of the string which will be displayed for user to enter
//
//  Return values:		int: It always equal 1 in this version
//
//****************************************************************/

int get_address(char *address, char string[], int maxSize)
{
  int boolean = 0;
  int counter = 0;
  char test_char0 = ' ', test_char1 = ' ' ;
  
  
  printf(" Enter the %s:  ", string);
  printf("\n Press the <Enter> key two times when you are done\n");

  do 
  {
    boolean = 0;
    counter = 0;
  

    test_char0 = ' ';
    test_char1 = '\0' ;
    StringColorPrint("# ", "def");
 
	while(boolean == 0) 
	{
	      
	  test_char0 = fgetc(stdin);
	  
	  if (counter <= maxSize)
	      *(address+counter) = test_char0;
	  
	  if (test_char0 == '\n' && test_char1 == '\0')       
	    boolean = 1;
	  
	  if (test_char0 == '\n' && test_char1 == '\n')    
	  {   
	    boolean = 1; 
	    counter--; 
	  }
	  
	  if (test_char0 == '\n' && boolean == 0) 
	    StringColorPrint("# ", "def");
	  
	test_char1 = test_char0;   
	
	if (counter <= maxSize) 
	  counter++;
	}
	
  
  *(address+counter-1) = '\0';
  

	if ( *address == '\0') 
	{
	  printf(RED);
	  printf(" Enter a valid %s again:\n", string);
	  printf(DEFCOLOR);
	}
      
  } while(*address == '\0');
  

return 1;
}

/*****************************************************************
//
//  Function name:		get_name  
//
//  DESCRIPTION:		a function to get name like strings 
				the input string Can NOT have new_line (i.e. '\n')
				
//  Parameters:			char *name: The pointer to the string which will be entered by user
//				char string[]: The name of the string which will be displayed for user to enter
//
//  Return values:		int: It always equal 1 in this version
//
//****************************************************************/

int get_name(char *name, char string[], int max_size)
{
  int boolean = 0;
  int counter = 0;
  char test_char0 = ' ', test_char1 = ' ' ;
    printf(" Enter the %s: ", string);

do {
  
  boolean = 0;
  counter = 0;
  test_char0 = ' ';
  test_char1 = ' ' ;

  while(boolean == 0 ) 
  {
    test_char0 = fgetc(stdin);
    if (counter <= max_size && (test_char1 != ' ' || test_char0 != ' '))   
    {
      *(name+counter) = test_char0;
      counter++;
    }

    if (test_char0 == '\n') boolean = 1;    
    test_char1 = test_char0;   
  }

  *(name+counter-1) = '\0';
  if (counter > 1 && *(name+counter-2) == ' ') 
    *(name+counter-2) = '\0';
  
  
  
  
  
  
  
  if ( *name == '\n' || *name == '\0') 
  {
   printf(RED);
   printf(" Enter a valid %s again: ", string); 
   printf(DEFCOLOR);
  }
  
} while(*name == '\n' || *name == '\0');
  

return 1;
}

/*****************************************************************
//
//  Function name:		get_int  
//
//  DESCRIPTION:		a function that asks a user to enter an integer number
				using 'fgetc' method. The entered number musr meet the upper and lower boundry
//
//  Parameters:			int *number: the pointer to the input number 
//				int lower: the lower limit of the input
				int upper: the upper limit of the input
				
//  Return values:		int: 1 if an integer number between lower and upper limit entered by user
				     0 if the above conditions is not satisfied
//
//****************************************************************/


int get_int(int *number, int lower, int upper)
{
  
char input_string[100], input_char;
int length_string = 0, i, delta, boolean = 1, sum = 0, get_char = 1;
char zero='0';

  while(get_char) 
  {
    
    input_char = fgetc(stdin);
    input_string[length_string] = input_char;
    length_string++;
    if (input_char == '\n') get_char = 0;
  } 
  
  
  length_string -= 1;
  *(input_string+length_string) = '\0';

  sum = 0;
  for(i=length_string-1; i >= 0; i--)
  {
    
	delta = (int) input_string[length_string-i-1] - (int) zero;

	if (delta <= 9 && delta >= 0) 
	  sum = 10 * sum + delta;
	else 
	{ 
	    boolean = 0;
	    break;
	}

  }
  
  if(boolean == 1 && sum >= lower && sum <= upper) 
    *number = sum;
  else boolean = 0;
  
  
return boolean;
}


/*****************************************************************
//
//  Function name:		get_int_txt  
//
//  DESCRIPTION:		a function that asks a user to enter an integer number
				using 'get_int' function. It is basically the same as 'get_int' function.
//
//  Parameters:			int *number: the pointer to the input number 
//				int lower: the lower limit of the input
				int upper: the upper limit of the input
				char text []: The string which will be displayed for user to enter
				
//  Return values:		int: 1 if an integer number between lower and upper limit entered by user
				     0 if the above conditions is not satisfied
//
//****************************************************************/

void get_int_txt(int *number, int lower, int upper, char text [])
{

  int boolean = 0;

  printf("%s", text);  
  boolean = get_int(number, lower, upper);
  
  while(!boolean) 
  {
   StringColorPrint(text, "red");
   boolean = get_int(number, lower, upper);
  }
    
}  
  
  
/*****************************************************************
//
//  Function name:		header  
//
//  DESCRIPTION:		It displayes the main header for the user  
				
//  Parameters:			No input
//				
//
//  Return values:		No output
//
//****************************************************************/

void header(void)
{
  
   //if (!debugmode) printf("\033[2J"); // clear screen
   //if (!debugmode) printf("\033[100A"); // 100 lines up
   if (debugmode)  printf("\n");
   StringColorPrint("[Address Book] (ICS212)", "yellow");
   StringColorPrint(" *** Copyright (Oct. 2013) Ehsan Kourkchi", "yellow"); 
   printf("\033[K");
   printf("\n\n");
   if (debugmode) StringColorPrint(" *** DEBUG MODE ***\n\n", "green");
}


/*****************************************************************
//
//  Function name:		main_menu  
//
//  DESCRIPTION:		a function to produce the main menu of the program 
//				asking user to enter the proper menu option
//
//  Parameters:			No input
//				
//  Return values:		int: the menu number that entered by user
//
//****************************************************************/

int main_menu(int numberOfRecords)
{
 
 int check = 1;
 int menu;
 do {
  
   //header();
   


   printf(" *** Menu Options ***\n");

   printf("\n 1) Add a contact\n");
   printf(" 2) Modify a contact\n");   
   printf(" 3) Remove a contact\n"); 
   printf(" 4) Print a contact\n");
   printf(" 5) Print all contacts\n");
   printf(" 6) Exit\n\n");
   printf(" ***********************\n");
   printf("   No. of contacts: %d\n", numberOfRecords);
   printf(" ***********************\n");  
   
    if (check ==0 ) 
      StringColorPrint(" Enter your choice (1..6): ", "red");
    else
      printf(" Enter your choice (1..6): ");

   check = get_int(&menu,1,6);
  
   } while(!check);
   
return menu;  
}

/*****************************************************************
//
//  Function name:		arguments  
//
//  DESCRIPTION:		a function to handle the permitted arguments of the program 
//				in a command line run
//
//  Parameters:			int argc: the number of arguments
//				char *argv[]: the pointer to the array of strings which hold all arguments
//
//  Return values:		int: = 1 if user runs the program with the proper arguments
//				     = 0 if the user is not running the program properly
//
//****************************************************************/

int  arguments(int argc, char *argv[])
{
  int exit_program = 0;
   if (argc == 1) 
 {
   debugmode = 0;
 }
 else if (argc == 2) 
 {
	if (string_equality(argv[1] , "--help") || string_equality(argv[1] , "-h")) 
	{
	  printf("\n\n Usage: database [OPTION] ");
	  printf("\n If no option is used,\n the program will be run in the normal mode.");
	  printf("\n\n *** OPTIONS *** ");

	  printf("\n\n -d, debug");
	  printf("\n   In this mode, the name of all functions");
	  printf("\n   and the passed parameters will be displayed.");
	  
	  printf("\n\n -v, --version");
	  printf("\n   output version information and exit");
	  

	  printf("\n\n -h, --help");
	  printf("\n   display this help and exit\n");

          printf("\n\n   Copyright (C) 2013");
	  printf("\n     Ehsan Kourkchi");
	  printf("\n\n");

	  
	  exit_program = 1;
	} 
	else if (string_equality(argv[1] , "debug") || string_equality(argv[1] , "-d")) 
	{
	  debugmode = 1;
	}
	else if (string_equality(argv[1] , "-v") || string_equality(argv[1] , "--version"))
	{
	 printf("\n   database");
 	 printf("\n   version: (ICS212)");
	 printf("\n   Copyright (C) 2013");	  
	 printf("\n   by: Ehsan Kourkchi\n\n");  
	 exit_program = 1;
	}
	else
	{
	  printf("\n Bad opperands\n Try '--help' flag for more information.\n\n");
	  exit_program = 1;
	}
  
 }
 else {
   printf("\n Bad operands.\n Try '--help' flag for more information.\n\n");
   exit_program = 1;
 }

 return exit_program;
}

/*****************************************************************
//
//  Function name:		getfield  
//
//  DESCRIPTION:		a funstion that asks user to enter a string field
//				this string can potentially contain new_line character (i.e '\n')
//
//  Parameters:			char *input_string: a pointer to the string that would be entered by user
//				char string_name[]: the name of the field that would be display for user
//				int mode: = 0  if no new_line ('\n') required, = 1 if string may contain new_line ('\n')
//
//  Return values:		int: = 0 when using with the correct mode, = 1 in the case of bad implementation
//
//****************************************************************/

int getfield(char *input_string, char string_name[], int mode, int maxSize)
{
  
  // Get one line string
  switch (mode)
  {
    case 0: 
      get_name(input_string, string_name, maxSize);
      break;
  // Get a string which potentialy can be more than one lines
    case 1:
      get_address(input_string, string_name, maxSize);
      break;
    default: return 1;
  }

return 0;
  
}


/*****************************************************************
//
//  Function name:		getdata  
//
//  DESCRIPTION:		a function that provide a user interface that asks 
//				the user interactively to add data to the data base 
//				It provides some user friendly menu facilities 
//
//  Parameters:			struct record *start: a pointer to the database
//
//  Return values:		int: = 1 to go back to the main menu of the program, 
//				     = 0 to exit the program
//****************************************************************/

int getdata(struct record **start)
{
  
  char address[80];
  char name[25];
  char telephone[15];
  int  yearofbirth;
  
  
  int menu=2,check=1;
  do 
  {

  //header();
  printf("\n");
  getfield(name,"name", 0, 25);
  getfield(address, "address", 1, 80); 
  get_int_txt(&yearofbirth, 1900, 2050, " Please enter the year of birth (1900-2050): ");
  getfield(telephone,"telephone number", 0, 15);
  

	    do {
	    //header();
	    
	    printf("\n New Contact:");

	    StringColorPrint("\n Name: ", "blue");
	    StringColorPrint(name, "green");

	    StringColorPrint("\n Address: ", "blue");
	    StringColorPrint(address, "green");

	      
	    StringColorPrint("\n Year of Birth: ", "blue");
	    printf(GREEN);
	    printf("%d\n", yearofbirth);
	    printf(DEFCOLOR);
	  
	    StringColorPrint(" Telephone #: ", "blue");
	    StringColorPrint(telephone, "green"); 
	    printf("\n\n");
      
	    printf("\n *** Is this true ? ***\n");
	    printf("\n 1) Yes (add it)\n");
	    printf(" 2) No (try again)\n");
	    printf(" 3) Main Menu (ignore it)\n");
	    printf(" 4) Exit the program\n\n");
	    printf(" *******************\n");

   
	    //if (check == 0 ) 
	      //StringColorPrint(" Enter your choice (1..4): ", "red");
	      
	    if (check != 0 ) 
	    {
	      printf(" The input data is correct?\n");
	      printf(" Enter your choice (1..4): "); 
	    }
	    else
	    {
	      printf(" The input data is correct?\n");
              StringColorPrint(" Enter your choice (1..4): ", "red");
	    }
	    
	    check = get_int(&menu,1,4);
  
	    } while(!check);

    
  } while(menu==2);


  
  switch (menu)
  {
    case 1:
    {
      addRecord (start, name, address, yearofbirth, telephone);
      printf("*** Added successfully ***\n");
      return 100; // it means that the record was added
    }
    case 3: 
      return 1;
    case 4: 
      return 0;
  }

  
  
  
}

/*****************************************************************
//
//  Function name:		printdata  
//
//  DESCRIPTION:		a function that provide a user interface that asks 
//				the user interactively to enter a data key (e.g. in an address book) 
//				and then prints the corresponding the record 
//
//  Parameters:			struct record *start: a pointer to the database
//
//  Return values:		int: = 1 to go back to the main menu of the program, 
//				     = 0 to exit the program
//****************************************************************/

int printdata(struct record * start)
{
  

  char name[25];
  int menu=2,check=1;
  
  do {

  //header();
  getfield(name,"contact name", 0, 25);
  
  
  
	    do {
  
	    //header();
	         
	    //StringColorPrint("\nName: ", "blue");
	    //StringColorPrint(name, "green");
	    
            if (printRecord (start, name) == 1) 
               printf("\n No contact with the name \"%s\"", name);    
	    
	    printf("\n\n");
      
	    printf("\n ***** Options *****\n");
	    printf("\n 1) Search again\n");
	    printf(" 2) Main Menu\n");
	    printf(" 3) Exit the program\n\n");
	    printf(" *******************\n");

   
	    if (check == 0 ) 
	      StringColorPrint(" Enter your choice (1..3): ", "red");
	    else
	      printf(" Enter your choice (1..3): ");
	    check = get_int(&menu,1,3);
  
	    } while(!check);


} while(menu==1);
  

      switch (menu)
      {
	case 2: 
	  return 1;
	case 3: 
	  return 0;
      }
  
}


/*****************************************************************
//
//  Function name:		modifydata  
//
//  DESCRIPTION:		a function that provide a user interface that asks 
//				the user interactively to enter a data key (e.g. in an address book) 
//				and other fields to modify an existing record in the database 
//
//  Parameters:			struct record *start: a pointer to the database
//
//  Return values:		int: = 1 to go back to the main menu of the program, 
//				     = 0 to exit the program
//****************************************************************/

int modifydata(struct record *start)
{
  
  char address[80];
  char name[25];
  char telephone[15];
  int  yearofbirth;
  int  modifiedNumber = 0;
  int menu, check=1;


  do {

  //header();




  

	    do {
	      
	        StringColorPrint("\n Contact to be modified \n", "blue");
                getfield(name,"name", 0, 25);
	      
	        if (hasRecord(start,name))
		{
		  
		   StringColorPrint(" Enter the new address \n", "blue");
                   getfield(address, "address", 1, 80); 

                   StringColorPrint(" New year of birth \n", "blue");
                   get_int_txt(&yearofbirth, 1900, 2050, " Please enter the year of birth (1900-2050):");
 
                   StringColorPrint(" New telephone number \n", "blue"); 
                   getfield(telephone,"telephone number", 0, 15); 
		  
		   menu = 2;
		   
		   modifiedNumber = modifyRecord (start, name, address, yearofbirth, telephone);       
		}
		else
		{
		  menu = 1;
		  if(start == NULL)  StringColorPrint("\nThe database is empty", "red");
		  StringColorPrint("\n The entered contact name does not exist in database.\n", "red");
		}
	    //header();
	    
	    if (menu !=1) 
	    {
	    
	      printf(" [New information for this contact]\n");

	      StringColorPrint("\nName: ", "blue");
	      StringColorPrint(name, "green");
 
	      StringColorPrint("\nAddress: ", "blue");
	      StringColorPrint(address, "green");
  
	      StringColorPrint("\nYear of Birth: ", "blue");
	      printf(GREEN);
	      printf("%d\n", yearofbirth);
	      printf(DEFCOLOR);
	  
	      StringColorPrint("Telephone #: ", "blue");
	      StringColorPrint(telephone, "green"); 
	      printf("\n\n Are you sure you want to apply this change?\n");
	      

	      
	      printf("\n ***** Options *****\n");
	      printf("\n 1) Yes (modify it)\n");
	      printf(" 2) No (try again)\n");
	      printf(" 3) Main Menu (ignore it)\n");
	      printf(" 4) Exit the program\n\n");
	      printf(" *******************\n");

   
	      if (check == 0 ) 
	        StringColorPrint(" Enter your choice (1..4): ", "red");
	       else
	         {
	           printf(" The input data is correct?\n");
	           printf(" Enter your choice (1..4): ");
	         }

	    check = get_int(&menu,1,4);
	    }

	    
	    
	    else // (menu == 1)
	      {
                  
		  
		  
		  printf("\n ***** Options *****\n");
		  printf(" 2) Try again\n");
		  printf(" 3) Main Menu (ignore it)\n");
		  printf(" 4) Exit the program\n\n");
		  printf(" *******************\n");
		  
	            if (check == 0 ) 
	              StringColorPrint(" Enter your choice (2..4): ", "red");
	            else
	              printf(" Enter your choice (2..4): ");
  
                  check = get_int(&menu,2,4);
	    
		  if (check == 0) 
	             menu = 1;
	      }
	      

	     } while(!check);

    if (menu == 2) StringColorPrint("\n No contact was modified\n", "red");
  } while(menu == 2);


    switch (menu)
    {
      case 1:
      {
	printf("\n The number of modified records: %d\n", modifiedNumber);
	return 1;
      }      
      case 3: 
      {
	printf("\n The number of modified records: %d\n", modifiedNumber);
	return 1;
      }
      case 4: 
	return 0;
    }

 
}


/*****************************************************************
//  Function name:		removedata  
//
//  DESCRIPTION:		a function that provide a user interface that asks 
//				the user interactively to enter a data key (e.g. in an address book) 
//				to remove an existing record of the database 
//
//  Parameters:			struct record **start: a pointer to the database head pointer
//
//  Return values:		int: = 1 to go back to the main menu of the program, 
//				     = 0 to exit the program
//****************************************************************/

int removedata(struct record **start)
{
  
  char name[25];
  int menu=2,check=1;
  int numberOfDeleted = 0;
  int allRemoved =0;
  int boolean = 1;
  
  do {

     //header();
     printf("\n [Removing a Contact]\n\n");
     //StringColorPrint("\n\n The contact to be removed \n", "blue");
     getfield(name,"contact name", 0, 25);
     boolean = 1;
     
	    do {
   
	    //header();
	    //StringColorPrint("\nName: ", "blue");
	    //StringColorPrint(name, "green");
	    
	    if (boolean == 1)
	    {
	      
			if ( (numberOfDeleted = deleteRecord (start, name)) <= 0) 
			{
			      printf("\n The contact name \"%s\" does not exist in the database.", name); 
			    if (numberOfDeleted == -1) {
			      StringColorPrint("\n The database is empty.\n", "red");
			      menu = 2;  // go to main menu
			      numberOfDeleted = 0; // no contact removed
			      break;  // exit the inner do-while
			    }
			}
			else 
			{
			  allRemoved += numberOfDeleted;
			  printf("\n No. of removed contacts: %d", numberOfDeleted);
			  if (*start == NULL) 
			  {
			    StringColorPrint("\n The database is empty now.\n\n", "red");
			    menu = 2;  // go to main menu
			    break;  // exit the inner do-while
			  }
			  
			  printf("\n");
			  printf("\n ***** Options *****\n");	
			  printf("\n 1) Remove another contact\n");
			  
			}
	    }
	    
	    
	    if (numberOfDeleted == 0) 
	    {
	         
	       printf("\n");
	       printf("\n ***** Options *****\n");	    
	       printf("\n 1) Try again\n");
	       
	    }
	    
	    numberOfDeleted = 0;
	    boolean = 0;
	    
	    printf(" 2) Main Menu\n");
	    printf(" 3) Exit the program\n\n");
	    printf(" *******************\n");

   
	    if (check == 0 ) 
	      StringColorPrint(" Enter your choice (1..3): ", "red");
	    else
	      printf(" Enter your choice (1..3): ");

	    check = get_int(&menu, 1, 3);
  
	    } while(!check);

    
     } while(menu==1);
  

switch (menu)
{
  case 2: 
    return allRemoved;
  case 3: 
    return -1;
}
  
  
}


/*****************************************************************
//
//  Function name:		string_equality  
//
//  DESCRIPTION:		a function to appends the second string argument 
				to the first string
//
//  Parameters:			char a []: The first string that is to compared with the second one
//				char b []: The secound string which is compared with the first one
//
//  Return values:		int: = 0 if two strings are not exactly the same, = 1 if both are exactly the same
//
//****************************************************************/


int string_equality(char a [], char b [])
{

int i=0, j=0, bool = 1;
 
 
while ( *(a+i) != '\0'  )  
  i++;
while ( *(b+j) != '\0'  )  
  j++;


 if (i != j) bool = 0;
 else 
 {
   i = 0;

      while(*(a+i) == *(b+i) )  
	i++;
      
      if (i-1 == j) 
	bool = 1; 
      else 
	bool = 0; 
 }

 
return bool;
}


/*****************************************************************
//
//  Function name:		StringColorPrint  
//
//  DESCRIPTION:		a colorful version of the printf
//				This function uses "printf" 
//				** This is not still completed, under development
//
//  Parameters:			char *string: The pointer to the string that would be displayed
//				char color[]: the color code of the displayed string
//
//  Return values:		No output.
//
//****************************************************************/

void StringColorPrint(char *string, char color[])
{ 
  
  
 if(color == "red") 
 {
   printf(RED);
   printf("%s", string); 
   printf(DEFCOLOR);
 }
  
  
 if(color == "green") 
 {
   printf(GREEN);
   printf("%s", string); 
   printf(DEFCOLOR);
 }
   
   
  if(color == "blue") 
 {
   printf(BLUE);
   printf("%s", string); 
   printf(DEFCOLOR);
 }

 
  if(color == "cyan") 
 {
   printf(CYAN);
   printf("%s", string); 
   printf(DEFCOLOR);
   printf("\033[K");
 } 
 
   if(color == "yellow") 
 {
   printf(YELLOW);
   printf("%s", string); 
   printf(DEFCOLOR);
 } 
  
  if(color == "def") 
 {
   printf("%s", string); 
 } 
 
 
}

//****************************************************************/
