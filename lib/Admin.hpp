#ifndef ADMIN_HPP
#define ADMIN_HPP
#include "cmn.hpp"

    string adminName = "kikonoStore";
    string adminPassword = "1234";

    void compare(string inputName, string inputPassword) {
        if (inputName == adminName && inputPassword == adminPassword) {
            cout << "Login Successfully!" << endl;
        } else {
            cout << "fail" << endl;

        }

    }



#endif 