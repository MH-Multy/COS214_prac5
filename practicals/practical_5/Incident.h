/*
Emmanuel Boateng ()
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 24 September 2026

Incident.h (ConcreteSubject/Domain, Observer)
*/

#ifndef INCIDENT_H
#define INCIDENT_H

#include <iostream>
#include <string>
#include <vector>

#include "Types.h"

using namespace std;

class IncidentObserver;

class Incident
{
	public:
		/// <summary>
		/// initialise the fields; initialise satus = REPORTED
		/// </summary>
		Incident(int id, string area, Severity severity);
		/// <summary>
		/// set status; call notifyAll
		/// </summary>
		void setStatus(Status status);
		Status getStatus() const { return this->status; }
		string getArea() const { return this->area; }
		Severity getSeverity() const { return this->severity; }
		int getId() const { return this->id; }
		void attach(IncidentObserver* observer);
		/// <summary>
		/// find the observer and erase it if found and return true (to help make this remove more maintainable as needed, by displaying more information); no-op if not found, return false in all other cases
		/// note that the observers are system wide responsibility holders (sort of like a computer) so the campus guard holds computers, which outlives any one incident, but no computer-incident (observer-subject) relationship outlives the incident/subject
		/// so we just use plain push and pops, clean up is responsibility of campus guard (that's why this is not a composition)
		/// specifically, no orphaning can be triggered by the incident class and the incident class has nothing to give back
		/// </summary>
		bool detach(IncidentObserver* observer);
		virtual ~Incident() { }

	private:
		/// <summary>
		/// loop over observers and call onStatusChange(*this) on each. this doesn't get called directly, only from within setStatus
		/// </summary>
		void notifyAll();
		int id;
		string area;
		Status status = Status::REPORTED;
		Severity severity;
		vector<IncidentObserver*> observers;
};

#endif // INCIDENT_H