#ifndef QSO_H
#define QSO_H

#include <string>
#include "Coordinates.h"


struct DateTime
{
	int year = 0;
	int month = 0;
	int day = 0;

	int hour = 0;
	int minute = 0;
	int second = 0;
};

class QSO {
private:

	std::string corCall;
	std::string band;
	std::string mode;
	std::string txRst;
	std::string rxRst;
	std::string notes;
	std::string myGrid;
	std::string corGrid;

	Coordinates myCoordinates;
	Coordinates corCoordinates;
	DateTime qsoDateTime;
	
	double distance = 0.0;
	double frequency = 0.0;

	bool corLocationKnown = false;
	bool corLocationFromGrid = false;

public:

	QSO() = default;

	const std::string& getCorCall() const;
	const std::string& getBand() const;
	const std::string& getMode() const;
	const std::string& getTxRst() const;
	const std::string& getRxRst() const;
	const std::string& getNotes() const;
	const std::string& getMyGrid() const;
	const std::string& getCorGrid() const;

	Coordinates getMyCoordinates() const;
	Coordinates getCorCoordinates() const;
	DateTime getQsoDateTime() const;

	double getDistance() const;
	double getFrequency() const;

	bool getCorLocationKnown() const;
	bool getCorLocationFromGrid() const;

	void setCorCall(const std::string& corCall);
	void setMode(const std::string& mode);
	void setTxRst(const std::string& txRst);
	void setRxRst(const std::string& rxRst);
	void setNotes(const std::string& notes);
	void setCorGrid(const std::string& corGrid);

	void setMyCoordinates(const Coordinates& myCoordinates);
	void setCorCoordinates(const Coordinates& corCoordinates);
	void setQsoDateTime(const DateTime& qsoDateTime);

	void setFrequency(double frequency);

	void setCorLocationKnown(bool state);
	void setCorLocationFromGrid(bool state);


	bool validate() const;

	void updateDerivedFields();
};


#endif