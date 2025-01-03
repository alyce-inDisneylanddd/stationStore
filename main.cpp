#include "lib/User.hpp"
#include "lib/Admin.hpp"

UserList user;


void pressKeyToContinue();

int main () {

    string inputID;
    string inputPassword;
    int choice;

    user.loadUserFromFile("db/usrDB.csv");

    clearScreen();
    cout << "Welcome to Kikono Store!!" << endl;
    do {
        cout << "\n----- Login as -----" << endl;
        cout << "1. Admin" << endl;
        cout << "2. User" << endl;
        cout << "3. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;
        if (choice <= 0) {
            cout << "Invalid choice!" << endl;
            pressKeyToContinue();
            clearScreen();
        }
    } while (choice <= 0 );
    

    return 0;
}

void pressKeyToContinue()
{
    cout << "Press anykey to return...";
    getch();
}