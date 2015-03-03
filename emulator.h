/*
emulator.h - emulator window class header

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



#ifndef EMULATOR_H
#define EMULATOR_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QThread>

#include <QMessageBox>

//colors
#define BLACK QColor(0,0,0)
#define WHITE QColor(255,255,255)

//fake constants
#define OLED_SPI_RESET              0
#define OLED_SPI_DC                 0
#define OLED_SPI_CS0                0
#define OLED_SPI_CS1                0
#define OLED_SPI_CS                 0
#define OLED_I2C_RESET              0
#define ADAFRUIT_I2C_ADDRESS        0
#define SEEEED_I2C_ADDRESS          0
#define	OLED_ADAFRUIT_SPI_128x32	0
#define	OLED_ADAFRUIT_SPI_128x64	1
#define	OLED_ADAFRUIT_I2C_128x32	2
#define	OLED_ADAFRUIT_I2C_128x64	3
#define	OLED_SEEED_I2C_128x64		4
#define	OLED_SEEED_I2C_96x96        5
#define OLED_LAST_OLED				6 /* always last type, used in code to end array */

class Adafruit_SSD1306 : public QMainWindow
{
    Q_OBJECT

public:
    Adafruit_SSD1306(QWidget *parent = 0);
    ~Adafruit_SSD1306();

    void checkState();
    void setEmulatorZoom(int z);
    void setSpeedEmulation(bool enable);

    bool oled_is_spi_proto(int device);
    bool init(int a, int b, int c, int oled_type);
    bool init(int a, int oled_type);

    void begin();
    void close();

    void clearDisplay();

    void drawPixel(int x,int y, QColor color);
    void drawLine(int x0, int y0, int x1, int y1, QColor color);
    void drawRect(int x, int y, int w, int h, QColor color);
    void fillRect(int x, int y, int w, int h, QColor color);
    void drawCircle(int x, int y, int r, QColor color);
    void fillCircle(int x, int y, int r, QColor color);
    void drawBitmap(int x, int y, const unsigned char *bitmap, int w, int h, QColor color);

    void drawPixel(int x,int y, int color);
    void drawLine(int x0, int y0, int x1, int y1, int color);
    void drawRect(int x, int y, int w, int h, int color);
    void fillRect(int x, int y, int w, int h, int color);
    void drawCircle(int x, int y, int r, int color);
    void fillCircle(int x, int y, int r, int color);
    void drawBitmap(int x, int y, const unsigned char *bitmap, int w, int h, int color);


    void setCursor(int x, int y);
    void setTextColor(QColor color);
    void print(const char * string);

    int device_height();
    int device_width();

    void setRotation(int r);

    void display();

protected:
    void paintEvent ( QPaintEvent* );
    //void keyPressEvent ( QKeyEvent* );

private:
    QPixmap** buffer;
    QPixmap *writeBuffer,*dispBuffer;
    int dispBufferID,writeBufferID;

    int screenWidth, screenHeight;
    int emulatorZoom;

    int cursorX, cursorY;
    QColor textColor;

    //checkers
    bool began;
    bool initialized;

    //speed emulation
    bool speedEmultaion;

};

#endif // EMULATOR_H
