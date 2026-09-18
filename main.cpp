#include "customer.h"
#include "mechanic.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace {
constexpr int serviceMinutes = 60;

bool readMechanics(const std::string& path, std::vector<mechanic>& out) {
    std::ifstream input(path);
    if (!input) { std::cerr << "Cannot open " << path << '\n'; return false; }
    std::set<int> ids;
    std::string line;
    int lineNumber = 0;
    while (std::getline(input, line)) {
        ++lineNumber;
        if (line.find_first_not_of(" \t\r") == std::string::npos) continue;
        std::istringstream row(line);
        std::string name, extra;
        int age, id;
        if (!(row >> name >> age >> id) || (row >> extra) || age <= 0 || id < 0 || !ids.insert(id).second) {
            std::cerr << "Invalid mechanic record at " << path << ':' << lineNumber << '\n';
            return false;
        }
        mechanic person;
        person.set_name(name);
        person.set_age(age);
        person.set_id(id);
        out.push_back(person);
    }
    if (out.empty()) { std::cerr << "No mechanics in " << path << '\n'; return false; }
    return true;
}

bool readCustomers(const std::string& path, std::vector<customer>& out) {
    std::ifstream input(path);
    if (!input) { std::cerr << "Cannot open " << path << '\n'; return false; }
    std::string line;
    int lineNumber = 0;
    while (std::getline(input, line)) {
        ++lineNumber;
        if (line.find_first_not_of(" \t\r") == std::string::npos) continue;
        std::istringstream row(line);
        std::string name, extra;
        int age, hours, mins;
        if (!(row >> name >> age >> hours >> mins) || (row >> extra) || age <= 0 ||
            hours < 0 || hours > 23 || mins < 0 || mins > 59 ||
            hours * 60 + mins + serviceMinutes > 24 * 60) {
            std::cerr << "Invalid customer record at " << path << ':' << lineNumber << '\n';
            return false;
        }
        customer person;
        person.set_name(name);
        person.set_age(age);
        person.setappointment({hours, mins});
        out.push_back(person);
    }
    return true;
}

int toMinutes(appointment ap) { return ap.hours * 60 + ap.mins; }
void printTime(appointment ap) {
    std::cout << std::setfill('0') << std::setw(2) << ap.hours << ':'
              << std::setw(2) << ap.mins << std::setfill(' ');
}
}  // namespace

int main(int argc, char* argv[]) {
    if (argc != 1 && argc != 3) {
        std::cerr << "Usage: scheduler [Mechanics.txt Customers.txt]\n";
        return 2;
    }
    const std::string mechanicsPath = argc == 3 ? argv[1] : "Mechanics.txt";
    const std::string customersPath = argc == 3 ? argv[2] : "Customers.txt";
    std::vector<mechanic> mechanics;
    std::vector<customer> customers;
    if (!readMechanics(mechanicsPath, mechanics) || !readCustomers(customersPath, customers)) return 1;

    // Earliest requested time first; ties retain input order. A mechanic can
    // serve up to four non-overlapping, one-hour appointments in one day.
    std::stable_sort(customers.begin(), customers.end(), [](const customer& a, const customer& b) {
        return toMinutes(a.getappointment()) < toMinutes(b.getappointment());
    });
    for (customer& person : customers) {
        const appointment requested = person.getappointment();
        for (mechanic& worker : mechanics) {
            if (worker.isavailable(requested)) {
                worker.setappointments(requested);
                person.setMechanicID(worker.get_id());
                break;
            }
        }
        std::cout << person.get_name() << " | ";
        printTime(requested);
        if (person.getMechanicID() < 0) std::cout << " | UNASSIGNED\n";
        else std::cout << " | mechanic " << person.getMechanicID() << '\n';
    }
    return 0;
}
