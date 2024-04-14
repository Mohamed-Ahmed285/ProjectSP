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




// ----- Functions ------
int readCarsFromFile(Car cars1[]);
void writeCarsToFile(int numCars, Car cars1[]);
int addCar(int& m, Car cars1[]);
void updateCar(Car cars1[]);
int removeCar(int* numCars, int to_remove, Car cars1[]);
void listCars(int n, Car cars1[]);
bool checkCar(Car cars1[]);
void rentCar(int x, Car cars1[]);
void login(int& num, Customer customers1[]);
int main() {

    Car cars[MAX_CARS]{};
    Customer customers[MAX_USERS]{};
    int numCustomers = 0;
    int numCars = readCarsFromFile(cars);



    login(numCustomers, customers);

    int ans;
    do {

        cout << "----------------------\n";
        cout << "   Main Menu:\n";
        cout << "   1. Add Car\n";
        cout << "   2. Update Car Details\n";
        cout << "   3. Remove Car\n";
        cout << "   4. List Cars\n";
        cout << "   5. Check Car Availability\n";
        cout << "   6. Rent Car \n";
        cout << "   7. Logout \n";
        cout << "----------------------\n";
        cout << "Enter your choice: ";
        cin >> ans;
        switch (ans) {
        case 1:
            addCar(numCars, cars);
            cout << "The New Car's Number is: " << numCars << endl;
            cout << "Car Added Successfully!\n";
            cout << "\t-----\n";
            break;
        case 2:
            updateCar(cars);
            break;
        case 3:
            int to_remove;
            cout << "Enter the number of the car you want to remove: ";
            cin >> to_remove;
            removeCar(&numCars, to_remove, cars);
            break;
        case 4:
            listCars(numCars, cars);
            break;
        case 5:
            if (checkCar(cars)) {
                cout << "Fortunately,this car is available." << endl;
                cout << "You can rent it" << endl;
            }
            else {
                cout << "Unfortunately,this car is not available." << endl;
                cout << "Press 5 to check for another car" << endl;
            }
            break;
        case 6:
            rentCar(numCars, cars);
            break;
        case 7:
            writeCarsToFile(numCars, cars);
            cout << "Logged out successfully.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (ans != 7);

    return 0;

}



int addCar(int& m, Car cars1[]) {//TODO:muhammad

    cars1[m].carnum = m + 1; // index of new car is m , and m is the number of cars in system

    cout << "Enter car's Brand : ";
    cin >> cars1[m].brand;

    cout << "Enter car's Model : ";
    cin >> cars1[m].model;

    cout << "Enter car's Color : ";
    cin >> cars1[m].color;

    cout << "Enter car's Distance Traveled : ";
    cin >> cars1[m].distanceTraveled;

    cars1[m].available = true;

    m++;
    return m;

}
// done ... <3

void updateCar(Car cars1[]) {//TODO:Nada
    int carChoice, detailChoice;
    cout << "Enter the number of the car you want to update its details : ";
    cin >> carChoice;
    cout << "\t-----\n";
    cout << "1.Brand\n2.Model\n3.Color\n4.Distance Travelled by kilometer\n";
    cout << "\t-----\n";
    cout << "What detail you want to change : ";
    cin >> detailChoice;
    if (carChoice >= 1 && carChoice <= MAX_CARS) {
        int carindex = carChoice - 1;
        cout << "Enter the updated details :" << endl;
        switch (detailChoice)
        {
        case 1:
            cout << "Brand :";
            cin >> cars1[carindex].brand;
            break;
        case 2:
            cout << "Model :";
            cin >> cars1[carindex].model;
            break;
        case 3:
            cout << "Color :";
            cin >> cars1[carindex].color;
            break;
        case 4:
            cout << "Distance Travelled by kilometer :";
            cin >> cars1[carindex].distanceTraveled;
            break;
        default:
            break;
        }
        cout << "The details are updated successfully" << endl;
    }
    else
        cout << "Invalid choice ,please try again !" << endl;
}
// done ... <3

int removeCar(int* numCars, int to_remove, Car cars1[]) { //TODO: loay
    bool isfound = false;

    for (int i = 0; i < *numCars; i++)
    {
        if (cars1[i].carnum == to_remove)
        {
            isfound = true;
            for (int j = i; j < *numCars - 1; j++) // i don't want to enter if its the last car
            {
                cars1[j] = cars1[j + 1];
            }
            (*numCars)--;
            break;
        }
    }

    if (isfound) {
        cout << "The car has been removed successfully !! \n";
    }else{
        cout << "the car is not found\n";
    }   

    return *numCars;
}
//done ... <3

void listCars(int n, Car cars1[]) { //TODO:mohamedAhmed
    if (n > 0) {
        cout << "\nThe list of Cars :\n";
        cout << "\n";
        for (int i = 0; i < n; i++) {

            cout << "car number " << cars1[i].carnum << "\n";
            cout << "brand : " << cars1[i].brand << "\n";
            cout << "model : " << cars1[i].model << "\n";
            cout << "Color : " << cars1[i].color << "\n";
            cout << "Traveld Distance : " << cars1[i].distanceTraveled << " K.m " << "\n";
            cout << "\t-----\n";
        }
    }
    else {

        cout << "There are no available cars to be shown \n";

    }
}
//done ... <3

bool checkCar(Car cars1[]) {
    bool check;
    int carnumber;
    cout << "PLease enter the number of the car you want to check: ";
    cin >> carnumber;
    carnumber -= 1;
    if (cars1[carnumber].available) {
        check = true;
    }
    else {
        check = false;
    }
    return check;
}
//done ... <3

void rentCar(int x, Car cars1[])
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

            if (cars1[n - 1].available == true) // check if the car is avaliable or rented
            {
                cout << "\n The Car is Avaliable, You have rented it Succefully!\n\n";
                cars1[n - 1].available = false;
                break;
            }
            else {
                cout << " Already rented.\n";
                bool f = 1;
                while (f) {
                    cout << "Do you want to choose another one? [y / n]\n";
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
                        cout << "invalid choice.\n";
                        continue;
                    }
                }
            }
        }
        else {
            cout << "Invalid Number.\n";
            bool f = 1;
            char w;
            while (f) {
                cout << "Do you want to choose another one? [y / n]\n";
                cin >> w;
                if (w == 'y' || w == 'Y') {
                    bool t = 1;
                    bool f = 0;
                    break;
                }
                else if (w == 'n' || w == 'N') {
                    bool t = 0;
                    bool f = 0;
                    return;
                }
                else {
                    cout << "invalid choice.\n";
                    continue;
                }
            }
        }
    }


}
//done ... <3 

void login(int& num, Customer customers1[]){

        cout << "\t\t\t\t\t\t\t\tWELCOME TO OUR PROJECT\n";
        cout << "\t\t\t\t\t\t\t\t----------------------\n";
        cout << "Please enter your data : \n";
        cout << "Name: ";
        getline(cin, customers1[num].name);
        cout << "Mobile number: ";
        getline(cin, customers1[num].mobileNum);
        cout << "Address: ";
        getline(cin, customers1[num].address);

    }
//done ... <3

// filestream functions -> mohammed
    int readCarsFromFile(Car cars1[]) {

        ifstream file("cars.txt");
        int numCars = 0;
        while (file >> cars1[numCars].carnum >> cars1[numCars].brand >> cars1[numCars].model >> cars1[numCars].color >> cars1[numCars].distanceTraveled >> cars1[numCars].available) {
            numCars++;
        }
        file.close();
        return numCars;
    }
    void writeCarsToFile(int numCars, Car cars1[]) {
        ofstream file("cars.txt");
        for (int i = 0; i < numCars; ++i) {
            file << cars1[i].carnum << " " << cars1[i].brand << " " << cars1[i].model << " " << cars1[i].color << " " << cars1[i].distanceTraveled << " " << cars1[i].available << endl;
        }
        file.close();
    }
