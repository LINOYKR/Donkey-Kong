#include "Timer.h"

Timer::Timer() : startTime(0), pausedTime(0), isRunning(false), isPaused(false) {}

long long Timer::currentTime() const {
    // Returns the current system time in milliseconds
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch())
        .count();
}

void Timer::start() {
    startTime = currentTime();
    pausedTime = 0;
    isRunning = true;
    isPaused = false;
}

void Timer::pause() {
    if (isRunning && !isPaused) {
        pausedTime = currentTime();
        isPaused = true;
    }
}

void Timer::resume() {
    if (isRunning && isPaused) {
        startTime += (currentTime() - pausedTime); // Adjust start time to account for pause duration
        pausedTime = 0;
        isPaused = false;
    }
}

void Timer::reset() {
    startTime = 0;
    pausedTime = 0;
    isRunning = false;
    isPaused = false;
}

// Returns the elapsed time in milliseconds since the timer started or resumed.
long long Timer::elapsedMilliseconds() const {
    if (!isRunning) return 0;
    if (isPaused) return pausedTime - startTime;
    return currentTime() - startTime;
}

// Returns the elapsed time in seconds since the timer started or resumed.
long long Timer::elapsedSeconds() const {
    return elapsedMilliseconds() / 1000;
}

// Displays the elapsed time in a human-readable format (e.g., "mm:ss").
void Timer::displayTime() const {
    long long seconds = elapsedSeconds();
    long long minutes = seconds / 60;
    seconds %= 60;
    std::cout << "Time: " << minutes << "m " << seconds << "s" << std::endl;
}
