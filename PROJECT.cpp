#include <iostream>
#include <fstream>
#include <string>
using namespace std;


const int maxusers = 100;
const int maxcars = 100;


struct Customer {
    string name;
    string mobileNum;
    string address;
};

struct Car {
    string brand;
    string model;
    string color;
    float distanceTraveled;
    bool available;
};

 Car cars[maxcars]{





    };


void addCar();
void updateCar();
void removeCar();
void listCars();
bool checkCar();
void rentCar();
void login();

int main() {

    Customer customers[maxusers]{




    };
   

    int numCustomers = 0;
    int numCars = 0;
    
    login();


    int ans;
    do {

        cout << "----------------------\n";
        cout << "Main Menu:\n";
        cout << "1. Add Car\n";
        cout << "2. Update Car Details\n";
        cout << "3. Remove Car\n";
        cout << "4. List Cars\n";
        cout << "5. Check Car Availability\n";
        cout << "6. Rent Car\n";
        cout << "7. Logout\n";
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
                listCars();
                break;
            case 5:
               if (checkCar()) {
     cout << "Fortunately,this car is available." << endl ;
     cout << "You can rent it" << endl ;
 }
 else {
     cout << "Unfortunately,this car is not available." << endl ;
     cout << "Press 5 to check for another car" << endl ;
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
    // Nada
}

void removeCar() {
   // loay
}

void listCars() {
    //mohamedAhmed
}

bool checkCar() {
    bool check = false;
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
     return check ;
}
void rentCar() {
    // abdallah
}

void login() {
    // mohamed gamel gdn
}
