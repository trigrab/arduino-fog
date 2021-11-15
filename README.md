# What is this?

This is a arduino project to control a simple fog machine like the crenova FM-02. The Original switch does nothing more than short circuit two of the three wires. I made a simple circuit which is connected to the original switch. Another possibility would be to replace the original switch.

# How to use?
Just change the define statements in `include/fogger.h` to match your requirements. Copy the `config.yml.dist` to `config.yml` and change th values to your needs.
To build it and upload it to your esp8266, use platformio.org
This is tested with PlatformIO 5.2.3, but any newer version and a few older versions should work too.

# What circuit do I need?
I myself used a relais to switch the fog machine. Normally a transistor should also work.

# Further work
In the future I want to read the led state of my original switch to know when the fog machine is in ready state. For now, this works fine enough for my needs.
