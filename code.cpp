#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class Product {
public:
    int productID;
    string name;
    float price;
    int stock;

    void addProduct() {
        cout << "Enter Product ID: ";
        cin >> productID;
        cout << "Enter Product Name: ";
        cin >> name;
        cout << "Enter Product Price: ";
        cin >> price;
        cout << "Enter Product Stock: ";
        cin >> stock;
    }

    void displayProduct() {
        cout << setw(10) << productID << setw(20) << name << setw(10) << price << setw(10) << stock << endl;
    }
};

void addProductToFile() {
    ofstream file;
    file.open("products.txt", ios::app);
    if (!file) {
        cout << "Error in opening file!" << endl;
        return;
    }

    Product p;
    p.addProduct();
    file << p.productID << " " << p.name << " " << p.price << " " << p.stock << endl;
    file.close();
    cout << "Product added successfully!" << endl;
}

void displayProducts() {
    ifstream file("products.txt");
    if (!file) {
        cout << "Error in opening file!" << endl;
        return;
    }

    Product p;
    cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Stock" << endl;
    while (file >> p.productID >> p.name >> p.price >> p.stock) {
        p.displayProduct();
    }
    file.close();
}

void generateBill() {
    ifstream file("products.txt");
    if (!file) {
        cout << "Error in opening file!" << endl;
        return;
    }

    Product p;
    int productID, quantity;
    float total = 0;

    cout << "Enter Product ID and Quantity (-1 to stop):" << endl;

    while (true) {
        cout << "Product ID: ";
        cin >> productID;

        if (productID == -1) break;

        cout << "Quantity: ";
        cin >> quantity;


        file.clear();
        file.seekg(0, ios::beg);

        bool found = false;
        while (file >> p.productID >> p.name >> p.price >> p.stock) {
            if (p.productID == productID) {
                if (p.stock >= quantity) {
                    total += p.price * quantity;
                    cout << "Added " << p.name << " (Qty: " << quantity << ") to bill." << endl;
                    found = true;
                } else {
                    cout << "Insufficient stock for " << p.name << endl;
                }
                break;
            }
        }
        if (!found) {
            cout << "Product not found!" << endl;
        }
    }

    file.close();
    cout << "Total bill: " << total << endl;
}

int main() {
    int choice;
    while (true) {
        cout << "\nSupermarket Billing System\n";
        cout << "1. Add Product\n";
        cout << "2. Display Products\n";
        cout << "3. Generate Bill\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addProductToFile();
                break;
            case 2:
                displayProducts();
                break;
            case 3:
                generateBill();
                break;
            case 4:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Try again!" << endl;
        }
    }
}
