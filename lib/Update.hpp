#include "Cart.hpp"
#include "Order.hpp"

void updateCheckout(ProductTree &pTree, CartList cart){
    for(auto entry = cart.cartList.begin(); entry != cart.cartList.end(); entry++) {
        int searchID = get<0>(*entry);
        int quantityChange = get<2>(*entry);
        if(pTree.search(searchID)) {
            //cout << "found: " << searchID << " ";
            ProductNode *tmp = pTree.search_node(pTree.getRoot(), searchID);
            //cout << tmp->product.product_name << " old quant: " << tmp->product.product_quantity;
            tmp->product.product_quantity -= quantityChange;
            //cout << " new quant:" << tmp->product.product_quantity << endl;
        } else {
            cout << "not found" << endl;
        }
    }
    // call this to update db pTree.saveProductListToFile(pTree.getRoot());
}

string getTime(){
    auto now = chrono::system_clock::now();
    time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Create a string stream to format the time
    ostringstream timeStream;
    timeStream << std::put_time(std::localtime(&currentTime), "%Y-%m %H:%M");

    // Store the formatted time in a std::string
    string formattedTime = timeStream.str();

    // Output the result
    return formattedTime;

}

void createOrder(OrderList &order, CartList cart, string userName, string timeStamp) {
    int productID;
    string productName;
    int quantity;
    float price, totalPrice;
    timeStamp = getTime();

    for(auto entry = cart.cartList.begin(); entry != cart.cartList.end(); entry++) {
        productID = get<0>(*entry);
        productName = get<1>(*entry);
        quantity = get<2>(*entry);
        price = get<3>(*entry);
        totalPrice = get<4>(*entry);
        order.orderList.push_back(make_tuple(
            userName,
            timeStamp,
            productID,
            productName,
            quantity,
            price,
            totalPrice
        ));
    }
}