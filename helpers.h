#ifndef _HELPERS
#define _HELPERS
    #include "person.h"
    #include "linkedList.h"
    #include "hashTable.h"
    #include "bloom-filter.h"
    #include "helpers.h"
    #include <ctime>
    #include <fstream>
    #include <iostream>  
    #include <string>
    #include <sstream>
    #include <cstring>

    using namespace std;

    int inputCheck(hashTable**, hashTable**, hashTable**, int, person**);
    string* readInput(int* );
    date* dateConverter(string);
    int checkDateInput(string date);
    string firstCap(string str);
    string toUpper(string str);
    
#endif