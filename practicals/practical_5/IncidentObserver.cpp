/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 27 September 2026

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

<<<<<<< HEAD
	cout << "  [IncidentLog] Recorded incident " << entry.id
	     << " (" << incident.getArea() << ")" << endl;
=======
	cout << "✍️ [IncidentLog] recorded incident " << entry.id << " (" << incident.getArea() << ")" << endl;
>>>>>>> observer
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
		}

		cout << "   Incident #" << it->id << "  ->  " << statusName << endl;
	}
	cout << "📜 =======================================" << endl;
}

// ==== ACCESS CONTROL OBSERVER (CONCRETE OBSERVER) ===== //

void AccessControlObserver::onStatusChange(Incident& incident)
{
	if (this->acs == nullptr)
	{
<<<<<<< HEAD
		cout << "  [AccessControlObserver] No access-control system attached" << endl;
=======
		cout << "⚠️ [AccessControlObserver] no access-control system attached" << endl;
>>>>>>> observer
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
<<<<<<< HEAD
			cout << "  [AccessControlObserver] Incident " << incident.getId()
			     << " is active, securing " << incident.getArea() << endl;
=======
>>>>>>> observer
			this->acs->lockArea(incident.getArea());
			cout << "🔒 [AccessControlObserver] Incident #" << incident.getId() << " is active, securing " << incident.getArea() << "." << endl;
		}
		catch(const std::exception& e)
		{
<<<<<<< HEAD
			cout << "  [AccessControlObserver] Incident " << incident.getId()
			     << " is resolved, releasing " << incident.getArea() << endl;
			this->acs->unlockArea(incident.getArea());
=======
			cout << "ℹ️ [AccessControlObserver] Could not lock " << incident.getArea() << ": " << e.what() << endl;
		} // failure cases
		catch (...)
		{
			cout << "⚠️ [AccessControlObserver] Access-control refused the request" << endl;
>>>>>>> observer
		}
	}

	else if (incident.getStatus() == Status::RESOLVED)
	{
<<<<<<< HEAD
		cout << "  [AccessControlObserver] Access-control refused the request: "
		     << e.what() << endl;
	}
	catch (...)
	{
		cout << "  [AccessControlObserver] Access-control refused the request" << endl;
=======
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
>>>>>>> observer
	}
}

#endif // INCIDENTOBSERVER_CPP