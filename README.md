# ELoad_v2
Arduino based electronic load

## Background:
As a beginning hobbyist I 'designed' and built an electronic load based on a suggestion of Dave Jones of EEVBLOG.
It worked great for smaller loads but unfortunately I overloaded it and destroyed a large part of the components. 
I took the opportunity to gather some additional requirements and redesigned it from scratch.

## The main requirements:
- Add temp., amp. and volt sensors (and a display) to track status and add protective limits
- Next to constant current add additional options like constant power and constant voltage
- Forced cooling (add a fan)
- Have reverse voltage protection 
- Settings/limits should be configurable
- use an external power source (don't rely on power from the device under test)
 
## Components used:
- 4x20 LCD
- rotary encoder to set values
- Several sensors
- Arduino pro mini to manage logic, configuration and control the applied load 
  - A separate DAC to improve granularity 

## Development plan ELoad v2.1:
GitHub project: https://github.com/users/srooij69/projects/1
Goal:
- create software for the new hardware
- Hardware:
    - LCD:
        Show state and sensor readings
        Show error + relevant sensor + config
    - Mode pushbutton: 
        (short) Select mode of operation
        (short) Select config item
        (long) Switch between config and operation
    - Run pushbutton:
        Switches runmode (Select / Run / Error)
    - LED shows runmode
    - Rotary Encoder:
        rotate change target value
        push switch increment size

    - DAC: used to drive Resistance
    - Sensors: Temp, Current & Voltage

Development using TDD

=> High level modules do only high level stuff
=> Low level modules 
=> All Arduino specific code = lowest level. Moved to interface modules
