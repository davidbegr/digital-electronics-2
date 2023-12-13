# Smart plant watering system

### Team members

* Viktor Vlček 
* Filip Tůma 
* Šimon Bárta 
* David Bartoň 

## Theoretical description and explanation

Our task for this project was to built smart plant watering system with Arduino UNO and other necessary external modules. To show temperature and humidity in plants' pot we used SSD1306 0.96 inch I2C OLED display. To measure the moisture we used Capacitive Soil Moisture sensor V1.2 and for room temperature Temperature and Humidity sensor DHT12. If moisture of soil is bellow certain percentage limit, then the system will turn on relay, which in the reality represents switching on solenoid that waters the plant.

## Hardware description of demo application

Our system will check soil moisture every 8 seconds with Soill Moisture Sensor V1.2. Once we read this data we will display it on OLED screen to let user know. Everything is powered by 5V from Arduino and connected to same GND. Soil moisture sensor analog output is connected to A0 (mandatory). OLED display uses I2C communication so it is connected to `SCL` and `SDA` pins. Relay input is controlled and connected to Arduino via digital PIN 8. The last thing is Temperature and humidity sensor DHT12. This module also uses I2C communication so it is connected to `SCL` and `SDA` pins.

**Schematic of our wiring:**
![Schematics](Schematics/UNO_schem.PNG)

## Software description

Data from soil moisture sensor needs to be put through internal Analog-to-digital converter on the Arduino board, which is utilized in the `main(void)` of our [main.c](src/main.c). It also needs `ISR(ADC_vect)`. Every pin we are using is hard-coded and therefore mandatory, this could be improved by libraries. For OLED and temperature sensor we are using IIC communication timed via `TIMER0`.

Direct link to source files in [lib](https://github.com/FilipTuma2001/DE2/tree/main/Moisture_sensor/lib):
- [UART library](lib/uart) (Source: from P. Fleury)
- [TWI library](lib/twi) (Source: from doc. T. Fryza)
- [OLED library](lib/oled) (Source: M. Köhler)
- [ADC library](lib/adc)

Direct link to source files in [src](https://github.com/FilipTuma2001/DE2/tree/main/Moisture_sensor/src):
- [Main](src/main.c)


## Instructions

Using this system is easy:
1. Connect power to the Arduino UNO and upload the code
2. Put moisture sensor into the soil in recommended depth
3. Place the display somewhere visible
4. Install solenoid onto your plant-watering-system.
5. You can also check the room temperature via DHT12 sensor

**Final form of the project:**
![Photos](Photos/Completed%20project.jpeg)

**Short demonstration of how it works:**
![Watch the video](https://youtu.be/CLtIR6DckKM)


## References

1. [Tomas Fryza's digital-electronics-2 repository](https://github.com/tomas-fryza/digital-electronics-2/tree/master)
2. [Working principle and hacking a capacitive soil moisture sensor](https://thecavepearlproject.org/2020/10/27/hacking-a-capacitive-soil-moisture-sensor-for-frequency-output/)
3. [ATmega328p datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
4. [Soil Moisture sensor V1.2 description](https://www.robotics.org.za/CAP-SW-12)
5. [OLED Display detasheet](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf)
6. [Temperature and humidity sensor DHT12 datasheet](https://datasheetspdf.com/pdf-file/1147840/Aosong/DHT12/1)