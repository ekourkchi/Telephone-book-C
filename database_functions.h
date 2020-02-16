 // Database handling
 int addRecord (struct record **,char [ ],char [ ],int, char [ ]);
 int printRecord (struct record *, char [ ]);    
 int modifyRecord (struct record *, char [ ], char [ ], int, char [ ]);       
 void printAllRecords(struct record *);
 int deleteRecord(struct record **, char [ ]);
 
 int hasRecord(struct record *, char [ ]);