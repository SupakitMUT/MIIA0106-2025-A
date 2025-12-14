// LAB4.5.cpp : Number guessing game (random 1-100).
// Compiles with C++14.

#include <iostream>
#include <random>
#include <string>

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    bool playAgain = true;
    while (playAgain)
    {
        int target = dist(gen);
        int attempts = 0;

        std::cout << "I'm thinking of a number between 1 and 100. Try to guess it.\n";

        while (true)
        {
            std::cout << "Enter your guess: ";
            int guess;
            if (!(std::cin >> guess))
            {
                std::cin.clear();
                std::string bad;
                std::cin >> bad; // consume invalid token
                std::cout << "Invalid input — please enter an integer between 1 and 100.\n";
                continue;
            }

            if (guess < 1 || guess > 100)
            {
                std::cout << "Please enter a number between 1 and 100.\n";
                continue;
            }

            ++attempts;

            if (guess < target)
            {
                std::cout << "Too low.\n";
            }
            else if (guess > target)
            {
                std::cout << "Too high.\n";
            }
            else
            {
                std::cout << "Correct! You guessed the number in " << attempts << " attempt"
                          << (attempts == 1 ? "" : "s") << ".\n";
                break;
            }
        }

        std::cout << "Play again? (y/n): ";
        char answer = 'n';
        std::cin >> answer;
        playAgain = (answer == 'y' || answer == 'Y');
    }

    return 0;
}
