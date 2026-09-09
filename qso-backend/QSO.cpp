#include <iostream>
#include <string>
#include "RadioUtils.h"
#include "Coordinates.h"
#include "QSO.h"

using namespace std;

const string& QSO::getCorCall() const { return corCall; }
const string& QSO::getBand() const { return band; }
const string& QSO::getMode() const { return mode; }
const string& QSO::getTxRst() const { return txRst; }
const string& QSO::getRxRst() const { return rxRst; }

const string& QSO::getNotes() const { return notes; }
const string& QSO::getMyGrid() const { return myGrid; }
const string& QSO::getCorGrid() const { return corGrid; }

Coordinates QSO::getMyCoordinates() const { return myCoordinates; }
Coordinates QSO::getCorCoordinates() const { return corCoordinates; }
DateTime QSO::getQsoDateTime() const { return qsoDateTime; }

double QSO::getDistance() const { return distance; }
double QSO::getFrequency() const { return frequency; }

bool QSO::getCorLocationKnown() const { return corLocationKnown; }

void QSO::setCorCall(const string& corCall) { this->corCall = corCall; }
void QSO::setMode(const string& mode) { this->mode = mode; }
void QSO::setTxRst(const string& txRst) { this->txRst = txRst; }
void QSO::setRxRst(const string& rxRst) { this->rxRst = rxRst; }
void QSO::setNotes(const string& notes) { this->notes = notes; }
void QSO::setCorGrid(const string& corGrid) { this->corGrid = corGrid; }
void QSO::setMyCoordinates(const Coordinates& myCoordinates) { this->myCoordinates = myCoordinates; }
void QSO::setCorCoordinates(const Coordinates& corCoordinates) { this->corCoordinates = corCoordinates; }
void QSO::setQsoDateTime(const DateTime& qsoDateTime) { this->qsoDateTime = qsoDateTime; }
void QSO::setFrequency(double frequency) { this->frequency = frequency; }

void QSO::setCorLocationKnown(bool state) { corLocationKnown = state; }


bool QSO::validate() const {
	bool ret = true;

	if (corCall.empty()) {
		ret = false;
	}

	if (getBandFromFrequency(frequency) == "Invalid") {
		ret = false;
	}
	
	if (mode.empty()) {
		ret = false;
	}

	if (!(qsoDateTime.day >= 1 && qsoDateTime.day <= 31) ||
		!(qsoDateTime.month >= 1 && qsoDateTime.month <= 12) ||
		!(qsoDateTime.year != 0) ||
		!(qsoDateTime.hour >= 0 && qsoDateTime.hour <= 23) ||
		!(qsoDateTime.minute >= 0 && qsoDateTime.minute <= 59) ||
		!(qsoDateTime.second >= 0 && qsoDateTime.second <= 59)) 
	{
		ret = false;
	}

	return ret;
}
