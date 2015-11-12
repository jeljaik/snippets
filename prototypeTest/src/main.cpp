#include "Image.h"
#include "SpotImage.h"
#include "LandSatImage.h"

// Simulated stream of creation requests
const int NUM_IMAGES = 8;
imageType input[NUM_IMAGES] = 
{
  LSAT, LSAT, LSAT, SPOT, LSAT, SPOT, SPOT, LSAT
};

int main()
{
  Image *images[NUM_IMAGES];

  // Given an image type, find the right prototype, and return a clone
  for (int i = 0; i < NUM_IMAGES; i++)
    images[i] = Image::findAndClone(input[i]);

  // Demonstrate that correct image objects have been cloned
  for (int i = 0; i < NUM_IMAGES; i++)
    images[i]->draw();

  // Free the dynamic memory
  for (int i = 0; i < NUM_IMAGES; i++)
    delete images[i];
}
