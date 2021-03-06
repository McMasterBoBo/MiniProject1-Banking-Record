// Banking Record System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class bankingSystem{
    private:
        char accountNum[20];
        char firstName[10];
        char lastName[10];
        float total_Balance;

    public:
        void introduction();
        void dataInput();
        void showData();
        void addRecord();
        void readData();
        void searchRecord();
        void editRecord();
        void deleteRecord();
};

void bankingSystem::introduction() {
    cout << "*** Account Information System ***" << endl;
    cout << "Select one option below" << endl;
    cout << "            1-->Add record to file" << endl;
    cout << "            2-->Show record from file" << endl;
    cout << "            3-->Search record from file" << endl;
    cout << "            4-->Update record " << endl;
    cout << "            5-->Delete record " << endl;
    cout << "            6-->Quit" << endl;
    cout << "Enter your choice: ";

}

void bankingSystem::dataInput() {
     
    cout << "------------------------------------" << endl;
    cout << "Please enter your first name: ";
    cin >> firstName;
    cout << "Please enter your last name: ";
    cin >> lastName;
    cout << "Please enter your account number: ";
    cin >> accountNum;
    cout << "Please enter your account balance: ";
    cin >> total_Balance;
    cout << "Record has been saved !" << endl;
    cout << "------------------------------------" << endl;
}

void bankingSystem::showData()
{
    cout << "First Name: " << firstName << endl;
    cout << "Last Name: " << lastName << endl;
    cout << "Account Number: " << accountNum << endl;
    cout << "Current Balance: $ " << total_Balance << endl;
    cout << "------------------------------------" << endl;
}

void bankingSystem::addRecord() {
    ofstream outfile;
    outfile.open("bankRecord.txt", ios::binary | ios::app);
    dataInput();
    outfile.write(reinterpret_cast<char*>(this), sizeof(*this));
    outfile.close();
}

void bankingSystem::readData() {
    ifstream infile;
    infile.open("bankRecord.txt", ios::binary);
    if (!infile)
    {
        cout << "Error in Opening! File Not Found!!" << endl;
        return;
    }
    cout << "****Data from file****" << endl;
    while (!infile.eof())
    {
        if (infile.read(reinterpret_cast<char*>(this), sizeof(*this)))
        {
            showData();
        }
    }
    infile.close();
}

void bankingSystem::searchRecord() {
    int n;
    int count;
    ifstream infile;
    infile.open("bankRecord.txt", ios::binary);
    if (!infile)
    {
        cout << "Error Message: File Not Found!!" << endl;
        return;
    }
    infile.seekg(0, ios::end);
    count = infile.tellg() / sizeof(*this);
    cout << " There are " << count << " record in the file";
    cout << " Enter Record Number to Search: ";
    cin >> n;
    infile.seekg((n - 1) * sizeof(*this));
    infile.read(reinterpret_cast<char*>(this), sizeof(*this));
    showData();
}

void bankingSystem::editRecord() {
    int n;
    int count;
    fstream iofile;

    iofile.open("bankRecord.txt", ios::in | ios::binary);
    if (!iofile)
    {
        cout << "Error Message: File Not Found!!" << endl;
        return;
    }
    iofile.seekg(0, ios::end);
    count = iofile.tellg() / sizeof(*this);
    cout << "There are " << count << " record in the file";
    cout << "Enter Record Number to edit: ";
    cin >> n;

    iofile.seekg((n - 1) * sizeof(*this));
    iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
    cout << "Record " << n << " has following data" << endl;
    showData();
    iofile.close();

    iofile.open("bankRecord.txt", ios::out | ios::in | ios::binary);
    iofile.seekp((n - 1) * sizeof(*this));
    cout << "Enter data to Modify " << endl;
    dataInput();
    iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
}

void bankingSystem::deleteRecord() {
    int n;
    int count;
    ifstream infile;

    infile.open("bankRecord.txt", ios::binary);
    if (!infile)
    {
        cout << "Error Message: File Not Found!!" << endl;
        return;
    }
    infile.seekg(0, ios::end);
    count = infile.tellg() / sizeof(*this);
    cout << "There are " << count << " record in the file";
    cout << "Enter Record Number to Delete: ";
    cin >> n;

    fstream tmpfile;
    tmpfile.open("tmpFile.txt", ios::out | ios::binary);
    infile.seekg(0);
    for (int i = 0; i < count; i++)
    {
        infile.read(reinterpret_cast<char*>(this), sizeof(*this));
        if (i == (n - 1))
            continue;
        tmpfile.write(reinterpret_cast<char*>(this), sizeof(*this));
    }
    infile.close();
    tmpfile.close();
    remove("bankRecord.txt");
    rename("tmpFile.txt", "bankRecord.txt");
    cout << "The record has been deleted.";
}

int main()
{
    bankingSystem banking;
    int userOption;

    while (true) {
        banking.introduction();
        cin >> userOption;

            switch (userOption) {
            case 1:
                banking.addRecord();
                break;
            case 2:
                banking.showData();
                break;
            case 3:
                banking.searchRecord();
                break;
            case 4:
                banking.editRecord();
                break;
            case 5:
                banking.deleteRecord();
                break;
            case 6:
                cout << "You have exited the system." << endl;
                exit(0);
                break;
            default:
                cout << "Error Message! Please try again!";
                exit(0);
            }
        }

    system("pause");
    return 0;
}

    
    




