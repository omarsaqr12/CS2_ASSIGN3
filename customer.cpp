#include <iostream>
#include <string>
#include "customer.h"
void customer::setMechanicID(int x){ MechanicID=x; }
void customer::setappointment(appointment app){ Appointment.hours=app.hours; Appointment.mins=app.mins; }
int customer::getMechanicID() const { return MechanicID; }
appointment customer::getappointment() const { return Appointment; }
bool customer::operator<(const appointment &x){ return Appointment.hours < x.hours || (Appointment.hours == x.hours && Appointment.mins < x.mins); }
bool customer::operator>(const appointment &x){ return Appointment.hours > x.hours || (Appointment.hours == x.hours && Appointment.mins > x.mins); }
bool customer::operator==(const appointment &x){ return Appointment.hours == x.hours && Appointment.mins == x.mins; }
void customer::print(){ cout << "Name of Customer: " << name << endl; cout << "Age: " << age << endl; }
