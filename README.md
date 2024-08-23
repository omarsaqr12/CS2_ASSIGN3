
# CS2_ASSIGN3

This repository contains the source code and related files for a C++ project that simulates a basic customer and mechanic scheduling system. The program reads customer and mechanic data from text files, schedules appointments, and outputs the results.

## Files

- **Customers.txt**: Contains data about the customers.
- **Mechanics.txt**: Contains data about the mechanics.
- **customer.cpp**: Implements the `Customer` class, which handles customer-specific data and functionality.
- **customer.h**: Header file for the `Customer` class.
- **main.cpp**: The main driver program that ties everything together, including scheduling appointments and displaying results.
- **mechanic.cpp**: Implements the `Mechanic` class, which handles mechanic-specific data and functionality.
- **mechanic.h**: Header file for the `Mechanic` class.
- **person.cpp**: Implements the `Person` class, a base class for both `Customer` and `Mechanic`.
- **person.h**: Header file for the `Person` class.

## How to Compile

To compile the project, use the following command:

```bash
g++ -o scheduler main.cpp customer.cpp mechanic.cpp person.cpp
```

This will generate an executable file named `scheduler`.

## How to Run

After compiling, run the program with the following command:

```bash
./scheduler
```

The program will read the data from the `Customers.txt` and `Mechanics.txt` files, schedule appointments based on the availability of the mechanics, and then output the schedule.

## Classes Overview

- **Person**: A base class representing a generic person with basic attributes like name and ID.
- **Customer**: Inherits from `Person` and includes additional attributes and methods specific to customers.
- **Mechanic**: Inherits from `Person` and includes attributes and methods specific to mechanics, such as availability times.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

Feel free to customize this `README.md` to fit the specific needs or additional details of your project.
