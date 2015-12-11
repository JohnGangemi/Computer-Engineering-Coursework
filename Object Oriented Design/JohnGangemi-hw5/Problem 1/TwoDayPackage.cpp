#include "TwoDayPackage.h"
#include <stdexcept>
using namespace std;

TwoDayPackage::TwoDayPackage(const string &sName, const string &sAddress,
	const string &sCity, const string &sState, int sZIP,
	const string &rName, const string &rAddress, const string &rCity,
	const string &rState, int rZIP, double w, double cost, double fee)
	: Package(sName, sAddress, sCity, sState, sZIP, rName, rAddress, rCity, rState, rZIP, w, cost)
{
	setFlatFee(fee); // validate and store fee
}

void TwoDayPackage::setFlatFee(const double &fee)
{
	if (fee >= 0)
		flat_fee = fee;
	else
		throw invalid_argument("Fee must be >= 0");
}

const double TwoDayPackage::getFlatFee()
{
	return flat_fee;
}

const double TwoDayPackage::calculateCost()
{
	return getFlatFee() + Package::calculateCost();
}