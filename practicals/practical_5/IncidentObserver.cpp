/*
Emmanuel Boateng (u23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 26 September 2026

IncidentObserver.cpp (Observers, Observer)
*/

#ifndef INCIDENTOBSERVER_CPP
#define INCIDENTOBSERVER_CPP

#include <ctime>
#include <exception>

#include "IncidentObserver.h"
#include "Incident.h"
#include "AccessControlSystem.h"

// ==== INCIDENT OBSERVER (OBSERVER) ==== //

// ==== INCIDENT LOG OBSERVER (CONCRETE OBSERVER) ==== //

void IncidentLogObserver::onStatusChange(Incident& incident)
{
	LogEntry entry;
	entry.timestamp = time(nullptr);
	entry.id = incident.getId();
	entry.status = incident.getStatus();

	this->log.push_back(entry);

	cout << "  [IncidentLog] recorded incident " << entry.id
	     << " (" << incident.getArea() << ")" << endl;
}

void IncidentLogObserver::printLog() const
{
	cout << "--- incident log (" << this->log.size() << " entries) ---" << endl;

	for (vector<LogEntry>::const_iterator it = this->log.begin(); it != this->log.end(); ++it)
	{
		string statusName;
		switch (it->status)
		{
			case Status::REPORTED:
				statusName = "REPORTED";
				break;
			case Status::ACTIVE:
				statusName = "ACTIVE";
				break;
			case Status::RESOLVED:
				statusName = "RESOLVED";
				break;
		}

		cout << "  incident " << it->id << " : " << statusName << endl;
	}
}

// ==== ACCESS CONTROL OBSERVER (CONCRETE OBSERVER) ===== //

void AccessControlObserver::onStatusChange(Incident& incident)
{
	if (this->acs == nullptr)
	{
		cout << "  [AccessControlObserver] no access-control system attached" << endl;
		return;
	}

	// REPORTED is the opening state of every incident and needs no access action
	if (incident.getStatus() == Status::REPORTED)
	{
		return;
	}

	try
	{
		if (incident.getStatus() == Status::ACTIVE)
		{
			cout << "  [AccessControlObserver] incident " << incident.getId()
			     << " is active, securing " << incident.getArea() << endl;
			this->acs->lockArea(incident.getArea());
		}
		else if (incident.getStatus() == Status::RESOLVED)
		{
			cout << "  [AccessControlObserver] incident " << incident.getId()
			     << " is resolved, releasing " << incident.getArea() << endl;
			this->acs->unlockArea(incident.getArea());
		}
	}
	catch (const exception& e)
	{
		cout << "  [AccessControlObserver] access-control refused the request: "
		     << e.what() << endl;
	}
	catch (...)
	{
		cout << "  [AccessControlObserver] access-control refused the request" << endl;
	}
}

#endif // INCIDENTOBSERVER_CPP
