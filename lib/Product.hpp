#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include "cmn.hpp"

class Cart; 


struct Product
{
    int product_ID;
    string product_name;
    int product_quantity;
    float product_price;
    
};

struct ProductNode {
    Product product;
    ProductNode *left;
    ProductNode *right;
};

class ProductTree{
    public:
    ProductNode *root;
    int treeSize;


    //Constructor
    ProductTree() {
        root = nullptr;
        treeSize = 0;
    }

    ProductNode *getRoot() {
        return this->root;
    }

    //Operation on Tree: insert, edit, delete, search

    //insert
    ProductNode *insert(ProductNode *root, const Product &product)
    {
        if (root == NULL)
        {
            root = new ProductNode;
            root->product = product;
            root->left = NULL;
            root->right = NULL;
        }
        else if (product.product_ID > root->product.product_ID)
        { // go right
            root->right = insert(root->right, product);
        }
        else if (product.product_ID < root->product.product_ID)
        { // go left
            root->left = insert(root->left, product);
        }
        return root;
    }
    // edit
    ProductNode *edit_node(ProductNode *root, int inputID) {
        if(root == nullptr){
            cout << "input does not exist" << endl;
            return root;
        } else if (inputID > root->product.product_ID)
        { // go right
            root->right = edit_node(root->right, inputID);
        }
        else if (inputID < root->product.product_ID)
        { // go left
            root->left = edit_node(root->left, inputID);
        } 
        if(inputID == root->product.product_ID) {
            cout << "found a node with input ID" << endl;
            cout << "enter new quantity: ";
            cin >> root->product.product_quantity; 
            cout << "enter new price: ";
            cin >> root->product.product_price; 
            cout << "update completed" << endl;
            
        }
        return root;
    }


    //delete
    ProductNode *delete_node(ProductNode *root, int delete_id)
    {
        if (root == NULL)
        {
            return root;
        }
        if (delete_id < root->product.product_ID)
        {
            root->left = delete_node(root->left, delete_id);
        }
        else if (delete_id > root->product.product_ID)
        {
            root->right = delete_node(root->right, delete_id);
        }
        else
        {
            // node with 1 child
            if (root->left == nullptr && root->right == nullptr)
            {
                return nullptr;
            }
            else if (root->left == nullptr)
            {
                return root->right;
            }
            else if (root->right == nullptr)
            {
                return root->left;
            }
            else
            {
                // node that has 2 children
                ProductNode *temp = minValue(root->right);
                root->product.product_ID = temp->product.product_ID;
                root->right = delete_node(root->right, temp->product.product_ID);
            }
        }

        return root;
    }

    ProductNode *minValue(ProductNode *min)
    {
        ProductNode *temp = min;
        while (temp != nullptr && temp->left != nullptr)
        {
            temp = temp->left;
        }
        return temp;
    }

    ProductNode* search_node(ProductNode* root, int inputID) {
        if (root == nullptr || root->product.product_ID == inputID) {
            return root;
        }

        if (inputID > root->product.product_ID) {
            return search_node(root->right, inputID);
        } else {
            return search_node(root->left, inputID);
        }
    }


    //Functions for main

    // view product 
    void view() {
        int i = 1;
        inOrder_traversal(root,i);
    }
    // add product
    void add(const Product &product) {
        this->root  = insert(root, product);
        treeSize++;
        saveProductListToFile(root);
    }
    bool search(int inputID){
        return search_node(root, inputID);
    }
    //edit product
    void edit(int inputID) {
        this ->root = edit_node(root, inputID);
        saveProductListToFile(root);
    }

    // remove product
    void remove(int inputID) {
        this -> root = delete_node(root, inputID);
        treeSize--;
        saveProductListToFile(root);
    }



    //Operation: load data to tree, save tree to file

    //load data from file to tree
    void readData_toBST()
    {
        fstream productList_file;
        productList_file.open("db/productList.csv", ios::in);

        // check if the file is existed
        if (!productList_file)
        {
            cout << "Cannot open file!" << endl;
            return;
        }

        string text;

        // skip header of the csv file
        getline(productList_file, text);

        while (getline(productList_file, text))
        {
            stringstream ss(text);
            Product product;
            string token;

            // get ID of product
            getline(ss, token, ',');
            product.product_ID = stoi(token); // convert from string to interger

            // get product name
            getline(ss, product.product_name, ',');

            // get product quantity
            getline(ss, token, ',');
            product.product_quantity = stoi(token);

            // get product price
            getline(ss, token, ',');
            product.product_price = stof(token);

            add(product);
        }
        productList_file.close();
    }


    void writeToFile(ProductNode *node, fstream &file)
    {
        if (node == nullptr)
        {
            return;
        }

        writeToFile(node->left, file);
        file << node->product.product_ID << ","
             << node->product.product_name << ","
             << node->product.product_quantity << ","
             << node->product.product_price << "\n";
        writeToFile(node->right, file);
    }

    void saveProductListToFile(ProductNode *root)
    {

        fstream file("db/productList.csv", ios::out);
        if(!file) {
            cout << endl << "fail to open productList.csv" << endl;
        }

        file << "ID,Product Name,Quantity,Price (USD)\n";
        writeToFile(root, file);
        file.close();
    }


    void inOrder_traversal(ProductNode *root, int &number)
    {

        if (root != NULL)
        {
            inOrder_traversal(root->left, number);
            cout << "| " << setw(10) << left << root->product.product_ID
                     << " | " << setw(5) << left << number
                     << " | " << setw(30) << left << root->product.product_name
                     << " | " << setw(10) << root->product.product_quantity
                     << " | " << setw(14) << root->product.product_price
                     << " |\n";
            number++;
            inOrder_traversal(root->right, number);
        }
    }

    void printPage(ProductNode *root, int& count, int start, int end) {
        if(!root) return;

        printPage(root->left, count, start, end);
        if(count >= start && count < end) {
            cout << "| " << setw(10) << left << root->product.product_ID
                     << " | " << setw(5) << left << count+1
                     << " | " << setw(30) << left << root->product.product_name
                     << " | " << setw(10) << root->product.product_quantity
                     << " | " << setw(14) << root->product.product_price
                     << " |\n";
        }
        count++;
        if(count >= end) return;
        printPage(root->right, count, start, end);
    }

    int countNodes (ProductNode *root) {
        if(root == nullptr) return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }

    void show() {
        const int itemPerPage = 5;
        int totalNodes = countNodes(root);
        int totalPages = (totalNodes + itemPerPage - 1) / itemPerPage;
        int currentPage = 0;
        while(1) {
            clearScreen();
            int start = currentPage * itemPerPage;
            int end = start + itemPerPage;
            int count = 0;
            cout << "== Product list ==" << endl;
            cout << "Page " << currentPage+1 << " of " << totalPages << endl;
            cout << "Total products: " << totalNodes << endl;
            for(int i = 0; i < 85; i++) cout<<"=";
            cout << endl;
            cout << "| " << setw(10) << left << "   ID"
                     << " | " << setw(5) << left << " No."
                     << " | " << setw(30) << left << "   Name"
                     << " | " << setw(10) << " Quantity"
                     << " | " << setw(14) << " Price $"
                     << " |\n";
            for(int i = 0; i < 85; i++) cout<<"-";
            cout << endl;
            printPage(root, count, start, end);
            for(int i = 0; i < 85; i++) cout<<"-";
            cout << endl;
            cout << "Previous page: <-, Next page: ->, Back: q" << endl;
            string navInput = readNav();
            if (navInput == "exit") {
                break;
            } else if (navInput == "left") {
                if (currentPage > 0) currentPage--;
            } else if (navInput == "right") {
                if (currentPage < totalPages - 1) currentPage++;
            }
        }
    }

    void showToSelect() {
        const int itemPerPage = 5;
        int totalNodes = countNodes(root);
        int totalPages = (totalNodes + itemPerPage - 1) / itemPerPage;
        int currentPage = 0;
        while(1) {
            clearScreen();
            int start = currentPage * itemPerPage;
            int end = start + itemPerPage;
            int count = 0;
            cout << "== Product list ==" << endl;
            cout << "Page " << currentPage+1 << " of " << totalPages << endl;
            cout << "Total products: " << totalNodes << endl;
            for(int i = 0; i < 85; i++) cout<<"=";
            cout << endl;
            cout << "| " << setw(10) << left << "   ID"
                     << " | " << setw(5) << left << " No."
                     << " | " << setw(30) << left << "   Name"
                     << " | " << setw(10) << " Quantity"
                     << " | " << setw(14) << " Price $"
                     << " |\n";
            for(int i = 0; i < 85; i++) cout<<"-";
            cout << endl;
            printPage(root, count, start, end);
            for(int i = 0; i < 85; i++) cout<<"-";
            cout << endl;
            cout << "Previous page: <-, Next page: ->, Select: q" << endl;
            string navInput = readNav();
            if (navInput == "exit") {
                break;
            } else if (navInput == "left") {
                if (currentPage > 0) currentPage--;
            } else if (navInput == "right") {
                if (currentPage < totalPages - 1) currentPage++;
            }
        }
    }

    // void updateCheckout(CartList cartList) {

    // }

};

#endif 