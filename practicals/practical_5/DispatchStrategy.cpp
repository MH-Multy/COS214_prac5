/*
Emmanuel Boateng ()
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 24 September 2026

DispatchStrategy.cpp (Strategy, Strategy)
*/

#ifndef DISPATCHSTRATEGY_CPP
#define DISPATCHSTRATEGY_CPP

#include "DispatchStrategy.h"

// === DISPATCH STRATEGY (STRATEGY) ==== //

// === HIGH SEVERITY (CONCRETE STRATEGY) === //

vector<ResponseUnit*> HighSeverity::selectUnits(const Incident& incident, SecurityTeam* security, MedicalTeam* medical, FacilitiesTeam* facilities)
{
	throw "Not yet implemented";
}

string HighSeverity::label()
{
	throw "Not yet implemented";
}

AlertType HighSeverity::alertMessage() {
	throw "Not yet implemented";
}

// === LOW SEVERITY (CONCRETE STRATEGY) ==== //

vector<ResponseUnit*> LowSeverity::selectUnits(const Incident& incident, SecurityTeam* security, MedicalTeam* medical, FacilitiesTeam* facilities)
{
	throw "Not yet implemented";
}

string LowSeverity::label()
{
	throw "Not yet implemented";
}

AlertType LowSeverity::alertMessage()
{
	throw "Not yet implemented";
}

#endif // DISPATCHSTRATEGY_CPP