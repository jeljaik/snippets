#ifndef _IESTIMATOR_H_
#define _IESTIMATOR_H_

// include the factory stuff so derived classes see the REGISTER macros
// without doing any extra work.
#include "EstimatorsFactory.h"

class IEstimator
{
public:
	virtual ~IEstimator() {}

	virtual void foo() = 0;
};

#endif
