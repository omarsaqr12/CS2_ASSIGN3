#include "mechanic.h"
#include <cassert>
#include <stdexcept>

int main() {
    mechanic worker;
    assert(worker.getcounter() == 0);
    assert(!worker.isavailable({23, 30}));
    assert(!worker.isavailable({8, 60}));
    assert(worker.isavailable({8, 0}));
    bool threw = false;
    try { (void)worker.getappointment(); } catch (const std::out_of_range&) { threw = true; }
    assert(threw);
    worker.setappointments({8, 0});
    assert(!worker.isavailable({8, 59}));
    assert(worker.isavailable({9, 0}));
    threw = false;
    try { worker.setappointments({8, 30}); } catch (const std::invalid_argument&) { threw = true; }
    assert(threw);
    worker.setappointments({9, 0});
    worker.setappointments({10, 0});
    worker.setappointments({11, 0});
    assert(worker.getcounter() == 4);
    assert(worker.getappointment().hours == 11);
    assert(!worker.isavailable({12, 0}));
    threw = false;
    try { worker.setappointments({12, 0}); } catch (const std::invalid_argument&) { threw = true; }
    assert(threw);
    threw = false;
    try { worker.setcounter(5); } catch (const std::out_of_range&) { threw = true; }
    assert(threw);
}
