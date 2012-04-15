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

      byte theByte = 0;
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
