#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <fstream>
#include <string>

using ll = long long;

// Singleton class Logger
class Logger {
   public:
    // It should not be copied using Copy contructor, so deleting default
    Logger(const Logger &rhs) = delete;

    // It should not be copied using Move constructor, so deleting default
    Logger(Logger &&rhs) = delete;

    // It should not be assignable using Copy semantics, so deleting it
    Logger &operator=(const Logger &rhs) = delete;

    // It should not be assignable using Move semantics, so deleting it
    Logger &operator=(Logger &&rhs) = delete;

    // Static method to access the only instance of the Logger class
    static Logger *getLogger();

    // Static method to close the file opened by logger and destroy logger object
    static void close();

    // Making overload << operator as friend function to write to file object
    friend Logger &operator<<(Logger &logger, ll num);
    friend Logger &operator<<(Logger &logger, const char &c);
    friend Logger &operator<<(Logger &logger, const std::string &str);

   private:
    // Logger class object pointer
    static Logger *logger;

    // Logger class filename
    static std::string filename;

    // Logger class file stream object
    static std::fstream file;

    // Constructor
    Logger();

    // Destructor
    ~Logger();
};

// Making overload << operator as friend function to write to file object
Logger &operator<<(Logger &logger, ll num);
Logger &operator<<(Logger &logger, const char &c);
Logger &operator<<(Logger &logger, const std::string &str);

//~ Idea of this class taken from the link provided in the question and the question suggested to look at them.
//~ https://cppcodetips.wordpress.com/2014/01/02/a-simple-logger-class-in-c/

#endif  // _LOGGER_H_