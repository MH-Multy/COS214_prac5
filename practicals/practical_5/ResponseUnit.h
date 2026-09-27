/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 27 September 2026

ResponseUnit.h (Colleagues, Mediator)
*/

#ifndef RESPONSEUNIT_H
#define RESPONSEUNIT_H

#include <iostream>
#include <string>

#include "IncidentCoordinator.h"
#include "Types.h"

using namespace std;

class ResponseUnit
{
	public:
		ResponseUnit(string name, IncidentCoordinator* coordinator);
		virtual void handleEvent(const string& event) = 0;
		virtual ~ResponseUnit() { } // coordinator is non-owning
		string getName() const { return this->name; }
		virtual void dispatch() = 0;
		virtual void recall() = 0;

	protected:
		/// <summary>
		/// coordinator->coordinate(this, event)
		/// </summary>
		void notifyCoordinator(const string& event);
		string name;
		IncidentCoordinator* coordinator;
};

/**
 * the operations of this class are very similar for each ResponseUnit
 */
class SecurityTeam : public ResponseUnit
{
	public:
		SecurityTeam(string name, IncidentCoordinator* coordinator) : ResponseUnit(name, coordinator) { }
		/// <summary>
		/// if dispatched is already true then start a failure case (cout and return) otherwise set dispatched to true and call notifyCoordinator("[TEAM]_DISPATCHED") eg. notifyCoordinator("SECURITY_DISPATCHED")
		/// </summary>
		void dispatch();
		/// <summary>
		/// called by undo on DispatchUnit, set dispatch = false
		/// </summary>
		void recall();
		/// <summary>
		/// flip the boolean corresponding to the event (check using strings against the triggers the unit cares about) and if it is unrecognised ignore it silently (no cout, a unit does not care about irrelevant events)
		/// </summary>
		void handleEvent(const string& event) override;
		bool isPerimeterSecured() const { return this->perimeterSecured; }

	private:
		bool dispatched = false;
		bool perimeterSecured = false;
};

class MedicalTeam : public ResponseUnit
{
	public:
		MedicalTeam(string name, IncidentCoordinator* coordinator) : ResponseUnit(name, coordinator) { }
		void dispatch();
		void recall();
		bool isTreating() const { return treating; }
		void handleEvent(const string& event) override;

	private:
		bool dispatched = false;
		bool treating = false;
};

class FacilitiesTeam : public ResponseUnit
{
	public:
		FacilitiesTeam(string name, IncidentCoordinator* coordinator) : ResponseUnit(name, coordinator) { }
		void dispatch();
		void recall();
		bool areExitsOpened() const { return exitsOpened; }
		void handleEvent(const string& event) override;

	private:
		bool dispatched = false;
		bool exitsOpened = false;
};

#endif // RESPONSEUNIT_H