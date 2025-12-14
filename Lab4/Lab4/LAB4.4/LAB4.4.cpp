// LAB4.4.cpp : Generates multiplication table for the last two digits "05" of a student ID.
// Compiles with C++14.

#include <iostream>
#include <iomanip>

int main()
{
    const int lastTwoDigits = 5; // "05" -> numeric value 5
    const int start = 1;
    const int end = 12;

    // Print header
    std::cout << "Multiplication table for last two digits: ";
    std::cout << std::setw(2) << std::setfill('0') << lastTwoDigits << "\n\n";

    // Print table 1..12, preserving the leading zero for the base ("05")
    for (int i = start; i <= end; ++i)
    {
        std::cout << std::setw(2) << std::setfill('0') << lastTwoDigits
                  << " x "
                  << std::setw(2) << std::setfill(' ') << i
                  << " = "
                  << std::setw(2) << std::setfill('0') << (lastTwoDigits * i)
                  << '\n';
    }

    return 0;
}
