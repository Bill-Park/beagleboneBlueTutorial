#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std ;

#define ADC_PATH "/sys/bus/iio/devices/iio:device0/in_voltage3_raw"

int main(int argc, char* [])
{
    char value[5] = "" ;

    ifstream adc_fs ;

    adc_fs.open(ADC_PATH) ;
    adc_fs.getline(value, 5) ;
    cout << value << endl ;
    adc_fs.close() ;
    
    return 0 ;
}
