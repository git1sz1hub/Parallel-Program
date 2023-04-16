#include "MAT_DEMO.h"
#include "TIMER.h"
#include<iostream>
#include<iomanip>
#include<string>
#include<cassert>
#include<time.h>
#include<limits.h>
#include<cstdlib>
#include<cfloat>
#include<cblas.h>
#include<lapacke.h>
using namespace std;

// Default constructor for matrix class
Mat_Demo::Mat_Demo()
{
	timer::tick("Mat_Demo", "Constructor1");
	timer::tick("Mat_Demo", "Constructor1");
}
//Copy Constructor for matrix class
Mat_Demo::Mat_Demo(const Mat_Demo& s)
{
	this->nrows = s.nr();
	this->ncols = s.nc();
	// Assert that the number of rows and columns of the matrix are both greater than 0
	assert(nrows > 0);
	assert(ncols > 0);

	if (nrows && ncols) // If the number of rows and columns are both greater than 0
	{
		// Dynamically allocate an array of type double, size is nrows*ncols, used to store matrix data
		this->d = new double[nrows * ncols];
		for (int i = 0; i < nrows * ncols; ++i)
		{
			this->d[i] = s.d[i]; // Initialize each element the same as the Matrix s
		}
	}
}
//Constructor for matrix class, initializes the matirx according to the number of rows, columns, and a pointer
Mat_Demo::Mat_Demo(
	const int& nrows_in,
	const int& ncols_in,
	double* d_in)
{
	this->nrows = nrows_in;
	this->ncols = ncols_in;
	// Assert that the number of rows and columns of the matrix are both greater than 0
	assert(nrows > 0);
	assert(ncols > 0);
	assert(d_in != NULL);
	this->d = new double[nrows * ncols];
	for (int i = 0; i < nrows * ncols; ++i)
	{
		this->d[i] = d_in[i]; // Initialize each element in the array to zero
	}
}
// Constructor for matrix class, initializes the number of rows and columns of the matrix and initial values (optional)
Mat_Demo::Mat_Demo(
	const int& nrows_in, // number of rows in the matrix
	const int& ncols_in, // number of columns in the matrix
	const bool flag_zero // whether to initialize matrix to zero
)
{
	this->nrows = nrows_in;
	this->ncols = ncols_in;
	// Assert that the number of rows and columns of the matrix are both greater than 0
	assert(nrows > 0);
	assert(ncols > 0);

	if (nrows && ncols) // If the number of rows and columns are both greater than 0
	{
		// Dynamically allocate an array of type double, size is nrows*ncols, used to store matrix data
		this->d = new double[nrows * ncols];

		if (flag_zero) // If initialization to zero is required
		{
			for (int i = 0; i < nrows * ncols; ++i)
			{
				this->d[i] = 0.0; // Initialize each element in the array to zero
			}
		}
	}
}

// Destructor for matrix class, used to release dynamically allocated memory
Mat_Demo::~Mat_Demo()
{
	if (this->d) // If array d is not empty
	{
		delete[]this->d; // Release the dynamically allocated memory
		this->d = nullptr;
	}
}

// Get the number of columns in the matrix
int Mat_Demo::nc(void)const
{
	return this->ncols;
}

// Get the number of rows in the matrix
int Mat_Demo::nr(void)const
{
	return Mat_Demo::nrows;
}

//Initialize using different methods
void Mat_Demo::init(string& s)
{
	timer::tick("Mat_Demo", "init");
	if (s == "zero")
	{
		this->zero();
	}
	else if (s == "random")
	{
		this->random();
	}
	else if (s == "one")
	{
		this->one();
	}
	timer::tick("Mat_Demo", "init");
}
// Set each element in the matrix to zero
void Mat_Demo::zero()
{
	for (int i = 0; i < this->nrows; ++i)
	{
		for (int j = 0; j < this->ncols; ++j)
		{
			d[i * this->ncols + j] = 0; // Set the element in the ith row and jth column of the matrix to zero
		}
	}
	return;
}

// Set each element in the matrix to zero, but the number of rows and columns can be specified
void Mat_Demo::zero(
	const int& nrows_in, // number of rows in the matrix
	const int& ncols_in // number of columns in the matrix
)
{
	for (int i = 0; i < nrows_in; ++i) // Traverse each row
	{
		for (int j = 0; j < ncols_in; ++j) // Traverse each column
		{
			// Set the element in the ith row and jth column of the matrix to zero
			d[i * this->ncols + j] = 0; 
		}
	}
	return;
}

// Set each element of the matrix to 1
void Mat_Demo::one()
{
	for (int i = 0; i < this->nrows; ++i)
	{
		for (int j = 0; j < this->ncols; ++j)
		{
			// Set the element in the ith row and jth column of the matrix to one
			d[i * this->ncols + j] = 1.0;
		}
	}
	return;
}

// Set each element of the matrix randomly
void Mat_Demo::random()
{
	srand(std::time(NULL));
	for (int i = 0; i < this->nrows; ++i)
	{
		for (int j = 0; j < this->ncols; ++j)
		{
			// Set the element in the ith row and jth column of the matrix randomly between 0 and 1
			d[i * this->ncols + j] = static_cast<double>(std::rand()) / RAND_MAX; 
		}
	}
	return;
}
// Definition of operator *=, used for scalar multiplication of a matrix
void Mat_Demo::operator*=(const double& s)
{
	timer::tick("Mat_Demo", "operator*=");
	// Iterate over each row
	for (int i = 0; i < this->nrows; ++i)
	{
		// Iterate over each column
		for (int j = 0; j < this->ncols; ++j)
		{
			// Multiply the element at the i-th row and j-th column by s
			d[i * this->ncols + j] *= s;
		}
	}
	timer::tick("Mat_Demo", "operator*=");
	return;
}

// Definition of operator =, used for matrix assignment
Mat_Demo& Mat_Demo::operator=(const Mat_Demo& s)
{
	timer::tick("Mat_Demo", "operator=");
	// Assert that matrix s has the same number of columns as the current matrix
	assert(s.nc() == this->nc());
	// Assert that matrix s has the same number of rows as the current matrix
	assert(s.nr() == this->nr());
	// Iterate over all elements
	for (int i = 0; i < nrows * ncols; ++i)
	{
		// Assign the current matrix's element to the corresponding element of matrix s
		this->d[i] = s.d[i];
	}
	timer::tick("Mat_Demo", "operator=");
	return *this;
}

// Definition of operator (), used for accessing elements of the matrix
double& Mat_Demo::operator()(int r, int c)
{
	// Return the element at the r-th row and c-th column
	return this->d[r * this->ncols + c];
}

// Definition of operator +, used for matrix addition
Mat_Demo Mat_Demo::operator+(const Mat_Demo& s)
{
	timer::tick("Mat_Demo", "operator+");
	// Assert that matrix s has the same number of columns as the current matrix
	assert(s.nc() == this->nc());
	// Assert that matrix s has the same number of rows as the current matrix
	assert(s.nr() == this->nr());
	Mat_Demo temp(s.nr(),s.nc(),true);
	for (int i = 0; i < this->nrows * this->ncols; ++i)
	{
		// Add the corresponding elements of the current matrix and matrix s
		temp.d[i] = this->d[i] + s.d[i];
	}
	timer::tick("Mat_Demo", "operator+");
	return temp;
}

// Definition of operator -, used for matrix subtraction
Mat_Demo Mat_Demo::operator-(const Mat_Demo& s)
{
	timer::tick("Mat_Demo", "operator-");
	// Assert that matrix s has the same number of columns as the current matrix
	assert(s.nc() == this->nc());
	// Assert that matrix s has the same number of rows as the current matrix
	assert(s.nr() == this->nr());
	Mat_Demo temp(s.nr(), s.nc(), true);
	for (int i = 0; i < this->nrows * this->ncols; ++i)
	{
		// Subtract the corresponding elements of matrix s from the current matrix
		temp.d[i] = this->d[i] - s.d[i];
	}
	timer::tick("Mat_Demo", "operator-");
	return temp;
}
// Definition of operator *, used for matrix multiplation
Mat_Demo Mat_Demo::operator*(const Mat_Demo& s)
{
	timer::tick("Mat_Demo", "operator*");
	// Assert that matrix s's number of rows is the same as the current matrix's number of columns
	assert(s.nr() == this->nc());

	Mat_Demo temp(this->nr(), s.nc(), true);
	double temp_sum = 0;
	for (int k = 0; k < this->nr(); ++k)
	{
		for (int j = 0; j < s.nc(); ++j)
		{
			temp_sum = 0;
			for (int i = 0; i < this->nc(); ++i)
			{
				temp_sum += this->d[k * this->nc() + i] * s.d[i * s.nc() + j];
			}
			temp.d[k * temp.nc() + j] = temp_sum;
		}
	}
	timer::tick("Mat_Demo", "operator*");
	return temp;
}
//Calaulate the matirx using different methods
void Mat_Demo::cal(string& s)
{
	timer::tick("Mat_Demo", "cal");
	cout << "--------------------------------------------" << endl;
	cout << "------------Result of Calculation-----------" << endl;
	cout << "--------------------------------------------" << endl;
	if (s == "max")
	{
		cout << "The max number of the matrix is: " << this->max() << endl;
	}
	else if (s == "min")
	{
		cout << "The min number of the matrix is: " << this->min() << endl;
	}
	timer::tick("Mat_Demo", "cal");
}
// Definition of member function max, used for finding the maximum element of the matrix
double Mat_Demo::max()
{
	double max = -DBL_MAX;
	for (int i = 0; i < this->nrows * this->ncols; ++i)
	{
		// Update max if the current element is greater than max
		if (max < d[i])
		{
			max = d[i];
		}
	}
	return max;
}
// Definition of member function min, used for finding the minimum element of the matrix
double Mat_Demo::min()
{
	double min = DBL_MAX;
	for (int i = 0; i < this->nrows * this->ncols; ++i)
	{
		// Update min if the current element is less than min
		if (min > d[i])
		{
			min = d[i];
		}
	}
	return min;
}
//Decide if a Matirx is RSM
bool Mat_Demo::isRSM()
{
	if (this->nc() != this->nr())return false;
	for (int i = 0; i < this->nr(); ++i)
	{
		for (int j = i + 1; j < this->nr(); ++j)
		{
			if ((d[i * this->nc() + j] - d[j * this->nc() + i]) > 1e-9)return false;
		}
	} 
	return true;
}
void Mat_Demo::blas_matmul(const Mat_Demo& mat_1, const Mat_Demo& mat_2, const Mat_Demo& result)
{
	timer::tick("Mat_Demo", "blas_matmul");
	cblas_dgemm(
	    CblasRowMajor,
		CblasNoTrans,
		CblasNoTrans,
		result.nr(), result.nc(), mat_1.nc(), 1.0, 
	    mat_1.d, mat_1.nc(), mat_2.d, mat_2.nc(), 0.0, result.d, result.nc());
	timer::tick("Mat_Demo", "blas_matmul");
}
ostream& Mat_Demo::lapack_diago(ostream& os, const Mat_Demo mat_1)
{
	double *w=new double[mat_1.nc()];
	timer::tick("Mat_Demo", "lapack_diago");
	int flag = LAPACKE_dsyev(LAPACK_ROW_MAJOR,'V','U',
		mat_1.nr(), mat_1.d, mat_1.nr(), w);
	timer::tick("Mat_Demo", "lapack_diago");
	assert(flag == 0);
	os << scientific << setprecision(4);
	os << "Eigenvalues:"<< endl;
	for (int i = 0; i < mat_1.nc(); i++) {
		os << setw(12) << right << w[i];
	}
	os << endl;
	os << "Eigenvectors :" << endl;
	for (int i = 0; i < mat_1.nc(); i++) {
		for (int j = 0; j < mat_1.nc(); j++) {
			os << setw(12) << right << mat_1.d[i * mat_1.nc() + j];
		}
		os << endl;
	}
	return os;
}
ostream& operator<<(ostream& os, const Mat_Demo& demo)// Overloaded the operator << , for outputting the information about the matrix
{
	//timer::tick("Mat_Demo", "operator<<");
	os << "--------------------------------------------" << endl;
	os << "--------------Print the Matrix--------------" << endl;
	os << "--------------------------------------------" << endl;
	os <<"row:" << demo.nr() 
		<< "      col:" << demo.nc() << endl; // Output the column and rol's information
	os << scientific << setprecision(4);
	for (int i = 0; i < demo.nr(); ++i)
	{
		for (int j = 0; j < demo.nc(); ++j)
		{
			os << setw(12) << demo.d[i * demo.nc() + j]; // Output all the elements of the matrix
		}
		os << endl;
	}
	//timer::tick("Mat_Demo", "operator<<");
	return os;
}