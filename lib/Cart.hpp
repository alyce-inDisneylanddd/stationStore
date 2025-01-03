#ifndef CART_HPP
#define CART_HPP

#include "Product.hpp"
class Product;


class CartList{
    public:
    list<tuple<int, string, int, float, float>> cartList;
    //<prouductID, productName, quantity, price, total Price>


    bool search(int inputID) {
        for (auto& entry : cartList) {
            if (get<0>(entry) == inputID) {
                return true;
                break;
            }

        }
        return false;
    }
    void add(int inputID, ProductTree &pTree) {
        
        int quantity;
        if (pTree.search(inputID)) {
            ProductNode *productNode = pTree.search_node(pTree.getRoot(), inputID);
            // check quatity of the product
            do {
                cout << "Input quantity: ";
                cin >> quantity;
                if (quantity <= 0 || quantity > productNode->product.product_quantity) {
                    cout << "Invalid quantity input!" << endl;
                }
            }while (quantity <= 0 || quantity > productNode->product.product_quantity);

            // total price 
            float total = productNode->product.product_price*quantity;

            // add product to cart 
            cartList.push_back(make_tuple(
                productNode->product.product_ID, 
                productNode->product.product_name, 
                quantity,
                productNode->product.product_price, 
                total
            ));
            cout << "Product added to cart sucessfully!" << endl;
            
        } else {
            cout << "The input ID does not exist!" << endl;
        }

    }

    void display_cart() {
        if (cartList.empty()) {
            cout << "Your cart is empty!" << endl;
            return;
        }
        for(int i = 0; i < 94; i++) cout<<"=";
        cout << endl;
        cout << "| " << setw(10) << left << "   ID"
                    << " | " << setw(30) << left << "   Name"
                    << " | " << setw(10) << left << " Quantity"
                    << " | " << setw(14) << " Unit Price"
                    << " | " << setw(14) << " Total Price"
                    << " |\n";
        for(int i = 0; i < 94; i++) cout<<"-";
        cout << endl;                 
        

        for (const auto& entry : cartList) {
            cout << "| " << setw(10) << left << get<0>(entry)
                            << " | " << setw(30) << left << get<1>(entry)
                            << " | " << setw(10) << left  << get<2>(entry)
                            << " | " << setw(14) << get<3>(entry)
                            << " | " << setw(14) << get<4>(entry)
                            << " |\n";

        }

        for(int i = 0; i < 94; i++) cout<<"-";
        cout << endl;  
            
    }

    void display_receipt() {
        float grandTotal = 0;
        if (cartList.empty()) {
            cout << "Your cart is empty!" << endl;
            return;
        }
        for(int i = 0; i < 94; i++) cout<<"=";
        cout << endl;
        cout << "| " << setw(10) << left << "   ID"
                    << " | " << setw(30) << left << "   Name"
                    << " | " << setw(10) << left << " Quantity"
                    << " | " << setw(14) << " Unit Price"
                    << " | " << setw(14) << " Total Price"
                    << " |\n";
        for(int i = 0; i < 94; i++) cout<<"-";
        cout << endl;                 
        

        for (const auto& entry : cartList) {
            grandTotal += get<4>(entry);
            cout << "| " << setw(10) << left << get<0>(entry)
                            << " | " << setw(30) << left << get<1>(entry)
                            << " | " << setw(10) << left  << get<2>(entry)
                            << " | " << setw(14) << get<3>(entry)
                            << " | " << setw(14) << get<4>(entry)
                            << " |\n";

        }

        for(int i = 0; i < 94; i++) cout<<"-";
        cout << endl;  
        cout << "Grand total: " << grandTotal << endl;
            
    }


    void edit(int inputID, ProductTree &pTree) {
        int newQuantity;
        int productQuantity;
        
        for (auto& entry : cartList) {
            if (search(inputID)) {
                ProductNode *productNode = pTree.search_node(pTree.getRoot(), inputID);
                productQuantity = productNode->product.product_quantity;
                
                do {
                    cout << "Enter new quatity(edit): ";
                    cin >> newQuantity;
                    if (newQuantity <= 0 || newQuantity > productQuantity) {
                        cout << "Invalid quantity" << endl;
                    }
                } while (newQuantity <= 0 || newQuantity > productQuantity);

                get<2>(entry) = newQuantity; 
                get<4>(entry) = newQuantity * get<3>(entry);  
                cout << "Quantity updated successfully!" << endl; 
                break;        
            }

        }
        if (search(inputID) == 0) {
            cout << "Input ID not found!" << endl;
        }
    }

    void remove(int inputID) {
        for (auto entry = cartList.begin(); entry != cartList.end(); entry++) {
            if (search(inputID)) {
                cartList.erase(entry);
                cout << "Product deleted successfully!" << endl; 
                break;        
            }

        }
        if (!search(inputID)) {
            cout << "Input ID not found!" << endl;
        }
    }



};


#endif 