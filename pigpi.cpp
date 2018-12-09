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
const unsigned int TIMECOUNT = 3600000;//<----one hour
const unsigned int TIMECOUNTMAX = 86,400,000;//<----one day


/*MAIN<------------------------------------>MAIN*/
int main(){
    //variables
    int priorityNum, setupNum, pinOne, pinTwo;
    unsigned int timeSinceStart = 0, timeSinceLastRun = 0;
    //initialize data file object
    ofstream dataFile;

    //if not signed in as root, exit
    if (geteuid() != 0){
        fprintf(stderr, "Need to be root to run (sudo?)\n");
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
    setupNum = wiringPiSetup();
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

    //start a count of time since starting program?
    timeSinceStart = millis();//<--will this work here or parallel loop?

    //main loop to keep checking pin state
    do{
        //reads pin state
        pinOne = digitalRead(1);//<---is this the right pin?
        pinTwo = digitalRead(2);//<---or.....????
        //based on pin state, turn other pin on or off
        if (pinOne == 0){
            break;//<----------if water level is good then skip and wait
        }else if (pinOne == 1){
            //make pin 2 turn on to let water flow until pinOne reads True/full
            while (pinOne == 0){
                digitalWrite(2, HIGH);//<---turn water solenoid on until pinOne reads true
            }
            digitalWrite(2, LOW);//<----turn water solenoid off
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

        //need to find a way to break the loop, maybe after X amount of time? Line #62
    }while(timeSinceStart != TIMECOUNTMAX);
 

    return 0;
}
