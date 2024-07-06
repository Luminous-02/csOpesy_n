#include "marquee.h"
#include <windows.h>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>
#include <conio.h> // Include this to use _kbhit() and _getch()

std::mutex mtx; // Mutex for synchronizing access to console functions

// Function prototypes
void handleUserInput(std::string& userInput, bool& exitFlag);

void marqueeWorker(SHORT& x, SHORT& y, SHORT& xDir, SHORT& yDir, const std::string& message, bool& exitFlag);

void printStaticHeader();

int displayMarquee()
{
    // Clear the console screen
    system("cls");

    printStaticHeader(); // Call the function to print the static header

    // Initialize console screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    SHORT x = 0, y = 3;       // Starting position for the marquee
    SHORT xDir = 1, yDir = 1; // Initial direction of movement
    std::string message = "Hello, World in marquee.";
    std::string userInput;
    bool exitFlag = false;

    // Start the handleUserInput function in a separate thread
    std::thread userInputThread(handleUserInput, std::ref(userInput), std::ref(exitFlag));

    // Start the marquee worker in a separate thread
    std::thread marqueeThread(marqueeWorker, std::ref(x), std::ref(y), std::ref(xDir), std::ref(yDir), std::ref(message), std::ref(exitFlag));


    while (!exitFlag)
    {
        // Display the prompt for user input
        mtx.lock();
        COORD coord = { 0, csbi.srWindow.Bottom - 1 }; // Position for the notification
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        std::cout << "Enter a command for MARQUEE_CONSOLE: " << userInput;
        mtx.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Delay to match the refresh rate
    }

    // Wait for both threads to finish
    marqueeThread.join();
    userInputThread.join();

    return 0;
}

void handleUserInput(std::string& userInput, bool& exitFlag)
{
    char ch;
    while (!exitFlag) // Keep checking for user input until exitFlag is set to true
    {
        if (_kbhit()) // Check if a key has been pressed
        {
            ch = _getch(); // Get the pressed key

            // Handle backspace
            if (ch == '\b' && !userInput.empty())
            {
                userInput.pop_back(); // Remove last character from userInput
            }
            // Handle other characters
            else if (ch != '\r' && ch != '\n')
            {
                userInput.push_back(ch); // Append character to userInput
            }
            else if (userInput == "exit" && ch == '\r' || ch == '\n')
            {
                exitFlag = true;
            }
            // Handle enter key
            else if (ch == '\r' || ch == '\n')
            {
                mtx.lock();
                CONSOLE_SCREEN_BUFFER_INFO csbi;
                GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
                COORD coord = { 0, csbi.srWindow.Bottom }; // Position for the notification
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                std::cout << "Command Processed in MARQUEE_CONSOLE Threaded: " << userInput;
                mtx.unlock();
                userInput.clear(); // Clear the userInput after processing
            }

        }
    }
}

void marqueeWorker(SHORT& x, SHORT& y, SHORT& xDir, SHORT& yDir, const std::string& message, bool& exitFlag)
{
    while (true)
    {
        // Check if the exitFlag is set to true
        if (exitFlag)
        {
            break; // Exit the loop
        }
        
        // Get the current console window size
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        SHORT currentWindowWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        SHORT currentWindowHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        // Clear the previous position of the marquee message
        COORD oldCoord = { x, y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), oldCoord);
        for (size_t i = 0; i < message.length(); ++i)
            std::cout << ' ';

        // Change direction if the message hits the screen borders
        SHORT next_x = x + xDir;
        SHORT next_y = y + yDir;
        if (next_x < 0 || next_x > currentWindowWidth - message.length())
            xDir *= -1;
        if (next_y < 3 || next_y > currentWindowHeight - 3)
            yDir *= -1;
        x += xDir; // Move the message horizontally
        y += yDir; // Move the message vertically

        // Set the cursor position and print the message
        COORD coord = { x, y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        std::cout << message;

        std::this_thread::sleep_for(std::chrono::milliseconds(60)); // Delay to match the refresh rate
    }
}



// Function to print the static header
void printStaticHeader()
{
    mtx.lock();
    COORD coord = { 0, 0 }; // Position for the static header
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    for (int i = 0; i < 40; i++)
        std::cout << "*";
    std::cout << "\n*   Displaying a marquee console!   *\n";
    for (int i = 0; i < 40; i++)
        std::cout << "*";
    mtx.unlock();
}
