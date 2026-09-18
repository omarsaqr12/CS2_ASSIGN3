# Mechanic Appointment Scheduler (CS2 assignment)

A small, file-driven C++17 course project that assigns customers requesting one-hour appointments to available mechanics. It demonstrates basic inheritance (`person` → `customer` / `mechanic`), bounded appointment storage, sorting and input validation. It is a local command-line exercise, **not** a booking service or production scheduling system.

## What it does

The program reads `Mechanics.txt` and `Customers.txt`, orders requests by requested start time (retaining file order for ties), then assigns each request to the **first mechanic in file order** with room for it. Each mechanic can take at most four appointments. Appointments last 60 minutes, cannot overlap for the same mechanic, and must finish by midnight. If nobody is available at the *requested* time, the request is printed `UNASSIGNED`; the program does **not** offer another time. All data and assignments are in memory, with no persistent updates.

These are explicit behavior choices for this repaired demonstration; no original assignment specification is included in this repository. The original `main.cpp` did not implement scheduling.

## Build and run

Requires a C++17 compiler such as g++; no third-party libraries or network access.

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror main.cpp customer.cpp mechanic.cpp person.cpp -o scheduler
./scheduler
```

Run from the repository root so the default relative input paths resolve. To supply your own text files:

```bash
./scheduler /path/to/Mechanics.txt /path/to/Customers.txt
```

Each nonblank line is whitespace-separated (names must be one token):

| File | Fields | Example |
| --- | --- | --- |
| `Mechanics.txt` | name, positive age, unique nonnegative integer ID | `Abed 24 2343` |
| `Customers.txt` | name, positive age, requested hour, requested minute | `ds 22 1 23` |

Hours use 24-hour local clock (`0`–`23`) and minutes `0`–`59`. A 60-minute appointment starting after `23:00` is invalid. Blank lines are skipped. Malformed records, duplicate mechanic IDs and missing files produce an error and a nonzero exit status **before any schedule is printed**. A valid but unschedulable request is shown as `UNASSIGNED` without failing the entire run. Sample data consists of 4 mechanics and 15 customers.

Example first output row with the committed sample data:

```text
ds | 01:23 | mechanic 2343
```

## Source and tests

- [`main.cpp`](main.cpp): file parsing, validation, stable time ordering, deterministic first-available assignment and output.
- [`mechanic.h`](mechanic.h), [`mechanic.cpp`](mechanic.cpp): four-appointment capacity and one-hour overlap checks.
- [`customer.h`](customer.h), [`customer.cpp`](customer.cpp): customer record and requested appointment.
- [`person.h`](person.h), [`person.cpp`](person.cpp): shared course-project base class.
- [`tests/test_scheduler.py`](tests/test_scheduler.py): runs compiled executable against sample, ordering, capacity, malformed-input and missing-file fixtures.
- [`tests/test_mechanic.cpp`](tests/test_mechanic.cpp): directed checks of time boundaries, conflict rejection and capacity.

Run the full test suite with Python 3 and g++:

```bash
python3 -m unittest discover -s tests -v
g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -I. tests/test_mechanic.cpp mechanic.cpp person.cpp -o mechanic_test
./mechanic_test
```

## Limitations and provenance

The input format has no customer IDs or explicit service durations; equal names are allowed. There are no business hours, staff skills, rescheduling, storage, concurrent bookings or optimal-assignment guarantees. The included names and records are sample data, not an external evaluation. No original assignment rubric, individual contribution breakdown or project license file is provided; no license is asserted here. The original coursework source is preserved in the Git history for comparison with these repairs.
