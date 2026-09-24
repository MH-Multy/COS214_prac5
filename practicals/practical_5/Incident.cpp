/*
Emmanuel Boateng ()
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 24 September 2026

Incident.cpp (ConcreteSubject/Domain, Observer)
*/

#ifndef INCIDENT_CPP
#define INCIDENT_CPP

#include "Incident.h"
#include "IncidentObserver.h"

Incident::Incident(int id, string area, Severity severity)
{
	this->id = id;
	this->area = area;
	this->severity = severity;
}

void Incident::setStatus(Status status)
{
	throw "Not yet implemented";
}

void Incident::attach(IncidentObserver* observer)
{
	throw "Not yet implemented";
}

bool Incident::detach(IncidentObserver* observer)
{
	throw "Not yet implemented";
}

void Incident::notifyAll()
{
	throw "Not yet implemented";
}

#endif // INCIDENT_CPP