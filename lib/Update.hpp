#include "Cart.hpp"

void updateCheckout(ProductTree &pTree, CartList cart){
    for(auto entry = cart.cartList.begin(); entry != cart.cartList.end(); entry++) {
        int searchID = get<0>(*entry);
        int quantityChange = get<2>(*entry);
        if(pTree.search(searchID)) {
            // cout << "found: " << searchID << " ";
            ProductNode *tmp = pTree.search_node(pTree.getRoot(), searchID);
            // cout << tmp->product.product_name << " old quant: " << tmp->product.product_quantity;
            tmp->product.product_quantity -= quantityChange;
            // cout << " new quant:" << tmp->product.product_quantity << endl;
        } else {
            cout << "not found" << endl;
        }
    }
    //pTree.saveProductListToFile(pTree.getRoot());
}