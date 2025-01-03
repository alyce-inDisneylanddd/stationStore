#include "lib/User.hpp"
#include "lib/Admin.hpp"
#include "lib/Product.hpp"

UserList user;
ProductTree pTree;



void pressKeyToContinue();
void SellerLogin();
void UserLogin();
void SellerMode();
void UserMode();
// for admin
void AddProduct();

int main () {

    pTree.readData_toBST();
    user.loadUserFromFile("db/usrDB.csv");

    string inputID;
    string inputPassword;
    int choice;



    clearScreen();
    cout << "Welcome to Kikono Store!!" << endl;
    while (1) {
        cout << "\n----- Login as -----" << endl;
        cout << "1. Admin" << endl;
        cout << "2. User" << endl;
        cout << "0. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;
        if (choice < 0 || choice > 2) {
            cout << "INVALID CHOICE! Please try again..." << endl;
            pressKeyToContinue();
            clearScreen();
        } else  {
            break;
        }
    }
    switch (choice) {
        case 1: {
            SellerLogin();
            SellerMode();
            break;
        }
        case 2: {
            UserLogin();
            break;
        }
        case 0: {
            clearScreen();
            cout << "Exiting..." << endl;
            return 0;
            break;
        }
        default: {
            cout << "INVALID CHOICE! Please try again..." << endl;
            break;
        }
    }

    return 0;
}

void pressKeyToContinue()
{
    cout << "Press anykey to return...";
    getch();
}

// Admin
void SellerLogin() {
    int choice;
    string inputName;
    string inputPassword;
    int attempt = 2;

    clearScreen();
    while (true) {
        cout << "----- Admin Login Screen ----" << endl;
        cout << "Input Name: ";
        cin >> inputName;
        cout << "Input Password: ";
        cin >> inputPassword;

        if (compare(inputName, inputPassword)) {
            cout << "Login Successful!" << endl;
            clearScreen();
            break;
        } else {
            attempt--;
            if (attempt >= 0) {
                clearScreen();
                cout << "Login Failed! Please try again..." << endl;
                cout << "\nYou have " << attempt + 1 << " attempt(s) left!\n" << endl;
            } else {
                cout << "Login failed! You have run out of attempts to log in." << endl;
                break;
            }
        }
    }

}

void SellerMode() {
    int choice;

    while(1) {
        again:
        cout << "----- SELLER PORTAL -----" << endl;
        cout << "1. View Products" << endl;
        cout << "2. Add Products" << endl;
        cout << "3. Remove Products" << endl;
        cout << "4. View Reports" << endl;
        cout << "5. View Order History" << endl;
        cout << "0. Exit" << endl; // use goto in the main function to get back to login page

        cout << "\nEnter your choice: ";
        cin >> choice;
        if (choice < 0 || choice > 5) {
            cout << "INVALID CHOICE! Please try again..." << endl;
        } else {
            break;
        }
    }

    switch (choice) {
        case 1: {
            pTree.show();
            clearScreen();
            goto again;
            break;
        }
        case 2: {
            AddProduct();
            break;
        }
    }
}
void AddProduct() {
    Product product;

    cout << "Adding new product:" << endl;
    cout << "\nEnter new product information: " << endl;
    
    // ID
    cout << "Product ID: ";
    cin >> product.product_ID;

    // name 
    cout << "Product Name: ";
    cin >> product.product_name;

    // quantity
    cout << "Product Quantity: ";
    cin >> product.product_quantity;

    // price
    cout << "Product Price: ";
    cin >> product.product_price;

    if (pTree.search(product.product_ID)) {
        cout << "ID: " << product.product_ID << endl;
        cout << "Duplicated ID" << endl;
        cout << "Enter again..." << endl;
    } else {
        pTree.add(product);

    }



}




// user
void UserLogin() {
    int choice;
    string inputName;
    string inputPassword;
    int attempt = 2;

    clearScreen();
    while (true) {
        cout << "----- User Login Screen ----" << endl;
        cout << "Input Name: ";
        cin >> inputName;
        cout << "Input Password: ";
        cin >> inputPassword;

        if (user.searchAndCompare(inputName, inputPassword)) {
            cout << "Login Successful!" << endl;
            clearScreen();
            break;
        } else {
            attempt--;
            if (attempt >= 0) {
                clearScreen();
                cout << "Login Failed! Please try again..." << endl;
                cout << "\nYou have " << attempt + 1 << " attempt(s) left!\n" << endl;
            } else {
                cout << "Login failed! You have run out of attempts to log in." << endl;
                break;
            }
        }
    }
}