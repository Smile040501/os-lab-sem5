#include <pthread.h>  // For using different POSIX threads functions
#include <unistd.h>   // For using `usleep` function

#include <cstdlib>   // For using `rand` and `srand` functions
#include <ctime>     // For using `time` function
#include <iostream>  // For basic I/O operations in C++

using ll = long long;  // typedef for `long long`

const ll START_DISTANCE = 0;           // Starting distance of the race for hare and turtle
const ll TOTAL_DISTANCE = 100;         // Total distance for which the race will occur
const ll DIST_FOR_HARE_TO_SLEEP = 10;  // Minimum distance between hare and turtle, so that hare can sleep
const ll START_TIME = 0;               // Starting time of the race for hare and turtle

// Distances of hare and turtle
ll hareDist = START_DISTANCE;
ll turtleDist = START_DISTANCE;

// Time taken by hare and turtle
ll hareTime = START_TIME;
ll turtleTime = START_TIME;

pthread_mutex_t hareMutex = PTHREAD_MUTEX_INITIALIZER;    // Mutex to modify hareDist and hareTime
pthread_mutex_t turtleMutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex to modify turtleDist and turtleTime
pthread_mutex_t outputMutex = PTHREAD_MUTEX_INITIALIZER;  // Mutext for writing output to the terminal

// Hare Thread
void* hareThread(void* arg) {
}

// Turtle Thread
void* turtleThread(void* arg) {
}

// Function that will generate any random position by god within the bounds of the racetrack
ll generateRandomPositionByGod() {
    ll min = START_DISTANCE, max = TOTAL_DISTANCE;
    // Generates a random value in [min, max]
    return min + (std::rand() % (max - min + 1));
}

// God Thread
void* godThread(void* arg) {
}

// Reporter Thread
void* reporterThread(void* arg) {
}

void checkThreadCreation(int iretCode) {
    if (iretCode) {
        std::cerr << "Error - pthread_creat() returns code: " << iretCode << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main() {
    std::srand(std::time(nullptr));  // seeding the pseudo-random number generator used by rand()

    // Creating thread ids for hare, turtle, god and reporter thread
    pthread_t hareTid, turtleTid, godTid, reporterTid;

    // Creating threads for hare, turtle, god and reporter
    int iretHare = pthread_create(&hareTid, nullptr, hareThread, nullptr);
    checkThreadCreation(iretHare);

    int iretTurtle = pthread_create(&turtleTid, nullptr, turtleThread, nullptr);
    checkThreadCreation(iretTurtle);

    int iretGod = pthread_create(&godTid, nullptr, godThread, nullptr);
    checkThreadCreation(iretGod);

    int iretReporter = pthread_create(&reporterTid, nullptr, reporterThread, nullptr);
    checkThreadCreation(iretReporter);

    // Waiting for each thread to finish their work
    pthread_join(hareTid, nullptr);
    pthread_join(turtleTid, nullptr);
    pthread_join(godTid, nullptr);
    pthread_join(reporterTid, nullptr);

    return EXIT_SUCCESS;
}
