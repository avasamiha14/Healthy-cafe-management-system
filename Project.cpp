#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

/// Class for a Menu Item
class MenuItem
{
public:
    string name;
    double price;
    int calories;
    MenuItem(string n, double p, int c)
    {   name = n;
        price = p;
        calories = c;
    }
};
/// Class for a Customer
class Customer
{
public:
    string name;
    bool isStudent;
    Customer(string n, bool s)
    {   name = n;
        isStudent = s;
    }
};
/// Class for an Order
class Order
{
public:
    Customer cust;
    vector<MenuItem> items;
    // Constructor, must use initialization list for class object
    Order(Customer c) : cust(c) {}
    void addItem(MenuItem m)
    {
        items.push_back(m);
    }
    //TOTAL BILL
    double total()
    {
        double sum = 0;
        for (int i = 0; i < (int)items.size(); i++)
        {
            sum += items[i].price;
        }
        if (cust.isStudent)
        {
            sum *= 0.65; // 35% discount
        }
        return sum;
    }
    //CALORIE CALCULATE
    int totalCalories()
    {
        int sum = 0;
        for (int i = 0; i < (int)items.size(); i++)
        {
            sum += items[i].calories;
        }
        return sum;
    }
   //FOR RECIEPT
    void printReceipt()
    {
        cout << "\n---- Receipt ----\n";
        cout << "Name: " << cust.name << "\n";
        cout << "Student: ";  //if student,then user can avail discount
        if (cust.isStudent)
        {
            cout << "Yes (35% off)";
        }
        else
        {
            cout << "No";
        }
        cout << "\nItems: ";
        for (int i = 0; i < (int)items.size(); i++)  //shows the items that user buys
            cout << items[i].name << ", ";
        cout << "\nTotal Calories: " << totalCalories() << "\n";
        cout << "Total Bill: BDT" << total() << "\n";
        cout << "Thank You For Your Co-operation." << endl;
    }
    //to save order
    void saveOrder()
    {
        ofstream f("orders.txt"); // open file
        if (!f)
        {
            cout << "Error opening file!" << endl;
            return;
        }
        f << "Name: " << cust.name << "\n";
        f << "Student: ";
        if (cust.isStudent)
        {
            f << "Yes";
        }
        else
        {
            f << "No";
        }
        f << "\nItems: ";
        for (int i = 0; i < (int)items.size(); i++)
            f << items[i].name << ", ";
        f << "\nTotal Calories: " << totalCalories() << "\n";
        f << "Total Bill: BDT" << total() << "\n";
        f << "----------------\n";
        f.close();
    }
}; // end of Order class
int main()
{
    // Menu
    vector<MenuItem> menu;
    menu.push_back(MenuItem("Burger", 90, 300));
    menu.push_back(MenuItem("Pizza", 120, 500));
    menu.push_back(MenuItem("Salad", 60, 150));
    menu.push_back(MenuItem("Pasta", 40, 400));
    int choice;
    do
    {
        cout << "WELCOME To Our Cafe" << endl; // you can make your choice by your own
        cout << "What Are You Waiting For?" << endl;
        cout << "\n1. Place New Order\n2. View Previous Orders\n0. Exit\nChoose: ";
        cin >> choice;
        cin.ignore();
        if (choice == 1)
        {
            string name;
            char s;
            cout << "Enter your name: ";
            getline(cin, name);
            cout << "Are you a university student? (y/n): ";
            cin >> s;
            cin.ignore();
            bool studentStatus = false;
            if (s == 'y' || s == 'Y') //to solve the issue of upper-lower case
            {
                studentStatus = true;
            }

            Customer cust(name, studentStatus);
            Order order(cust);

            int itemChoice;
            do
            {
                cout << "\n--- MENU ---\n";
                for (int i = 0; i < (int)menu.size(); i++)
                    cout << i + 1 << ". " << menu[i].name << " (BDT" << menu[i].price << ", " << menu[i].calories << " cal)\n";
                cout << "Choose item number (0 to finish): ";
                cin >> itemChoice;
                cin.ignore();

                if (itemChoice > 0 && itemChoice <= (int)menu.size())
                    order.addItem(menu[itemChoice - 1]);
                else if (itemChoice != 0)
                    cout << "Invalid input, try again!\n";  //shows invalid input
            }
            while (itemChoice != 0);

            order.printReceipt();
            order.saveOrder();
            cout << " Order saved!\n";
        }
        else if (choice == 2)
        {
            ifstream f("orders.txt");
            if (!f)
            {
                cout << "No previous orders found.\n"; //if there is no prev record
            }
            else
            {   string line;
                cout << "\n---- Previous Orders ----\n";
                while (getline(f, line))
                    cout << line << "\n";
                f.close();
            }
        }
    }
    while (choice != 0);
    if (choice != 0 && choice != 1 && choice != 2)
    {cout << "Invalid Input, Please select 1, 2, or 0!\n";}  //shows invalid input
     cout << "Thank You! Please Visit Us Again.\n";}

