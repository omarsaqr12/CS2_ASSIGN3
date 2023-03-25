
#include "mechanic.h"


mechanic:: mechanic(){
  counter = 0;
}

bool mechanic::isavailable(appointment ap){ //incomplete
  if (counter <10)
    return true;
  else return false;
}


void mechanic::setcounter(int x){
  counter = x;}

void mechanic::setappointments(appointment app){
  apps[++counter].hours = app.hours+1;
  apps[counter].mins =app.mins;

}

int mechanic::getcounter(){
  return counter;}

appointment mechanic::getappointment(){
  return apps[counter];
}
void mechanic::print(){
  cout << "Name: "<< name <<endl;
  cout << "Mechanic ID: "<< id << endl;
  cout << "Age: "<< age << endl;}



