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
- 
## Components used:
- 4x20 LCD
- rotary encoder to set values
- Several sensors
- Arduino pro mini to manage logic, configuration and control the applied load 
  - A separate DAC to improve granularity 
