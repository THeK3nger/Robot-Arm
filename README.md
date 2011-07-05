# Robot Arm v. 1.2

RobotArm is a 3D simulation of a robotic arm. The model was build throught the Denavit-Hartenberg table.

## Dependence

* OpenGL
* Glut
* libxmu
* libxi

## How to build

### Linux

    mkdir build
    cd build
    cmake ..
    make

### Windows

TODO

## How to run

In the build directory run `./robotarm`.

## Controll

In *Robot Arm* you can use the following control key:

* `a/d` - Turn the camera around the robot clockwise/counterclockwise. 
* `+/-` - Change the selected joint.
* `o/p` - Change the q-value of the selected joint.
* `SPACE` - Start/Stop the animation.
