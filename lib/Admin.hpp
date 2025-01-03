#ifndef ADMIN_HPP
#define ADMIN_HPP
#include "cmn.hpp"

    string adminName = "kikonoStore";
    string adminPassword = "1234";

    bool compare(string inputName, string inputPassword) {
        if (inputName == adminName && inputPassword == adminPassword) {
            return true;
        }
        return false;
    }
    
#endif 