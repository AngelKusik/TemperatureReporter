/**
* Author(s): Angelica Kusik
             Filip Kostov
* Date: March 22, 2022
* Description: Lab 4 - Arrays and Pointers
**/

#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

//Function Declarations:
/**
*This function prompts the user to enter the number of days that they wish to enter temperatures for and validates it.
**/
int getNumberOfDays(const int, const int);
/**
*This function prompts the user to enter a temperature for a number of days, validates
*the input and add it to an array of temperatures.
**/
void getTemperature(const double, const double, int, double []);
/**
*This function converts a celsius temperature to fahrenheit.
**/
inline double ConvertCelsiusToFahrenheit(double *celsius) {return ((*celsius * 1.8) + 32); }
/**
*This function prints the celsius and corresponding fahrenheit temperatures (the output of the program).
**/
void printTemperatures(double *, int);


int main()
{
    //Variable Declarations:
    int numberOfDays;
    const int MINIMUMDAYS = 1; // User must enter temperatures for at least one day
    const int MAXIMUMDAYS = 365; // user must enter temperatures for up to 365 days.
    const double MAXTEMPERATURE = 60.00; //Maximum temperature registered on earth
    const double MINTEMPERATURE = -90.00; //Minimum temperature registered on earth

    //GET INPUT & VALIDATION
    //Display the title of the application.
	cout << "        LAB-4        " << endl
	     << "=====================" << endl
	     << fixed << setprecision(2);

    //Use the getNumberOfDays functions to prompt the user to enter the number of days
    //that a temperature will be entered.
    //The function will also be used to validate the input.
    numberOfDays = getNumberOfDays(MAXIMUMDAYS, MINIMUMDAYS);

    //Once a valid number of days is entered use a try & catch to address other errors that might occur.
    try
    {
        //Use the numberOfDays input to create a new array using a pointer.
        double *temperatures = new double[numberOfDays];

        //Display the title of the application.
        cout << "\nTEMPERATURE REPORTER" << endl
	         << "====================" << endl;

        //Prompt the user to enter the temperatures and validate it using the  getTemperature function
        cout << "\nPlease enter the temperature for each day." << endl;

        //Call the function to get the temperature input, validate it and add it to the array
        getTemperature(MAXTEMPERATURE, MINTEMPERATURE, numberOfDays, temperatures);

        //PROCESSING
        //Display the output title
        cout << "\nDAILY TEMPERATURE REPORT" << endl
	         << "========================" << endl;

        //call the printTemperatures function to process and print the output.
        printTemperatures(temperatures, numberOfDays);

        //Freed the memory allocated for the new[] operator and delete the pointer.
        delete[] temperatures;

    }
    catch(bad_alloc &ex) //If the memory allocation fails at run-time thow a bad_alloc exception..
    {
        cerr << ex.what() << endl //And inform the user what happened.
        << "\nError allocating memory." << endl;
    }
    catch(...) //If something else goes wrong, could be anything
    {
        cerr << "\nAn exception has occurred, ending program..." << endl; //Display a generic error message to the user
    }

    cout << endl <<endl;

    return 0;
}
//end of the program

/**
* FUNCTIONS
**/

int getNumberOfDays(const int MAXDAYS, const int MINDAYS)
{
    bool inputIsValid = false;
    int daysInput;

    while(!inputIsValid) //while input is not valid
    {
        //Prompt the user to enter the number of days they wish to enter temperatures for.
        cout << "How many days do you wish to enter?  ";
        cin >> daysInput;
        //Read the value entered by the user until a numeric value is entered.

        if(cin.fail())
        {
            //If input is not numeric...
            cin.clear(); //Reset the fail() state of the cin object.
            cin.sync(); //Clear the buffer
            cout << "\nInvalid input. Please try again and enter a numeric value." << endl;; //Tell user what went wrong.

        }
        //Now check if numberOfDays is in an acceptable range.
        else if (daysInput < MINDAYS || daysInput > MAXDAYS)
        {
            cout << "\nInvalid input. Please try again and enter a value between " << MINDAYS << " and " << MAXDAYS << "." << endl;
        }
        else //If the input is numeric and within the range end the loop and carry on.
        {
            inputIsValid = true;
        }
    }

    return daysInput;
}

void getTemperature (const double MAXTEMP, const double MINTEMP, int days, double temperatures[])
{

    double temperatureInput;
    int i;
    bool inputIsValid = false;

    //Prompt the user to enter the temperatures for each day
    for (i=0; i<days; i++)
    {
        inputIsValid = false;
        //Prompt the user to enter the temperature for the day.
        cout << "\nCelsius temperature for day " << i+1 <<": ";
        cin >> temperatureInput;

        //Read the value entered by the user until a numeric value is entered.
        while(!inputIsValid) //while input is not valid
        {

            if(cin.fail())
            {
                //If input is not numeric...
                cin.clear(); //Reset the fail() state of the cin object.
                cin.sync(); //Clear the buffer
                cout << "\nInvalid input. Please try again and enter a numeric value." << endl;; //Tell user what went wrong.

                //Prompt the user to enter the temperature for the day again.
                cout << "\nCelsius temperature for day " << i+1 <<": ";
                cin >> temperatureInput;

            }
            //Now check if temperatureInput is in an acceptable range.
            else if (temperatureInput < MINTEMP || temperatureInput > MAXTEMP)
            {
                cerr << "\nInvalid input. Please try again and enter a value between " << MINTEMP << " and " << MAXTEMP << "." << endl;

                //Prompt the user to enter the temperature for the day again.
                cout << "\nCelsius temperature for day " << i+1 <<": ";
                cin >> temperatureInput;
            }
            else //If the input is numeric and within the range end the loop and carry on.
            {
                inputIsValid = true;

            }

        }
        //Add the valid temperature to the array;
        temperatures[i] = temperatureInput;
    }
}

void printTemperatures(double *ptrTemperatures, int days)
{
    int i;
    const char DEGREE_SYMBOL = (char)248; // ASCII degree symbol
    //print the values in the array
    for (i=0;i<days;i++)
    {
        cout << "Day: " << i+1 << right << setw(10) << ConvertCelsiusToFahrenheit(ptrTemperatures + i) << DEGREE_SYMBOL <<"F";
        cout << right<< setw(10) << *(ptrTemperatures + i) << DEGREE_SYMBOL <<"C" << endl;
    }
}



