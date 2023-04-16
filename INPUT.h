#ifndef INPUT_H 
#define INPUT_H
#include<string>
#include<iostream>
#include<fstream>
using namespace std;
class Input
{
public:
	Input();
	~Input();
	void init(const string& fn);

	string cal; // calculation type
	string mat_typ; // matrix type
	int timer_prt; // timer print type
	int res_prt; // result print type.
	string fn_1; // the file path of matrix 1 
	string fn_2; // the file path of matrix 2
	double* d[2]; // Pointer for storing matrix data
	int nc[2];
	int nr[2];
private:
	void read_Input(const string& fn); // Read in the parameters
	void read_Mat(const string& fn, int id); // Read in the matrix
};
#endif