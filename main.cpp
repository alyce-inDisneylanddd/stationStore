#include "lib/User.hpp"
#include "lib/Admin.hpp"
#include "lib/Product.hpp"
#include "lib/Order.hpp"
#include "lib/Cart.hpp"
#include "lib/Update.hpp"

UserList user;
ProductTree pTree;
OrderList order;
CartList cart;



void pressKeyToContinue();
void SellerLogin();
void UserLogin();
void SellerMode();
void UserMode();

// for admin
void AddProduct();

// for user
void checkoutCart();

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
            break;
        }
        case 2: {
            // UserLogin();
            UserMode();
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
            SellerMode();
            break;
        } else {
            attempt--;
            if (attempt >= 0) {
                clearScreen();
                cout << "Login Failed! Please try again..." << endl;
                cout << "\nYou have " << attempt + 1 << " attempt(s) left!\n" << endl;
            } else {
                cout << "Login failed! You have run out of attempts to log in." << endl;
                return;
            }
        }
    }

}

void SellerMode() {
    int choice;
    int inputID;

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
            // display product
            pTree.show();
            clearScreen();
            goto again;
            break;
        }
        case 2: {
            // add new product
            AddProduct();
            pressKeyToContinue();
            clearScreen();
            goto again;
            break;
        }
        case 3: {
            // remove product
            pTree.showToSelect();
            delete_again:
            cout << "\nInput ID to delete: ";
            cin >> inputID;
            if (pTree.search(inputID)) {
                pTree.remove(inputID);
                cout << "ID <" << inputID << "> deleted successfully!" << endl;
            } else {
                cout << "Invalid ID! Please enter again..." << endl;
                goto delete_again;
            }
            pressKeyToContinue();
            clearScreen();
            goto again;
            break;           
        }
        case 4: {
            // view report
            
        }
        case 5: {
            // view order history
            order.readFromDB();
            order.print();
        }
    }
}

void AddProduct() {
    Product product;
    clearScreen();
    again:
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
        cout << "\nID: " << product.product_ID << endl;
        cout << "Duplicated ID" << endl;
        cout << "Press anykey to enter again...";
        getch();
        clearScreen();
        goto again;
    } else {
        cout << "Product added successfully!" << endl;
        pTree.add(product);
    }
}




void UserMode() {
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

    int inputID;
    int choice_1;

    while(1) {
        again:
        cout << "----- USER PORTAL -----" << endl;
        cout << "1. Add item to Cart" << endl;
        cout << "2. Checkout" << endl;
        cout << "3. Edit cart" << endl;
        cout << "4. Remove items from cart" << endl;
        cout << "0. Exit" << endl;

        cout << "\nEnter your choice: ";
        cin >> choice;
        if (choice < 0 || choice > 4) {
            cout << "INVALID CHOICE! Please try again..." << endl;
        } else {
            break;
        }
    }

    switch (choice) {
        case 1: {
            // add product to cart
            pTree.showToSelect();
            while (1) {
                enterID:
                cout << "\nSelect product by ID: " << endl;
                cout << "Input ID: ";
                cin >> inputID;
                if (pTree.search(inputID)) {
                    if (!cart.search(inputID)) {
                        cart.add(inputID, pTree);
                        clearScreen();
                        break;
                    } else {
                        cout << "\nThis item already exited in the cart\nGo to edit mode to update your item." << endl;
                        pressKeyToContinue();
                        clearScreen();
                        break;
                    }
                } else {
                    cout << "Invalid ID! Please enter again..." << endl;
                }
            }

            while (1) {
                addMore:
                cout << "1. Add more product" << endl;
                cout << "2. View current item in cart" << endl;
                cout << "0. Exit" << endl;
                cout << "\nEnter your choice: ";
                cin >> choice_1;
                if (choice < 0 || choice > 2) {
                    cout << "INVALID CHOICE! Please try again..." << endl;
                } else {
                    break;
                }
            }

            if (choice_1 == 1) {
                clearScreen();
                goto enterID;
            } else if (choice_1 == 2) {
                clearScreen(); 
                cout << "\n----- Display items in cart -----\n" << endl;
                cart.display_cart();
                pressKeyToContinue();
                clearScreen();
                goto again;
            } else if (choice_1 == 0) {
                clearScreen();
                goto again;
                break;           
            } else {
                cout << "Invalid input! Please try again..." << endl;
                goto addMore;

            }
        }

        case 2: {
            // checkout
            checkout:
            clearScreen();
            cout << "----- YOUR CART -----" << endl;
            cart.display_cart();
            cout << "1. Purchase now" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice_1;
            if (choice_1 == 1) {
                createOrder(order, cart, inputName, getTime());
                order.print();
                updateCheckout(pTree, cart);
                goto again;
            } else if (choice_1 == 0) {
                clearScreen();
                goto again;
                break;
            } else {
                cout << "Invalid input! Please try again..." << endl;
                goto checkout;
            }
            break;
           
        }

        case 0: {

        }
    }
}

// void checkoutCart () {
//     order.
// }