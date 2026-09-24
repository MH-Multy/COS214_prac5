/*
Emmanuel Boateng ()
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 24 September 2026

IncidentCoordinator.h (Mediators, Mediator)
*/

#ifndef INCIDENTCOORDINATOR_H
#define INCIDENTCOORDINATOR_H

#include <iostream>
#include <string>

#include "Types.h"

using namespace std;

// forward declare only (circular references)
class ResponseUnit;

class SecurityTeam;
class MedicalTeam;
class FacilitiesTeam;

class IncidentCoordinator
{
	public:
		virtual void coordinate(ResponseUnit* sender, const string& event) = 0;
		virtual ~IncidentCoordinator() { }; // the mediator does not own the references
};

/**
 * this is where the bulk of the coordination lives
 */
class IncidentResponseDesk: public IncidentCoordinator
{
	public:
		/// <summary>
		/// mediator's job is to coordinate so an if/else chain works fine, it needs to find who to talk to e.g.
		/// event == "MEDICAL_DISPATCHED" → security->handleEvent(event)
		/// event == "AREA_SECURED" → medical->handleEvent(event)
		/// event == "ALERT_DELIVERED_EVACUATE" → facilities->handleEvent(EVACUATION_ORDERED)
		/// handleEvent will then react to the event passed in where needed, causing the unit to change its internal state, each ResponseUnit does not coordinate with the other, they coordinate with mediator
		/// (different from observer which is a listener problem, not a coordinator problem)
		/// </summary>
		void coordinate(ResponseUnit* sender, const string& event) override;
		IncidentResponseDesk(SecurityTeam* security, MedicalTeam* medical, FacilitiesTeam* facilities);

	private:
		SecurityTeam* security;
		MedicalTeam* medical;
		FacilitiesTeam* facilities;
};

#endif // INCIDENTCOORDINATOR_H