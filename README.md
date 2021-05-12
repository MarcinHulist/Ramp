# Ramp

App that creates pattern in 565 RGB format based on colours of four corners of the screen. Then it displays it.

## Requirements

1. CMake
1. C++ compiler

## External Libraries

1. Catch2 for Unit tests https://github.com/catchorg/Catch2 (included in the repo)

## Building

1. Run Cmake
1. Build (Unit test should run automaticlly on succesfull build)

## How to use it

Run ramp.exe with parameters:

`ramp.exe display tl tr [bl] [br] `  
| Parameter   | Description |
| ------------|-----------------------------------------------------------------------------------------------------|
| display     |  the name of the display device.                                                                    |
| tl          | the top left colour value (decimal or hex). Value Range [0 - 65535].                                |
| tr          | the top right colour value (decimal or hex). Value Range [0 - 65535].                               |
| bl          | the bottom left colour value (decimal or hex). Value Range [0 - 65535]. [optional, defaults to tl]  |
| br          | the bottom right colour value (decimal or hex). Value Range [0 - 65535]. [optional, defaults to tr] |
