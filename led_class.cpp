#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std ;

#define LED_PATH "/sys/class/leds/beaglebone:green:usr"

class LED
{
    private :
        string path ;
        int number ;
        void writeLED(string filename, string value) ;
        void resetTrigger() ;
    public :
        LED(int number);
        void on() ;
        void off() ;
        void blink(string delayms) ;
        void currentState() ;
        void test() ;
} ;

LED::LED(int led_number)
{
   number = led_number ;
   path = LED_PATH + to_string(number) ;
}

void LED::writeLED(string filename, string value)
{
    ofstream fs ;
    fs.open((path + filename).c_str()) ;
    fs << value ;
    fs.close() ;
}

void LED::resetTrigger()
{
    writeLED("/trigger", "none") ;
}

void LED::on()
{
    resetTrigger() ;
    writeLED("/brightness", "1") ;
}

void LED::off()
{
    resetTrigger() ;
    writeLED("/brightness", "0") ;
}

void LED::blink(string delayms)
{
    writeLED("/trigger", "timer") ;
    writeLED("/delay_on", delayms) ;
    writeLED("/delay_off", delayms) ;
}

void LED::currentState()
{
    ifstream fs ;
    fs.open((path + "/trigger").c_str()) ;
    string line ;
    while(getline(fs,line)) cout << line << endl ;
    fs.close() ;
}

void LED::test()
{
    cout << number << endl ;
    cout << path << endl ;
}


int main(int argc, char* argv[])
{
    std::fstream fs ;
    
    LED led1 = LED(0) ;
    LED led2 = LED(1) ;
    // led1.currentState() ;
    
    // led1.blink("500") ;
    // led2.blink("1000") ;
    led1.test() ;
    while(1) {
        led1.on() ;
        led2.off() ;
        sleep(1) ;
        led1.off() ;
        led2.on() ;
        sleep(1) ;
    }
}