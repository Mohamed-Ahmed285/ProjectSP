#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ----- Constants ------

const int MAX_USERS = 100;
const int MAX_CARS = 100;


// ----- Structs ------

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

Car cars[MAX_CARS]{};
Customer customers[MAX_USERS]{};


// ----- Functions ------
int readCarsFromFile();
void writeCarsToFile(int numCars);
void addCar(int& m);
void updateCar();
void removeCar(int* numCars, int to_remove);
void listCars(int n);
bool checkCar();
void rentCar(int x);
void login();


int main() {

    int numCustomers = 0;
    int numCars = readCarsFromFile();

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
            addCar(numCars);
            break;
        case 2:
            updateCar();
            break;
        case 3:
            int to_remove;
            cout << "Enter the number of the car you want to remove: ";
            cin >> to_remove;
            removeCar(&numCars, to_remove);
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
            rentCar(numCars);
            break;
        case 7:
            writeCarsToFile(numCars);
            cout << "Logged out successfully.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (ans != 7);

    return 0;

}



void addCar(int& m) {//TODO:muhammad

    cars[m].carnum = m + 1; // index of new car is m , and m is the number of cars in system

    cout << "Enter car's Brand: \n";
    cin >> cars[m].brand;

    cout << "Enter car's Model \n";
    cin >> cars[m].model;

    cout << "Enter car's Color \n";
    cin >> cars[m].color;

    cout << "Enter car's Distance Traveled \n";
    cin >> cars[m].distanceTraveled;

    cars[m].available = true;

    cout << "The New Car's Number is: " << cars[m].carnum << endl;
    m++;
    cout << "Car Added Successfully!\n";
    cout << "\t-----\n";

}
// done ... <3

void updateCar() {
    int choice;
    cout << "Enter the number of the car you want to update its details : ";
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

void removeCar(int* numCars, int to_remove) { //TODO: loay && will be updated removing by number of listing car not by carnum
    bool isfound = false;

    for (int i = 0; i < *numCars; i++)
    {
        if (cars[i].carnum == to_remove)
        {
            isfound = true;
            cars[i] = cars[*numCars - 1]; //just swap
            (*numCars)--; //to remove from couter the last one
            cout << "The car has been removed successfully !! \n";
            break;
        }
    }

    if (!isfound) {
        cout << "the car is not found\n";
    }


}
//done ... <3

void listCars(int n) { //TODO:mohamedAhmed
    if (n > 0) {
        cout << "\nThe list of Cars :\n";
        cout << "\n";
        for (int i = 0; i < n; i++) {

            cout << "car number " << cars[i].carnum << "\n";
            cout << "brand : " << cars[i].brand << "\n";
            cout << "model : " << cars[i].model << "\n";
            cout << "Color : " << cars[i].color << "\n";
            cout << "Traveld Distance : " << cars[i].distanceTraveled << "\n";
            cout << "\t-----\n";
        }
    }
    else {

        cout << "There are no available cars to be shown \n";

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

void rentCar(int x)
{
    //TODO: abdallah
    int n;
    char z;
    bool t = 1;
    while (t)
    {
        cout << "Select the car's number : ";
        cin >> n;

        if (n <= x && n > 0) // check the number is in the range
        {

            if (cars[n - 1].available == true) // check if the car is avaliable or rented
            {
                cout << "\n The Car is Avaliable, You have rented it Succefully!\n\n";
                cars[n - 1].available = false;
                break;
            }
            else {
                cout << " Already rented,";
                bool f = 1;
                while (f) {
                    cout << " Do you want to choose another one? [y / n]\n";
                    cin >> z;
                    if (z == 'y' || z == 'Y') {
                        bool t = 1;
                        bool f = 0;
                        break;
                    }
                    else if (z == 'n' || z == 'N') {
                        bool t = 0;
                        bool f = 0;
                        return;
                    }
                    else {
                        cout << "invalid choice,";
                        continue;
                    }
                }
            }
        }
        else {
            cout << "Invalid Number , Please Try Again\n ";
            continue;
        }
    }

}
//done ... <3 

void login() {
    //TODO: mohamed gamel gdn
}

// filestream functions -> mido
int readCarsFromFile() {
    ifstream file("cars.txt");
    int numCars = 0;
    while (file >> cars[numCars].carnum >> cars[numCars].brand >> cars[numCars].model >> cars[numCars].color >> cars[numCars].distanceTraveled >> cars[numCars].available) {
        numCars++;
    }
    file.close();
    return numCars;
}
void writeCarsToFile(int numCars) {
    ofstream file("cars.txt");
    for (int i = 0; i < numCars; ++i) {
        file << cars[i].carnum << " " << cars[i].brand << " " << cars[i].model << " " << cars[i].color << " " << cars[i].distanceTraveled << " " << cars[i].available << endl;
    }
    file.close();
}
