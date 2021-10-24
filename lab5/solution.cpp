#include <pthread.h>  // For using different POSIX threads functions
#include <unistd.h>   // For using `usleep` function

#include <cstdlib>  // For using `rand` and `srand` functions
#include <ctime>    // For using `time` function
#include <iostream>
#include <string>

using ll = long long;  // typedef for `long long`

const ll START_DISTANCE = 0;           // Starting distance of the race for hare and turtle
const ll TOTAL_DISTANCE = 300;         // Total distance for which the race will occur
const ll DIST_FOR_HARE_TO_SLEEP = 15;  // Minimum distance between hare and turtle, so that hare can sleep
const ll ONE_HARE_STEP = 5;            // Distance covered by hare in one step
const ll ONE_TURTLE_STEP = 1;          // Distance covered by turtle in one step
const ll MIN_HARE_SLEEP_TIME = 10;     // Minimum amount of time (in seconds) hare will sleep
const ll MAX_HARE_SLEEP_TIME = 50;     // Maximum amount of time (in seconds) hare will sleep

// Distances of hare and turtle
ll hareDist = START_DISTANCE;
ll turtleDist = START_DISTANCE;

bool isHareSleeping = false;  // Is hare sleeping or not
bool isRaceStarted = false;   // Has the race started by god

pthread_mutex_t hareMutex = PTHREAD_MUTEX_INITIALIZER;    // Mutex to modify hareDist
pthread_mutex_t turtleMutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex to modify turtleDist
pthread_mutex_t outputMutex = PTHREAD_MUTEX_INITIALIZER;  // Mutext for writing output to the terminal

// Function to generate a random number in [a, b]
ll generateRandomNumber(ll a, ll b) {
    return a + (rand() % (b - a + 1));
}

// Hare Thread
void* hareThread(void* arg) {
    while (hareDist < TOTAL_DISTANCE) {
        if (!isRaceStarted) continue;  // Race is not yet started by god

        // Hare can sleep for some random amount of time
        if (hareDist - turtleDist >= DIST_FOR_HARE_TO_SLEEP) {
            // Generating a random sleep time for the Hare
            ll sleepTime = generateRandomNumber(MIN_HARE_SLEEP_TIME, MAX_HARE_SLEEP_TIME);
            isHareSleeping = true;

            // Suspending the execution of hare thread for some time of sleep
            usleep(sleepTime * 100000);
        }

        // Hare is awake
        isHareSleeping = false;

        pthread_mutex_lock(&hareMutex);
        hareDist += ONE_HARE_STEP;  // Hare moving ahead
        pthread_mutex_unlock(&hareMutex);

        usleep(50000);  // Suspending execution so that we can slowly see output on terminal
    }

    pthread_exit(nullptr);
}

// Turtle Thread
void* turtleThread(void* arg) {
    while (turtleDist < TOTAL_DISTANCE) {
        if (!isRaceStarted) continue;  // Race is not yet started by god

        pthread_mutex_lock(&turtleMutex);
        turtleDist += ONE_TURTLE_STEP;  // Turtle moving ahead
        pthread_mutex_unlock(&turtleMutex);

        usleep(50000);  // Suspending execution so that we can slowly see output on terminal
    }

    pthread_exit(nullptr);
}

// God Thread
void* godThread(void* arg) {
    pthread_mutex_lock(&outputMutex);
    std::cout << "Hello, World! Myself God of All!" << std::endl;
    std::cout << "Let's start the race!" << std::endl;
    std::cout << "Type \"god\" on the terminal and press enter to make a godly move!!" << std::endl;
    pthread_mutex_unlock(&outputMutex);
    isRaceStarted = true;

    while (hareDist < TOTAL_DISTANCE && turtleDist < TOTAL_DISTANCE) {
        // Waiting for user to give some string as input to make a godly move
        std::string input;
        std::cin >> input;
        if (input == ":god") {
            pthread_mutex_lock(&hareMutex);
            pthread_mutex_lock(&turtleMutex);
            pthread_mutex_lock(&outputMutex);
            std::cout << "===================================================================================" << std::endl;
            std::cout << "Enter the new positions of Hare and Turtle respectively: ";
            std::cin >> hareDist >> turtleDist;
            std::cout << "===================================================================================" << std::endl;
            usleep(1000000);  // Suspending the execution of the god thread for some time
            pthread_mutex_unlock(&outputMutex);
            pthread_mutex_unlock(&turtleMutex);
            pthread_mutex_unlock(&hareMutex);
        }
    }

    pthread_exit(nullptr);
}

// Reporter Thread
void* reporterThread(void* arg) {
    bool isRaceFinished = false;  // whether the race is finished or not

    while (!isRaceFinished) {
        if (!isRaceStarted) continue;  // Race is not yet started by god

        pthread_mutex_lock(&outputMutex);
        std::cout << "=================================STATE OF THE RACE=================================" << std::endl;
        if (!isHareSleeping) {
            std::cout << "Position of Hare: " << hareDist << std::endl;
        } else {
            std::cout << "Hare is sleeping at position: " << hareDist << std::endl;
        }
        std::cout << "Position of Turtle: " << turtleDist << std::endl;
        std::cout << "===================================================================================" << std::endl;

        if (hareDist >= TOTAL_DISTANCE && turtleDist >= TOTAL_DISTANCE) {
            std::cout << "=================================RACE FINISHED=================================" << std::endl;
            std::cout << "It's a DRAW!!" << std::endl;
            isRaceFinished = true;
        } else if (hareDist >= TOTAL_DISTANCE) {
            std::cout << "=================================RACE FINISHED=================================" << std::endl;
            std::cout << "HARE Won!!" << std::endl;
            isRaceFinished = true;
        } else if (turtleDist >= TOTAL_DISTANCE) {
            std::cout << "=================================RACE FINISHED=================================" << std::endl;
            std::cout << "TURTLE Won!!" << std::endl;
            isRaceFinished = true;
        }
        pthread_mutex_unlock(&outputMutex);

        // Suspending the execution of the reporter thread for some time
        if (!isRaceFinished) usleep(1000000);
    }

    pthread_exit(nullptr);
}

// Function that checks whether the thread creation was successful or not
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
    pthread_join(reporterTid, nullptr);

    return EXIT_SUCCESS;
}
