#include <iostream>
#include <string>
#include "customer.h"


void customer::setMechanicID(int x){
  MechanicID = x;}

void customer::setappointment(appointment app){
  Appointment.hours = app.hours;
  Appointment.mins = app.mins;
  ;}

int customer::getMechanicID(){
  return MechanicID;}

appointment customer::getappointment(){
  return Appointment;}

bool customer::operator<  (const appointment &x ){
  if(Appointment.hours == x.hours && Appointment.mins < x.mins || Appointment.hours < x.hours){
    return true;
  }

  else
    return false;
  }


bool customer::operator>  (const appointment &x ){
  if(Appointment.hours == x.hours && Appointment.mins > x.mins || Appointment.hours > x.hours){
    return true;
  }

  else
    return false;
  }
bool customer::operator== (const appointment &x){
  if(Appointment.hours == x.hours && Appointment.mins == x.mins){
    return true;
  }

  else
    return false;
}
void customer::print(){
  cout << "Name of Custoemr: "<< name <<endl;
  cout << "Age: "<<age << endl;}
