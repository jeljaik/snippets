#ifndef _ESTIMATORSCREATOR_H_
#define _ESTIMATORSCREATOR_H_

#include <string>

class IEstimator;

class EstimatorsCreator
{
public:
	EstimatorsCreator(const std::string& classname);
	virtual ~EstimatorsCreator() {};

	virtual IEstimator* create() = 0;
};

#endif

