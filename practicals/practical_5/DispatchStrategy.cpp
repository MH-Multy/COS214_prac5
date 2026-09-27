/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 27 September 2026

DispatchStrategy.cpp (Strategy, Strategy)
*/

#ifndef DISPATCHSTRATEGY_CPP
#define DISPATCHSTRATEGY_CPP

#include "DispatchStrategy.h"
#include "ResponseUnit.h"
// #include "Incident.h"

// === DISPATCH STRATEGY (STRATEGY) ==== //

// === HIGH SEVERITY (CONCRETE STRATEGY) === //

vector<ResponseUnit*> HighSeverity::selectUnits(SecurityTeam* security, MedicalTeam* medical, FacilitiesTeam* facilities)
{
	// The incident has no use at the moment and has been removed.
	return {security, medical, facilities};
}

string HighSeverity::label() const
{
	return "🔥 High-severity: All response teams dispatched (Security + Medical + Facilities)";
}

AlertType HighSeverity::alertMessage() const
{
	cout << "🚁 High-severity call has been detected. Please Evacuate the area.";
	return AlertType::EVACUATE;
}

// === LOW SEVERITY (CONCRETE STRATEGY) ==== //

vector<ResponseUnit*> LowSeverity::selectUnits(SecurityTeam* security, MedicalTeam* medical, FacilitiesTeam* facilities)
{
	return {security};
}

string LowSeverity::label() const
{
	return "🟡 Low-severity: Security-only response";
}

AlertType LowSeverity::alertMessage() const
{
	cout << "🔐 Low-severity incident has been detected. Initiating Lockdown of area.";
	return AlertType::LOCKDOWN;
}

#endif // DISPATCHSTRATEGY_CPP