//
// Created by jmwat on 3/23/2021.
//
/*
 * An interface is a shared boundary that contains no data or code. It defines function signatures that all
 * implementations of the interface agree to support. An implementation is code or data that declares support
 * for an interface. An interface is a contract between classes that implement the interface and users (or consumers)
 * of that class.
 */

#include <cstdio>
#include <stdexcept>


// logger is a pure virtual class (interface) with a default virtual destructor and a single method.
struct Logger
{
    virtual ~Logger() = default;
    virtual void log_transfer(long from, long to, double amount) = 0;
};

// Both of these methods are Logger implementations
struct ConsoleLogger : Logger
{
    void log_transfer(long from, long to, double amount) override
    {
        printf("[cons] %ld -> %ld: %f\n", from, to, amount);
    }
};

struct Filelogger : Logger
{
    void log_transfer(long from, long to, double amount) override
    {
        printf("[file] %ld -> %ld: %f\n", from, to, amount);
    }
};

struct Bank
{
    // constructor injection:
    // sets the value of logger using a member initializer. This is constructor injection and pass in a logger reference
    // You establish the kind of logging that a particular bank instantiation will perform. This cannot be reseated
    // therefore you cannot change the behavior of bank.
    Bank(Logger& logger) : logger{logger} {}
    // property injection. This approach uses a pointer instead of a reference. Pointers can be reseated, you can
    // change the behavior of bank anytime.
    // void set_logger(Logger* new_logger) {
    //      logger = new_logger;
    //}
    void make_transfer(long from, long to, double amount)
    {
        logger.log_transfer(from, to, amount);
    }
private:
    Logger& logger;
};

int main()
{
    ConsoleLogger logger;
    Filelogger flogger;
    // decide on the type of logger. Use constructor injector
    Bank bank{logger};
    bank.make_transfer(1000, 2000, 49.95);
    bank.make_transfer(2000, 4000, 20.00);
    Bank newBank{flogger};
    newBank.make_transfer(1000, 2000, 49.95);
    newBank.make_transfer(2000, 4000, 20.00);

    // property injection
    //bank.set_logger(&console_logger);
    //bank.make_transaction(1000, 2000, 49.95)
    //bank.set_logger(&file_logger);
    //bank.make_transaction(1000, 2000, 49.95)
}