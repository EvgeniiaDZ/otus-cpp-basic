#pragma once 

#include "statistics.hpp"

class Min : public IStatistics {
public:
	Min();
	void update(double next) override;
	double eval() override;
	const char* name() const override;

private:
	double m_min;
};