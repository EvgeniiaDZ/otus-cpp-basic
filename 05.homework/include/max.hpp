#pragma once 

#include "statistics.hpp"

class Max : public IStatistics {
public:
	Max();
	void update(double next) override;
	double eval() const override;
	const char* name() const override;

private:
	double _max;
};