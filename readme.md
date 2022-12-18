# DualSense Controller for Arduino

This lib provides easy to use event-based access to the functionalities of the DualSense PlayStation Controller.

It is based on the PS5 core of the [USB Host Shield 2.0 Library](https://github.com/felis/USB_Host_Shield_2.0).
It is a more comfortable wrapper with event based access to changes.

## Features:

- event callback for state changes of:
  - digital buttons
  - analog buttons
  - analog hats
  - gyro and acceleration sensors
  - touchpad


- set and control:
  - leds
  - hard and soft rumble
  - adaptive trigger force

## Supported Boards

Because this lib is based on the [USB Host Shield 2.0 Library](https://github.com/felis/USB_Host_Shield_2.0) it should be usable with all [boards which are supported by the USB Host Shield Library 2.0](https://github.com/felis/USB_Host_Shield_2.0#boards)

On boards small flash storage. like the Arduino Uno or the Arduino Nano it could be problematic to upload the example.

We tested our lib only with [ESP32 DevKitC V4](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/hw-reference/esp32/get-started-devkitc.html) and this [ESP8266 Board](https://www.az-delivery.de/en/collections/esp8266/products/nodemcu-lolin-v3-modul-mit-esp8266).
For both boards u need an extra Arduino core: [ESP8266 Arduino Core](https://github.com/esp8266/Arduino) or [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32/)


## Getting started 

The best documentation for the lib is currently the [DualSenseControllerDemo](https://github.com/yesbotics/dualsense-controller/blob/main/examples/DualSenseControllerDemo/DualSenseControllerDemo.ino)
