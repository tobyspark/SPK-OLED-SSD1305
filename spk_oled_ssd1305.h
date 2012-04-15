// OLED display using SSD1305 driver
// Copyright *spark audio-visual 2012
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License version 3 as published by the Free Software Foundation.

#ifndef SPK_OLED_SSD1305_h
#define SPK_OLED_SSD1305_h

#include "mbed.h"
#include <string> 

#define bufferCount 1056
#define bufferWidth 132
#define pixelWidth 128
#define pixelHeight 64
#define pixInPage 8
#define pageCount 8

/** Display class for 128x64 OLEDs using the SSD1305 driver
  * Display ie. DENSITRON - DD-12864YO-3A
  *
  * This is a ground-up, minimal library. Further functionality as and when its needed or anybody wants to contribute.
  * 
  * This library includes two processing sketches to create a font and full-screen image in the required byte representations.
  * Without creating your a font and image, all this library will do is blank the screen and draw horizontal lines. But at least you'll know its working!
  * 
  * Terminology:
  * 'rows' are 8 pixel high rows across the display, 0 being the topmost and 7 the bottom.
  * 'lines' are single pixel lines, origin top left 
  *
  * Example:
  * @code
  * // Create object and load font
  * SPKDisplay screen(p5, p7, p8, p10, p9)
  * screen.fontStartCharacter = &myStartChar;
  * screen.fontEndCharacter = &myEndChar;
  * screen.fontCharacters = myFontArray;
  * // Draw
  * screen.imageToBuffer(myImageByteArray);
  * screen.textToBuffer("*spark OLED SSD1305",0);
  * screen.textToBuffer("v01",1);
  * screen.sendBuffer
  * @endcode
  */
class SPKDisplay
{
  public:
    /** Create a display object connected via SPI
     *
     * @param mosi  SPI MOSI
     * @param clk   SPI SCK
     * @param cs    Chip Select - a digital out pin
     * @param dc    Data/Command - a digital out pin
     * @param res   Reset - a digital out pin
     * @param debugSerial An optional serial object to log to
     */
    SPKDisplay(PinName mosi, PinName clk, PinName cs, PinName dc, PinName res, Serial *debugSerial = NULL);

    /** Font - Assign the ASCII value of the character at the start of the implemented range */
    const int *fontStartCharacter;
    
    /** Font - Assign the ASCII value of the character at the end of the implemented range */
    const int *fontEndCharacter;
    
    /** Font - Assign the font, an array of 8x8px characters
     *
     * @note The processing sketch spk_oled_fontByteMaker--processing takes characterCount*8px x 8px images and creates the code to declare the font array needed by this method
     */
    uint8_t const **fontCharacters;
    
    /** Completely clear the object's display representation */
    void clearBuffer();
    
    /** Clear a row of the object's display representation
     *
     * @param row The row to clear.
     */
    void clearBufferRow(int row);
    
    /** Replace the object\s display representation with the contents of image
     *
     * @param image An array of 1056 bytes representing an image.
     * @note The processing sketch spk_oled_screenByteMaker--processing takes 132x64 images and creates the code to declare such arrays
     */ 
    void imageToBuffer(const uint8_t* image);
    
    /** Draw a horizontal line in the object's display representation 
     * 
     * @param y The y position of the line to draw
     */
    void horizLineToBuffer(int y);
    
    /** Write a line of text in the object's display representation
     * Requires the font to have been set
     * 
     * @param message   The text to write. The text will be truncated if longer than the screen's width.
     * @param row       The row in which to write the text
     */ 
    void textToBuffer(std::string message, int row);
    
    /** Send the object's display representation to the OLED
     * 
     * You can safely call this once per main loop, it will only transmit the buffer contents if there has been an update
     */
    void sendBuffer();
    
  private:
    SPI *spi;
    DigitalOut *cs;
    DigitalOut *dc;
    DigitalOut *res;
    
    Serial *debug;
    uint8_t buffer[bufferCount];
    
    bool bufferHasChanged;
    
    void setup(); 
};

#endif
