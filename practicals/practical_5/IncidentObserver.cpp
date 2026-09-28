/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 28 September 2026

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

	cout << "✍️ [IncidentLog] Recorded incident " << entry.id << " (" << incident.getArea() << ")" << endl;
}

void IncidentLogObserver::printLog() const
{
	cout << "📜 ============ Incident Log (" << this->log.size() << " entries) ============" << endl;

	for (vector<LogEntry>::const_iterator it = this->log.begin(); it != this->log.end(); ++it)
	{
		string statusName;
		switch (it->status)
		{
			case Status::REPORTED:
				statusName = "🆕 REPORTED";
				break;
			case Status::ACTIVE:
				statusName = "🔴 ACTIVE";
				break;
			case Status::RESOLVED:
				statusName = "✅ RESOLVED";
				break;
			default:
				statusName = "⚠️ Unknown";
				break;
		}

		time_t ts = it->timestamp;
		string time_string = ctime(&ts);
		time_string.pop_back();

		cout << "[" << time_string << "] Incident #" << it->id << "  ->  " << statusName << endl;
	}
	cout << "📜 ==================================================" << endl;
}

// ==== ACCESS CONTROL OBSERVER (CONCRETE OBSERVER) ===== //

void AccessControlObserver::onStatusChange(Incident& incident)
{
	if (this->acs == nullptr)
	{
		cout << "⚠️ [AccessControlObserver] No access-control system attached" << endl;
		return;
	}

	// REPORTED is the opening state of every incident and needs no access action
	if (incident.getStatus() == Status::REPORTED)
	{
		return;
	}

	if (incident.getStatus() == Status::ACTIVE)
	{
		try
		{
			this->acs->lockArea(incident.getArea());
			cout << "🔒 [AccessControlObserver] Incident #" << incident.getId() << " is active, securing " << incident.getArea() << "." << endl;
		}
		catch(const std::exception& e)
		{
			cout << "ℹ️ [AccessControlObserver] Could not lock " << incident.getArea() << ": " << e.what() << endl;
		} // failure cases
		catch (...)
		{
			cout << "⚠️ [AccessControlObserver] Access-control refused the request" << endl;
		}
	}

	else if (incident.getStatus() == Status::RESOLVED)
	{
		try
		{
			this->acs->unlockArea(incident.getArea());
			cout << "🔓 [AccessControlObserver] Incident #" << incident.getId() << " is resolved, reopening " << incident.getArea() << "." << endl;
		}
		catch(const std::exception& e)
		{
			cout << "ℹ️ [AccessControlObserver] Could not unlock " << incident.getArea() << ": " << e.what() << endl;
		}
		catch (...)
		{
			cout << "⚠️ [AccessControlObserver] Access-control refused the request" << endl;
		}
	}
}

#endif // INCIDENTOBSERVER_CPP