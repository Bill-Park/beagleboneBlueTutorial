import Adafruit_BBIO.PWM as PWM

servoPin = "P9_14"
PWM.start(servoPin, 5, 50)