# 7701F

Code for Vex Robotics Competition 2021-2022 Tipping Point for 7701F

## Authors

- **Michael Gummere** - [GitHub](https://github.com/Chrono-byte)

See also the list of [contributors](https://github.com/7701F/2021-Tipping-Point/contributors) who participated in this project.

# Dependancies

[PROS](https://github.com/purduesigbots/pros) A lightweight and fast alternative open source operating system for the VEX V5 Brain.

[ARMS](https://github.com/purduesigbots/ARMS) ARMS is a library that makes programming a VEX V5 robot a piece of cake.

<!-- [EZ-Template](https://github.com/EZ-Robotics/EZ-Template): 2.1.0 -->

<!-- [gif-pros](https://github.com/theol0403/gif-pros) Allows GIFS to be displayed on LVGL (Currently removed) -->

 This should give you the location of the line that triggered the exception.
# Debugging Guide

In case of a segfault or data abort exception, the first step is to make sure you run your program with the PROS terminal connected. When the exception occurs, you should see a section that starts with "BEGIN STACK TRACE" and contains a list of numbers. These numbers are the addresses of the instructions on the call stack at the time of the exception. Make a note of them.

Now we can translate the addresses into filenames and even line numbers. Close the PROS terminal connection if you haven't already, and run the following command:
(For windows:)
```
"%PROS_TOOLCHAIN%\bin\arm-none-eabi-addr2line" -faps -e .\bin\hot.package.elf
```
(For linux/macos:)
```
arm-none-eabi-addr2line -faps -e ./bin/hot.package.elf
```
then you can paste in the addresses from earlier.

Note: You may also need to change `hot.package.elf` to `cold.package.elf` if you get a bunch of question marks. Also if you don't have the hot or cold packages, run with `monolith.elf` instead.

This should give you the location of the line that triggered the exception.

# License

This project is licensed under the terms of [MPL-2.0](https://github.com/7701F/2021-Tipping-Point/blob/master/LICENSE)
