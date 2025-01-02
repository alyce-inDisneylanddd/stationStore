#ifndef ORDER_HPP
#define ORDER_HPP
#include "lib/cmn.hpp"

class OrderList{
    public:
    list<tuple<string, string, string, string, string>> orderList;
    //<usrName, prdID, prdName, totalPrice, time>
};

#endif 