/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 27 September 2026

Incident.cpp (ConcreteSubject/Domain, Observer)
*/

#ifndef INCIDENT_CPP
#define INCIDENT_CPP

#include <algorithm>

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
	// a status that has not actually changed is not a status change; notifying
	// here would duplicate every log entry and re-lock areas that are already locked
	if (status == this->status && status != Status::REPORTED)
	{
		cout << "⚠️ [Incident " << this->id << "] already in this state, no notification sent" << endl;
		return;
	}

	this->status = status;
	notifyAll();
}

void Incident::attach(IncidentObserver* observer)
{
	if (observer == nullptr)
	{
		cout << "⚠️ [Incident " << this->id << "] refused a null observer" << endl;
		return;
	}

	// a duplicate attach would make the observer fire twice per change
	if (find(this->observers.begin(), this->observers.end(), observer) != this->observers.end())
	{
		cout << "⚠️ [Incident " << this->id << "] observer is already attached" << endl;
		return;
	}

	this->observers.push_back(observer);
}

void Incident::notifyAll()
{
	// iterate over a copy to avoid changes invalidating the vector during notification
	vector<IncidentObserver*> snapshot = this->observers;

	for (vector<IncidentObserver*>::iterator it = snapshot.begin(); it != snapshot.end(); ++it)
	{
		(*it)->onStatusChange(*this);
	}
}

#endif // INCIDENT_CPP