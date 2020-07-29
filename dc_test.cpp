#include <iostream>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

#include <rc/motor.h>
#include <rc/time.h>

using namespace std ;

int main(int argc, char* [])
{
    int ch = 1 ;
    double speed = 0.0 ;
    int freq = RC_MOTOR_DEFAULT_PWM_FREQ ;
    int status ; 
    
    status = rc_motor_init_freq(freq) ;
    cout << "init freq " << status << endl ;
    rc_motor_brake(1) ;
    
    cout << "input speed : " ;
    cin >> speed ;
    rc_motor_set(ch, speed) ;
    rc_usleep(1000 * 3000) ;
    
    rc_motor_cleanup() ;
    
    return 0 ;    
}