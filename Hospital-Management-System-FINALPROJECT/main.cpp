#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

// Definition of Struct (Doctor)
struct Doctor
{
    int doctorID;
    string firstName;
    string lastName;
    string branch;
    string phone;
    int roomNumber;
    int yearsExperience;
};

// Dynamic array expanded function
Doctor* expandArray(Doctor* oldArray, int beforeExpanded, int afterExpanded)
{
    Doctor* newArray = new Doctor[afterExpanded];
    for (int i = 0; i < beforeExpanded; i++)
    {
        newArray[i] = oldArray[i];
    }
    delete[] oldArray;
    return newArray;
}

// save doctor information to the file
void saveToFile(Doctor doctors[], int count)
{
    ofstream outFile("doctors.txt");
    for (int i = 0; i < count; i++) {
        outFile << doctors[i].doctorID << endl
                << doctors[i].firstName << endl
                << doctors[i].lastName << endl
                << doctors[i].branch << endl
                << doctors[i].phone << endl
                << doctors[i].roomNumber << endl
                << doctors[i].yearsExperience << endl;
    }
    outFile.close();
}

// load doctor information from the file
int loadFromFile(Doctor*& doctors, int& capacity)
{
    ifstream inFile("doctors.txt");
    int count = 0;
    if (inFile.is_open())
        {
        while (inFile >> doctors[count].doctorID)
            {
            inFile.ignore();
            getline(inFile, doctors[count].firstName);
            getline(inFile, doctors[count].lastName);
            getline(inFile, doctors[count].branch);
            getline(inFile, doctors[count].phone);
            inFile >> doctors[count].roomNumber;
            inFile >> doctors[count].yearsExperience;
            count++;

            // Capacity control and expansion. Expand the array if capacity is exceeded.
            if (count >= capacity)
                {
                int afterExpanded = capacity * 2;
                doctors = expandArray(doctors, capacity, afterExpanded);
                capacity = afterExpanded;
                cout << "Array expanded to " << capacity << endl;
            }
        }
        inFile.close();
    }
    return count;
}

void editSingleRow(Doctor doctors[], int place, int count);
int findRow(int searchType, string query, Doctor doctors[], int count);
void menu();
int insertNewRow(Doctor*& doctors, int& capacity, int count);
void displayTable(Doctor doctors[], int count);
int deleteRow(Doctor doctors[], int place, int count);

int main()
{
    int capacity = 1;
    Doctor* doctors = new Doctor[capacity];

    int count = loadFromFile(doctors, capacity);

    bool running = true;
    while (running)
    {
        unsigned int process;
        cout << "-----------Welcome to the Hospital system----------" << endl;
        menu();
        bool validInput = false;
        do
        {
            cout << "Please enter your process: " << endl;
            if (cin >> process)
            {
                validInput = true;
            }
            else
            {
                cout << "Invalid input! Numbers only between 1 to 4.\n";
                cin.clear();
                cin.ignore(1000,'\n');
            }
        } while (!validInput);

        switch (process)
        {
            case 1:
                count = insertNewRow(doctors, capacity, count);
                saveToFile(doctors, count);
            break;
            case 2:
                {
                    int searchType;
                    string query;
                    cout << "Select search type:" << endl;
                    cout << "1. ID\n2. First Name\n3. Last Name\n4. Branch\n5. Phone\n6. Room Number\n";
                    cout << "Choice: ";
                    cin >> searchType;

                    cout << "Enter the value to search: ";
                    if (searchType == 4)
                    {
                        cin.ignore();
                        getline(cin, query);
                    }
                    else
                    {
                        cin >> query;
                    }
                    count = findRow(searchType, query, doctors, count);
                    saveToFile(doctors, count);
                }
            break;
            case 3:
                displayTable(doctors, count);
            break;
            case 4:
                cout << "Exiting from the system...";
                running = false;
            break;
            default:
                cout << "Invalid input!" << endl;
        }
        cout << endl;
    }
    delete[] doctors;
    return 0;
}

// Display menu options
void menu()
{
    cout << "1- Add new doctor"<<endl;
    cout << "2- Find the doctor "<<endl;
    cout << "3- List all the doctors"<<endl;
    cout << "4- Exit"<<endl;
}

//deleting row (doctor information)
int deleteRow(Doctor doctors[], int place, int count)
{
    for (int j = place; j < count-1; j++)
    {
        doctors[j] = doctors[j+1];
    }
    return count-1;
}

//add a new doctor
int insertNewRow(Doctor*& doctors, int& capacity, int count)
{
    if (count >= capacity) {    //capacity check
        int afterExpanded = capacity * 2;
        doctors = expandArray(doctors, capacity, afterExpanded);
        capacity = afterExpanded;
    }

    int doctorID2, roomNumber2, yearsExperience2;
    string firstName2, lastName2, phone2, branch2;
    bool check;

    //check unique id
    do
    {
        bool validInput = false;
        do
        {
            cout << "Please enter doctor ID: ";
            if (cin >> doctorID2)
            {
                validInput = true;
                cin.ignore();
            }
            else
            {
                cout << "You shall not enter a letter, Numbers only\n";
                cin.clear();
                cin.ignore(1000,'\n');
            }
        } while (!validInput);

        check = false;
        for (int i = 0; i < count; i++)
        {
            if (doctors[i].doctorID == doctorID2)
            {
                cout << "You cannot assign the same ID to 2 doctors!\n";
                check = true;
                break;
            }
        }
    } while (check);

    doctors[count].doctorID = doctorID2;

    cout << "Please enter doctor's first name: ";
    getline(cin, firstName2);
    doctors[count].firstName = firstName2;

    cout << "Please enter doctor's last name: ";
    getline(cin, lastName2);
    doctors[count].lastName = lastName2;

    cout << "Please enter doctor's branch: ";
    getline(cin, branch2);
    doctors[count].branch = branch2;

    cout << "Please enter doctor's phone (write without gap): ";
    cin >> phone2;
    doctors[count].phone = phone2;

    bool validInput2 = false;
    do
    {
        cout << "Please enter doctor's room number: ";
        if (cin >> roomNumber2)
        {
            validInput2 = true;
            cin.ignore();
        }
        else
        {
            cout << "You shall not enter a letter, Numbers only\n";
            cin.clear();
            cin.ignore(1000,'\n');
        }
    } while (!validInput2);
    doctors[count].roomNumber = roomNumber2;

    do
    {
        validInput2 = false;
        cout << "Please enter doctor's years of experience: ";
        if (cin >> yearsExperience2)
        {
            validInput2 = true;
            cin.ignore();
        }
        else
        {
            cout << "You shall not enter a letter, Numbers only\n";
            cin.clear();
            cin.ignore(1000,'\n');
        }
    } while (!validInput2);

    doctors[count].yearsExperience = yearsExperience2;
    cout << "Doctor Successfully Added" << endl;
    count++;
    return count;
}

// edit single doctor information
void editSingleRow(Doctor doctors[], int place, int count)
{
    bool check;
    int doctorID2, roomNumber2, yearsExperience2;
    string firstName2, lastName2, phone2, branch2;

    do
    {
        bool validInput = false;
        do
        {
            cout << "Please enter Doctor ID: ";
            if (cin >> doctorID2)
            {
                validInput = true;
                cin.ignore();
            }
            else
            {
                cout << "You shall not enter a letter, Numbers only\n";
                cin.clear();
                cin.ignore(1000,'\n');
            }
        } while (!validInput);

        check = false;
        for (int i = 0; i < count; i++)        //check if doctor id is already used by another doctor
        {
            if (i != place && doctorID2 == doctors[i].doctorID)
            {
                cout << "You cannot assign the same ID to 2 doctors!\n";
                check = true;
                break;
            }
        }
    } while (check);

    doctors[place].doctorID = doctorID2;

    cout << "Please enter doctor's first name: ";
    getline(cin, firstName2);
    doctors[place].firstName = firstName2;

    cout << "Please enter doctor's last name: ";
    getline(cin, lastName2);
    doctors[place].lastName = lastName2;
    cin.ignore();

    cout << "Please enter doctor's branch: ";
    getline(cin, branch2);
    doctors[place].branch = branch2;

    cout << "Please enter doctor's phone (write without gap): ";
    cin >> phone2;
    doctors[place].phone = phone2;

    bool validInput3 = false;
    do
    {
        cout << "Please enter doctor's room number: ";
        if (cin >> roomNumber2)
        {
            validInput3 = true;
        }
        else
        {
            cout << "You shall not enter a letter, Numbers only\n";
            cin.clear();
            cin.ignore(1000,'\n');
        }
    } while (!validInput3);
    doctors[place].roomNumber = roomNumber2;

    validInput3 = false;
    do
    {
        cout << "Please enter doctor's years of experience: ";
        if (cin >> yearsExperience2)
        {
            validInput3 = true;
        }
        else
        {
            cout << "You shall not enter a letter, Numbers only\n";
            cin.clear();
            cin.ignore(1000,'\n');
        }
    } while (!validInput3);

    doctors[place].yearsExperience = yearsExperience2;
    cout << "Successfully Changed!" << endl;
}

//display all doctors in a table
void displayTable(Doctor doctors[], int count)
{
    cout << "\n" << left
         << setw(6)  << "ID"
         << setw(15) << "First Name"
         << setw(15) << "Last Name"
         << setw(20) << "Branch"
         << setw(15) << "Phone"
         << setw(8)  << "Room"
         << "Experience" << endl;
    cout << "--------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < count; i++)
    {
        cout << left
             << setw(6)  << doctors[i].doctorID
             << setw(15) << doctors[i].firstName
             << setw(15) << doctors[i].lastName
             << setw(20) << doctors[i].branch
             << setw(15) << doctors[i].phone
             << setw(8)  << doctors[i].roomNumber
             << doctors[i].yearsExperience << endl;
    }
}

//search the doctor and process action (edit, delete, exit)
int findRow(int searchType, string query, Doctor doctors[], int count)
{
    int place;
    bool found = false;
    for (int i = 0; i < count; i++)
    {
        bool isMatch = false;

        switch (searchType)
        {
            case 1:
                if (to_string(doctors[i].doctorID) == query)
                    isMatch = true;
                break;
            case 2:
                if (doctors[i].firstName == query)
                    isMatch = true;
                break;
            case 3:
                if (doctors[i].lastName == query)
                    isMatch = true;
                break;
            case 4:
                if (doctors[i].branch == query)
                    isMatch = true;
                break;
            case 5:
                if (doctors[i].phone == query)
                    isMatch = true;
                break;
            case 6:
                if (to_string(doctors[i].roomNumber) == query)
                    isMatch = true;
                break;
            default:
                cout << "Invalid search type." << endl;
                return count;
        }

        if (isMatch)
        {
            found = true;
            int progress;

            // display all information
            cout << "\n--- Doctor Found ---" << endl;
            cout << "ID: " << doctors[i].doctorID << endl;
            cout << "First Name: " << doctors[i].firstName << endl;
            cout << "Last Name: " << doctors[i].lastName << endl;
            cout << "Branch: " << doctors[i].branch << endl;
            cout << "Phone: " << doctors[i].phone << endl;
            cout << "Room Number: " << doctors[i].roomNumber << endl;
            cout << "Years of Experience: " << doctors[i].yearsExperience << endl;
            cout << "--------------------\n" << endl;

            cout << "1 - Edit ------------ 2 - Delete ------------ 3 - Exit\n";
            cout << "Enter your choice: ";
            cin >> progress;
            place = i;

            switch (progress)
            {
                case 1:
                    editSingleRow(doctors, place, count);
                    break;
                case 2:
                    return deleteRow(doctors, place, count);
                case 3:
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
            }
            break;
        }
    }
    if (!found)
        cout << "Record not found!" << endl;
    return count;
}