/*
main.cpp - main file

Copyright (C) 2015  Balázs Kóti (ktibalazs@gmail.com)

This file is part of Adafruit SSD1306 OLED screen emulator for development.

Foobar is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * WARNING - THE CODE IS IN ALPHA STAGE -
 * FUNCTIONALITY IS VERY LIMITED
 */

#define development_on

#ifdef development_on
    #include "emulator.h"
    #include <QApplication>
    #include <QThread>
#endif

#ifdef development_on
    #define width() device_width()
    #define height() device_height()
    #define usleep(us) QApplication::processEvents(QEventLoop::AllEvents);\
                        QThread::msleep(us/1000);
    #define sleep(s) QApplication::processEvents(QEventLoop::AllEvents);\
                        QThread::sleep(s);

    #define uint8_t unsigned int
    #define int16_t int
#endif

#include "ArduiPi_SSD1306.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

//SAMPLE CODE
#include "example.h"

int main(int argc, char *argv[])
{
    #ifdef development_on
        QApplication a(argc, argv);
    #endif

    Adafruit_SSD1306* device = new Adafruit_SSD1306;

    #ifdef development_on
        //show emulator window
        device->show();
        device->setEmulatorZoom(3);
        device->setSpeedEmulation(false);
    #endif

/***PUT YOUR CODE HERE***/

    /*EXAMPLE CODE: SSD1306_demo.cpp*/
    int i;

    //initialize screen
    // SPI
    int oled_type = OLED_ADAFRUIT_I2C_128x64;
    if (device->oled_is_spi_proto(oled_type)){
        //SPI change parameters to fit to your LCD
        if ( !device->init(OLED_SPI_DC,OLED_SPI_RESET,OLED_SPI_CS, oled_type) )
            exit(EXIT_FAILURE);
    }
    else{
        //I2C change parameters to fit to your LCD
        if ( !device->init(OLED_I2C_RESET, oled_type) )
            exit(EXIT_FAILURE);
    }


    device->begin();

    // init done
    device->clearDisplay();   // clears the screen and buffer


    // draw a single pixel
    device->drawPixel(10, 10, WHITE);
    device->display();
    sleep(2);
    device->clearDisplay();

    // draw many lines

    /*Testdrawline*/
    for (int16_t i=0; i<device->width(); i+=4) {
                device->drawLine(0, 0, i, device->height()-1, WHITE);
                device->display();
          }
          for (int16_t i=0; i<device->height(); i+=4) {
                device->drawLine(0, 0, device->width()-1, i, WHITE);
                device->display();
          }
          usleep(250000);

          device->clearDisplay();
          for (int16_t i=0; i<device->width(); i+=4) {
                device->drawLine(0, device->height()-1, i, 0, WHITE);
                device->display();
          }
          for (int16_t i=device->height()-1; i>=0; i-=4) {
                device->drawLine(0, device->height()-1, device->width()-1, i, WHITE);
                device->display();
          }
          usleep(250000);

          device->clearDisplay();
          for (int16_t i=device->width()-1; i>=0; i-=4) {
                device->drawLine(device->width()-1, device->height()-1, i, 0, WHITE);
                device->display();
          }
          for (int16_t i=device->height()-1; i>=0; i-=4) {
                device->drawLine(device->width()-1, device->height()-1, 0, i, WHITE);
                device->display();
          }
          usleep(250000);

          device->clearDisplay();
          for (int16_t i=0; i<device->height(); i+=4) {
                device->drawLine(device->width()-1, 0, 0, i, WHITE);
                device->display();
          }
          for (int16_t i=0; i<device->width(); i+=4) {
                device->drawLine(device->width()-1, 0, i, device->height()-1, WHITE);
                device->display();
          }
          usleep(250000);
    /*end*/
    device->display();
    sleep(2);
    device->clearDisplay();

    for (int16_t i=0; i<device->height()/2; i+=2) {
          device->drawRect(i, i, device->width()-2*i, device->height()-2*i, WHITE);
          device->display();
    }

    device->display();
    sleep(2);
    device->clearDisplay();

    int color = 1;
    for (int16_t i=0; i<device->height()/2; i+=3) {
          // alternate colors
          device->fillRect(i, i, device->width()-i*2, device->height()-i*2, color%2);
          device->display();
          color++;
    }

    device->display();
    sleep(2);
    device->clearDisplay();

    for (int16_t i=0; i<device->height(); i+=2) {
        device->drawCircle(device->width()/2, device->height()/2, i, WHITE);
        device->display();
    }

    device->display();
    sleep(2);
    device->clearDisplay();

    device->fillCircle(device->width()/2, device->height()/2, 10, WHITE);

    device->display();
    sleep(2);

    // miniature bitmap display
    device->clearDisplay();
    device->drawBitmap(30, 16,  logo16_glcd_bmp, 16, 16, 1);
    device->display();

    sleep(2);

    int w = 16;
    int h = 16;

    uint8_t icons[NUMFLAKES][3];
    srand(666);     // whatever seed

      // initialize
      for (uint8_t f=0; f< NUMFLAKES; f++) {
        icons[f][XPOS] = rand() % device->width();
        icons[f][YPOS] = 0;
        icons[f][DELTAY] = rand() % 5 + 1;

        printf("x: %d", icons[f][XPOS]);
        printf("y: %d", icons[f][YPOS]);
        printf("dy: %d\n", icons[f][DELTAY]);
      }

      while (1) {
        // draw each icon
        for (uint8_t f=0; f< NUMFLAKES; f++) {
          device->drawBitmap(icons[f][XPOS], icons[f][YPOS], logo16_glcd_bmp, w, h, WHITE);
        }
        device->display();
        usleep(100000);

        // then erase it + move it
        for (uint8_t f=0; f< NUMFLAKES; f++) {
          device->drawBitmap(icons[f][XPOS], icons[f][YPOS],  logo16_glcd_bmp, w, h, BLACK);
          // move it
          icons[f][YPOS] += icons[f][DELTAY];
          // if its gone, reinit
          if (icons[f][YPOS] > device->height()) {
        icons[f][XPOS] = rand() % device->width();
        icons[f][YPOS] = 0;
        icons[f][DELTAY] = rand() % 5 + 1;
          }
        }
       }


/***END OF YOUR CODE***/

    #ifdef development_on
        return a.exec();
    #else
        return 0;
    #endif
}
