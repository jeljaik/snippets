#ifndef _NEWESTIMATOR_H_
#define _NEWESTIMATOR_H_

#include "IEstimator.h"

class NewEstimator : public IEstimator
{
	REGISTER(NewEstimator);

public:
	virtual ~NewEstimator() {}

	virtual void foo();
};

#endif

