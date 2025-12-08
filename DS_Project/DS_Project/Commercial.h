#pragma once
#ifndef COMMERCIAL_H
#define COMMERCIAL_H

#include "../DS_Project/HashTable.h"
#include "../DS_Project/Graph.h"
#include <iostream>
using namespace std;

class Product {
public:
    string productName;
    string category;
    int price;
    string mallName;

    Product(string name, string cat, int p, string mall)
        : productName(name), category(cat), price(p), mallName(mall) {
    }

    string toString() {
        return productName + "|" + category + "|" + to_string(price) + "|" + mallName;
    }
};

class Mall {
public:
    string mallName;
    string sector;
    int shops;

    Mall(string name, string sec, int s) : mallName(name), sector(sec), shops(s) {}
};

class CommercialModule {
private:
    Mall* malls[50];
    int mallCount;

    Product* products[1000];
    int productCount;

    HashTable mallRegistry;
    HashTable productByName;
    HashTable productByCategory;
    Graph mallNetwork;

    void parseProductData(string data) {
        string tokens[4];
        int tokenCount = 0;
        string temp = "";

        for (int i = 0; i < data.length(); i++) {
            if (data[i] == '|') {
                tokens[tokenCount++] = temp;
                temp = "";
            }
            else {
                temp += data[i];
            }
        }
        tokens[tokenCount++] = temp;

        if (tokenCount >= 4) {
            cout << "Product: " << tokens[0] << "\n";
            cout << "Category: " << tokens[1] << "\n";
            cout << "Price: Rs." << tokens[2] << "\n";
            cout << "Mall: " << tokens[3] << "\n";
        }
    }

public:
    CommercialModule() : mallCount(0), productCount(0) {
        for (int i = 0; i < 50; i++) malls[i] = nullptr;
        for (int i = 0; i < 1000; i++) products[i] = nullptr;
    }

    ~CommercialModule() {
        for (int i = 0; i < mallCount; i++) {
            delete malls[i];
        }
        for (int i = 0; i < productCount; i++) delete products[i];
    }

    void registerMall(string name, string sector, int shops) {
        if (mallCount >= 50) {
            cout << "Mall limit reached!\n";
            return;
        }

        Mall* newMall = new Mall(name, sector, shops);
        malls[mallCount++] = newMall;

        mallRegistry.insert(name, sector + "|" + to_string(shops));
        mallNetwork.addVertex(name);

        cout << "Registered mall: " << name << " (" << sector << ") with " << shops << " shops\n";
    }

    void addProduct(string productName, string category, int price, string mallName) {
        if (productCount >= 1000) {
            cout << "Product limit reached!\n";
            return;
        }

        Product* newProduct = new Product(productName, category, price, mallName);
        products[productCount++] = newProduct;

        productByName.insert(productName, newProduct->toString());

        string existing = productByCategory.search(category);
        if (existing == "") {
            productByCategory.insert(category, productName + "@" + mallName);
        }
        else {
            productByCategory.insert(category, existing + ";" + productName + "@" + mallName);
        }

        cout << "Added product: " << productName << " (" << category << ") - Rs." << price << " at " << mallName << "\n";
    }

    void searchProductByName(string productName) {
        string result = productByName.search(productName);

        if (result != "") {
            cout << "Product Found \n";
            parseProductData(result);
        }
        else {
            cout << "Product '" << productName << "' not found!\n";
        }
    }

    void searchProductsByCategory(string category) {
        string result = productByCategory.search(category);

        if (result == "") {
            cout << "No products found in category: " << category << "\n";
            return;
        }

        cout << "Products in " << category << "\n";

        string current = "";
        int count = 1;
        for (int i = 0; i <= result.length(); i++) {
            if (i == result.length() || result[i] == ';') {
                if (current != "") {
                    int atPos = current.find('@');
                    if (atPos != string::npos) {
                        string prodName = current.substr(0, atPos);
                        string mall = current.substr(atPos + 1);
                        cout << count++ << ". " << prodName << " at " << mall << "\n";
                    }
                    current = "";
                }
            }
            else {
                current += result[i];
            }
        }
    }

    void connectMalls(string mall1, string mall2, int distance) {
        mallNetwork.addEdge(mall1, mall2, distance);
    }

    void findNearestMall(string fromLocation, string toMall) {
        mallNetwork.FindShortestPath(fromLocation, toMall);
    }

    void listAllMalls() {
        if (mallCount == 0) {
            cout << "No malls registered.\n";
            return;
        }

        cout << "Registered Malls:\n";
        for (int i = 0; i < mallCount; i++) {
            cout << (i + 1) << ". " << malls[i]->mallName
                << " (" << malls[i]->sector << ") - "
                << malls[i]->shops << " shops\n";
        }
    }

    void listAllProducts() {
        if (productCount == 0) {
            cout << "No products registered.\n";
            return;
        }

        cout << "All Product:\n";
        for (int i = 0; i < productCount; i++) {
            cout << (i + 1) << ". " << products[i]->productName << " (" << products[i]->category << ") - Rs." << products[i]->price << " at " << products[i]->mallName << "\n";
        }
    }
};

#endif // COMMERCIAL_H