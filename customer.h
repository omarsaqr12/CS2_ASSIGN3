#ifndef CUSTOMER
#define CUSTOMER
#include "person.h"
class customer : public person {
private:
    int MechanicID = -1;
    appointment Appointment{0, 0};
public:
    void setMechanicID(int);
    void setappointment(appointment);
    int getMechanicID() const;
    appointment getappointment() const;
    bool operator<(const appointment &);
    bool operator>(const appointment &);
    bool operator==(const appointment &);
    void print();
};
#endif
