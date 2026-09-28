/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 27 September 2026

IncidentObserver.h (Observers, Observer)
*/

#ifndef INCIDENTOBSERVER_H
#define INCIDENTOBSERVER_H

#include <iostream>
#include <string>
#include <vector>

#include"Types.h"

class Incident;
class AccessControlSystem;

class IncidentObserver
{
	public:
		virtual void onStatusChange(Incident& incident) = 0;
		virtual ~IncidentObserver() { };
};

/**
 * observer dp, when there is a status change of an incident, it writes a structured record of the change to its internal log. there is a queryable history of what happened when,
 * it just records. there is no clear log function. if this were a genuine system built at a large scale, it may become helpful (write the log to a second location,
 * clear the vector, restart tracking) but for a practical it is unnecessary and redundant, the log vector would not get so big, also the program ends so there is no accumulation issue
 */
class IncidentLogObserver: public IncidentObserver
{
	public:
		/// <summary>
		/// construct a LogEntry{now(), incident.getId(), incident.getStatus()} and push that into the log vector (there's a LogEntry struct) it just silently watches and logs
		/// </summary>
		void onStatusChange(Incident& incident) override;
		/// <summary>
		/// return the plain log vector
		/// </summary>
		const vector<LogEntry>& getLog() const { return this->log; } // memory efficiency, vector isn't re-copied
		/// <summary>
		/// prints the log, but formatted and easier on the eye
		/// </summary>
		void printLog() const;

	private:
		vector<LogEntry> log;
};


class AccessControlObserver: public IncidentObserver
{
	public:
		AccessControlObserver(AccessControlSystem* acs) { this->acs = acs; }
		/// <summary>
		/// if the incident status is ACTIVE, lock the area, if it is RESOLVED, unlock the area, if it's REPORTED, do nothing. if this switch/if chain expands to be too big replace with the state dp, but because it is currently is small. lockArea call and unlockArea call need to be in a try/catch to error handle (see those functions for their internal mechanisms for why that's necessary) REPORTED is just the first status of every incident
		/// </summary>
		void onStatusChange(Incident& incident) override;

	private:
		AccessControlSystem* acs;
};

#endif // INCIDENTOBSERVER_H