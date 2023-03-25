#ifndef PERSON
#define PERSON
#include <iostream>
#include <string>
using namespace std;



class person{
    protected:
    string name;
    int id;
    int age;

    public:
    person();
    void set_name(string);
    void set_id(int );
   void set_age(int );
    string get_name();
    int get_id();
    int get_age();
    virtual void print()=0;
};

struct appointment{
int hours;
int mins;
};

#endif