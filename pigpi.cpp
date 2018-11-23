/*
Program to monitor, feed and water guinea pigs for my daughter, in an attempt
to get her into STE(A)M.
11/22/2018
kilo.kilo.delta8@gmail.com
rev......X
*/
#include <iostream>
#include <wiringPi.h>
#include <string>
using namespace std;

/*Classes<------------------------------->Classes*/
class Cage{
    private:
    
    public:
};

class Initializer{  //<---to initialize gpio pins, maybe can add to Sensor class
    private:
    int x;
    public:
    int set(void){
        int y;
        int errorCode = 305;
        y = wiringPiSetup();
        if (y){
            return y;
        }
        else if (!(y)){
            return y;
        }
        else{
            return errorCode;
        }
    }

};

class Sensor{
    private:
    int state, pin;
    public:
    //setup gpio
    int stateReader(void){

    }
    //verify correct gpio
    //read state
    //
};

class Camera{
    private:
    public:
};

/*MAIN<------------------------------------>MAIN*/
int main()
{
    //define variables
    Sensor water, food;
    int x, y, z;
    //read gpio states<---move to proper classes
    x = water.stateReader();
    y = food.stateReader();
    if (x == 0 && y == 0){
        cout << "The water & food sensor is reading full\n";
    }
    else if (x == 1 && y == 1){
        cout << "The water & food sensor is reading empty\n";
    }
    else{
        cout << "ERROR 304\n";
    }

    //read water sensor
    //if water sensor false
        //solenoid gpio true until sensor true
        //solenoid sensor false
    //repeat every hour
    //end

    return 0;
}
