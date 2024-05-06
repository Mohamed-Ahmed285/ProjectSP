#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include<conio.h>
using namespace std;

// ----- Constants ------
const int MAX_USERS = 100;
const int MAX_CARS = 100;
const string adminUsername = "admin";
const string adminPassword = "admin123";

// ----- Structs ------
struct Customer {
    int Id;
    string name;
    string mobileNum;
    string address;
    string Password;

};
struct Car {
    int carnum;
    string brand;
    string model;
    string color;
    float distanceTraveled;
    bool available;
};
int  removeCar(int& numCars, int to_remove, Car cars1[], bool& x);   //Loay
void removeUser(int& numCustomers, int to_removeId, Customer customers[], bool& message, Car usercars[], Car cars[], int& numcars);//Mohammed
void copyfunction(int sysnum, int usernum, Car cars[], Car usercars[]); //Nada


// ==============files===============
int  readCarsFromFile(Car cars1[]);
int  readUserCars(Car usercars[], int id);
void writeCarsToFile(int numCars, Car cars1[]);
void writeUserCars(int UserNumCars, Car usercars[], int id);
int  readCustomersFromFile(Customer customers[]);
void writeCustomersToFile(int numCustomers, Customer customers[]);
void CreateFile(int numCustomers, Customer customers[]);
//------------------------------------

int  addCar(int& m, Car cars1[]); //Mohammed Tarek
void updateCar(int carChoice, Car cars1[], int numCars); //Nada
void listCars(int n, Car cars1[]); //Mohammed
void listUsers(int n, Customer customers[]); // Mohamed
void listUsersCars(int n, Car usercars[]); // Mohamed
bool checkCar(int NumCars, Car cars1[]); //Noha
void rentCar(int x, Car cars1[], int& n); //Abdallah
bool Customerlogin(int num, Customer customers[], int& IDnum); //Gamel
bool Adminlogin(); //Gamel
void signUp(int& numCustomers, Customer customers[], int& IDnum); //Gamel
void AdminMenu(int& numCustomers, int& numCars, Customer customers[], Car cars[], Car usercars[]);
void CustomerMenu(int& numCustomers, int& numCars, Customer customers[], Car cars[], Car usercars[], int id, int& UserNumCars);
void Rearrange(int UserNumCars, int Numcars, Car cars[], Car usercars[], bool& changed); //Mohammed
int  searchByCarNum(int CarNum, int NumCars, Car cars[]); //Noha
void checkremovedCars(int& usernumcars, int numcars, Car usercars[], Car cars[], bool& removed); //Loay
void updateUser(int id, Customer customers[], int numCustomers); //Noha

// ==============files===============
/*readCarsFromFile
 readUserCars
 writeCarsToFile
 writeUserCars
 readCustomersFromFile
 writeCustomersToFile
 CreateFile
//------------------------------------
//EXTRA FUNCTIONS:
  updateUser------>Noha
 searchByCarNum----->Noha
 listUsers------>Mohammed
  removeUser------>Mohammed
  Rearrange------>Mohammed
 checkremovedCars------>Loay
 copyfunction------>Nada
//-------------------------------------
//MAIN FUNCTIONS:
  addCar------>Mohammed Tarek
 updateCar------>Nada
 listCars------>Mohammed
 checkCar------>Noha
  removeCar------>Loay
 rentCar------>Abdallah
 Customerlogin------>Gamel
 Adminlogin------>Gamel
 signUp------>Gamel
 AdminMenu------>ALL THE TEAM
 CustomerMenu------>//ALL THE TEAM */



int main() {

    Car cars[MAX_CARS]{};
    Car usercars[MAX_CARS]{};
    Customer customers[MAX_USERS]{};
    int numCustomers = readCustomersFromFile(customers);
    int numCars = readCarsFromFile(cars);


    cout << "WELCOME TO THE CAR RENTAL SYSTEM!" << endl;
    cout << "---------------------------------\n";
    int userType;
    bool validInput = false;
    int id;
    while (!validInput) {
        cout << "-----------------------\n";
        cout << "1. Admin." << endl;
        cout << "2. Old User." << endl;
        cout << "3. New User." << endl;
        cout << "4. Exit." << endl;
        cout << "-----------------------\n";
        cout << "Enter your choice : ";
        cin >> userType;
        cin.ignore(100,'\n');
        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please try again." << endl;
            cout << "Enter your choice : ";
            cin >> userType;
            cin.ignore(100,'\n');
        }
        switch (userType) {
        case 1: {
            if (Adminlogin()) {
                AdminMenu(numCustomers, numCars, customers, cars, usercars);
                break;
            }
            else {
                break;
            }
        }
        case 2: {

            bool changed;
            bool removed;
            if (Customerlogin(numCustomers, customers, id)) {
                int UserNumCars = readUserCars(usercars, id);
                Rearrange(UserNumCars, numCars, cars, usercars, changed);
                if (changed) {
                    cout << "\n-------------\n";
                    cout << "The admin has updated one of your cars.";
                    cout << "\n-------------\n";
                }
                checkremovedCars(UserNumCars, numCars, usercars, cars, removed);
                if (removed) {
                    cout << "\n-------------\n";
                    cout << "The admin has removed one of your cars.";
                    cout << "\n-------------\n";
                }
                CustomerMenu(numCustomers, numCars, customers, cars, usercars, id, UserNumCars);
                writeUserCars(UserNumCars, usercars, id);
                break;
            }
            else {
                break;
            }
        }
        case 3: {
            signUp(numCustomers, customers, id);
            writeCustomersToFile(numCustomers, customers);
            int UserNumCars = readUserCars(usercars, id);
            CustomerMenu(numCustomers, numCars, customers, cars, usercars, id, UserNumCars);
            writeUserCars(UserNumCars, usercars, id);
            break;
        }
        case 4: {
            cout << "Exiting the program.............................." << endl;
            validInput = true;
            break;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
        }
        }
    }
    return 0;
}

int addCar(int& numCars, Car cars1[]) {//TODO:muhammad

    cars1[numCars].carnum = (cars1[numCars - 1].carnum + 1);

    cout << "Enter car's Brand : ";
    cin >> cars1[numCars].brand;

    cout << "Enter car's Model : ";
    cin >> cars1[numCars].model;

    cout << "Enter car's Color : ";
    cin >> cars1[numCars].color;

    cout << "Enter car's Distance Traveled : ";
    cin >> cars1[numCars].distanceTraveled;
    cin.ignore();
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please try again." << endl;
        cout << "Enter car's Distance Traveled : ";
        cin >> cars1[numCars].distanceTraveled;
    }
    cars1[numCars].available = true;
    cout << "The New Car's Number is: " << cars1[numCars].carnum << endl;
    cout << "Car Has Been Added Successfully!\n";
    cout << "\t-----\n";
    numCars++;
    return numCars;
}
// done ... <3

void updateCar(int carChoice, Car cars1[], int numCars) {//TODO:Nada

    bool repeat = 1;
    while (repeat) {

        int detailChoice;
        cout << "\t-----------\n";
        cout << "1.Brand.\n2.Model.\n3.Color.\n4.Distance travelled by kilometer.\n5.Availability.\n6.Go back.\n";
        cout << "\t-----------\n";
        cout << "Which detail you want to change? : ";
        cin >> detailChoice;
        cin.ignore();
        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice." << endl;
            cout << "Which detail you want to change? : ";
            cin >> detailChoice;
        }


        if (carChoice >= 1 && carChoice <= MAX_CARS) {
            int carindex = searchByCarNum(carChoice, numCars, cars1);
            switch (detailChoice)
            {
            case 1:
                cout << "Enter the updated details :" << endl;
                cout << "Brand :";
                cin >> cars1[carindex].brand;
                cout << "The details have been updated successfully!" << endl;
                break;
            case 2:
                cout << "Enter the updated details :" << endl;
                cout << "Model :";
                cin >> cars1[carindex].model;
                cout << "The details have been updated successfully!" << endl;
                break;
            case 3:
                cout << "Enter the updated details :" << endl;
                cout << "Color :";
                cin >> cars1[carindex].color;
                cout << "The details have been updated successfully!" << endl;
                break;
            case 4: {
                cout << "Enter the updated details :" << endl;
                cout << "Distance travelled by kilometer :";
                cin >> cars1[carindex].distanceTraveled;
                cin.ignore();
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid choice. Please try again." << endl;
                    cout << "Enter a number:";
                    cin >> cars1[carindex].distanceTraveled;
                }
                cout << "The details have been updated successfully!" << endl;
                break;
            }

            case 5:
            {
                if (cars1[carindex].available) {
                    char ans;
                    cout << "Do you want to make this car unavailable? [Y / N] \n";
                    cin >> ans;
                    if (ans == 'y' || ans == 'Y') {
                        cars1[carindex].available = 0;
                        cout << "The details have been updated successfully!" << endl;
                    }
                    else {
                        break;
                    }

                }
                else {

                    char ans;
                    cout << "Do you want to make this car available? [Y / N] \n";
                    cin >> ans;
                    if (ans == 'y' || ans == 'Y') {
                        cars1[carindex].available = 1;
                        cout << "The details have been updated successfully!" << endl;
                    }
                    else {
                        break;
                    }


                }


            }
            case 6: {
                repeat = false;
                break;
            }

            default: {
                cout << "Invalid choice." << endl;
                break;
            }


            }
        }
    }
}
void updateUser(int id, Customer customers[], int numCustomers)
{
    int userindex;
    bool repeat = 1;
    while (repeat) {

        int dataChoice;
        cout << "\t-----------\n";
        cout << "1.Name.\n2.Mobile number.\n3.Address.\n4.Password.\n5.Go back.\n";
        cout << "\t-----------\n";
        cout << "Which one of your data you want to change? : ";
        cin >> dataChoice;
        cin.ignore();
        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice." << endl;
            cout << "Which one of your data you want to change? : ";
            cin >> dataChoice;
        }
        if (id >= 1 && id <= MAX_USERS) {
            for (int i = 0; i < numCustomers; i++) {
                if (customers[i].Id == id)
                    userindex = i;
            }

            switch (dataChoice)
            {
            case 1: {
                cout << "Enter the updated details :" << endl;
                cout << "Name :";
                cin >> customers[userindex].name;
                cout << "The details have been updated successfully!" << endl;
                break;
            }

            case 2: {
                cout << "Enter the updated details :" << endl;
                cout << "Mobile number :";
                cin >> customers[userindex].mobileNum;
                cout << "The details have been updated successfully!" << endl;
                break;
            }
            case 3: {
                cout << "Enter the updated details :" << endl;
                cout << "Address :";
                cin >> customers[userindex].address;
                cout << "The details have been updated successfully!" << endl;
                break;
            }

            case 4:
            {
                cout << "Enter the updated details :" << endl;
                cout << "Password :";
                cin >> customers[userindex].Password;
                cout << "The details have been updated successfully!" << endl;
                break;
            }
            case 5: {
                repeat = false;
                break;
            }

            default: {
                cout << "Invalid choice." << endl;
                break;
            }


            }
        }
    }
}

// done ... <3



int removeCar(int& numCars, int to_remove, Car cars1[], bool& x) { //TODO: loay

    bool isfound = false;
    for (int i = 0; i < numCars; i++)
    {
        if (cars1[i].carnum == to_remove)
        {
            isfound = true;
            for (int j = i; j < numCars - 1; j++)
                for (int j = i; j < numCars - 1; j++)
                {
                    cars1[j] = cars1[j + 1];
                }
            (numCars)--;
            break;
        }
    }

    if (isfound) {
        x = true;
    }
    else {
        x = false;
    }

    return numCars;
}
//done ... <3

void removeUser(int& numCustomers, int to_removeId, Customer customers[], bool& message, Car usercars[], Car cars[], int& numcars) {

    bool isfound = false;
    int UserNumCars;
    for (int i = 0; i < numCustomers; i++)
    {
        if (customers[i].Id == to_removeId)
        {

            UserNumCars = readUserCars(usercars, to_removeId);
            isfound = true;
            for (int j = i; j < numCustomers - 1; j++)
            {
                customers[j] = customers[j + 1];
            }
            (numCustomers)--;
            break;
        }
    }

    if (isfound) {

        for (int i = 0; i < UserNumCars; i++) {
            for (int n = 0; n < numcars; n++)
            {
                if (usercars[i].carnum == cars[n].carnum) {
                    bool x;
                    removeCar(numcars, (cars[i].carnum), cars, x);
                    ofstream file("User " + to_string(to_removeId) + ".txt");
                    file << "";
                    break;
                }
            }
        }

        message = true;
    }
    else {
        message = false;
    }

}
//done ... <3

void listCars(int n, Car cars1[]) { //TODO:mohamedAhmed
    if (n > 0) {
        cout << "\nTHE LIST OF CARS :\n";
        cout << "\n";
        for (int i = 0; i < n; i++) {

            cout << "Car number " << cars1[i].carnum << "\n";
            cout << "Brand : " << cars1[i].brand << "\n";
            cout << "Model : " << cars1[i].model << "\n";
            cout << "Color : " << cars1[i].color << "\n";
            cout << "Distance Traveled : " << cars1[i].distanceTraveled << " K.m " << "\n";
            cout << "\t-------------\n";
        }
    }
    else {

        cout << "There are no available cars to be shown. \n";

    }
}
//done ... <3
void listUsersCars(int num, Car usercars[]) {
    if (num > 0) {
        cout << "\nTHE LIST OF YOUR CARS :\n";
        cout << "\n";
        for (int i = 0; i < num; i++) {
            cout << "Car number " << usercars[i].carnum << "\n";
            cout << "Brand : " << usercars[i].brand << "\n";
            cout << "Model : " << usercars[i].model << "\n";
            cout << "Color : " << usercars[i].color << "\n";
            cout << "Distance Traveled : " << usercars[i].distanceTraveled << " K.m " << "\n";
            cout << "\t-------------\n";

        }
    }
    else {
        cout << "You do not have any car in the system to be shown. \n";
    }
}
void listUsers(int n, Customer customers[]) {


    if (n > 0) {
        cout << "\nTHE LIST OF USERS :\n";
        cout << "\n";
        for (int i = 0; i < n; i++) {

            cout << "Customer number " << customers[i].Id << "\n";
            cout << "Name : " << customers[i].name << "\n";
            cout << "Mobile number : " << customers[i].mobileNum << "\n";
            cout << "Address : " << customers[i].address << "\n";
            cout << "\t-------------\n";
        }
    }
    else {
        cout << "There are no Users to be shown. \n";
    }

}
//done ... <3

bool checkCar(int NumCars, Car cars1[]) { //TODO:Noha
    bool check;
    int carnumber;
    cout << "PLease enter the number of the car you want to check: ";
    cin >> carnumber;
    cin.ignore();
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid data. Please try again." << endl;
        cout << "PLease enter the number of the car you want to check: ";
        cin >> carnumber;
        cin.ignore();
    }
    carnumber = searchByCarNum(carnumber, NumCars, cars1);
    if (cars1[carnumber].available) {
        check = true;
    }
    else {
        check = false;
    }
    return check;

}
//done ... <3

void rentCar(int numCars, Car cars1[], int& n) {//TODO: abdallah

    char ans;
    bool t = 1;
    while (t)
    {
        cout << "Enter the car's number : ";
        cin >> n;
        cin.ignore();
        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid data. Please try again." << endl;
            cout << "Enter the car's number : ";
            cin >> n;
            cin.ignore();
        }
        int CarIndex = searchByCarNum(n, numCars, cars1);
        if (n <= numCars && n > 0) // check the number is in the range
        {

            if (cars1[CarIndex].available == true) // check if the car is avaliable or rented.
            {
                cout << "\n The Car is Available, You have rented it Succefully!\n\n";
                cars1[CarIndex].available = false;
                break;
            }
            else {
                cout << " We are sorry, This car is already rented.\n";
                bool f = 1;
                while (f) {
                    cout << "Do you want to choose another one? [Y / N]\n";
                    cin >> ans;
                    if (ans == 'y' || ans == 'Y') {
                        bool t = 1;
                        bool f = 0;
                        break;
                    }
                    else if (ans == 'n' || ans == 'N') {
                        bool t = 0;
                        bool f = 0;
                        return;
                    }
                    else {
                        cout << "Invalid choice.\n";
                        continue;
                    }
                }
            }
        }
        else {
            cout << "This Car is not found.\n";
            bool f = 1;
            char ans2;
            while (f) {
                cout << "Do you want to choose another one? [Y / N]\n";
                cin >> ans2;
                if (ans2 == 'y' || ans2 == 'Y') {
                    bool t = 1;
                    bool f = 0;
                    break;
                }
                else if (ans2 == 'n' || ans2 == 'N') {
                    bool t = 0;
                    bool f = 0;
                    return;
                }
                else {
                    cout << "Invalid choice.\n";
                    continue;
                }
            }
        }
    }
}
//done ... <3





// login and signup functions --->
// login and signup functions --->
bool Adminlogin() {

    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (username == adminUsername && password == adminPassword) {
        cout << "-----------------------\n\n";
        cout << "Admin logged in successfully!\n" << endl;
        return 1;
    }
    else {
        cout << "Invalid username or password. Please try again." << endl;
        cout << "If you are a user please press 2 (Old User) or 3 (New User). " << endl;
        return 0;
    }


};
//done ... <3
bool Customerlogin(int num, Customer customers[], int& IDnum)
{
    int index;
    string username;
    string password;
    cout << "Please enter your data : \n";
    cout << "Name: ";
    cin >> username;
    cin.ignore(100, '\n');
    cout << "ID: ";
    cin >> IDnum;
    cin.ignore();
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid data. Please try again." << endl;
        cout << "ID: ";
        cin >> IDnum;
        cin.ignore();
    }
    cout << "Password: ";
    cin >> password;
    cin.ignore(100, '\n');
    bool vailddata = 0;
    for (int i = 0; i < num; i++) {

        if ((customers[i].Id == IDnum) && (customers[i].Password == password) && (customers[i].name == username)) {
            index = i;
            vailddata = 1;
        }

    };
    if (vailddata) {
        cout << "-----------------------\n\n";
        cout << "You logged in successfully!\n\n";
        cout << "WELCOME BACK, " << customers[index].name << endl << endl;
        return 1;
    }
    else {
        cout << "Invalid data\n";
    }
    return 0;

}
//done ... <3
void signUp(int& numCustomers, Customer customers[], int& IDnum) {

    if (numCustomers >= MAX_USERS) {
        cout << "Maximum number of customers has been reached. Cannot sign up more users." << endl;
        return;
    }

    Customer newCustomer;
    newCustomer.Id = numCustomers + 1;
    cout << "Enter your name: ";
    cin >> newCustomer.name;
    cin.ignore(100, '\n');
    cout << "Enter your mobile number: ";
    cin >> newCustomer.mobileNum;
    cin.ignore(100, '\n');
    cout << "Enter your address: ";
    cin >> newCustomer.address;
    cin.ignore(100, '\n');
    cout << "Create your password: ";
    cin >> newCustomer.Password;
    cin.ignore(100, '\n');
    customers[numCustomers++] = newCustomer;
    cout << "-----------------------\n\n";
    cout << "You signed up successfully! Your ID is: " << newCustomer.Id << "\n\n";
    IDnum = newCustomer.Id;
    CreateFile(numCustomers, customers);
};
//done ... <3




// filestream functions
// filestream functions

int readCarsFromFile(Car cars1[]) {

    ifstream file("cars.txt");
    int numCars = 0;
    while (file >> cars1[numCars].carnum >> cars1[numCars].brand >> cars1[numCars].model >> cars1[numCars].color >> cars1[numCars].distanceTraveled >> cars1[numCars].available) {
        numCars++;
    }
    file.close();
    return numCars;
}
//done ... <3
void writeCarsToFile(int numCars, Car cars1[]) {
    ofstream file("cars.txt");
    for (int i = 0; i < numCars; ++i) {
        file << cars1[i].carnum << " " << cars1[i].brand << " " << cars1[i].model << " " << cars1[i].color << " " << cars1[i].distanceTraveled << " " << cars1[i].available << endl;
    }
    file.close();
}
//done ... <3
int readCustomersFromFile(Customer customers[]) {

    ifstream file("customers.txt");
    int numCustomers = 0;
    while (file >> customers[numCustomers].Id >> customers[numCustomers].name >> customers[numCustomers].mobileNum >> customers[numCustomers].address >> customers[numCustomers].Password) {
        numCustomers++;
    }
    file.close();
    return numCustomers;

}
//done ... <3
void writeCustomersToFile(int numCustomers, Customer customers[])
{
    ofstream file("customers.txt");
    for (int i = 0; i < numCustomers; i++) {
        file << customers[i].Id << " " << customers[i].name << " " << customers[i].mobileNum << " " << customers[i].address << " " << customers[i].Password << endl;
    }
    file.close();
}
//done ... <3
void CreateFile(int numCustomers, Customer customers[])
{
    ofstream file;
    file.open("User " + to_string(customers[numCustomers - 1].Id) + ".txt");
    file.close();
}
//done ... <3
int readUserCars(Car usercars[], int id) {

    ifstream file("User " + to_string(id) + ".txt");
    int numCars = 0;
    while (file >> usercars[numCars].carnum >> usercars[numCars].brand >> usercars[numCars].model >> usercars[numCars].color >> usercars[numCars].distanceTraveled >> usercars[numCars].available)
    {
        numCars++;
    }
    file.close();
    return numCars;

}
//done ... <3
void writeUserCars(int UserNumCars, Car usercars[], int id) {
    ofstream file("User " + to_string(id) + ".txt");
    for (int i = 0; i < UserNumCars; ++i) {
        file << usercars[i].carnum << " " << usercars[i].brand << " " << usercars[i].model << " " << usercars[i].color << " " << usercars[i].distanceTraveled << " " << usercars[i].available << endl;
    }
    file.close();
}
//done ... <3






void copyfunction(int sysnum, int usernum, Car cars[], Car usercars[])
{

    usercars[usernum].carnum = cars[sysnum].carnum;
    usercars[usernum].brand = cars[sysnum].brand;
    usercars[usernum].model = cars[sysnum].model;
    usercars[usernum].color = cars[sysnum].color;
    usercars[usernum].distanceTraveled = cars[sysnum].distanceTraveled;
    usercars[usernum].available = cars[sysnum].available;

}
//done ... <3


void Rearrange(int UserNumCars, int Numcars, Car cars[], Car usercars[], bool& changed) {

    changed = 0;
    int carindex_userfile = 0;
    bool notfound = true;
    int carindex_sysfile = 0;

    for (int i = 0; i < UserNumCars; i++)
    {
        for (int n = 0; n < Numcars; n++) {
            for (int n = 0; n < Numcars; n++) {
                if (usercars[i].carnum == cars[n].carnum)
                {
                    carindex_userfile = i;
                    carindex_sysfile = n;
                    notfound = false;
                }
                notfound = false;
            }
        }
        if (notfound)
        {
            continue;
        }
        else {

            if (usercars[carindex_userfile].brand != cars[carindex_sysfile].brand) {

                copyfunction(carindex_sysfile, carindex_userfile, cars, usercars);
                changed = 1;

            }
            else if (usercars[carindex_userfile].model != cars[carindex_sysfile].model) {

                copyfunction(carindex_sysfile, carindex_userfile, cars, usercars);
                changed = 1;

            }
            else if (usercars[carindex_userfile].color != cars[carindex_sysfile].color) {

                copyfunction(carindex_sysfile, carindex_userfile, cars, usercars);
                changed = 1;

            }
            else if (usercars[carindex_userfile].distanceTraveled != cars[carindex_sysfile].distanceTraveled) {

                copyfunction(carindex_sysfile, carindex_userfile, cars, usercars);
                changed = 1;

            }
            else if (usercars[carindex_userfile].available != cars[carindex_sysfile].available) {

                copyfunction(carindex_sysfile, carindex_userfile, cars, usercars);
                changed = 1;

            }
        }
    }
}
//done ... <3
int searchByCarNum(int CarNum, int NumCars, Car cars[]) {

    int carIndex;
    for (int i = 0; i < NumCars; i++)
    {
        if (cars[i].carnum == CarNum) {
            carIndex = i;
        }
        else {
            continue;
        }

    }

    return carIndex;

};
//done ... <3
void checkremovedCars(int& usernumcars, int numcars, Car usercars[], Car cars[], bool& removed) {
    bool found = true;
    removed = false;
    for (int i = 0; i < usernumcars; i++)
    {


        for (int n = 0; n < numcars; n++) {

            if (usercars[i].carnum == cars[n].carnum) {
                found = false;
                break;
            }
            else {
                found = true;
            }


        }

        if (found)
        {
            bool x;
            removeCar(usernumcars, (usercars[i].carnum), usercars, x);
            removed = true;
        }
    }
}
//done ... <3

void AdminMenu(int& numCustomers, int& numCars, Customer customers[], Car cars[], Car usercars[]) {
    int ans;
    do {

        cout << "-----------------------\n";
        cout << "   MAIN MENU:\n";
        cout << "   1. Add Car.\n";
        cout << "   2. Update Car Details.\n";
        cout << "   3. Remove Car.\n";
        cout << "   4. Remove User.\n";
        cout << "   5. List Of All Cars.\n";
        cout << "   6. List of Users.\n";
        cout << "   7. Check Car Availability.\n";
        cout << "   8. Rent Car.\n";
        cout << "   9. Logout.\n";
        cout << "-----------------------\n";
        cout << "Enter your choice: ";
        cin >> ans;
        cin.ignore();
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please try again." << endl;
        }
        else {
            switch (ans) {
            case 1:
                addCar(numCars, cars);
                break;
            case 2: {
                int carindex_userfile;
                int carChoice;
                bool notfound = true;
                cout << "Enter the number of the car you want to update its details : ";
                cin >> carChoice;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid choice. Please try again." << endl;
                    cout << "Enter the number of the car you want to update its details : ";
                    cin >> carChoice;
                }

                for (int i = 0; i < numCars; i++)
                {
                    if (cars[i].carnum == carChoice)
                    {
                        notfound = false;
                    }
                    else
                    {
                        continue;
                    }
                }

                if (notfound)
                {
                    cout << "This car doesn't exist please choose another one." << endl;
                }
                else {
                    updateCar(carChoice, cars, numCars);
                }
                break;
            }
            case 3:
                int to_remove;
                bool x;
                cout << "Enter the number of the car you want to remove: ";
                cin >> to_remove;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid choice. Please try again." << endl;
                    cout << "Enter the number of the car you want to remove: ";
                    cin >> to_remove;
                }

                removeCar(numCars, to_remove, cars, x);
                if (x)
                {
                    cout << "The car has been removed successfully! \n";
                }
                else {
                    cout << "The car is not found.\n";
                }

                break;
            case 4:
                int to_removeId;
                bool message;
                cout << "Enter the Id of the User you want to remove: ";
                cin >> to_removeId;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid choice. Please try again." << endl;
                    cout << "Enter the Id of the User you want to remove: ";
                    cin >> to_removeId;

                }

                removeUser(numCustomers, to_removeId, customers, message, usercars, cars, numCars);
                if (message)
                {
                    cout << "The User has been removed successfully! \n";
                }
                else {
                    cout << "The User is not found.\n";
                }

                break;
            case 5:
                listCars(numCars, cars);
                break;
            case 6:
                listUsers(numCustomers, customers);
                break;
            case 7:
                if (checkCar(numCars, cars)) {
                    cout << "Fortunately, This car is available." << endl;
                    cout << "You can rent it." << endl;
                }
                else {
                    cout << "Unfortunately, This car is not available." << endl;
                    cout << "Press 5 to check for another car." << endl;
                }
                break;
            case 8:
                int rent_carnum;
                rentCar(numCars, cars, rent_carnum);
                break;


            case 9:
                writeCarsToFile(numCars, cars);
                writeCustomersToFile(numCustomers, customers);
                cout << "Logged out successfully.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } while (ans != 9);

}
//done ... <3
void CustomerMenu(int& numCustomers, int& numCars, Customer customers[], Car cars[], Car usercars[], int id, int& UserNumCars) {
    int ans;
    bool repeat = true;
    do {

        cout << "-----------------------\n";
        cout << "   MAIN MENU:\n";
        cout << "   1. Add Car.\n";
        cout << "   2. Update Car Details.\n";
        cout << "   3. Update Your Personal Details.\n";
        cout << "   4. Remove Car.\n";
        cout << "   5. List Of All Cars.\n";
        cout << "   6. List Of Your Cars.\n";
        cout << "   7. Check Car Availability.\n";
        cout << "   8. Rent Car.\n";
        cout << "   9. Logout.\n";
        cout << "-----------------------\n";
        cout << "Enter your choice: ";
        cin >> ans;
        cin.ignore();
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please try again." << endl;
        }
        else {
            switch (ans) {

            case 1: {
                addCar(numCars, cars);
                copyfunction((numCars - 1), UserNumCars, cars, usercars);
                UserNumCars++;
                break;
            }
            case 2: {
                int carindex_userfile;
                int carChoice;
                bool notfound = true;
                cout << "Enter the number of the car you want to update its details : ";
                cin >> carChoice;
                cin.ignore();
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid choice. Please try again." << endl;
                    cout << "Enter the number of the car you want to update its details : ";
                    cin >> carChoice;
                }


                for (int i = 0; i < UserNumCars; i++)
                {
                    if (usercars[i].carnum == carChoice)
                    {
                        carindex_userfile = i;
                        notfound = false;
                    }
                    else
                    {
                        continue;
                    }
                }
                if (notfound)
                {
                    cout << "This car is either not yours or doesn't exist please choose another one." << endl;
                }
                else {
                    updateCar(carChoice, cars, numCars);
                    copyfunction((searchByCarNum(carChoice, numCars, cars)), carindex_userfile, cars, usercars);
                }
                break;
            }
            case 3: {
                updateUser(id, customers, numCustomers);
                break;
            }
            case 4: {
                int to_remove;
                bool notfound = true;
                cout << "Enter the number of the car you want to remove: ";
                cin >> to_remove;
                cin.ignore();
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid choice. Please try again." << endl;
                    cout << "Enter the number of the car you want to remove: ";
                    cin >> to_remove;
                }

                for (int i = 0; i < UserNumCars; i++)
                {
                    if (usercars[i].carnum == to_remove)
                    {
                        notfound = false;
                    }
                    else
                    {
                        continue;
                    }
                }
                if (notfound)
                {
                    cout << "This car is either not yours or doesn't exist please choose another one." << endl;
                }
                else {
                    bool x;
                    removeCar(numCars, to_remove, cars, x);
                    removeCar(UserNumCars, to_remove, usercars, x);
                    if (x) {
                        cout << "The car has been removed successfully! \n";
                    }
                    else {
                        cout << "The car is not found.\n";
                    }
                }



                break;
            }
            case 5: {
                listCars(numCars, cars);
                break;
            }
            case 6: {
                listUsersCars(UserNumCars, usercars);
                break;
            }
            case 7: {
                if (checkCar(numCars, cars)) {
                    cout << "Fortunately, This car is available." << endl;
                    cout << "You can rent it" << endl;
                }
                else {
                    cout << "Unfortunately, This car is not available." << endl;
                    cout << "Press 5 to check for another car." << endl;
                }
                break;
            }
            case 8: {
                int carindex_userfile;
                int rent_carnum;
                rentCar(numCars, cars, rent_carnum);
                for (int i = 0; i < UserNumCars; i++)
                {
                    if (usercars[i].carnum == rent_carnum)

                        carindex_userfile = i;
                }
                copyfunction(searchByCarNum(rent_carnum, numCars, cars), carindex_userfile, cars, usercars);
                break;
            }
            case 9: {

                writeCarsToFile(numCars, cars);
                writeUserCars(UserNumCars, cars, id);
                writeCustomersToFile(numCustomers, customers);
                repeat = false;
                cout << "Logged out successfully!\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
            }

            }
        }
    } while ((ans != 9) && (repeat));
}
//done ... <3
