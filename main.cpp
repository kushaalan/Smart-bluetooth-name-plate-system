#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

// Colors and Display settings (not used in console version)
#define BLACK   0
#define WHITE   1
#define DISPLAY_WIDTH 480
#define DISPLAY_HEIGHT 320

std::string firstLine = "Waiting for data...";
std::string secondLine = "";
std::string thirdLine = "";

// Simulated display centered texts (console version)
void displayCenteredTexts() {
    // Simulate clearing the screen
    std::cout << "\033[2J\033[1;1H";  // ANSI escape codes to clear the console screen

    // Display first line
    if (!firstLine.empty()) {
        std::cout << firstLine << std::endl;
    }

    // Display second line
    if (!secondLine.empty()) {
        std::cout << secondLine << std::endl;
    }

    // Display third line
    if (!thirdLine.empty()) {
        std::cout << thirdLine << std::endl;
    }

    std::cout << "----------------------------------------" << std::endl;
}

// Simulated loop to handle user input
void processInput(const std::string& newInput) {
    // Shift lines and add the new input
    if (firstLine == "Waiting for data...") {
        firstLine = newInput;
    } else if (secondLine.empty()) {
        secondLine = newInput;
    } else if (thirdLine.empty()) {
        thirdLine = newInput;
    } else {
        // Shift lines up
        firstLine = secondLine;
        secondLine = thirdLine;
        thirdLine = newInput;
    }
}

int main() {
    std::string newInput;

    // Initial display
    displayCenteredTexts();

    // Main loop (simulating Arduino loop)
    while (true) {
        std::cout << "Enter new data (or type 'exit' to quit): ";
        std::getline(std::cin, newInput);  // Read input from console

        if (newInput == "exit") {
            break;  // Exit the loop if the user types 'exit'
        }

        processInput(newInput);
        displayCenteredTexts();  // Refresh the "display"

        // Simulating the delay in the original Arduino loop
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
