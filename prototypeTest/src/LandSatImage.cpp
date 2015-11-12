#include <stdio.h>
#include "Image.h"
#include "LandSatImage.h"

using namespace std;

// Register the subclass's prototype
LandSatImage LandSatImage::_landSatImage;
// Initialize the "state" per instance mechanism
int LandSatImage::_count = 1;


imageType LandSatImage::returnType()
{
    return LSAT;
}

void LandSatImage::draw()
{
    cout << "LandSatImage::draw " << _id << endl;
}

Image* LandSatImage::clone()
{
    return new LandSatImage(1);
}

LandSatImage::LandSatImage(int dummy)
{
    _id = _count++;
}

LandSatImage::LandSatImage()
{
    addPrototype(this);
}