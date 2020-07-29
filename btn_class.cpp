#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std ;

#define BTN_PATH "/sys/class/gpio/gpio"
#define SYSFS_GPIO_EXPORT_DIR "/sys/class/gpio/export"
#define SYSFS_GPIO_UNEXPORT_DIR "/sys/class/gpio/unexport"

class Button
{
    private :
        string path ;
        int number ;
    public :
        Button(int button_number) ;
        void attach() ;
        void release() ;
        int read() ;
} ;

Button::Button(int button_number)
{
    number = button_number ;
    path = BTN_PATH + to_string(button_number) ;
}

void Button::attach()
{
    ofstream fs ;
    fs.open(SYSFS_GPIO_EXPORT_DIR) ;
    fs << to_string(this->number) ;
    fs.close() ;
}

void Button::release()
{
    ofstream fs ;
    fs.open(SYSFS_GPIO_UNEXPORT_DIR) ;
    fs << to_string(this->number) ;
    fs.close() ;
}

int Button::read()
{
    ifstream fs ;
    char value ;
    fs.open(this->path + "/value") ;
    fs.read(&value, 1) ;
    fs.close() ;
    
    return (int)value - '0' ;
}


int main(int argc, char* [])
{
    int value0, value1 ;
    
    Button btn0 = Button(68) ;
    Button btn1 = Button(69) ;
    btn0.attach() ;
    btn1.attach() ;
    
    while (1) {
        value0 = btn0.read() ;
        value1 = btn1.read() ;
        
        cout << value0 << " " << value1 << endl ;
        sleep(1) ;
    }
    
    btn0.release() ;
    btn1.release() ;
    
    return 0 ;
}

