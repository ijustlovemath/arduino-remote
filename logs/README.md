These log files are the output of strace, used to diagnose the differences in how the Arduino IDE and my attempts at other serial port usages differed. There's pretty clear differences in port setup and polling mechanisms which may explain the functionality differences.

Here's the status of these logs:

- `django-strace.log`: This reflects a functional serial driver launched from Django using pySerial. Look for "/dev/ttyUSB0", file descriptor 3, to see how it sets up the port and reads (char by char!)

- `strace-rust.log`: This reflects a nonfunctional serial driver launched from actix, using serialport.rs. Again, look for "/dev/ttyUSB0", the section with relevant ioctls is remarkably short

- `strace-arduinoIDE.log`: This reflects a functional serial driver as contained within the Arduino IDE. This one is extremely long, so look for "/dev/ttyUSB0" again, which is opened starting on line 954.
