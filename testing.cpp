//
// Created by jwats on 8/6/2021.
//

// Unit tests
// Unit tests verify that a focused, cohesive collection of code -- a unit, such as a function or class --
// behaves exactly as the programmer intended. Unit tests isolate the unit being tested from its dependencies.
// If this is difficult, then use mocks to stand in for these dependencies. Mocks are fake objects used solely for testing
// to provide one with fine-grained control over how a unit's dependencies behave during the test.
// You can also use  mocks to simulate rare events, such as a system running out of memory, by programming them to throw
// an exception.

// integration tests
// testing a collection of units together.  Can also refer to testing interactions between software and hardware.
// Ensures that the software you've written works together as a system.

// Acceptance tests
// Ensures that your software meets all of your customers requirements. Can be used to guide development.
// Once all of the acceptance tests pass, then your software is deliverable.

// Performance tests
// evaluate whether software meets effectiveness requirements, such as speed of execution or memory/power consumption.
// YOu can use performance tests to instrument your code and provide relevant measures.
// Instrumentation is a technique for measuring product performance, detecting errors, and logging how a program executes.
// You can automate testing such requirements and make sure that future code changes don't violate them.

// Example
// You are helping develop software for an autonomous vehicle.
// The monumental task of writing all the vehicle's software is broken into teams.  Services interact with each other via
// a service bus, where each service publishes events. Other services subscribe to these events as needed. This design pattern
// is called a service bus architecture.
// My team is responsible for the autonomous braking service.  The service must determine whether a collision is about
// to happen and tell the car to brake.
// My service subscribes to two event types: the SpeedUpdate class, which tells you that the car's speed has changed, and the
// carDetected class, which tells you that some other car has been detected in front of you.  Your system is responsible
// for publishing a BrakeCommand to the service bush whenever an imminent collision is detected.

struct SpeedUpdate
{
    double velocity_mps;
};

struct CarDetected
{
    double distance_m;
    double velocity_mps;
};

struct BrakeCommand
{
    double time_to_collision_s;
};

struct ServiceBus
{
    void publish(const BrakeCommand&);
    // -- snip --
};

template <typename T>
struct AutoBrake
{
    AutoBrake(const T& publish) : publish { publish } {};
    void observe(const SpeedUpdate& cd) {};
    void observe(const CarDetected& cd) {};
private:
    const T& publish;
    // -- snip --
};

int main()
{
    ServiceBus bus;
    AutoBrake auto_brake{ [&bus]  (const auto& cmd) {
        bus.publish(cmd);
        }
    };
    while (true)
    {
        auto_brake.observe(SpeedUpdate{ 10l });
        auto_brake.observe(CarDetected{ 250L, 25L });
    }
}