#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <asm/termbits.h>

using namespace std ;

#define UART_PATH "/dev/ttyS"

class UART
{
    private :
        struct termios2 uartTerm ;
        string path ;
        int uartID, uartNum, uartStatus ;
        int baudrates ;
        char buffer[10] ;
    public :
        UART(int num, int baud) ;
        int init() ;
        int write_string(string data) ;
        int read_bytes(int len) ;
        ~UART() ;
} ;

UART::UART(int num, int baud)
{
    path = UART_PATH + to_string(num) ;
    baudrates = baud ;
}

int UART::init()
{
    uartID = open(path.c_str(), O_RDWR | O_NOCTTY | O_NDELAY) ;
    if (uartID < 0) {
        return uartID ;
    }
    
    uartNum = ioctl(uartID, TCGETS2, &uartTerm) ;
    if (uartNum < 0) {
        return uartNum ;
    }
    
    uartTerm.c_cflag &= ~CBAUD ;
    uartTerm.c_cflag |= BOTHER ;
    
    uartTerm.c_cflag |= CREAD ;
    uartTerm.c_ospeed = baudrates ;
    uartTerm.c_ispeed = baudrates ;
    
    uartNum = ioctl(uartID, TCSETS2, &uartTerm) ;
    if (uartNum < 0) {
        return uartNum ;
    }
    
    return 0 ;
}

int UART::write_string(string data)
{
    uartStatus = write(uartID, data.c_str(), data.length()) ;
    return uartStatus ;
}

int UART::read_bytes(int len)
{
    uartStatus = read(uartID, buffer, len) ;
    cout << buffer << endl ;
    return uartStatus ;
}

UART::~UART()
{
    close(uartID) ;
}



int main(int argc, char* [])
{
    int status ;
    UART uart = UART(1, 9600) ;
    
    status = uart.init() ;
    cout << status << endl ;
    
    status = uart.write_string("test") ;
    cout << status << endl ;
    
    sleep(3) ;
    
    status = uart.read_bytes(5) ;
    cout << status << endl ;
    
    return 0 ;
}