#pragma once

#include "statistics.hpp"
#include <vector>

class Std : public IStatistics {
public:
	Std();
	void update(double next) override;
	double eval() override;
	const char* name() const override;

private:
	double _std;
	std::vector<double> _val;

	double mean() const;
};