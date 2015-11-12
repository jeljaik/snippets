#ifndef LANDSATIMAGE_H
#define LANDSATIMAGE_H

class LandSatImage: public Image
{
  public:
    imageType returnType();
    void draw();
    // When clone() is called, call the one-argument ctor with a dummy arg
    Image *clone();
  protected:
    // This is only called from clone()
    LandSatImage(int dummy);
  private:
    // Mechanism for initializing an Image subclass - this causes the
    // default ctor to be called, which registers the subclass's prototype
    static LandSatImage _landSatImage;
    // This is only called when the private static data member is inited
    LandSatImage();
    // Nominal "state" per instance mechanism
    int _id;
    static int _count;
};

#endif