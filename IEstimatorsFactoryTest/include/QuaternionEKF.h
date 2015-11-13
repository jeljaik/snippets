#ifndef _QUATERNIONEKF_H_
#define _QUATERNIONEKF_H_

#include "IEstimator.h"

class QuaternionEKF : public IEstimator
{
	REGISTER(QuaternionEKF);

public:
	virtual ~QuaternionEKF() {}

	virtual void foo();
};

#endif

