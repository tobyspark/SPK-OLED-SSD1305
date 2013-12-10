// OLED display using SSD1305 driver
// A library by *spark audio-visual

/* Copyright (c) 2011 Toby Harris, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 * and associated documentation files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, 
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

int w = 132;
int h = 64;
int scaleFactor = 5;

PImage imgPixel;
color white = color(255, 255, 255, 255);
color black = color(0, 0, 0, 255);

void setup()
{
  imgPixel = loadImage("spk_dvimxr_font.png");
  w = imgPixel.width;
  h = imgPixel.height;

  size(w*scaleFactor, h*scaleFactor);

  noSmooth();
}

void draw()
{
  background(0);
  image(imgPixel, 0, 0, w*scaleFactor, h*scaleFactor);
}

void mouseDragged() 
{
  int x = mouseX/scaleFactor;
  int y = mouseY/scaleFactor;

  imgPixel.set(x, y, white);
}

void mousePressed()
{
  int x = mouseX/scaleFactor;
  int y = mouseY/scaleFactor;

  if (imgPixel.get(x, y) == white)
  {
    imgPixel.set(x, y, black);
  }
  else
  {
    imgPixel.set(x, y, white);
  }
}

void keyPressed()
{
  int startID = 33;
  int stopID = 126;

  for (int charID = startID; charID <= stopID; charID++)
  {
    boolean blank = false;
    String output = "";
    int counter = 0;
    while (blank == false)
    {
      int x = (charID-startID)*8 + counter;

      char theByte = 0; // byte and other types are signed in java! char is the exception
      for (int b = 0; b < 8; b++)
      {
        if (imgPixel.get(x, b) == white)
        {
          theByte += pow(2, b);
        }
      }

      if (theByte > 0)
      {
        if (output.length() > 0) output = output + ", ";
        output = output + "0x" + hex(theByte, 2);
      } 
      else
      {
        blank = true;
        println("const uint8_t char" + charID + "[] = {" + counter + ", " + output + "};");
      }
      
      counter++;
    }
  }
  println();
  println("const int characterBytesStartChar = " + startID + ";");
  println("const int characterBytesEndChar = " + stopID + ";");
  print("const uint8_t* characterBytes[] = {");
  for (int charID = startID; charID <= stopID; charID++)
  {
    print("char" + charID + ", ");
  }
  println("};");
}
