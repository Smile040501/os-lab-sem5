#include <pthread.h>  // For using different POSIX threads functions
#include <unistd.h>   // For using `usleep` function

#include <cstdlib>   // For using `rand` and `srand` functions
#include <ctime>     // For using `time` function
#include <iostream>  // For basic I/O operations in C++

using ll = long long;  // typedef for `long long`

const ll START_DISTANCE = 0;            // Starting distance of the race for hare and turtle
const ll TOTAL_DISTANCE = 1e5;          // Total distance for which the race will occur
const ll DIST_FOR_HARE_TO_SLEEP = 10;   // Minimum distance between hare and turtle, so that hare can sleep
const ll START_TIME = 0;                // Starting time of the race for hare and turtle
const ll ONE_HARE_STEP = 4;             // Distance covered by hare in one step
const ll ONE_TURTLE_STEP = 1;           // Distance covered by turtle in one step
const ll MIN_HARE_SLEEP_TIME = 0;       // Minimum amount of time (in seconds) hare will sleep
const ll MAX_HARE_SLEEP_TIME = 50;      // Maximum amount of time (in seconds) hare will sleep
const double GOD_POSITIVE_PROB = 0.50;  // Probability above which god will change positions
const ll GOD_SLEEP_TIME = 500;          // Time in milliseconds for which god thread will be suspended
const ll REPORTER_SLEEP_TIME = 500;     // Time in milliseconds for which reporter thread will be suspended

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
    while (true) {
        pthread_mutex_lock(&hareMutex);

        if (hareDist >= TOTAL_DISTANCE) {  // Hare has already covered the whole distance
            pthread_mutex_unlock(&hareMutex);
            break;
        }

        pthread_mutex_lock(&turtleMutex);

        if (hareDist - turtleDist >= DIST_FOR_HARE_TO_SLEEP) {
            // Generating a random sleep time for the Hare
            ll sleepTime = MIN_HARE_SLEEP_TIME + (rand() % (MAX_HARE_SLEEP_TIME - MIN_HARE_SLEEP_TIME + 1));
            hareTime += sleepTime;

            pthread_mutex_unlock(&turtleMutex);
            pthread_mutex_unlock(&hareMutex);

            // Suspending the execution of hare thread for some time of sleep
            usleep(sleepTime * 10);
            continue;
        }

        pthread_mutex_unlock(&turtleMutex);

        // Hare moving ahead
        hareDist += ONE_HARE_STEP;
        ++hareTime;

        pthread_mutex_unlock(&hareMutex);
    }

    pthread_exit(nullptr);
}

// Turtle Thread
void* turtleThread(void* arg) {
    while (true) {
        pthread_mutex_lock(&turtleMutex);

        if (turtleDist >= TOTAL_DISTANCE) {  // Turtle has already covered the whole distance
            pthread_mutex_unlock(&turtleMutex);
            break;
        }

        // Turtle moving ahead
        turtleDist += ONE_TURTLE_STEP;
        ++turtleTime;

        pthread_mutex_unlock(&turtleMutex);
    }

    pthread_exit(nullptr);
}

// Function that will generate any random position by god within the bounds of the racetrack
ll generateRandomPositionByGod() {
    ll min = START_DISTANCE, max = TOTAL_DISTANCE;
    // Generates a random value in [min, max]
    return min + (std::rand() % (max - min + 1));
}

// Function that randomly decides whether god should change positions of hare and turtle or not
bool shouldChangePositions() {
    return ((double)generateRandomPositionByGod() / (double)TOTAL_DISTANCE) >= GOD_POSITIVE_PROB;
}

// God Thread
void* godThread(void* arg) {
    while (true) {
        pthread_mutex_lock(&outputMutex);
        pthread_mutex_lock(&hareMutex);
        pthread_mutex_lock(&turtleMutex);

        if (hareDist >= TOTAL_DISTANCE && turtleDist >= TOTAL_DISTANCE) {  // Race is over
            pthread_mutex_unlock(&turtleMutex);
            pthread_mutex_unlock(&hareMutex);
            pthread_mutex_unlock(&outputMutex);
            break;
        }

        if (shouldChangePositions()) {  // God is going to change the positions
            std::cout << "===================================================================================" << std::endl;
            std::cout << "=================================GOD SHOWING POWER=================================" << std::endl;
            if (hareDist < TOTAL_DISTANCE) {  // Change distance only if hare has not finished the race
                hareDist = generateRandomPositionByGod();
                std::cout << "New position of Hare: " << hareDist << ", at time: " << hareTime << " s." << std::endl;
            }
            if (turtleDist < TOTAL_DISTANCE) {  // Change distance only if turtle has not finished the race
                turtleDist = generateRandomPositionByGod();
                std::cout << "New position of Turtle: " << turtleDist << ", at time: " << turtleTime << " s." << std::endl;
            }
            std::cout << "===================================================================================" << std::endl;
        } else {
            pthread_mutex_unlock(&turtleMutex);
            pthread_mutex_unlock(&hareMutex);
            pthread_mutex_unlock(&outputMutex);

            // Suspend execution of God thread for some time if god is not changing positions
            usleep(GOD_SLEEP_TIME);
            continue;
        }

        pthread_mutex_unlock(&turtleMutex);
        pthread_mutex_unlock(&hareMutex);
        pthread_mutex_unlock(&outputMutex);
    }

    pthread_exit(nullptr);
}

// Function to announce the final results
void announceResults() {
    std::cout << "===================================================================================" << std::endl;
    std::cout << "=================================RACE FINISHED=================================" << std::endl;
    std::cout << "Time taken by Hare: " << hareTime << std::endl;
    std::cout << "Time taken by Turtle: " << turtleTime << std::endl;
    if (hareTime > turtleTime) {
        std::cout << "The winner of the race is Hare!!" << std::endl;
    } else if (hareTime < turtleTime) {
        std::cout << "The winner of the race is Turtle!!" << std::endl;
    } else {
        std::cout << "It's a tie breaker!!" << std::endl;
    }
    std::cout << "===================================================================================" << std::endl;
}

// Reporter Thread
void* reporterThread(void* arg) {
    while (true) {
        pthread_mutex_lock(&hareMutex);
        pthread_mutex_lock(&turtleMutex);
        pthread_mutex_lock(&outputMutex);

        if (hareDist >= TOTAL_DISTANCE && turtleDist >= TOTAL_DISTANCE) {  // Race is over

            announceResults();  // announcing the final results

            pthread_mutex_unlock(&outputMutex);
            pthread_mutex_unlock(&turtleMutex);
            pthread_mutex_unlock(&hareMutex);
            break;
        }
        std::cout << "===================================================================================" << std::endl;
        std::cout << "=================================STATE OF THE RACE=================================" << std::endl;
        std::cout << "Position of Hare: " << hareDist << ", at time: " << hareTime << " s." << std::endl;
        std::cout << "Position of Turtle: " << turtleDist << ", at time: " << turtleTime << " s." << std::endl;
        std::cout << "===================================================================================" << std::endl;

        pthread_mutex_unlock(&outputMutex);
        pthread_mutex_unlock(&turtleMutex);
        pthread_mutex_unlock(&hareMutex);

        // Suspending the execution of the reporter thread for some time
        usleep(REPORTER_SLEEP_TIME);
        continue;
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
    pthread_join(hareTid, nullptr);
    pthread_join(turtleTid, nullptr);
    pthread_join(godTid, nullptr);
    pthread_join(reporterTid, nullptr);

    return EXIT_SUCCESS;
}
