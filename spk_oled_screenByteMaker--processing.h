int w = 132;
int h = 64;
int scaleFactor = 10;

PImage imgPixel;
color white = color(255, 255, 255, 255);
color black = color(0, 0, 0, 255);

void setup()
{
  size(w*scaleFactor, h*scaleFactor);
  imgPixel = loadImage("spk_dvimxr_screen.png");

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
  println("{");
  for (int page = 0; page < 8; page++)
  {
    for (int i = 0; i < w; i++)
    {
      byte theByte = 0;
      for (int j = 0; j < 8; j++)
      {
       if (imgPixel.get(i, (page*8)+j) == white)
       {
          theByte += pow(2, j); 
       }
      }
      print("0x" + hex(theByte, 2));
      print(", ");
    }
    println();
  }
  println("}");
}
