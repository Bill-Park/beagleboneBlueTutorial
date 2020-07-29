#include <iostream>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

#include <rc/time.h>
#include <rc/adc.h>
#include <rc/servo.h>

using namespace std ;

int main(int argc, char* [])
{
    int ch = 1 ;
    int status ;
    
    status = rc_adc_init() ;
    cout << "adc_init " << status << endl ;
    
    status = rc_adc_batt() ;
    cout << "battery check " << status << endl ;
    
    rc_adc_cleanup() ;
    
    status = rc_servo_init() ;
    cout << "servo init " << status << endl ;
    
    rc_servo_power_rail_en(1) ;
    
    
    int p = 1300 ;
    int r = 1 ;
    while (1) {
        rc_servo_send_pulse_us(ch, p) ;
        rc_usleep(1000 * 20) ;
        cout << p << endl ;
        p += r * 10 ;
        if (p > 1800 || p < 1200) {
            r *= -1 ;
        }
    }
    
    rc_servo_power_rail_en(0) ;
    rc_servo_cleanup() ;
    
    return 0 ;
}