# /*****************************************************************
# //
# //  NAME:		Ehsan Kourkchi
# //
# //  HOMEWORK:		3
# //
# //  CLASS:		ICS 212
# //
# //  INSTRUCTOR:	Ravi Narayan
# //
# //  DATE:		September 21, 2013           
# //
# //  FILE:		Makefile        
# //
# //  DESCRIPTION:	Makefile for "database.c"
# //
# //****************************************************************/


all: database.o database_functions.o databaseio.o  record.h databaseio.h database_functions.h
	cc -o database  database.o database_functions.o databaseio.o

database.o: database.c record.h databaseio.h database_functions.h
	cc -c database.c

database_functions.o: database_functions.c record.h database_functions.h
	cc -c database_functions.c

databaseio.o:  databaseio.c databaseio.h record.h database_functions.h
	cc -c databaseio.c


.PHONY: clean

clean:
	rm -f *.o