#ifndef MAT_DEMO_H
#define MAT_DEMO_H

#include<iostream> 
#include<string>
using namespace std; 
class Mat_Demo
{
public:
	// Functions for getting number of rows and columns of matrix
	int nr(void)const;
	int nc(void)const;
	double* d = nullptr; // Pointer for storing matrix data
	// Default constructor of matrix class
	Mat_Demo();
	//Constructor for matrix class, initializes the matirx according to another matirx
	Mat_Demo(const Mat_Demo& s);
	//Constructor for matrix class, initializes the matirx according to the number of rows, columns, and a pointer
	Mat_Demo(
		const int& nrows_in,
		const int& ncols_in,
		double* d_in);
	// Constructor of matrix class to initialize the number of rows, columns, and initial values
	Mat_Demo(
		const int& nrows_in,
		const int& ncols_in,
		const bool flag_zero = true);

	// Destructor of matrix class to release dynamically allocated memory space
	~Mat_Demo();

	//Initialize using different methods
	void init(string& s);

	// Set each element of the matrix to 0
	void zero();

	// Set each element of the matrix to 0, but rows and columns can be specified
	void zero(
		const int& nrows_in,
		const int& ncols_in
	);

	// Set each element of the matrix to 1
	void one();

	// Set each element of the matrix randomly
	void random();

	// Overloaded operator *= for matrix scalar multiplication
	void operator*=(const double& s);
	
	// Overloaded operator = for matrix assignment
	Mat_Demo& operator=(const Mat_Demo& s);

	// Overloaded operator () for matrix element-wise assignment
	double& operator()(int r, int c);

	// Overloaded operator + for matrix addition
	Mat_Demo operator+(const Mat_Demo& s);

	// Overloaded operator - for matrix subtraction
	Mat_Demo operator-(const Mat_Demo& s);

	// Overloaded operator * for matrix multiplation
	Mat_Demo operator*(const Mat_Demo& s);

	//Calaulate the matirx using different methods
	void cal(string& s);

	//Decide if a Matirx is RSM
	bool isRSM();
	// Member function to find the maximum element in the matrix
	double max();

	// Member function to find the minimum element in the matrix
	double min();
	static void blas_matmul(const Mat_Demo& mat_1, const Mat_Demo& mat_2, const Mat_Demo& result);
	static ostream& lapack_diago(ostream& os, const Mat_Demo mat_1);
private:
	int nrows = 0; // Number of rows of the matrix
	int ncols = 0; // Number of columns of the matrix
};

// Overloaded operator << for printing matrix information
ostream& operator<<(ostream& os, const Mat_Demo& demo);

#endif