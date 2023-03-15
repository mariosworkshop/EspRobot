# Servos driver
- control legs of robot and listen serial communication and ps2 controller

## Gyro.h
- set MPU6050 on
- read data from gyro

## PS2_remote.h
- initialize ps2 receiver
- read joystick value
- read buttons value

## ReadServo.h
- :exclamation: ~~experimental class~~
- will read state of servos before start
- robot start will fluent (not jerky)
> to future use

## SERVOControl.h
- initialize pca9685
- read data from FS (file system of esp)
- assign base position to servos and eliminates inaccuracy of servos (±2 degrees)
- move servos in delay
> ready to be deployed to neural network

## ServoJoint.h
- store data about servo (mid., max, min, ... positions)
- move servo about 1 step, if needed

## main.ino
- move servos by SERVOControl.h, if needed
- parse serial data to array and send it to servos
- react to ps2 events

## [data](https://github.com/mariokompan/EspRobot/tree/main/Programs/Servos%20driver/main/data)
- contain data to home positions of servos
