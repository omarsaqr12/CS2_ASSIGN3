#include "mechanic.h"
#include <cstdlib>
#include <stdexcept>

namespace {
int minutes(appointment time) { return time.hours * 60 + time.mins; }
bool valid(appointment time) {
    return time.hours >= 0 && time.hours < 24 && time.mins >= 0 &&
           time.mins < 60 && minutes(time) + 60 <= 24 * 60;
}
}

mechanic::mechanic() = default;
bool mechanic::isavailable(appointment ap) {
    if (!valid(ap) || counter >= maxAppointments) return false;
    for (int i = 0; i < counter; ++i) {
        if (std::abs(minutes(ap) - minutes(apps[i])) < 60) return false;
    }
    return true;
}
void mechanic::setcounter(int x) {
    if (x < 0 || x > maxAppointments) throw std::out_of_range("appointment count outside capacity");
    counter = x;
}
void mechanic::setappointments(appointment ap) {
    if (!isavailable(ap)) throw std::invalid_argument("invalid, overlapping or over-capacity appointment");
    apps[counter++] = ap;
}
int mechanic::getcounter() { return counter; }
appointment mechanic::getappointment() {
    if (counter == 0) throw std::out_of_range("no appointments");
    return apps[counter - 1];
}
void mechanic::print() {
    std::cout << "Name: " << name << '\n' << "Mechanic ID: " << id << '\n' << "Age: " << age << '\n';
}
