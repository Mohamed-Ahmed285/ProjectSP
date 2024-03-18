#include <iostream>
#include <fstream>
#include <string>
using namespace std;


const int MAX_USERS = 100;
const int MAX_CARS = 100;


struct Customer {
    string name;
    string mobileNum;
    string address;
};

struct Car {
    int carnum;
    string brand;
    string model;
    string color;
    float distanceTraveled;
    bool available;
};

Car cars[MAX_CARS]{

    {1 , "brand1" , "model1" , "color1" , 0.0 , true},      // exampels for testing
    {2, "brand2" , "model2" , "color2" , 1.1 , false},     //
    {3, "brand3" , "model3", "color3", 2.0 , true},       //

};
Customer customers[MAX_USERS]{};

void addCar();
void updateCar();
void removeCar();
void listCars(int n);
bool checkCar();
void rentCar();
void login();

int main() {

    int numCustomers = 0;
    int numCars = 3;

    login();


    int ans;
    do {

        cout << "----------------------\n";
        cout << "   Main Menu:\n";
        cout << "   1. Add Car\n";
        cout << "   2. Update Car Details\n";
        cout << "   3. Remove Car\n";
        cout << "   4. List Cars\n";
        cout << "   5. Check Car Availability\n";
        cout << "   6. Rent Car\n";
        cout << "   7. Logout\n";
        cout << "----------------------\n";
        cout << "Enter your choice: ";
        cin >> ans;
        switch (ans) {
        case 1:
            addCar();
            break;
        case 2:
            updateCar();
            break;
        case 3:
            removeCar();
            break;
        case 4:
            listCars(numCars);
            break;
        case 5:
            if (checkCar()) {
                cout << "Fortunately,this car is available." << endl;
                cout << "You can rent it" << endl;
            }
            else {
                cout << "Unfortunately,this car is not available." << endl;
                cout << "Press 5 to check for another car" << endl;
            }
            break;
        case 6:
            rentCar();
            break;
        case 7:
            cout << "Logged out successfully.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (ans != 7);

    return 0;

}



void addCar() {
    //muhammad
}


void updateCar() {
    int choice;
    cout << "Enter the number of the car you want to update its details :" << endl;
    cin >> choice;
    if (choice >= 1 && choice <= MAX_CARS) {
        int carindex = choice - 1;
        cout << "Enter the updated details :" << endl;
        cout << "Brand :";
        cin >> cars[carindex].brand;
        cout << "Model :";
        cin >> cars[carindex].model;
        cout << "Color :";
        cin >> cars[carindex].color;
        cout << "Distance Travelled :";
        cin >> cars[carindex].distanceTraveled;
        cout << "The details are updated successfully" << endl;
    }
    else
        cout << "Invalid choice ,please try again !" << endl;
}
//done ... <3

void removeCar() {
    // loay
}


void listCars(int n) {
    //mohamedAhmed
    cout << "\nThe list of Cars :\n";
    cout << "\n";
    for (int i = 0; i < n; i++) {


        cout << "car number " << cars[i].carnum << "\n";
        cout << "brand : " << cars[i].brand << "\n";
        cout << "model : " << cars[i].model << "\n";
        cout << "Color : " << cars[i].color << "\n";
        cout << "Traveld Distance : " << cars[i].distanceTraveled << "\n";

        if (cars[i].available) {

            cout << "available \n";

        }
        else
        {
            cout << "unavailable \n";
        }

        cout << "\t-----\n";

    }

}
//done ... <3

bool checkCar() {
    bool check;
    int carnumber;
    cout << "PLease enter the number of the car you want to check: ";
    cin >> carnumber;
    carnumber -= 1;
    if (cars[carnumber].available) {
        check = true;
    }
    else {
        check = false;
    }
    return check;
}
//done ... <3

void rentCar() {
    // abdallah
}


void login() {
    // mohamed gamel gdn
}
