/*
Program to monitor, feed and water guinea pigs for my daughter, in an attempt
to get her into STE(A)M.
For use on a Raspberry Pi using the wiringPi.h library.
11/22/2018
kilo.kilo.delta8@gmail.com
rev......X
*/
#include <iostream>
#include <wiringPi.h>
#include <string>
#include <fstream>
using namespace std;

//number of pins being used<---not sure this is the right way to do it
const int NUMofPINS = 2;
//time constant for do-while
const unsigned int TIMECOUNT = 3600000;


/*MAIN<------------------------------------>MAIN*/
int main(){
    //variables
    int priorityNum, setupNum. pinOne, pinTwo;
    //initialize data file object
    ofstream dataFile;

    //if not signed in as root, exit
    if (geteuid() != 0){
        fprintf(stderr, "ladder: Need to be root to run (sudo?)\n");
        exit(0);
    }

    //set program to high priority
    priorityNum = piHiPri(1);
    if (priorityNum == 0){
        break;
    }else if (priorityNum != 0){
        cout << "Failed to set as high priority...\n";
    }

    //set gpio pins
    setupNum = wiringPiSetup(void);
    if (setupNum == 0){
        break;
    }else if (setupNum != 0){
        cout << "WiringPi failed to setup GPIO pins...\n";
    }

    //set pins to in/out mode (how many pins do I need based on 1 sensor)
    for (int i = 0; i < NUMofPINS; i++){
        if (i == 0){
            pinMode(i, INPUT);//<--------need to better define setting pin numbers
        }else if (i == 1){
            pinMode(i, OUTPUT);
        }
    }

    //main loop to keep checking pin state
    do{
        //reads pin state
        pinOne = digitalRead(1);
        pinTwo = digitalRead(2);
        //based on pin state, turn other pin on or off
        if (pinOne == 0){
            break;//<----------if water level is good then skip and wait
        }else if (pinOne == 1){
            //make pin 2 turn on to let water flow
        }

        //add data to dataFile
        dataFile.open("dataFile.txt", ios::out);
        if (dataFile.is_open()){
            //add/append data to file Date/Frequency/Etc
            dataFile.close();
        }else{
            cout << "Data file failed to open...\n";
        }
        
        //wait one hour
        delay(TIMECOUNT);//<-----waits an hour before restarting loop
        //need to find a way to break the loop, maybe after X amount of time?
    }while();
 

    //read water sensor
    //if water sensor false
        //solenoid gpio true until sensor true
        //solenoid sensor false
    //repeat every hour
    //end

    return 0;
}
