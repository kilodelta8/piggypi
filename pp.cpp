#include <iostream>
#include <iomanip>
#include <string>
#include <unistd.h>
#include <fstream>
#include <wiringPi.h>
#include <chrono>
#include <ctime>


//function prototype----------------------------------------------------------gteTime() proto
std::string time();
void log(std::ofstream &outFile, std::string data);



int main()
{
    
    //setup a file for logging
    std::ofstream outFile; //<-----all ops for outFile are carried out in log()
    
    //Setup wiringPi
    wiringPiSetup();

    //check to see if wiring pi setup correctly
    if (!wiringPiSetup()){
        std::cout << "WiringPi failed to setup properly, Exiting the program!\n";//let you know
        log(outFile, "Failed to setup wiringPi()");
        return 1;
    }
    else if (wiringPiSetup())
    {
        log(outFile, "wiringPiSetup() initialzed successfully");
    }
    else
    {
        std::cout << "Some other failure has occurred!\n";
        log(outFile, "Else executed, unknown reason!");
    }

    //Setup pins
    //run the program until quit

    return 0;
}

//----------->>FUNCTIONS<<--------------------------------------------------------------

//This functions gets the current time and returns it as a string
std::string time()
{
    // declaring argument of time() 
    time_t my_time = time(NULL); 
    // ctime() used to give the present time 
    std::string time = ctime(&my_time); 
    return time;
}

//log() takes the OFSTREAM object and a string as an argument and appends both to
//a text file specified in the function.  It also calls the time() function and adds
//the date and time the log was made to the file.
void log(std::ofstream &outFile, std::string data)
{
    //dont forget to create the file object in main
    outFile.open("/home/kd8/cpp/piggypi/testData.txt", std::ios::app);
    //check to make sure the file has opened correctly
    if (!outFile.is_open())
    {
        std::cout << "Log() Failed to open file...\n";//<----let you know via console
    }
    else if (outFile.is_open())
    {
        outFile << time() << data << std::endl; //<------log the data to the file
    }
    //close the file
    outFile.close();
}