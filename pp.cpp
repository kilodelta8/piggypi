#include <iostream>
#include <iomanip>
#include <string>
#include <unistd.h>
#include <fstream>
#include <wiringPi.h>
#include <chrono>
#include <ctime>

//Classes using wiring pi
class Gpio{
    private:
        std::string pinName;
        int pinNumber;
        bool pinState;
    public:
        void setPinInOut();
        void setPinName(std::string name);
        void setPinNumber(int *pNums, int number);
        void setPinState(int x);
        std::string getPinName();
        int getPinNumber();
        bool getPinState();
        void displayInfo();
};
//sets the pin as input or output
void Gpio::setPinInOut(){
    char ans;
    int pNum = getPinNumber();
    std::string pn = getPinName();
    std::cout << "Is this pin for input (i) or output (o): ";
    std::cin >> ans;
    if (ans == 'i'){
        if (pNum == NULL){
            std::cout << "You must set the pin name and number first.\n";
        } else {
            if (pn == ""){
                std::cout << "You must set the pin name and number first.\n";
            } else {
                pinMode(pNum, INPUT);
            }
        }
    } else if (ans == 'o'){
        if (pNum == NULL){
            std::cout << "You must set the pin name and number first.\n";
        } else {
            if (pn == ""){
                std::cout << "You must set the pin name and number first.\n";
            } else {
                pinMode(pNum, OUTPUT);
            }
        }
    } else {
        std::cout << "An error has occurred while setting the pin to in or out.\n";
        //how can i activate a logging function/class??
    }
}
//sets the pin name
void Gpio::setPinName(std::string name){
    pinName = name;
}
//sets the pin number
void Gpio::setPinNumber(int *pNums, int number){
    int count = 0;
    for (int i = 0; i < 40; i++){
        if (pNums[i] == number){
            pNums[i] == 0;
            pinNumber = number;
        } else if (pNums[i] == 0){
            std::cout << "That number is already in use.\n";
            break;
        } else {
            std::cout << "Something else occurred while setting pin number.\n";
            //logger?
        }
    }
}
//sets the pin state
void Gpio::setPinState(int x){
    int num = getPinNumber();
    pinState = digitalRead(num);
    if (x == 0){
        digitalWrite(num, LOW);
    } else if (x == 1){
        digitalWrite(num, HIGH);
    } else {
        std::cout << "Some error occurred while setting the pin state!\n";
    }
}
//returns the pin name
std::string Gpio::getPinName(){
    return pinName;
}
//returns the pin number
int Gpio::getPinNumber(){
    return pinNumber;
}
//returns the pin state
bool Gpio::getPinState(){
    pinState = digitalRead(getPinNumber());
    return pinState;
}
//displays the pin info
void Gpio::displayInfo(){
    std::cout << "Pin Name: " << pinName << "\n";
    std::cout << "Pin Numb: " << pinNumber << "\n";
    std::cout << "Pin Stat: " << pinState << "\n";
}

//Class to record data-------------not even started yet---------------------------------LOGGER
class Logger{
    private:
    public:
    //is this necassary?????
    //maybe a function would suffice??
};

//function prototype----------------------------------------------------------gteTime() proto
int getTime();

//##################################################################################MAIN
int main(){
    //array to keep track of used/unused pin numbers
    int pNums[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
    17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,
    35,36,37,38,39,40};

    //variables
    std::time_t t = std::time(0);//<-------logs what time the program started
    std::tm* now = std::localtime(&t);

    //setup a file for logging
    std::ofstream outFile;
    outFile.open("/home/kd8/cpp/piggpi/datalog.txt", std::ios::app);

    //Setup wiringPi
    int setupValue = wiringPiSetup();

    //check to see if wiring pi setup correctly
    if (!setupValue){
        std::cout << "WiringPi failed to setup properly. . . . \n";//let you know
        std::cout << "Logging and Exiting the program. . . . .\n";
        if (!outFile.is_open()){ //<---------------------------------make sure logging file opened
            std::cout << "Failed to log failures. . . . .. \n";
        } else if (outFile.is_open()){
            outFile << getTime();//<--------------------------------note the time and error to log
            outFile << "ERROR: WiringPi failed to load.";
            outFile.close();
        } else {
            std::cout << "Some other error occurred!!!\n";
        }
        return 1;
    }

    //Setup pins
    Gpio waterValve;
    Gpio waterSensor1;
    Gpio waterSensor2;
    Gpio alertLed1;
    alertLed1.setPinNumber(pNums, 0);
    alertLed1.setPinName("WaterSensor1led");
    Gpio alertLed2;
    alertLed2.setPinNumber(pNums, 4);
    alertLed2.setPinName("WaterSensor2led");
    Gpio alertLed3;
    alertLed3.setPinNumber(pNums, 7);
    alertLed3.setPinName("WaterSensor3led");


    //clean up
    outFile.close();

    return 0;
}

//----------->>FUNCTIONS<<----------------------------------------------------------------------FUNCTION(S)
int getTime(){
    std::time_t t = std::time(0);//<-------logs what time the program started
    std::tm* now = std::localtime(&t);
    int date = ((now->tm_mon + 1) + (now->tm_mday) + (now->tm_year + 1900));
    return date;
}