/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 27 September 2026

IncidentCoordinator.cpp (Mediators, Mediator)
*/

#ifndef INCIDENTCOORDINATOR_CPP
#define INCIDENTCOORDINATOR_CPP

#include "IncidentCoordinator.h"
#include "ResponseUnit.h"

// === INCIDENT COORDINATOR (MEDIATOR) === //

// === INCIDENT RESPONSE DESK (CONCRETE MEDIATOR) === //

IncidentResponseDesk::IncidentResponseDesk(SecurityTeam* security, MedicalTeam* medical, FacilitiesTeam* facilities)
{
    this->security = security;
    this->medical = medical;
    this->facilities = facilities;
}

void IncidentResponseDesk::coordinate(ResponseUnit* sender, const string& event)
{
	if (event == "Event[0]") // MEDICAL_DISPATCHED
        security->handleEvent(event);
    else if (event == "Event[1]") // AREA_SECURED
        medical->handleEvent(event);
    else if (event == Event[2]) // ALERT_DELIVERED_EVACUATE
        facilities->handleEvent("EVACUATION_ORDERED");
}

#endif // INCIDENTCOORDINATOR_CPP