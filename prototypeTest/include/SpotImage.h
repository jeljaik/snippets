#ifndef SPOTIMAGE_H
#define SPOTIMAGE_H

#include "Image.h"

class SpotImage: public Image
{
  public:
    imageType returnType();
    void draw();
    Image *clone();
  protected:
    SpotImage(int dummy);
  private:
    SpotImage();
    int _id;
    static SpotImage _spotImage;
    static int _count;
};

#endif