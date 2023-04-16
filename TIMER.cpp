#include "TIMER.h"
#include<iostream> 
#include<string>
#include <chrono>
#include <map>
#include<iomanip>

using namespace std;

// Initialize static member variables for the timer class
map<string, unsigned long long> timer::cnt_;
map<string, double> timer::time_;
map<string, bool> timer::flag_;
double timer::time_total = 0;
map<string, chrono::high_resolution_clock::time_point> timer::start_time;
map<string, chrono::high_resolution_clock::time_point> timer::end_time;

// Static member function that records the start and end times for a given class and function
void timer::tick(const string& class_name, const string& function_name)
{
    // Concatenate the class name and function name to form a unique identifier for the function
    string name = class_name + "#" + function_name;

    // If the function is being called for the first time, record the start time
    if (flag_[name] != true)
    {
        flag_[name] = true; // Set the flag to true to indicate that the function has been called
        cnt_[name]++; // Increment the counter for the number of times the function has been called
        start_time[name] = chrono::high_resolution_clock::now(); // Record the start time
    }
    // If the function is being called after having been started before, record the end time and calculate the elapsed time
    else
    {
        end_time[name] = chrono::high_resolution_clock::now(); // Record the end time
        flag_[name] = false; // Set the flag back to false to indicate that the function has finished
        chrono::duration<double> elapsed_time = chrono::duration_cast<chrono::duration<double>>(end_time[name] - start_time[name]); // Calculate elapsed time
        double elapsed_seconds = elapsed_time.count(); // Get elapsed time in seconds
        time_[name] += elapsed_seconds; // Add the elapsed time to the total time spent in the function
    }
}
// Overloaded stream insertion operator that allows printting a timer object to an output stream
ostream& operator<<(ostream& os, const timer& timer)
{
    int partLength;
    int lineLength = 90;
    string dashLine(lineLength, '-');
    string word = "Print the Elapsed Time";
    int wordLength = word.length();
    int fillerLength = lineLength - wordLength;
    if (fillerLength < 0) {
        fillerLength = 0;
    }
    os << dashLine<< endl;
    os << setfill('-') << setw(fillerLength / 2) << ""
        << word << setw((fillerLength + 1) / 2) << "" << endl;
    os << dashLine << endl;


    word = "|CLASS_NAME";
    wordLength = word.length();
    partLength = 20;
    fillerLength = partLength - wordLength;
    if (fillerLength < 0) {
        fillerLength = 0;
    }
    os << word << setfill('-') << setw(fillerLength) << " ";

    word = "|NAME";
    wordLength = word.length();
    partLength = 20;
    fillerLength = partLength - wordLength;
    if (fillerLength < 0) {
        fillerLength = 0;
    }
    os << word << setfill('-') << setw(fillerLength) << " ";

    word = "|TIME(Sec)";
    wordLength = word.length();
    partLength = 20;
    fillerLength = partLength - wordLength;
    if (fillerLength < 0) {
        fillerLength = 0;
    }
    os << word << setfill('-') << setw(fillerLength) << " ";

    word = "|CALLS";
    wordLength = word.length();
    partLength = 10;
    fillerLength = partLength - wordLength;
    if (fillerLength < 0) {
        fillerLength = 0;
    }
    os << word << setfill('-') << setw(fillerLength) << " ";

    word = "|AVG";
    wordLength = word.length();
    partLength = 10;
    fillerLength = partLength - wordLength;
    if (fillerLength < 0) {
        fillerLength = 0;
    }
    os << word << setfill('-') << setw(fillerLength) << " ";

    word = "|PER%";
    wordLength = word.length();
    partLength = 10;
    fillerLength = partLength - wordLength;
    if (fillerLength < 0) {
        fillerLength = 0;
    }
    os << word << setfill('-') << setw(fillerLength) << " ";
    os << endl;
    os.fill(' '); 
    //os <<right << setw(40)<<"total" << setw(20) << fixed << setprecision(6)
         //<< timer::time_total << setw(10) << 1 << setw(10) 
        //<< scientific << setprecision(2) <<timer::time_total / 1 
        //<< setw(10)<< fixed << setprecision(1) <<100.0 << "%" << endl;
    
    // Record the total elapsed time
    timer::time_total = timer::time_[" #total"];
    map<string, unsigned long long>::iterator itr_1;
    map<string, double>::iterator itr_2;
    for (itr_1 = timer::cnt_.begin(), itr_2 = timer::time_.begin();
        itr_1 != timer::cnt_.end() && itr_2 != timer::time_.end(); 
        ++itr_1, ++itr_2)
    {
        os <<right<<setw(20)<< itr_2->first.substr(0, itr_2->first.find('#'))<< setw(20) 
            << itr_2->first.substr(itr_2->first.find('#') + 1, itr_2->first.length())
            << setw(20) << scientific << setprecision(5) << itr_2->second 
            << setw(10) << itr_1->second
            << setw(10) << scientific<< setprecision(2) << itr_2->second / itr_1->second
            <<setw(10)<< fixed <<setprecision(1)<<itr_2->second/timer::time_total*100<<"%" << endl;
    }
    os << dashLine << endl;
    return os;
}