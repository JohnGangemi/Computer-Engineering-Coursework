#ifndef TWODAYPACKAGE_H
#define TWODAYPACKAGE_H

#include "Package.h"
#include <string>

class TwoDayPackage : public Package // public inheritance from class Package
{
public:
	TwoDayPackage(const std::string &, const std::string &, const std::string &,
		const std::string &, int, const std::string &, const std::string &, const std::string &,
		const std::string &, int, double, double, double);

	void setFlatFee(const double &); // set fee for two day shipping
	const double getFlatFee(); // return flat fee

	const double calculateCost(); // calculate cost for two day shipping
private:
	double flat_fee; // base charge for two day shipping
};

#endif