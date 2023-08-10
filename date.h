#ifndef DATE_H
#define DATE_H
#include <iostream>
class date{
    private: 
        int day;
        int month;
        int year;
    public:
    
        date(int day, int month, int year);
        date(const date *obj);
        int compare(date*& date1, date*& date2);
        void printDate();
        int checkDate();
        int empty();
        bool operator <=(const date& obj);
        bool operator >=(const date& obj);
};
#endif
