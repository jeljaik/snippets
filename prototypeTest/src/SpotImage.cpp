#include "SpotImage.h"

using namespace std;

SpotImage SpotImage::_spotImage;
int SpotImage::_count = 1;

imageType SpotImage::returnType()
{
    return SPOT;
}

void SpotImage::draw()
{
    cout << "SpotImage::draw " << _id << endl;
}

Image* SpotImage::clone()
{
    return new SpotImage(1);
}

SpotImage::SpotImage(int dummy)
{
    _id = _count++;
}

SpotImage::SpotImage()
{
    addPrototype(this);
}