#pragma once
#include <iostream>
#include <chrono>

class Timer {
private:
    long long startTime;   // Stores the start time
    long long pausedTime;  // Stores the time at which the timer was paused
    bool isRunning;        // Indicates whether the timer is currently running
    bool isPaused;         // Indicates whether the timer is currently paused

    long long currentTime() const;

public:
    Timer();

    void start(); // Starts the timer.
    void pause(); // Pauses the timer.
    void resume();// Resumes the timer.
    void reset(); // Resets the timer.

    long long elapsedMilliseconds() const;// Returns the elapsed time in milliseconds since the timer started or resumed.
    long long elapsedSeconds() const;   // Returns the elapsed time in seconds since the timer started or resumed.

    void displayTime() const;    // Displays the elapsed time in a human-readable format (e.g., "mm:ss").

};
