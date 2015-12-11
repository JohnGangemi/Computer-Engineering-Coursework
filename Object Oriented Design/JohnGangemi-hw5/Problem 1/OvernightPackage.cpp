#include "OvernightPackage.h"
#include <stdexcept>
using namespace std;

OvernightPackage::OvernightPackage(const string &sName, const string &sAddress,
	const string &sCity, const string &sState, int sZIP,
	const string &rName, const string &rAddress, const string &rCity,
	const string &rState, int rZIP, double w, double cost, double fee)
	: Package(sName, sAddress, sCity, sState, sZIP, rName, rAddress, rCity, rState, rZIP, w, cost)
{
	setFeePerOunce(fee);
}

void OvernightPackage::setFeePerOunce(const double &fee)
{
	if (fee >= 0)
		fee_per_ounce = fee;
	else
		throw invalid_argument("Fee must be >= 0");
}

const double OvernightPackage::getFeePerOunce()
{
	return fee_per_ounce;
}

const double OvernightPackage::calculateCost()
{
	return (getFeePerOunce() + Package::getCostPerOunce()) * Package::getWeight();
}