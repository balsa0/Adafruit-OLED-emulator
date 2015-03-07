/*
emulator.cpp - emulator window implementation

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


#include "emulator.h"
#include <QDebug>
#include <QFontDatabase>

Adafruit_SSD1306::Adafruit_SSD1306(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Adafruit OLED emulator");
    this->setFixedSize(256,128);
    this->setWindowIcon(QIcon(":/res/icon"));

    //create the buffer
    buffer = new QPixmap*[2];
    for (int i = 0; i < 2; ++i) {
        buffer[i] = new QPixmap(screenWidth,screenHeight);
        buffer[i]->fill(BLACK);
    }

    writeBuffer = buffer[0];
    dispBuffer = buffer[1];
    writeBufferID = 0;
    dispBufferID = 1;

    //initialite
    screenWidth = 128;
    screenHeight = 64;

    emulatorZoom = 2;

    cursorX = 0;
    cursorY = 0;
    textColor = BLACK;
    textSize = 1;

    //checkers
    began = false;
    initialized = false;

    speedEmultaion = true;

    //font
    QFontDatabase fontDB;
    fontDB.addApplicationFont(":/font/pixelmix");
    pixelFont.setFamily("pixelmix");
    pixelFont.setStyleStrategy(QFont::NoAntialias);
    pixelFont.setStyleHint(QFont::Monospace);
    //pixelFont.setPointSize(10);
    pixelFont.setFixedPitch(true);
    pixelFont.setPixelSize(8);
}

Adafruit_SSD1306::~Adafruit_SSD1306()
{

}

void Adafruit_SSD1306::paintEvent(QPaintEvent *){
    //speed emulation
    if(speedEmultaion)
        QThread::msleep(40);

    //draw screen
    QPainter p( this );
    p.drawPixmap(0,0,screenWidth*emulatorZoom,
                 screenHeight*emulatorZoom,*buffer[dispBufferID]);
}

/*CHECKER*/
void Adafruit_SSD1306::checkState(){
    QMessageBox* msg = new QMessageBox;
    msg->setText(QString("DEVELOPMENT WARNING"));
    if(!initialized){
        msg->setInformativeText("You forgot 'init(...)'!");
        msg->exec();
    }
    if(!began){
        msg->setInformativeText(QString("You forgot 'begin()'!"));
        msg->exec();
    }
}

/*EMULATOR ZOOM*/

void Adafruit_SSD1306::setEmulatorZoom(int z){
    //set zoom
    emulatorZoom = z;

    //set screen size
    this->setFixedSize(screenWidth*emulatorZoom,
                       screenHeight*emulatorZoom);
}

/*DRIVER STUFF*/
bool Adafruit_SSD1306::oled_is_spi_proto(int device){
    //NOT SPI
    return false;
}

bool Adafruit_SSD1306::init(int a, int b, int c, int oled_type){
    return init(b,oled_type);
}

bool Adafruit_SSD1306::init(int a, int oled_type){

    switch(oled_type){
    case OLED_ADAFRUIT_SPI_128x32:
    case OLED_ADAFRUIT_I2C_128x32:
        screenWidth = 128;
        screenHeight = 32;
        break;
    case OLED_ADAFRUIT_SPI_128x64:
    case OLED_ADAFRUIT_I2C_128x64:
    default:
        screenWidth = 128;
        screenHeight = 64;
        break;
    }

    this->setWindowTitle("Adafruit OLED emulator ("
                         +QString::number(screenWidth)+"x"
                         +QString::number(screenHeight)+")");

    //create the buffer
    for (int i = 0; i < 2; ++i) {
        buffer[i] = new QPixmap(screenWidth,screenHeight);
        buffer[i]->fill(BLACK);
    }

    writeBuffer = buffer[0];
    dispBuffer = buffer[1];
    writeBufferID = 0;
    dispBufferID = 1;

    //set screen size
    this->setFixedSize(screenWidth*emulatorZoom,
                       screenHeight*emulatorZoom);

    this->initialized = true;
    //successfully initialized
    return true;
}

void Adafruit_SSD1306::begin(){
    this->began = true;
    return;
}

void Adafruit_SSD1306::close(){
    this->began = false;
    return;
}

void Adafruit_SSD1306::clearDisplay(){
    QPainter p(writeBuffer);
    p.setPen(Qt::black);
    p.setBrush(Qt::black);
    p.drawRect(0,0,writeBuffer->width(),writeBuffer->height());
}

/*DRAW*/
void Adafruit_SSD1306::drawPixel(int x, int y, QColor color){
    QPainter p(writeBuffer);
    p.setPen(color);
    p.drawPoint(x,y);
}

void Adafruit_SSD1306::drawLine(int x0, int y0, int x1, int y1, QColor color){
    QPainter p(writeBuffer);
    p.setPen(color);
    p.drawLine(x0,y0,x1,y1);
}

void Adafruit_SSD1306::drawRect(int x, int y, int w, int h, QColor color){
    QPainter p(writeBuffer);
    p.setPen(color);
    p.setBrush(Qt::NoBrush);
    p.drawRect(x,y,w,h);
}

void Adafruit_SSD1306::fillRect(int x, int y, int w, int h, QColor color){
    QPainter p(writeBuffer);
    p.setPen(color);
    p.setBrush(color);
    p.drawRect(x,y,w,h);
}

void Adafruit_SSD1306::drawCircle(int x, int y, int r, QColor color){
    QPainter p(writeBuffer);
    p.setPen(color);
    p.setBrush(Qt::NoBrush);
    QPoint center(x,y);
    p.drawEllipse(center,r,r);
}

void Adafruit_SSD1306::fillCircle(int x, int y, int r, QColor color){
    QPainter p(writeBuffer);
    p.setPen(color);
    p.setBrush(color);
    QPoint center(x,y);
    p.drawEllipse(center,r,r);
}

void Adafruit_SSD1306::setCursor(int x, int y){
    this->cursorX = x;
    this->cursorY = y;
}

void Adafruit_SSD1306::setTextColor(QColor color){
    this->textColor = color;
}

void Adafruit_SSD1306::setTextSize(int size){
    this->textSize = size;
    pixelFont.setPixelSize(8*textSize);
}

void Adafruit_SSD1306::print(const char *string){
    QString s(string);

    QPainter p(writeBuffer);
    p.setPen(textColor);
    p.setFont(pixelFont);
    p.drawText(cursorX,cursorY,s);
}

void Adafruit_SSD1306::drawBitmap(int x, int y, const unsigned char *bitmap, int w, int h, QColor color){
    //check if size is valid
    if(w%8 != 0 || h%8 != 0){
        qWarning() << "Width and Height of bitmap shold be multiply of 8 (widht % 8 = 0)";
        return;
    }

    //GENERATE PIXMAP FROM BITMAP
    QPixmap temp(w,h);
    temp.fill(Qt::transparent);

    QPainter tempPaint(&temp);
    tempPaint.setPen(color);

    for(int i = 0; i < w*h; i++){
        bool value = (bitmap[i/8] >> (7-(i%8))) & 0x01 == 0x01 ? true : false;
        if(value){
            tempPaint.drawPoint(i%w,i/w);
        }
    }

    QPainter p(writeBuffer);
    p.drawPixmap(x,y,w,h,temp);
}


void Adafruit_SSD1306::display(){
    checkState();

    //swap buffers
    int temp = dispBufferID;
    dispBufferID = writeBufferID;
    writeBufferID = temp;

    //set active write buffer
    writeBuffer = buffer[writeBufferID];
    dispBuffer = buffer[dispBufferID];

    //copy actual screen to new buffer
    QPainter p(writeBuffer);
    p.drawPixmap(0,0,screenWidth,screenHeight,*dispBuffer);

    this->repaint();
}

void Adafruit_SSD1306::drawPixel(int x,int y, int color){
    if(color)
        drawPixel(x,y,WHITE);
    else
        drawPixel(x,y,BLACK);
}

void Adafruit_SSD1306::drawLine(int x0, int y0, int x1, int y1, int color){
    if(color)
        drawLine(x0,y0,x1,y1,WHITE);
    else
        drawLine(x0,y0,x1,y1,BLACK);
}

void Adafruit_SSD1306::drawRect(int x, int y, int w, int h, int color){
    if(color)
        drawRect(x,y,w,h,WHITE);
    else
        drawRect(x,y,w,h,BLACK);
}

void Adafruit_SSD1306::fillRect(int x, int y, int w, int h, int color){
    if(color)
        fillRect(x,y,w,h,WHITE);
    else
        fillRect(x,y,w,h,BLACK);
}

void Adafruit_SSD1306::drawCircle(int x, int y, int r, int color){
    if(color)
        drawCircle(x,y,r,WHITE);
    else
        drawCircle(x,y,r,BLACK);
}

void Adafruit_SSD1306::fillCircle(int x, int y, int r, int color){
    if(color)
        fillCircle(x,y,r,WHITE);
    else
        fillCircle(x,y,r,BLACK);
}

void Adafruit_SSD1306::drawBitmap(int x, int y, const unsigned char *bitmap, int w, int h, int color){
    if(color)
        drawBitmap(x,y,bitmap,w,h,WHITE);
    else
        drawBitmap(x,y,bitmap,w,h,BLACK);
}

/*UTILS*/

void Adafruit_SSD1306::setRotation(int r){
    //no rotation in development
    return;
}

int Adafruit_SSD1306::device_width(){
    return screenWidth;
}

int Adafruit_SSD1306::device_height(){
    return screenHeight;
}

void Adafruit_SSD1306::setSpeedEmulation(bool enable){
    this->speedEmultaion = enable;
}
