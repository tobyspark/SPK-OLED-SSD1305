// OLED display using SSD1305 driver
// Copyright *spark audio-visual 2012


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
  * ie. DENSITRON - DD-12864YO-3A
  *
  * This is a ground-up, minimal library. Currently it will display a full-screen image, draw horizontal lines, and display rows of text.
  * 
  * This library includes two processing sketches to create a font and full-screen image in the required byte representations.
  * It won't compile without you doing that - it expects const uint8_t image[] and const uint8_t* characterBytes[]
  * 
  * Terminology:
  * 'rows' are 8 pixel high rows across the display, 0 being the topmost and 7 the bottom.
  * 'lines' are single pixel lines, origin top left 
  *
  * Example:
  * @code
  * SPKDisplay screen(p5, p7, p8, p10, p9)
  * screen.imageToBuffer();
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

    /** Completely clear the object's display representation */
    void clearBuffer();
    
    /** Clear a row of the object's display representation
     *
     * @param row The row to clear.
     */
    void clearBufferRow(int row);
    
    /** Replace the object\s display representation with the contents of image[] */ 
    void imageToBuffer();
    
    /** Draw a horizontal line in the object's display representation 
     * 
     * @param y The y position of the line to draw
     */
    void horizLineToBuffer(int y);
    
    /** Write a line of text in the object's display representation
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
