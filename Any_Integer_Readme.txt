Any_Integer C++ Library

Overview
Any_Integer is a custom C++ library designed to handle arbitrarily large integer values, overcoming the limitations of standard data types like `int` and `long`. This implementation supports a variety of arithmetic and comparison operations, making it suitable for applications that require precise calculations with large numbers.

Features
- Arbitrary Precision Arithmetic: Supports addition and subtraction of integers with no predefined size limit.
- Comparison Operators: Provides comparison functionality for equality, less-than, and greater-than operations.
- Output: Integrates seamlessly with C++ streams for easy output.
- Constructors: Initialize Any_Integer instances from strings, another Any_Integer or standard integer types.
- Robust Error Handling: Ensures reliable handling of incorrect input formats and other edge cases.

Key Methods and Functionalities

Public Methods
- Constructors:
  - Construct an Any_Integer from a string representation.
  - Construct an Any_Integer from a standard long integer.
  - Construct an Any_Integer from a another Any_Integer.

- Assignment Operators:
  - Assign a string representation to the object.
  - Assign a long integer to the object.
  - Assign a amother Any_Integer object to the object

- Arithmetic Operators:
  - Addition of two Any_Integer objects.
  - Subtraction of one Any_Integer object from another.

- Comparison Operators:
  - Compare if the current object is less than another.
  - Check if two `Any_Integer` objects are equal.
  - Compare if the current object is greater than another.

- Stream Insertion:
  - Overload the `<<` operator for output.

Private Methods
- Partition Handling:
  - Partition the string into manageable segments.
  - Perform addition operations on the partitioned data.
  - etc

- Helper Functions:
  - Check if a character is a digit.
  - Resize the partition container.
  - Check if the current number is zero.
  - etc.

Example Usage
- You can run or view the test.cpp file for ensuring the usage of objects.

Installation and Compilation
To use the Any_Integer library:
1. Clone the repository or include the Any_Integer class in your project.
2. Ensure your compiler supports C++11 or later.
3. Compile your project using:
   g++ -std=c++11 main.cpp -o main

Future Enhancements
- Multiplication and Division Support: Implement additional arithmetic operations.
- Error Handling Improvements: Enhance exception handling for more informative error messages.

License
This project is licensed under the MIT License. Feel free to use, modify, and distribute as needed.

Contributions
Contributions are welcome! Feel free to submit issues, feature requests, and pull requests.

Contact
For questions, feedback, or contributions, please reach out via haykdarbinian@gmail.com, hayk.darbin.1998@gmail.com or open an issue on GitHub.

