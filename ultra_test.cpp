#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>

using namespace std ;
using namespace std::chrono ;

#define GPIO_PATH "/sys/class/gpio/gpio"
#define GPIO_EXPORT "/sys/class/gpio/export"
#define GPIO_UNEXPORT "/sys/class/gpio/unexport"

int write_to_path(const char* path, string value)
{
    int f ;
    f = open(path, O_WRONLY | O_CLOEXEC) ;
    if (f < 0) {
        return -1 ;
    }
    write(f, value.c_str(), value.length()) ;
    close(f) ;
    return 0 ;
}

void read_from_path(const char* path, char* buffer, int length)
{
    int f ;
    f = open(path, O_RDONLY | O_CLOEXEC) ;
    read(f, buffer, length) ;
    close(f) ;
}

int main(int argc, char* [])
{
    int f_export, f_unexport, status ;
    string echo = "113" ;
    string trig = "116" ;
    
    f_export = open(GPIO_EXPORT, O_WRONLY | O_CLOEXEC) ;
    cout << f_export << endl ;
    
    status = write(f_export, echo.c_str(), echo.length()) ;
    status = write(f_export, trig.c_str(), trig.length()) ;
    close(f_export) ;
    
    if (status < 0) {
        return -1 ;
    }
    
    write_to_path((GPIO_PATH + trig + "/direction").c_str(), "out") ;
    
    write_to_path((GPIO_PATH + trig + "/value").c_str(), "1") ;
    usleep(10) ;
    write_to_path((GPIO_PATH + trig + "/value").c_str(), "0") ;
    
    int f_echo ;
    char buf[5] = "" ;
    system_clock::time_point start, end ;
    
    while (1) {
        read_from_path((GPIO_PATH + echo + "/value").c_str(), buf, 1) ;
        if (buf[0] == '1') {
            start = system_clock::now() ;
            break ;
        }
    }
    
    while (1) {
        read_from_path((GPIO_PATH + echo + "/value").c_str(), buf, 1) ;
        if (buf[0] == '0') {
            end = system_clock::now() ;
            break ;
        }
    }
    
    microseconds micro = duration_cast<microseconds>(end - start) ;
    cout << "length " << micro.count() / 58 << " cm" << endl ;
    
    f_unexport = open(GPIO_UNEXPORT, O_WRONLY | O_CLOEXEC) ;
    cout << f_unexport << endl ;
    
    status = write(f_unexport, echo.c_str(), echo.length()) ;
    status = write(f_unexport, trig.c_str(), trig.length()) ;
    close(f_unexport) ;
    
    return 0 ;
}



// 113 - echo
// 116 - trig

// trig를 HIGH로 설정
// 10us 대기
// trig를 LOW로 설정

// echo가 HIGH 될 때까지 대기
// 타이머 시작
// echo가 LOW 될 때까지 대기
// 타이머 종료
// 타이머 간격을 통한 거리값 읽기
