#include <stdexcept>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include "Application.hpp"

int main(int argc, char** argv)
{
  try {

    // Create a Game object and launch it
    // Game game(argc, argv);
    // game.run();
    Application app(argc, argv);
    app.run();

  } catch (std::exception& exc) { // If any fatal exception is thrown...

    // Create a time_point object containing the time at which the exception was caught
    std::chrono::time_point<std::chrono::system_clock> currentTime;
    currentTime = std::chrono::system_clock::now();
    // Pass the object to a new time_t object so it can be output via a stream
    std::time_t outputTime = std::chrono::system_clock::to_time_t(currentTime);

    // Open the error log in append mode
    std::ofstream errorLog;
    errorLog.open("error_log.log", std::ostream::out | std::ostream::app);
    // Write the exception and the time it was caught to file in a nice format
    errorLog
    << "\n== " << std::ctime(&outputTime)
    << "EXCEPTION: " << exc.what() << std::endl;

    errorLog.close();
  }
}
