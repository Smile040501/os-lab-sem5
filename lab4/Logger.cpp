#include "Logger.h"

#include <fstream>
#include <string>

#include "constants.h"
#include "exceptions.h"

using ll = long long;

// Logger class object pointer
Logger* Logger::logger = nullptr;

// Logger class filename
std::string Logger::filename = constants::LOG_FILE;

// Logger class file stream object
std::fstream Logger::file;

// Constructor
Logger::Logger() {
}

// Destructor
Logger::~Logger() {
}

// Static method to access the only instance of the Logger class
Logger* Logger::getLogger() {
    if (Logger::logger == nullptr) {
        Logger::logger = new Logger();
        // Opening file for writing to it in append mode
        Logger::file.open(Logger::filename, std::ios::out | std::ios::app);
    }
    return Logger::logger;
}

// Static method to close the file opened by logger and destroy logger object
void Logger::close() {
    if (Logger::logger != nullptr) {
        delete Logger::logger;
        Logger::logger = nullptr;
        if (Logger::file.is_open()) {
            Logger::file.close();
        }
    }
}

// Making overload << operator as friend function to write to file object
Logger& operator<<(Logger& logger, ll num) {
    if (Logger::file.is_open()) {
        Logger::file << num;
    } else {
        throw FileNotFoundException();
    }
    return logger;
}

Logger& operator<<(Logger& logger, const char& c) {
    if (Logger::file.is_open()) {
        Logger::file.put(c);
    } else {
        throw FileNotFoundException();
    }
    return logger;
}

Logger& operator<<(Logger& logger, const std::string& str) {
    if (Logger::file.is_open()) {
        Logger::file << str;
    } else {
        throw FileNotFoundException();
    }
    return logger;
}