// LAB4.6.cpp : Line-following robot control simulation (color sensor: left/center/right).
// Compiles with C++14.

#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <thread>

enum class SensorPosition
{
    Left,
    Center,
    Right,
    Unknown
};

SensorPosition parseInput(const std::string &s)
{
    if (s.empty()) return SensorPosition::Unknown;
    char c = std::tolower(static_cast<unsigned char>(s[0]));
    if (c == 'l') return SensorPosition::Left;
    if (c == 'c') return SensorPosition::Center;
    if (c == 'r') return SensorPosition::Right;
    return SensorPosition::Unknown;
}

void applyControl(SensorPosition pos)
{
    // Simple actuator model: (leftMotor, rightMotor) as percent speed [-100..100]
    int leftMotor = 0;
    int rightMotor = 0;

    switch (pos)
    {
    case SensorPosition::Left:
        // Line is on the left -> turn left (slow left wheel, fast right wheel)
        leftMotor = 30;
        rightMotor = 100;
        std::cout << "Sensor: LEFT  -> Action: Turn LEFT\n";
        break;
    case SensorPosition::Right:
        // Line is on the right -> turn right (fast left wheel, slow right wheel)
        leftMotor = 100;
        rightMotor = 30;
        std::cout << "Sensor: RIGHT -> Action: Turn RIGHT\n";
        break;
    case SensorPosition::Center:
        // Line is centered -> go straight
        leftMotor = 100;
        rightMotor = 100;
        std::cout << "Sensor: CENTER -> Action: Go FORWARD\n";
        break;
    default:
        // Unknown reading: stop or search
        leftMotor = 0;
        rightMotor = 0;
        std::cout << "Sensor: UNKNOWN -> Action: Stop / Search\n";
        break;
    }

    // Print motor commands
    std::cout << "Motors -> Left: " << leftMotor << "%, Right: " << rightMotor << "%\n";
}

int main()
{
    std::cout << "Line-Following Robot Simulation\n";
    std::cout << "Commands:\n";
    std::cout << "  l - simulate sensor: line on LEFT\n";
    std::cout << "  c - simulate sensor: line at CENTER\n";
    std::cout << "  r - simulate sensor: line on RIGHT\n";
    std::cout << "  s - switch to RANDOM automatic mode\n";
    std::cout << "  q - quit\n\n";

    bool running = true;
    bool autoMode = false;

    std::mt19937 rng(static_cast<unsigned int>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(0, 2); // 0=Left,1=Center,2=Right

    while (running)
    {
        if (autoMode)
        {
            // automatic random simulation
            int r = dist(rng);
            SensorPosition pos = (r == 0) ? SensorPosition::Left :
                                 (r == 1) ? SensorPosition::Center :
                                            SensorPosition::Right;
            applyControl(pos);

            // small delay to simulate time between sensor readings
            std::this_thread::sleep_for(std::chrono::milliseconds(700));

            // allow user to break automatic mode
            if (std::cin.rdbuf()->in_avail() > 0)
            {
                std::string cmd;
                std::cin >> cmd;
                if (!cmd.empty() && (cmd[0] == 'q' || cmd[0] == 'Q'))
                {
                    running = false;
                }
                else if (!cmd.empty() && (cmd[0] == 's' || cmd[0] == 'S'))
                {
                    autoMode = false;
                    std::cout << "Switched to manual mode.\n";
                }
            }
        }
        else
        {
            std::cout << "Enter command (l/c/r/s/q): ";
            std::string input;
            if (!(std::cin >> input))
            {
                break;
            }

            char cmd = std::tolower(static_cast<unsigned char>(input[0]));
            if (cmd == 'q')
            {
                running = false;
            }
            else if (cmd == 's')
            {
                autoMode = true;
                std::cout << "Switched to RANDOM automatic mode. Press 's' to return to manual or 'q' to quit.\n";
            }
            else
            {
                SensorPosition pos = parseInput(input);
                applyControl(pos);
            }
        }
    }

    std::cout << "Exiting simulation.\n";
    return 0;
}
