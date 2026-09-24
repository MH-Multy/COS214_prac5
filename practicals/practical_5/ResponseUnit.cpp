/*
Emmanuel Boateng ()
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 24 September 2026

ResponseUnit.cpp (Colleagues, Mediator)
*/

#ifndef RESPONSEUNIT_CPP
#define RESPONSEUNIT_CPP

#include "ResponseUnit.h"

// === RESPONSE UNIT (COLLEAGUE) ==== //

ResponseUnit::ResponseUnit(string name, IncidentCoordinator* coordinator)
{
	this->name = name;
	this->coordinator = coordinator;
}

void ResponseUnit::notifyCoordinator(const string& event)
{
	throw "Not yet implemented";
}

// ==== SECURITY TEAM (CONCRETE COLLEAGUE) ==== //

void SecurityTeam::dispatch()
{
	throw "Not yet implemented";
}

void SecurityTeam::recall()
{
	throw "Not yet implemented";
}

void SecurityTeam::handleEvent(const string& event)
{
	throw "Not yet implemented";
}

// === FACILITIES TEAM (CONCRETE COLLEAGUE) ==== //

void FacilitiesTeam::dispatch()
{
	throw "Not yet implemented";
}

void FacilitiesTeam::recall()
{
	throw "Not yet implemented";
}

void FacilitiesTeam::handleEvent(const string& event)
{
	throw "Not yet implemented";
}

// ==== MEDICAL TEAM (CONCRETE COLLEAGUE) ==== //

void MedicalTeam::dispatch()
{
	throw "Not yet implemented";
}

void MedicalTeam::recall()
{
	throw "Not yet implemented";
}

void MedicalTeam::handleEvent(const string& event)
{
	throw "Not yet implemented";
}

#endif // RESPONSEUNIT_CPP