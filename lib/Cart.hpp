#ifndef CART_HPP
#define CART_HPP
// #include "lib/cmn.hpp"
#include "Product.hpp"

class CartList{
    public:
    list<tuple<int, string, int, float, float>> cartList;
    //<prouductID, productName, quantity, price, total Price>

    void add (int inputID) {
        ProductTree product;
        
        int quantity;
        if (product.search(inputID)) {
            ProductNode *productNode = product.search_node(product.getRoot(), inputID);
            // check quatity of the product
            do {
                cout << "Input quantity: ";
                cin >> quantity;
                if (quantity < productNode->product.product_quantity) {
                    cout << "Invalid quantity input!" << endl;
                }
            }while (quantity <= 0);

            // total price 
            float total = productNode->product.product_price*quantity;

            // add product to cart 
            cartList.push_back(make_tuple(
                productNode->product.product_ID, 
                productNode->product.product_name, 
                productNode->product.product_quantity,
                productNode->product.product_price, 
                total
            ));

            // update product quatity
            productNode->product.product_quantity -= quantity;
            product.saveProductListToFile(product.getRoot());

            cout << "Product added to cart sucessfully!" << endl;
            

        } else {
            cout << "The input ID does not exist!" << endl;
        }

    }
};


#endif 