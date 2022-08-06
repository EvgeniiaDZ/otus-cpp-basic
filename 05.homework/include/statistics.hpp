#pragma once

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() = 0;
	virtual const char * name() const = 0;
};