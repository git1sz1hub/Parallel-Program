#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include "MAT_DEMO.h"
#include "INPUT.h"
#include "TIMER.h"
#include <cassert>
#include <cmath>
using namespace std;


double norm2_diff(double a[], double b[], int len)
{
	double sum = 0;
	assert(len > 0);
	for (int i = 0; i < len; i++)
	{
		sum += pow(a[i] - b[i], 2);
	}
	return pow(sum, 0.5);
}
int main(int argc, char* argv[]) // Get file names form command lines
{
	timer timer;
	timer::tick(" ", "total");

	Input input; // Initialize the Input class
	string fn = argv[1]; // The input file name 
	string fn_out = argv[2]; // The output file name
	input.init(fn); // Read in the parameters and open files for matirxes
	ofstream ofs(fn_out);
	if (!ofs)
	{
		cout << "Cannot find the output file" << endl;
		exit(0);
	}
	Mat_Demo mat_1(input.nr[0], input.nr[0],input.d[0]); // Initialize the matrix by input
	if (input.cal == "matmul")
	{
		Mat_Demo mat_2(input.nr[1], input.nr[1],input.d[1]);
		Mat_Demo result_1 = mat_1 * mat_2;
		Mat_Demo result_2(result_1.nr(), result_1.nc());
		Mat_Demo::blas_matmul(mat_1, mat_2, result_2);
		// Write into file
		ofs << scientific << setprecision(9);
		ofs << "L2 norm difference between results of two methods: " << norm2_diff(result_1.d, result_2.d, result_1.nc()*result_1.nr()) << endl;
		ofs << result_1 << endl;
		ofs << result_2 << endl;
        // Print to the screen
		if (input.res_prt == 1)
		{
			cout << scientific << setprecision(9);
	     	cout << "L2 norm difference between results of two methods: " 
			<< norm2_diff(result_1.d, result_2.d, result_1.nc()*result_1.nr()) << endl;
			cout << result_1 << endl;
		    cout << result_2 << endl;
		}
	}
	else
	{
		if (mat_1.isRSM())
		{
			Mat_Demo::lapack_diago(ofs,mat_1); // Write into file
			if (input.res_prt == 1)
		    {
				Mat_Demo::lapack_diago(cout,mat_1); // Print to the screen
			}
		}
		else
		{
			cout << "mat_1 is not a real symmetric matrix" << endl;
		}
	}
	timer::tick(" ", "total");
	if (input.timer_prt == 1)
		{
			cout << timer; // Print the Elapsed Time Information
		}
	ofs << timer; // Wrtie the time information to the output file

	return 0;
}
