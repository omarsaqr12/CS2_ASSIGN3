#ifndef MECHANIC
#define MECHANIC
#include "person.h"
class mechanic : public person {
private:
    static constexpr int maxAppointments = 4;
    int counter = 0;
    appointment apps[maxAppointments]{};
public:
    mechanic();
    bool isavailable(appointment ap);
    void setcounter(int x);
    void setappointments(appointment ap);
    int getcounter();
    appointment getappointment();
    void print();
};
#endif
