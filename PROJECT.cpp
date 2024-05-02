#include <iostream>
#include <fstream>
#include <string>
#include <limits>
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
// ----- Functions ------
int  removeCar(int& numCars, int to_remove, Car cars1[],bool& x);   //Loay
void copyfunction(int sysnum , int usernum,Car cars[],Car usercars[]); //Noha
int  readCarsFromFile(Car cars1[]);
int  readUserCars(Car usercars[], int id);
void writeCarsToFile(int numCars, Car cars1[]);
void writeUserCars(int UserNumCars, Car usercars[],int id);
int  readCustomersFromFile(Customer customers[]);
void writeCustomersToFile(int numCustomers, Customer customers[]);
int  addCar(int& m, Car cars1[]); //Mohammed Tarek
void updateCar(int carChoice, Car cars1[],int numCars); //Nada
void listCars(int n, Car cars1[]); //Mohammed
bool checkCar(int NumCars,Car cars1[]); //Noha
void CreateFile(int numCustomers ,Customer customers[]); 
void rentCar(int x, Car cars1[], int& n); //Abdallah
bool Customerlogin(int num, Customer customers[],int& IDnum); //Gamel
bool Adminlogin(); //Gamel
void signUp(int& numCustomers,Customer customers[],int& IDnum); //Gamel
void AdminMenu(int numCustomers, int numCars , Customer customers[] , Car cars[]); //Mohammed
void CustomerMenu(int numCustomers, int numCars , Customer customers[] , Car cars[],Car usercars[],int id,int& UserNumCars); //Mohammed
void Rearrange(int UserNumCars,int Numcars , Car cars[],Car usercars[],bool& changed); //Mohammed
int  searchByCarNum(int CarNum, int NumCars,Car cars[]); //Noha
void checkremovedCars(int& usernumcars,int numcars,Car usercars[],Car cars[],bool& removed); //Loay


int  main() {

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
        cout << " \n\n";
        cout << "----------------------\n";
        cout << "1. Admin" << endl;
        cout << "2. Old User" << endl;
        cout << "3. New User" << endl;
        cout << "4. Exit" << endl;
        cout << "----------------------\n";
        cout << "Enter your choice : ";
        cin >> userType;
        while(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please try again."<<endl;
        cout << "Enter your choice : ";
        cin >> userType;
          }

        switch(userType) {
            case 1:{
                if(Adminlogin()){
                    AdminMenu(numCustomers, numCars , customers,cars);
                    break;
                }else{
                    break;
                }
            }
            case 2:{

                    bool changed;
                    bool removed;
                    if(Customerlogin(numCustomers,customers,id)){
                    int UserNumCars = readUserCars(usercars,id);
                    Rearrange(UserNumCars,numCars,cars,usercars,changed);
                    if(changed){
                            cout << "\n-------------\n";
                            cout << "The admin has updated one of your cars.";
                            cout << "\n-------------\n";
                    }
                    checkremovedCars(UserNumCars,numCars,usercars,cars,removed);    
                    if(removed){
                            cout << "\n-------------\n";
                            cout << "The admin has removed one of your cars.";
                            cout << "\n-------------\n";
                    }
                    CustomerMenu(numCustomers, numCars,customers,cars,usercars,id,UserNumCars);
                    writeUserCars(UserNumCars,usercars,id);
                    break;
                }else{
                    break;
                }}
            case 3:{
                signUp(numCustomers,customers,id);
                writeCustomersToFile(numCustomers,customers);
                int UserNumCars = readUserCars(usercars,id);
                CustomerMenu(numCustomers,numCars,customers,cars,usercars,id,UserNumCars);
                writeUserCars(UserNumCars,usercars,id);
                break;}
            case 4:{
                cout << "Exiting the program.............................." << endl;
                validInput = true;
                break;}
            default:{
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
    return 0;
}

int addCar(int& numCars, Car cars1[]) {//TODO:muhammad

    cars1[numCars].carnum = (cars1[numCars-1].carnum + 1); // index of new car is numCars , and (numCars+1) is the number of cars in system after adding

    cout << "Enter car's Brand : ";
    cin >> cars1[numCars].brand;

    cout << "Enter car's Model : ";
    cin >> cars1[numCars].model;

    cout << "Enter car's Color : ";
    cin >> cars1[numCars].color;

    cout << "Enter car's Distance Traveled : ";
    cin >> cars1[numCars].distanceTraveled;
        while(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please try again."<<endl;
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

void updateCar(int carChoice, Car cars1[],int numCars) {//TODO:Nada
bool repeat=1;
while(repeat){

    int detailChoice;
    cout << "\t-----\n";
    cout << "1.Brand.\n2.Model.\n3.Color.\n4.Distance travelled by kilometer.\n5.Go back.\n";
    cout << "\t-----\n";
    cout << "Which detail you want to change : ";
    cin >> detailChoice;
    while(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid choice."<<endl;
        cout << "Which detail you want to change : ";
        cin >> detailChoice;
                    }


    if(carChoice >= 1 && carChoice <= MAX_CARS) {
        int carindex = searchByCarNum(carChoice,numCars,cars1);
        switch (detailChoice)
        {
        case 1:
            cout << "Enter the updated details :" << endl;
            cout << "Brand :";
            cin >> cars1[carindex].brand;
            cout << "The details are updated successfully" << endl;
            repeat = false;
            break;
        case 2:
            cout << "Enter the updated details :" << endl;
            cout << "Model :";
            cin >> cars1[carindex].model;
            cout << "The details are updated successfully" << endl;
            repeat = false;
            break;
        case 3:
            cout << "Enter the updated details :" << endl;
            cout << "Color :";
            cin >> cars1[carindex].color;
            cout << "The details are updated successfully" << endl;
            repeat = false;
            break;
        case 4:{
            cout << "Enter the updated details :" << endl;
            cout << "Distance travelled by kilometer :";
            cin >> cars1[carindex].distanceTraveled;
            while(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please try again."<<endl;
            cout << "Enter a number:";
            cin >> cars1[carindex].distanceTraveled;}
            cout << "The details are updated successfully" << endl;
            repeat = false;
            break;
                }
        case 5:{
            repeat = false;
            break;
        }

        default:{
            cout << "Invalid choice." << endl;
            break;
        }


}}}}
// done ... <3



int removeCar(int& numCars, int to_remove, Car cars1[],bool& x) { //TODO: loay

    bool isfound = false;
    for (int i = 0; i < numCars; i++)
    {
        if (cars1[i].carnum == to_remove)
        {
            isfound = true;
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
    }else{
        x = false;
    }

    return numCars;
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
            cout << "\t-----\n";
        }
    }
    else {

        cout << "There are no available cars to be shown. \n";

    }
}
//done ... <3

bool checkCar(int NumCars,Car cars1[]) { //TODO:Noha
    bool check;
    int carnumber;
    cout << "PLease enter the number of the car you want to check: ";
    cin >> carnumber;
     while(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid data. Please try again."<<endl;
        cout<<"PLease enter the number of the car you want to check: ";
        cin >> carnumber;
    }
    carnumber = searchByCarNum(carnumber,NumCars,cars1);
    if (cars1[carnumber].available) {
        check = true;
    }
    else {
        check = false;
    }
    return check;

}
//done ... <3

void rentCar(int numCars, Car cars1[], int& n){//TODO: abdallah

    char ans;
    bool t = 1;
    while (t)
    {
        cout << "Enter the car's number : ";
        cin >> n;
        while(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid data. Please try again."<< endl;
        cout << "Enter the car's number : ";
        cin >> n;
        }
        int CarIndex = searchByCarNum(n,numCars,cars1);
        if (n <= numCars && n > 0) // check the number is in the range
        {

            if (cars1[CarIndex].available == true) // check if the car is avaliable or rented.
            {
                cout << "\n The Car is Avaliable, You have rented it Succefully!\n\n";
                cars1[CarIndex].available = false;
                break;
            }
            else {
                cout << " Already rented.\n";
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
bool Adminlogin() {

    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (username == adminUsername && password == adminPassword) {
        cout << "\t\t-----\n";
        cout << "Admin logged in successfully!" << endl;
        return 1;
    } else {
        cout << "Invalid username or password. Please try again." << endl;
    return 0;
    }


};
//done ... <3
bool Customerlogin(int num, Customer customers[],int& IDnum)
{
        string username;
        string password;
        cout << "Please enter your data : \n";
        cout << "Name: ";
        cin >> username;
        cout << "ID: ";
        cin >>IDnum;
        while(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid data. Please try again."<<endl;
        cout<<"ID: ";
          cin >>IDnum;
    }
        cout << "Password: ";
        cin >> password;
        bool vailddata = 0;
        for(int i = 0 ; i<num; i++){

            if((customers[i].Id == IDnum ) && (customers[i].Password == password) && (customers[i].name == username)){
                vailddata = 1;
            }

        };
    if(vailddata){
        cout << "\t\t-----\n";
        cout << "You logged in successfully!\n";
        cout << "WELCOME BACK, " << customers[(IDnum-1)].name << endl;
        return 1;
    }else{
        cout <<"Invalid data\n";
     }
     return 0;

}
//done ... <3
void signUp(int& numCustomers,Customer customers[],int& IDnum) {

    if (numCustomers >= MAX_USERS) {
        cout << "Maximum number of customers has been reached. Cannot sign up more users." << endl;
        return;
    }

    Customer newCustomer;
    newCustomer.Id = numCustomers + 1;
    cout << "Enter your name: ";
    cin >> newCustomer.name;
    cout << "Enter your mobile number: ";
    cin >> newCustomer.mobileNum;
    cout << "Enter your address: ";
    cin >> newCustomer.address;
    cout << "Create your password: ";
    cin >> newCustomer.Password;
    customers[numCustomers++] = newCustomer;
    cout << "\t\t-----\n";
    cout << "You signed up successfully! Your ID is: " << newCustomer.Id << "\n";
    IDnum = newCustomer.Id;
    CreateFile(numCustomers,customers);
};
//done ... <3




// filestream functions -> mohammedAhmed 

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
            file <<customers[i].Id << " " <<customers[i].name << " " << customers[i].mobileNum << " " << customers[i].address<< " " << customers[i].Password<< endl;
        }
        file.close();
    }
//done ... <3
void CreateFile(int numCustomers , Customer customers[])
{
    ofstream file;
    file.open ("User " + to_string(customers[numCustomers-1].Id) + ".txt" );
    file.close();
}
//done ... <3
int readUserCars(Car usercars[], int id){

ifstream file("User " + to_string(id) + ".txt" );
        int numCars = 0;
        while (file >> usercars[numCars].carnum >> usercars[numCars].brand >> usercars[numCars].model >> usercars[numCars].color >> usercars[numCars].distanceTraveled >> usercars[numCars].available)
        {
            numCars++;
        }
        file.close();
        return numCars;

}
//done ... <3
void writeUserCars(int UserNumCars,Car usercars[],int id) {
        ofstream file("User " + to_string(id) + ".txt" );
        for (int i = 0; i < UserNumCars; ++i) {
            file << usercars[i].carnum << " " << usercars[i].brand << " " << usercars[i].model << " " << usercars[i].color << " " << usercars[i].distanceTraveled << " " << usercars[i].available << endl;
        }
        file.close();
    }
//done ... <3




//other functions ---->  mohamedAhmed
void copyfunction(int sysnum , int usernum,Car cars[],Car usercars[])
{

usercars[usernum].carnum = cars[sysnum].carnum ;
usercars[usernum].brand = cars[sysnum].brand;
usercars[usernum].model = cars[sysnum].model;
usercars[usernum].color = cars[sysnum].color;
usercars[usernum].distanceTraveled = cars[sysnum].distanceTraveled;
usercars[usernum].available = cars[sysnum].available;

}
//done ... <3
void Rearrange(int UserNumCars,int Numcars , Car cars[],Car usercars[],bool& changed){

                changed=0;
                int carindex_userfile=0;
                bool notfound = true;
                int carindex_sysfile=0;

                for(int i = 0 ; i < UserNumCars ; i++)
                {
                    for(int n = 0; n < Numcars ; n++) {
                    if(usercars[i].carnum == cars[n].carnum)
                    {
                        carindex_userfile=i;
                        carindex_sysfile=n;
                        notfound = false;  }
                    }
                if(notfound)
                {
                    continue;
                }
                else{
                    if(usercars[carindex_userfile].brand!=cars[carindex_sysfile].brand){

                    copyfunction(carindex_sysfile , carindex_userfile ,cars,usercars);
                    changed=1;

                     }else if(usercars[carindex_userfile].model!=cars[carindex_sysfile].model){
                        
                    copyfunction(carindex_sysfile , carindex_userfile ,cars,usercars);
                    changed=1;

                     }else if(usercars[carindex_userfile].color!=cars[carindex_sysfile].color){
                        
                    copyfunction(carindex_sysfile , carindex_userfile ,cars,usercars);
                    changed=1;

                     }else if(usercars[carindex_userfile].distanceTraveled!=cars[carindex_sysfile].distanceTraveled){
                        
                    copyfunction(carindex_sysfile , carindex_userfile ,cars,usercars);
                    changed=1;

                     }else if(usercars[carindex_userfile].available!=cars[carindex_sysfile].available){
                        
                    copyfunction(carindex_sysfile , carindex_userfile ,cars,usercars);
                    changed=1;

                     }
                        }
                   }
                }
//done ... <3
int searchByCarNum(int CarNum, int NumCars,Car cars[]){

    int carIndex;
    for(int i=0;i<NumCars;i++)
        {
            if(cars[i].carnum == CarNum){
                carIndex = i;
            }else {
                continue;
            }

        }

    return carIndex;

};
//done ... <3
void checkremovedCars(int& usernumcars,int numcars,Car usercars[],Car cars[],bool& removed){
bool found=true;
removed = false;
for(int i=0;i<usernumcars;i++)
{


    for (int n = 0 ; n<numcars  ;n++){

        if(usercars[i].carnum == cars[n].carnum){
            found = false;
            break;
        }else{
            found = true;
        }


    }

    if(found)
        {
        bool x;
        removeCar(usernumcars,(usercars[i].carnum),usercars, x);
        removed = true;
        }
    }
}
//done ... <3




// Menus functions----> mohamedAhmed 
void AdminMenu(int numCustomers, int numCars , Customer customers[] , Car cars[]){
    int ans;
    do {

        cout << "----------------------\n";
        cout << "   MAIN MENU:\n";
        cout << "   1. Add Car\n";
        cout << "   2. Update Car Details\n";
        cout << "   3. Remove Car\n";
        cout << "   4. List Of Cars\n";
        cout << "   5. Check Car Availability\n";
        cout << "   6. Rent Car \n";
        cout << "   7. Logout \n";
        cout << "----------------------\n";
        cout << "Enter your choice: ";
        cin >> ans;
        if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please try again."<<endl;
    }
    else{
        switch (ans) {
        case 1:
            addCar(numCars, cars);
            break;
        case 2:{
            int carindex_userfile;
        	int carChoice;
            bool notfound = true;
            cout << "Enter the number of the car you want to update its details : ";
            cin >> carChoice;
            while(cin.fail()){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid choice. Please try again."<<endl;
                        cout << "Enter the number of the car you want to update its details : ";
                        cin >> carChoice;
                            }

            for(int i = 0 ; i < numCars ; i++)
                {
                    if(cars[i].carnum == carChoice)
                    {
                        notfound = false;
                    }else
                    {
                        continue;
                    }
                }

                if(notfound)
                {
                    cout << "This car doesn't exist please choose another one."<< endl;
                }else{
            updateCar(carChoice,cars,numCars);
                    }
                break;
                }
        case 3:
            int to_remove;
            bool x;
            cout << "Enter the number of the car you want to remove: ";
            cin >> to_remove;
            while(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please try again."<<endl;
        cout << "Enter the number of the car you want to remove: ";
        cin >> to_remove;
          }

            removeCar(numCars, to_remove, cars,x);
            if(x)
            {
                cout << "The car has been removed successfully! \n";
            }else{
                cout << "The car is not found\n";
            }

            break;
        case 4:
            listCars(numCars, cars);
            break;
        case 5:
            if (checkCar(numCars,cars)) {
                cout << "Fortunately, This car is available." << endl;
                cout << "You can rent it" << endl;
            }
            else {
                cout << "Unfortunately, This car is not available." << endl;
                cout << "Press 5 to check for another car." << endl;
            }
            break;
        case 6:
            int rent_carnum;
            rentCar(numCars, cars,rent_carnum);
            break;
        case 7:
            writeCarsToFile(numCars, cars);
            writeCustomersToFile(numCustomers, customers);
            cout << "Logged out successfully.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    } while (ans != 7);

}
//done ... <3
void CustomerMenu(int numCustomers, int numCars , Customer customers[] , Car cars[],Car usercars[],int id,int& UserNumCars){
 int ans;
 bool repeat = true;
    do {

        cout << "----------------------\n";
        cout << "   MAIN MENU:\n";
        cout << "   1. Add Car\n";
        cout << "   2. Update Car Details\n";
        cout << "   3. Remove Car\n";
        cout << "   4. List Of Cars\n";
        cout << "   5. Check Car Availability\n";
        cout << "   6. Rent Car \n";
        cout << "   7. Logout \n";
        cout << "----------------------\n";
        cout << "Enter your choice: ";
        cin >> ans;
          if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please try again."<<endl;
          }
          else{
        switch (ans) {

        case 1:{
            addCar(numCars, cars);
            copyfunction((numCars-1) , UserNumCars ,cars,usercars);
            UserNumCars++;
            break;
                }
        case 2:{
            int carindex_userfile;
            int carChoice;
            bool notfound = true;
                cout << "Enter the number of the car you want to update its details : ";
                cin >> carChoice;
                        while(cin.fail()){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid choice. Please try again."<<endl;
                        cout << "Enter the number of the car you want to update its details : ";
                        cin >> carChoice;
                            }


                for(int i = 0 ; i < UserNumCars ; i++)
                {
                    if(usercars[i].carnum == carChoice)
                    {
                        carindex_userfile=i;
                        notfound = false;
                    }else
                    {
                        continue;
                    }
                }
                if(notfound)
                {
                    cout << "This car is either not yours or doesn't exist please choose another one."<< endl;
                }
                else{
                    updateCar(carChoice,cars,numCars);
                    copyfunction((searchByCarNum(carChoice,numCars,cars)) , carindex_userfile ,cars,usercars);
                    }
            break;
                }
        case 3:{

            int to_remove;
            bool notfound = true;
            cout << "Enter the number of the car you want to remove: ";
            cin >> to_remove;
              while(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please try again."<<endl;
        cout << "Enter the number of the car you want to remove: ";
        cin >> to_remove;
          }

            for(int i = 0 ; i < UserNumCars ; i++)
                {
                    if(usercars[i].carnum == to_remove)
                    {
                        notfound = false;
                    }else
                    {
                        continue;
                    }
                }
                if(notfound)
                {
                    cout << "This car is either not yours or doesn't exist please choose another one"<< endl;
                }
                else{
                        bool x;
                        removeCar(numCars, to_remove, cars,x);
                        removeCar(UserNumCars,to_remove,usercars,x);
                        if(x){
                        cout << "The car has been removed successfully! \n";
                         }else{
                        cout << "The car is not found\n";  }
                }



            break;
            }
        case 4:{
            listCars(numCars, cars);
            break;}
        case 5:{
            if (checkCar(numCars,cars)) {
                cout << "Fortunately, This car is available." << endl;
                cout << "You can rent it" << endl;
            }
            else {
                cout << "Unfortunately, This car is not available." << endl;
                cout << "Press 5 to check for another car." << endl;
            }
            break;}
        case 6:{
            int carindex_userfile;
            int rent_carnum;
            rentCar(numCars, cars,rent_carnum);
            for(int i = 0 ; i < UserNumCars ; i++)
                {if(usercars[i].carnum == rent_carnum)

             carindex_userfile=i;}
            copyfunction(searchByCarNum(rent_carnum,numCars,cars),carindex_userfile,cars,usercars);
            break;}
        case 7:{

            writeCarsToFile(numCars, cars);
            writeUserCars(UserNumCars,cars,id);
            repeat = false;
            cout << "Logged out successfully!\n";
            break;
                }
                default:{
                   cout << "Invalid choice. Please try again.\n";
                   break;
                }

             }
        }
    } while ((ans != 7) && (repeat));
}
//done ... <3
