# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "record.h"
# include "databaseio.h"
#include "database_functions.h"

extern int debugmode;

/*****************************************************************
//
//  Function name:		writefile  
//
//  DESCRIPTION:		a function to write a database with 3 fields into a file 
//				If the file is previously available, it would be overwritten
//
//  Parameters:			struct account accarray[]: the database in a form of array of structure. The array name would be pass here
//				int numcust: The number of bank customers which must be equal or less than the number of array elements
//				char filename[]: The name of the file which will be created.
//
//  Return values:		int: = 0 if the file is successfully created. = 1 in the case of error or empty database
//
//****************************************************************/

int writefile(struct record *start, char filename[ ])
{
  
  FILE *outputfile;
  int index;
  struct record *current;
  int i=0;
  
  
  if (debugmode ==1)
  {
     fprintf(outputfile, "\n*** These are all contacts ***\n");
     fprintf(outputfile, "Fuction: printAllRecords\n");
  }   
      
  outputfile = fopen(filename, "w");
  
  if (outputfile == NULL)
  {
     return 1;
  }
      
  current = start;
  
  if (current == NULL)
    fprintf(outputfile, "There is no record in this database.\n");
  else
  {
    fprintf(outputfile, "****************************\n");
    fprintf(outputfile, "The list of all contacts", i);
    fprintf(outputfile, "\n****************************\n\n");
      
  while (current != NULL)
    {
        
	fprintf(outputfile, "Contact No.: %d", ++i);
        
	
        fprintf(outputfile, "\nName: ");
        fprintf(outputfile, "%s", current->name);
	
        fprintf(outputfile, "\nAddress: ");
        fprintf(outputfile, "%s\n", current->address);
	
        fprintf(outputfile, "YearofBirth: ");
        fprintf(outputfile, "%d\n", current->yearofbirth);
	
	
        fprintf(outputfile, "Telephone: ");
        fprintf(outputfile, "%s\n", current->telno); 
        
        fprintf(outputfile, "\n****************************\n");
        current = current->next;
    }
  }
    
  fprintf(outputfile, "Number of contacts: %d", i);
  fprintf(outputfile, "\n****************************\n\n");    
  
  fclose(outputfile);
  return 0;
}

/*****************************************************************
//
//  Function name:		readfile  
//
//  DESCRIPTION:		a function to read from a file of data and import it into a database with 3 fields
//				
//  Parameters:			struct account accarray[]: the database in a form of array of structure. The array name would be pass here
//				int *numcust: The pointer to the variable whic holds the 
//				number of bank customers which must be equal or less than the number of array elements
//				If the number of records in the input file is less than *numcust, then the number of imported records would be pass
//				char filename[]: The name of the file which will be imported.
//				
//				The input file format:
//				Each record have a keyword which ends with a ":" or without it.
//				The keywords are ad following: (they are NOT even case-sensitive)
//
//				Name:
//				AccountNo:
//				Balance:
//
//				Any other line of the file which does not follow this keyword formatting would be ignored.
//				The field value after any keyword can be attached to it or sperated by spaces (no matter how many space)
//				
//				This function can pretty much handle any wrong input format to import as much as possible into the databse.
//				So, it is well prepared for most of the strange circumstances. Please note that in this version each line of the input text cannot 
//				be bigger than 2000 charachter size, otherwise the program crashes.
//
//  Return values:		int: = 0 if the file is successfully created. = 1 in the case of error.
//
//
//****************************************************************/

int readfile(struct record **start, char filename[])
{
  
  FILE * inputfile;
  char readstring1[1000], readstring2[1000], test_char, address_st[1000];
  char Lowerreadstring1[1000];
  
  int i, i_address, j, k, check, numrecords, boolean, counter;
  
  char uname[25];
  char uaddress[80];
  int  uyearofbirth;
  char utelephone[15];
  
  
  
  inputfile = fopen(filename, "r");
  if (inputfile == NULL)
  {
     return 0;  //  No. of contacts = 0
  }
 
  numrecords = 0;
  
  // i, j, i_address, k are cecking variables. If a new record is created, they are all set to zero. 
  // If any of them becomes 2, then a new record would be generated.
  i = 0; 
  i_address=0;
  j = 0;  
  k = 0;
  
  
  
 /*********************************************/ 

  while(!readfield2string(inputfile,  readstring1,  readstring2, 1000)) 
  {
 
  //printf("Test1: %s   %s\n", readstring1, readstring2);
  
    stringlower(Lowerreadstring1, readstring1);
  
  
    // check for address field
  if (!strcmp(Lowerreadstring1, "address") || !strcmp(Lowerreadstring1, "address:")) 
  {
      
	  strcpy(address_st, readstring2);
	  
	  while(!readfield2string(inputfile,  readstring1,  readstring2, 1000))
	  {
		stringlower(Lowerreadstring1, readstring1);
		
		
		if (!strcmp(Lowerreadstring1, "\n") || !strcmp(Lowerreadstring1, "") || !strcmp(Lowerreadstring1, "name") || 
			!strcmp(Lowerreadstring1, "name:") || !strcmp(readstring1, "YearofBirth") || 
			  !strcmp(readstring1, "YearofBirth:") || !strcmp(Lowerreadstring1, "telephone") || 
			      !strcmp(Lowerreadstring1, "telephone:")) 
				  break;
		      
		strappend(address_st,"\n");
		strappend(address_st, readstring1);
		
		if (strcmp(readstring2, "")) strappend(address_st," ");
			strappend(address_st, readstring2);
		
	  if (strlen(address_st) > 80) break;
	  
	  } // end-while    
	    
	      
	    i_address++;
	    if (i_address == 2) 
	    {
	      
	      if (i == 0)
		strcpy(uname, " ");
	      
	      if (j == 0 ) 
		uyearofbirth = 0;
	      
	      if (k == 0 ) 
		strcpy(utelephone, " ");
	      
	      
	      addRecord (start, uname, uaddress, uyearofbirth, utelephone); 
	      numrecords++;
	      
	      i = 0;
	      i_address = 1;  
	      j = 0;  
	      k = 0;
	    }
	    
	    //printf("address: %s", address_st);
	    strncpy(uaddress, address_st, 80);  
	    //printf("address: %s", address_st);
  } // end of chcek for "address"
  
 
  
  // check if it is the "name" field
  if (!strcmp(Lowerreadstring1, "name") || !strcmp(Lowerreadstring1, "name:")) 
  {
	  i++;
	  if (i == 2) 
	  {
	    
	    if (i_address == 0)
	      strcpy(uaddress , " ");
	    
	    if (j == 0 ) 
	      uyearofbirth = 0;
	    
	    if (k == 0 ) 
	      strcpy(utelephone, " ");
	    
	    
	    addRecord (start, uname, uaddress, uyearofbirth, utelephone); 
	    numrecords++; 
	    
	    i = 1;  
	    i_address = 0;
	    j = 0;  
	    k = 0;
	  }
	      
	  strncpy( uname , readstring2, 25);
	  
  }

  // check if it is the "name" field
  else if (!strcmp(readstring1, "YearofBirth") || !strcmp(readstring1, "YearofBirth:")) 
  {
	  j++;
	  if (j == 2) 
	  {
	    
	    if (i == 0)
	      strcpy(uname, " ");
	    
	    if (i_address == 0)
	      strcpy(uaddress, " ");
	    
	    if (k == 0 ) 
	      strcpy(utelephone, " ");
	    
	    
	    addRecord (start, uname, uaddress, uyearofbirth, utelephone); 
	    numrecords++;
	    
	    i = 0;
	    i_address = 0;  
	    j = 1;  
	    k = 0;    
	  
	  } 
	  
	  //printf("birth: %s", readstring2);
	  uyearofbirth = atoi(readstring2);
	  //printf("birth: %d", uyearofbirth);
  }

  
  // check if it is the "name" field
  else if (!strcmp(Lowerreadstring1, "telephone") || !strcmp(Lowerreadstring1, "telephone:")) 
  {

	  k++;
	  
	  if (k == 2) 
	  {
	    
	    if (i == 0)
	      strcpy(uname, " ");
	    
	    if (i_address == 0)
	      strcpy(uaddress, " ");
	    
	    if (j == 0 ) 
	      uyearofbirth = 0;
	    
	    addRecord (start, uname, uaddress, uyearofbirth, utelephone); 
	    numrecords++;     
	  
	    i = 0;
	    i_address = 0;  
	    j = 0;  
	    k = 1;  
	    
	  } 
	  
	  //printf("tilif: %s", readstring2);
	  strncpy(utelephone , readstring2, 15);
	  //printf("tilif: %s", readstring2);
  } 
  
  else ;

  /*********************************************/ 
  } // end of the outer while statement
 /*********************************************/ 
 

       if (i == 0 ) 
	    strcpy(uname, " ");
        
       if (i_address == 0 ) 
        strcpy(uaddress, " ");
       
       if (j == 0 )  
	    uyearofbirth = 0;
        
       if (k == 0 ) 
	    strcpy(utelephone, " ");
       

       if (i == 1 || i_address == 1 || j == 1 || k == 1 )
       {
	 numrecords++;
	 addRecord (start, uname, uaddress, uyearofbirth, utelephone); 
       }

       
  fclose(inputfile);
  return numrecords;
  
}


/*****************************************************************
//
//  Function name:		readfield2string  
//
//  DESCRIPTION:		A function which reads a line from the input file. And it returns two strings. 
//				In the line is empty both string would be empty as well. 
//				The fitst and second strings can be either seprated by ":" or one space or even muliple spaces.
//				There might be several spaces in the second string. The first string plays the role of keyword in any text formating applications.
//				The secound string will be the corresponding value.
//
//  Parameters:			FILE *inputfile: The pointer pointing at the file to read from
//				char readstring1[]: The first returned string (keyword)
//				char readstring2[]: The secound returned string (corresponding value)
//				int max_length2): The maximum number of allowd characters for the secound string. 
//
//  Return values:		int: = 1 if no line can be red from the file after reaching to EOF. = 0 if one line of the file is read and returned.
//****************************************************************/
// return 1 > EOF ... nothing happens
// return 0 > some string is read ... successful

int readfield2string(FILE *inputfile, char readstring1[], char readstring2[], int max_length2)
{
  int i=0;
  char test_char;
  readstring1[0]='\0';
  readstring2[0]='\0';
  
  if (!feof(inputfile))
  {
   
    do 
    { 
      test_char = fgetc(inputfile);
    }   while ((test_char == ' ' || test_char == '\t' ) && test_char != '\n' && !feof(inputfile));
    
    i = 0;
    while (test_char != '\n' && test_char != ' ' && test_char != '\t' && !feof(inputfile) )
    {
      readstring1[i] = test_char;
      i++; 
      test_char = fgetc(inputfile);
      if (test_char == ':') break;
    } 
    readstring1[i]  = '\0';
    
    if (i > 0 && readstring1[i-1] == ' ') 
      readstring1[i-1]  = '\0';
    
    if (test_char == ':') 
      test_char = fgetc(inputfile);
    
    while (test_char != '\n' && (test_char == '\t' || test_char == ' ') && !feof(inputfile))
    {
      test_char = fgetc(inputfile);
    }
         
    i=0;
    
    while (test_char != '\n' && !feof(inputfile))
    {
      readstring2[i] = test_char;
      
      if ((test_char != '\t' && test_char != ' ') || readstring2[i-1]!=' ')
      {
        i++;
      }
        
      test_char = fgetc(inputfile);
    } 
    
    readstring2[i]  = '\0';
    
    if (i > 0 && readstring2[i-1] == ' ') 
      readstring2[i-1]  = '\0';
    
    if (i>max_length2) 
    { readstring2[max_length2]  = '\0';
      if (readstring2[max_length2-1] == ' ' ) readstring2[max_length2-1]  = '\0';
    }

    
    while (test_char != '\n' && !feof(inputfile))
      test_char = fgetc(inputfile); 
    
    //printf("\'%s\'.\'%s\'\n", readstring1, readstring2);
    return 0;
  }
 
 
return 1;
}


/*****************************************************************
//
//  Function name:		strappend  
//
//  DESCRIPTION:		a function to appends the second string argument 
				to the first string
//
//  Parameters:			char[] string1: The first string that the secound is to be attached to
//				char[] string2: The secound string which is to be attached to the forst one
//
//  Return values:		No output.
//
//****************************************************************/

void strappend(char string1[ ], char string2[ ]) 
{
  int index1 = 0, index2 = 0;
  
  while (string1[index1] != '\0') 
  {
    index1++;
  }

  while (string2[index2] != '\0') 
  {
    string1[index1] = string2[index2];
    index1++;
    index2++;
  }
  
  string1[index1] = '\0';

}


/*****************************************************************
//
//  Function name:		stringlower  
//
//  DESCRIPTION:		This function returns the input string in lowercase format.
//
//  Parameters:			char *lowerstring: the output lowercase string
//				char *string: the pointer assigned to the input string
//  Return values:		void (no output)
//
//****************************************************************/

void stringlower(char *lowerstring, char *string) 

{
  int index = 0;
  
  while (string[index] != '\0') 
  {

   lowerstring[index] = tolower(string[index]);
    
    index++;
  
  }
  lowerstring[index] = '\0';
  
}

//****************************************************************/

