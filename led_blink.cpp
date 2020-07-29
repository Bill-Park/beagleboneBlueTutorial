#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std ;

#define LED0_PATH "/sys/class/leds/beaglebone:green:usr0"

int main(int argc, char* argv[])
{
    std::fstream fs ;
    
    fs.open(LED0_PATH "/trigger", std::fstream::out) ;
    fs << "none" ;
    fs.close() ;
    
    while(1) {
        fs.open(LED0_PATH "/brightness", std::fstream::out) ;
        fs << "1" ;
        fs.close() ;
        sleep(1) ;
        
        fs.open(LED0_PATH "/brightness", std::fstream::out) ;
        fs << "0" ;
        fs.close() ;
        sleep(1) ;
    }
}