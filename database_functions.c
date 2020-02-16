# include  <stdio.h>
# include  <stdlib.h>
# include "record.h"
# include "database_functions.h"
# include "databaseio.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m" 
#define BLUE "\033[1;34m" 
// background: blue foeground: cyan
#define CYAN "\033[44;1;36m"
// "\033[K" clears the end of Line
#define DEFCOLOR "\033[0m\033[K"
#define YELLOW "\033[44;1;33m"


extern int debugmode;
    


/*****************************************************************
//
//  Function name:		addRecord  
//
//  DESCRIPTION:		a funstion that add new record to the existing database
//
//  Parameters:			struct record **start: a pointer to the database record
//				char name[ ]: name 
//				char address[ ]: address 
//				int yearofbirth: Year of Birth
//				char telephone[ ]: Telephone #
//
//  Return values:		int: = 0 if it is successful, = 1 if it is not successful
//
//****************************************************************/

int addRecord (struct record **start,char uname[ ],char uaddr[ ],int uyob, char utelno[ ]) 
  {

  struct record *current;
  int i;
  
  current = *start;
  
  if (current != NULL) 
  {
  
    while (current->next != NULL)
    {
      current = current->next;
    }
  
  current->next = (struct record *)malloc(sizeof(struct record));
  current = current->next;
    
  }
  else
  {
   
    *start = (struct record *)malloc(sizeof(struct record));
    current = *start;
    
  }
   
  current->next = NULL;
  for (i=0; i<25; i++)  current->name[i] = uname[i];
  for (i=0; i<80; i++)  current->address[i] = uaddr[i];
  current->yearofbirth = uyob;
  for (i=0; i<15; i++)  current->telno[i] = utelno[i];
      
    if (debugmode ==1)
    {
      printf("\n\n*** DEBUG ***\n");
      printf("Fuction: addRecord\n");
      printf("Name: %-10s\n", current->name);
      printf("Address: %-10s\n", current->address);
      printf("Year of Birth: %-10d\n", current->yearofbirth);
      printf("Telephone No.: %-10s\n", current->telno);
      printf("************\n");

    }
    
    
  return 1;
 }
    
   
/*****************************************************************
//
//  Function name:		printRecord  
//
//  DESCRIPTION:		a funstion that prints a record based on the 'key' 
//
//  Parameters:			struct record *start: a pointer to the database
//				char name[ ]: name ... which is the 'key' here
//
//  Return values:		int: = 0 if the contact name is found, = 1 if there is no such contact
//
//****************************************************************/
   
   
    int printRecord (struct record *start, char name[ ])
    {
    
      
    struct record *current;
    int i = 0, isAvailable = 0;
    char lower_current_name [25];
    char lower_name [25];
    
    current = start;
      
    if (debugmode ==1)
    {
      printf("\n\n *** DEBUG ***\n");
      printf(" Fuction: printRecord\n");
      printf(" Name: %-10s\n", name);
      printf(" ************\n");

    }   


    if (current == NULL)
    {
      printf("\n The database is empty.");
      return 1;
    }
    else
    {

      
      while (current != NULL)
      {
        i++;
	stringlower(lower_current_name,current->name);
	stringlower(lower_name,name);
	
        if (!strcmp(lower_current_name, lower_name))
	{
	  
	  isAvailable ++;
	  
	  if (isAvailable == 1)
	  {
	        printf("\n****************************\n");
                printf("The list of all contacts for \"%s\"", name);
                printf("\n****************************\n");
	  }
	  
	
	printf("Contact No.: %d", i);
        
	
        printf("\nName: ");
	printf(GREEN);
        printf("%-10s", current->name);
	printf(DEFCOLOR);
	
        printf("\nAddress: ");
	printf(GREEN);
        printf("%-10s\n", current->address);
        printf(DEFCOLOR);
	
        printf("Year of Birth: ");
        printf(GREEN);
        printf("%-10d\n", current->yearofbirth);
        printf(DEFCOLOR);
	
	
        printf("Telephone No.: ");
	printf(GREEN);
        printf("%-10s\n", current->telno); 
        //printf("\n\n");
	printf(DEFCOLOR);
	
        
        printf("\n****************************\n");
	}
	
        current = current->next;
      }
    }
    
    if (isAvailable) return 0;
    
    return 1;  
    }
    
/*****************************************************************
//
//  Function name:		modifyRecord  
//
//  DESCRIPTION:		a funstion that modify record based on the input 'key'
//
//  Parameters:			struct record **start: a pointer to the database record
//				char name[ ]: name  ... which is the 'key' here
//				..the filloin parameters would be modified
//				char address[ ]: address 
//				int yearofbirth: Year of Birth
//				char telephone[ ]: Telephone #
//
//  Return values:		int: = 0 if no record is modified, otherwise it would be the number of modified records
//
//****************************************************************/


  int modifyRecord (struct record *start, char name[ ],char address[ ],int yearofbirth, char telephone[ ])
  {
    
    struct record *current;
    int i = 0, isAvailable = 0;
    char lower_current_name [25];
    char lower_name [25];
    
    current = start;
      
    if (debugmode ==1)
    {
      
      printf(" Fuction: modifyRecord\n");
      printf(" Name: %-10s\n", name);
      printf(" Address: %-10s\n", address);
      printf(" Year of Birth: %-10d\n", yearofbirth);
      printf(" Telephone #: %-10s\n", telephone);
      printf(" ************\n");

    }
    
    
    if (current == NULL)
    {
      return 0;
    }
    else
    {

      
      while (current != NULL)
      {
	
	stringlower(lower_current_name,current->name);
	stringlower(lower_name,name);
	
        if (!strcmp(lower_current_name, lower_name))
	{
	  
	  isAvailable ++;
	  
          for (i=0; i<25; i++)  current->name[i] = name[i];

          for (i=0; i<80; i++)  current->address[i] = address[i];

          current->yearofbirth = yearofbirth;
  
          for (i=0; i<15; i++)  current->telno[i] = telephone[i];
        
	}
	
        current = current->next;
	
      }
    }
    
    return isAvailable;    
    } 

 /*****************************************************************
//
//  Function name:		printAllRecords  
//
//  DESCRIPTION:		a funstion that prints all records of the database 
//
//  Parameters:			struct record *start: a pointer to the database
//
//  Return values:		void ... no outout
//
//****************************************************************/

 void printAllRecords(struct record *start)
  {
      
      struct record *current;
      int i=0;
      
      current = start;
     
      
	if (debugmode ==1)
      {
	printf("\n\n *** DEBUG ***");
	printf("\n *** These are all contacts ***\n");
	printf(" Fuction: printAllRecords\n");
	
	printf("\n ****************************\n");
      }   
      
    if (current == NULL)
    {
      printf(RED);
      printf("\n There is no record in this database.\n");
      printf(DEFCOLOR);
    }
    else
    {
      printf("\n****************************\n");
      printf("The list of all contacts", i);
      printf("\n****************************\n");
      
      while (current != NULL)
      {

        
	printf("Contact No.: %d", ++i);
        
	
        printf("\nName: ");
	printf(GREEN);
        printf("%-10s", current->name);
	printf(DEFCOLOR);
	
        printf("\nAddress: ");
	printf(GREEN);
        printf("%-10s\n", current->address);
        printf(DEFCOLOR);
	
        printf("Year of Birth: ");
        printf(GREEN);
        printf("%-10d\n", current->yearofbirth);
        printf(DEFCOLOR);
	
	
        printf("Telephone No.: ");
	printf(GREEN);
        printf("%-10s\n", current->telno); 
	printf(DEFCOLOR);
	
        
        printf("\n ****************************\n");
        current = current->next;
      }
    }
    
      printf(" Number of contacts: %d", i);
      printf("\n ****************************\n\n");    
  }
    
/*****************************************************************
//
//  Function name:		deleteRecord  
//
//  DESCRIPTION:		a funstion that delete a record based on the 'key' 
//
//  Parameters:			struct record *start: a pointer to the database
//				char name[ ]: name ... which is the 'key' here
//
//  Return values:		int: = -1 if the database is empty, otherwise it would 
//				be the number of removed records
//
//****************************************************************/  
    
int deleteRecord(struct record **start, char name[ ])
  {
      
     struct record *current;
     struct record *temp;
     int i = 0, isAvailable = 0;
     char lower_current_name [25];
     char lower_name [25];
     
    
     current = *start;
  
	if (debugmode ==1)
	{
	    printf("\n\n *** DEBUG ***\n");
	    printf(" Fuction: deleteRecord\n");
	    printf(" Name: %-10s\n", name);
	    printf(" ************\n");

	}  
     
     
     if (current == NULL)
     {
      
       return -1;
     }
     else
     {   

		  
		  while(current != NULL) 
		  {
		    
		    stringlower(lower_current_name, current->name);
		    stringlower(lower_name, name);
		    
		    if (strcmp(lower_current_name, lower_name) == 0) 
		    {
		    
		      if (current == *start)
		      { 
			
			*start = (*start)->next;
			isAvailable++;
			free(current);
			current = *start;
			
		      }
		      else
		      {

			temp->next = current->next;
			isAvailable++;
			free(current);
			current = temp->next;

		      }
		    
		  }
		  else
		  {
		    temp = current;
		    current = current->next;
		  }
		  
		}
     }

 return isAvailable;
}
    
    
/*****************************************************************
//
//  Function name:		hasRecord  
//
//  DESCRIPTION:		a funstion that checks if there is any record associate with the 'key'
//
//  Parameters:			struct record *start: a pointer to the database
//				char name[ ]: name ... which is the 'key' here
//
//  Return values:		int: = 0 if the record not found, = 1 if at least one record matches
//
//****************************************************************/  

  int hasRecord(struct record *start, char name[ ])
  {
    
      
    struct record *current;
    int i = 0, isAvailable = 0;
    char lower_current_name [25];
    char lower_name [25];
    
    current = start;
  


    if (current == NULL)
    {
      
      return 0;
    }
    else
    {

      
      while (current != NULL)
      {
        
	stringlower(lower_current_name,current->name);
	stringlower(lower_name,name);
	
        if (!strcmp(lower_current_name, lower_name))
	  return 1;
        
	current = current->next;
      }

    }
    return 0;
 } 
 