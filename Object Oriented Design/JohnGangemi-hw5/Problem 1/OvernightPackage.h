#ifndef OVERNIGHTPACKAGE_H
#define OVERNIGHTPACKAGE_H

#include "Package.h"
#include <string>

class OvernightPackage : public Package // public inheritance from class Package
{
public:
	OvernightPackage(const std::string &, const std::string &, const std::string &,
		const std::string &, int, const std::string &, const std::string &, const std::string &,
		const std::string &, int, double, double, double);

	void setFeePerOunce(const double &); // validate fee for overnight shipping
	const double getFeePerOunce(); // return fee per ounce

	const double calculateCost(); // calculate cost for overnight shipping
private:
	double fee_per_ounce; // charge for overnight shipping
};

#endif