#ifndef USER_HPP
#define USER_HPP
#include "cmn.hpp"
#define FILENAME "db/usrDB.csv"

class UserNode
{
private:
    string userName;
    string userPassword;
    UserNode *next;
    UserNode *prev;

    UserNode(string userName, string userPassword)
    {
        this->userName = userName;
        this->userPassword = userPassword;
        next = nullptr;
        prev = nullptr;
    }
    // this is used to let the UserList class access to the attributes in UserNode
    friend class UserList;
};
class UserList {
    private:
        UserNode *head;
        UserNode *tail;
        int length;

    public:
        UserList() {
            head = nullptr;
            tail = nullptr;
            length = 0;
        }

    

        void loadUserFromFile(string filename){
            ifstream loadUser(filename);
            if(!loadUser){
                cout << "Failed to open file" << endl;
                return;
            }
            string line;
            while(getline(loadUser, line)){ 
                stringstream UserInfo(line);
                string UserName, UserPassword;

                if(getline(UserInfo, UserName, ',') &&
                getline(UserInfo, UserPassword, ',')){
                    UserNode* newNode = new UserNode(UserName, UserPassword);
                    if(head == nullptr){
                        head = tail = newNode;
                    }else{
                        tail->next = newNode;
                        newNode->prev = tail;
                        tail = newNode;
                    }
                    length++;
                }
            }
            loadUser.close();
        }    
        bool searchAndCompare(string inputName, string inputPassword){
            UserNode* curr = head;
            while(curr != nullptr){
                if(curr->userName == inputName && curr->userPassword == inputPassword){
                    return true;
                }
                curr = curr->next; // move to next node
            }
            return false;
        }

};
#endif