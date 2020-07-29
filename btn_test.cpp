#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std ;

#define BTN_PATH "/sys/class/gpio/gpio68/value"
#define SYSFS_GPIO_EXPORT_DIR "/sys/class/gpio/export"
#define SYSFS_GPIO_UNEXPORT_DIR "/sys/class/gpio/unexport"

int main(int argc, char* [])
{
    string btn_num = "68" ;
    char value[5] = "" ;
    
    ofstream fs ;
    ifstream btn_fs ;
    
    fs.open(SYSFS_GPIO_EXPORT_DIR) ;
    fs << btn_num ;
    fs.close() ;
    
    btn_fs.open(BTN_PATH) ;
    btn_fs.read(value, 1) ;
    cout << value << endl ;
    btn_fs.close() ;
    
    fs.open(SYSFS_GPIO_UNEXPORT_DIR) ;
    fs << btn_num ;
    fs.close() ;
    
    return 0 ;
}

