#ifndef CART_HPP
#define CART_HPP
#include "lib/cmn.hpp"

class CartList{
    public:
    list<tuple<int, string, int, float, float>> cartList;
    //<prouductID, productName, quantity, price, total Price>
};

#endif 