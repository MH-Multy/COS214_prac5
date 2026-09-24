/*
Emmanuel Boateng ()
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 24 September 2026

IncidentObserver.cpp (Observers, Observer)
*/

#ifndef INCIDENTOBSERVER_CPP
#define INCIDENTOBSERVER_CPP

#include "IncidentObserver.h"
#include "Incident.h"
#include "Receiver.h"

// ==== INCIDENT OBSERVER (OBSERVER) ==== //

// ==== INCIDENT LOG OBSERVER (CONCRETE OBSERVER) ==== //

void IncidentLogObserver::onStatusChange(Incident& incident)
{
	throw "Not yet implemented";
}

void IncidentLogObserver::printLog() const
{
	throw "Not yet implemented";
}

// ==== ACCESS CONTROL OBSERVER (CONCRETE OBSERVER) ===== //

void AccessControlObserver::onStatusChange(Incident& incident)
{
	throw "Not yet implemented";
}

#endif // INCIDENTOBSERVER_CPP