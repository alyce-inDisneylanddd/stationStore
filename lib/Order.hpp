#ifndef ORDER_HPP
#define ORDER_HPP
#include "cmn.hpp"

class OrderList{
    public:
    list<tuple<string, string, int, string, int, float, float>> orderList;
    //<usrName, time,prdID, prdName, quantity, price, totalPrice>

    //read/write to file

    void readFromDB() {
        ifstream file("db/orderDB.csv");
        if(!file.is_open()) {
            cout << "unable to open file" << endl;
            return;
        }
        string line, token;
        string userName, timeStamp, productName;
        int productId, quantity;
        float price, totalPrice;
        while(getline(file,line)) {
            stringstream ss(line);
            //get userName
            getline(ss, userName, ',');
            //get timeStamp
            getline(ss, timeStamp, ',');
            //get productId
            getline(ss, token, ',');
            productId = stoi(token);
            //get prouductName
            getline(ss, productName, ',');
            //get quantity
            getline(ss, token, ',');
            quantity = stoi(token);
            //get price
            getline(ss, token, ',');
            price = stof(token);
            //get totalPrice
            getline(ss, token, ',');
            totalPrice = stof(token);

            orderList.push_back(make_tuple(
                userName,
                timeStamp,
                productId,
                productName,
                quantity,
                price,
                totalPrice
            ));
        }
    }

    void writeOrderToDB() {
        ofstream file("db/orderDB.csv");
        if(!file.is_open()) {
            cout << "orderDB not found" << endl;
            return;
        }
        cout << endl << "==writing order to db==" << endl;
        for(auto entry = orderList.begin(); entry != orderList.end(); entry++) {
            file<< get<0>(*entry) <<","
                << get<1>(*entry) <<","
                << get<2>(*entry) <<","
                << get<3>(*entry) <<","
                << get<4>(*entry) <<","
                << get<5>(*entry) <<","
                << get<6>(*entry) <<endl;
        }

    }


    void print(){
        for(auto entry = orderList.begin(); entry != orderList.end(); entry++) {
            cout<< get<0>(*entry) << ", "
                << get<1>(*entry) << ", "
                << get<2>(*entry) << ", "
                << get<3>(*entry) << ", "
                << get<4>(*entry) << ", "
                << get<5>(*entry) << ", "
                << get<6>(*entry) << endl;
        }
    }

    void view(){
        list<tuple<string, string, int, string, int, float, float>>::iterator listIt;
        string navKey;
        const int entryPerPage = 10;
        int totalEntry = orderList.size();
        int totalPage = (totalEntry/entryPerPage) + 1;
        int currentPage = 1;
        int lower = 0;
        int k = 0;
        while(1){
            clearScreen();
        }
    }
};

#endif 