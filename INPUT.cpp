#include "INPUT.h"
#include "TIMER.h"
#include<iostream>
#include<algorithm>
#include<limits>
#include<iomanip>
#include<string>
#include<cassert>
#include<time.h>
#include<limits.h>
#include<cstdlib>
#include <cfloat>
using namespace std;

Input::Input()
{
    this->timer_prt = -1; 
    this->res_prt = -1;
    this->d[0] = nullptr;
    this->d[1] = nullptr;
    this->nc[0] = -1;
    this->nc[1] = -1; 
    this->nr[0] = -1; 
    this->nr[1] = -1;
}
Input:: ~Input()
{
    if (this->d[0]) // If array d[0] is not empty
    {
        delete[]d[0]; // Release the dynamically allocated memory
        d[0] = nullptr;
    }
    if (this->d[1]) // If array d[1] is not empty
    {
        delete[]d[1]; // Release the dynamically allocated memory
        d[1] = nullptr;
    }
}
void Input::init(
	const string& fn
)
{
    //timer::tick("Input", "init");
	read_Input(fn); // Read in the parameters
    read_Mat(this->fn_1, 0); // Read in the first matrix
    if (this->cal == "matmul")
    {
        read_Mat(this->fn_2, 1); // Read in the first matrix
    }
    //timer::tick("Input", "init");
}

void Input::read_Input(const string& fn)
{
	ifstream ifs(fn);
	if (!ifs)
	{
		cout << "Cannot find the input file" << endl;
		exit(0);
	}
	string temp;
	int flag[6] = { 0 }; // Declare an bool array to keep track of which fields have been read.
    int max_Loop = 100; // Set a max number for loop times
    while (max_Loop > 0)
    {
        max_Loop--;
        if (ifs.eof()) // Check if the end of file has been reached.
        {
            ifs.seekg(0); // Move the file pointer to the beginning of the file.
        }
        ifs >> temp;
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower); // Convert the string to lowercase.
        if (temp.find('#') != std::string::npos) // Check if the string contains a comment.
        {
            ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line.
        }
        else if (temp == "calculation" && !flag[0]) // Check if the string is the calculation type field.
        {
            ifs >> temp; // Read the calculation type.
            if (temp.find('#') != std::string::npos) // If # is read accidentally 
            {
                temp = temp.substr(0, temp.find('#')); // Cut the notation part off
                ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line.
            }
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower); // Convert the calculation type to lowercase.
            assert(temp == "matmul" || temp == "rsmdiago");
            this->cal = temp;
            ++flag[0]; // Set the flag for the calculation type field to indicate that it has been read.
        }
        else if (temp == "matrix_type" && !flag[1]) // Check if the string is the matrix type field.
        {
            ifs >> temp; // Read the matrix type.
            if (temp.find('#') != std::string::npos) // If # is read accidentally 
            {
                temp = temp.substr(0, temp.find('#')); // Cut the notation part off
                ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line.
            }
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower); // Convert the matrix type to lowercase.
            assert(temp == "file");
            this->mat_typ = temp;
            ++flag[1]; // Set the flag for the matrix type field to indicate that it has been read.
        }
        else if (temp == "result_print" && !flag[2]) // Check if the string is the matrix print type field.
        {
            ifs >> temp; // Read the matrix print type.
            if (temp.find('#') != std::string::npos) // If # is read accidentally 
            {
                temp = temp.substr(0, temp.find('#')); // Cut the notation part off
                ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line.
            }
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower); // Convert the matrix type to lowercase.
            assert(temp == "1" || temp == "0");
            this->res_prt = stoi(temp);
            ++flag[2]; // Set the flag for the matrix print type field to indicate that it has been read.
        }
        else if (temp == "timer_print" && !flag[3]) // Check if the string is the timer print type.
        {
            ifs >> temp; // Read the number of rows.
            if (temp.find('#') != std::string::npos) // If # is read accidentally 
            {
                temp = temp.substr(0, temp.find('#')); // Cut the notation part off
                ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line.
            }
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower); // Convert the matrix type to lowercase.
            assert(temp == "1" || temp == "0");
            this->timer_prt = stoi(temp);
            ++flag[3]; 
        }
        else if (temp == "matrix_1" && !flag[4]) // Check if the string is the path of matrix 1.
        {
            getline(ifs, temp); // Read the number of columns.
            if (temp.find('#') != std::string::npos) // If # is read accidentally 
            {
                temp = temp.substr(0, temp.find('#')); // Cut the notation part off
            }
            while (temp.find(' ') != std::string::npos) // If redundant space is read accidentally
            {
                temp.erase(temp.find(' '), temp.find(' ') + 1);
            }
            //transform(temp.begin(), temp.end(), temp.begin(), ::tolower); // Convert the matrix type to lowercase.
            this->fn_1 = temp;
            ++flag[4];
        }
        else if (temp == "matrix_2" && !flag[5]) // Check if the string is the path of matrix 1.
        {
            getline(ifs, temp); // Read the number of columns.
            if (temp.find('#') != std::string::npos) // If # is read accidentally 
            {
                temp = temp.substr(0, temp.find('#')); // Cut the notation part off
                ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line.
            }
            while (temp.find(' ') != std::string::npos) // If redundant space is read accidentally
            {
                temp.erase(temp.find(' '), temp.find(' ') + 1);
            }
            //transform(temp.begin(), temp.end(), temp.begin(), ::tolower); // Convert the matrix type to lowercase.
            this->fn_2 = temp;
            ++flag[5];
        }
        if (flag[0] && flag[1] && flag[2] && flag[3] && flag[4] && flag[5])// If all the parameters have been read
        {
            break;// break the while loop
        }
        if (flag[0] && flag[1] && flag[2] && flag[3] && flag[4] && this->cal == "RSMdiago")// If all the parameters needed have been read
        {
            break;// break the while loop
        }
    }
    ifs.close();// Close the file

}
void Input::read_Mat(const string& fn, int id)
{
    string val_typ;
    ifstream ifs(fn);
    if (!ifs)
    {
        cout << "Cannot find the matrix file" << " " << id + 1 << endl;
        exit(0);
    }
    string temp;
    int flag[4] = { 0 }; // Declare an bool array to keep track of which fields have been read.
    int max_Loop = 100; // Set a max number for loop times
    while (max_Loop > 0)
    {
        max_Loop--;
        if (ifs.eof()) // Check if the end of file has been reached.
        {
            ifs.seekg(0); // Move the file pointer to the beginning of the file.
        }
        ifs >> temp;
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower); // Convert the string to lowercase.
        if (temp.find('#') != std::string::npos) // Check if the string contains a comment.
        {
            ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line.
        }
        else if (temp == "nrows:" && !flag[0]) // Check if the string is the rows' number.
        {
            ifs >> temp; 
            if (temp.find('#') != std::string::npos) // If # is read accidentally 
            {
                temp = temp.substr(0, temp.find('#')); // Cut the notation part off
                ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line.
            }
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower); // Convert the calculation type to lowercase.
            assert(stoi(temp) > 0);
            nr[id] = stoi(temp);
            ++flag[0]; 
        }
        else if (temp == "ncols:" && !flag[1]) // Check if the string is the columns' number.
        {
            ifs >> temp;
            if (temp.find('#') != std::string::npos) // If # is read accidentally 
            {
                temp = temp.substr(0, temp.find('#')); // Cut the notation part off
                ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line.
            }
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower); // Convert the calculation type to lowercase.
            assert(stoi(temp) > 0);
            nc[id] = stoi(temp);
            ++flag[1]; 
        }
        else if (temp == "type:" && !flag[2]) // Check if the string is the matrix value type.
        {
            ifs >> temp; // Read the matrix value type.
            if (temp.find('#') != std::string::npos) // If # is read accidentally 
            {
                temp = temp.substr(0, temp.find('#')); // Cut the notation part off
                ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line.
            }
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower); // Convert the matrix type to lowercase.
            assert(temp == "double");
            val_typ = temp;
            ++flag[2]; 
        }
        else if (temp == "value:" && !flag[3]) // Check if the string is the value.
        {
                this->d[id] = new double[nr[id] * nc[id]];
                for (int i = 0; i < nr[id]; ++i)
                {
                    for (int j = 0; j < nc[id]; ++j)
                    {
                        ifs >> temp;
                        if (temp.find(',') != std::string::npos) // If # is read accidentally 
                        {
                            temp = temp.substr(0, temp.find('#')); // Cut the redundant part off
                        }
                        assert(stod(temp) != 0.0 && !temp.empty());
                        this->d[id][i * nc[id] + j] = stod(temp);
                    }
                }
                ++flag[3];
        }
        if (flag[0] && flag[1] && flag[2] && flag[3])// If all the parameters have been read
        {
            break;// break the while loop
        }
    }
    ifs.close();// Close the file
}