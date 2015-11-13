#ifndef _LEGGEDODOMETRY_H_
#define _LEGGEDODOMETRY_H_

#include "IEstimator.h"

class LeggedOdometry : public IEstimator
{
	REGISTER(LeggedOdometry);

public:
	virtual ~LeggedOdometry() {}

	virtual void foo();
};

#endif

