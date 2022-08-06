#pragma once 

#include "statistics.hpp"

class Mean : public IStatistics {
public:
	Mean();
	void update(double next) override;
	double eval() override;
	const char* name() const override;
    
private:
	double _mean;
	long double _sum;
	int _count;
};