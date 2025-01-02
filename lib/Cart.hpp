#ifndef CART_HPP
#define CART_HPP
// #include "lib/cmn.hpp"
#include "Product.hpp"

class CartList{
    public:
    list<tuple<int, string, int, float, float>> cartList;
    //<prouductID, productName, quantity, price, total Price>


    void add(int inputID, ProductTree &pTree) {
        
        int quantity;
        if (pTree.search(inputID)) {
            ProductNode *productNode = pTree.search_node(pTree.getRoot(), inputID);
            // check quatity of the product
            do {
                cout << "Input quantity: ";
                cin >> quantity;
                if (quantity > productNode->product.product_quantity) {
                    cout << "Invalid quantity input!" << endl;
                }
            }while (quantity <= 0);

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
    //    cout << get<0>(entry) <<", " << get<1>(entry) <<", "<< get<2>(entry) <<", " << get<3>(entry) <<", " << get<4>(entry) << endl;
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
};


#endif 