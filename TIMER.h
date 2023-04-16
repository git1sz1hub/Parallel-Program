#ifndef TIMER_H
#define TIMER_H

#include<iostream> 
#include<string>
#include<ctime>
#include<chrono>
#include<map>

using namespace std;

class timer {
public:
    // Static member function that records the start or end time for a given class and function
    static void tick(const string& class_name, const string& function_name);

    // Static member variables that keep track of the number of times a function is called,
    // the total time spent in each function, and whether each function has been called at least once
    static map<string, unsigned long long> cnt_;
    static map<string, double> time_;
    static map<string, bool> flag_;

    // Static member variables that keep track of the total time spent in all functions,
    // as well as the start and end times for each function
    static double time_total;
    static map<string, chrono::high_resolution_clock::time_point> start_time;
    static map<string, chrono::high_resolution_clock::time_point> end_time;

};

// Overloaded stream insertion operator that allows you to print a timer object to an output stream
ostream& operator<<(ostream& os, const timer& timer);

#endif