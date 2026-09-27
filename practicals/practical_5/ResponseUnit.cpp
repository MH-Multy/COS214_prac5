/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 27 September 2026

ResponseUnit.cpp (Colleagues, Mediator)
*/

#ifndef RESPONSEUNIT_CPP
#define RESPONSEUNIT_CPP

#include "ResponseUnit.h"

// === RESPONSE UNIT (COLLEAGUE) ==== //

ResponseUnit::ResponseUnit(string name, IncidentCoordinator* coordinator)
{
	this->name = name;
	this->coordinator = coordinator;
}

void ResponseUnit::notifyCoordinator(const string& event)
{
	if (coordinator)
		coordinator->coordinate(this, event); // pass to the coordinator
	else cout << "⚠️ " << name << " has no coordinator.";
}

// ==== SECURITY TEAM (CONCRETE COLLEAGUE) ==== //

void SecurityTeam::dispatch()
{
	if (dispatched)
	{
		// here we do logic handling for if a unit is already dispatched
		cout << "⚠️ " << name << " is already dispatched. Duplicate order ignored." << endl;
		return;
	}
	dispatched = true;
	cout << "🚓 " << name << " dispatched to the scene." << endl;
	notifyCoordinator(Events::SECURITY_DISPATCHED);
}

void SecurityTeam::recall()
{
	if (!dispatched)
	{
		cout << "⚠️ " << "Cannot recall a non-dispatched unit." << endl;
		return;
	}
	if (perimeterSecured) perimeterSecured = false;
	dispatched = false;
	cout << "↩️ " << name << " recalled." << endl;
}

void SecurityTeam::handleEvent(const string& event)
{
	if (event == Events::MEDICAL_DISPATCHED && dispatched)
	{
		perimeterSecured = true;
		cout << "🛡️ [Mediator] " << name << " secures the perimeter now that Medical is on scene." << endl;
	}
	else if (!dispatched)
	{
		cout << "⚠️ " << name << " is not yet on the scene."  << endl;
	}
	// should the security need to handle a medical dispatch, the perimeter will be secured
	// if there is no available security, there is nothing they can do
}

// === FACILITIES TEAM (CONCRETE COLLEAGUE) ==== //

void FacilitiesTeam::dispatch()
{
	if (dispatched)
	{
		// here we do logic handling for if a unit is already dispatched
		cout << "⚠️ " << name << " is already dispatched. Duplicate order ignored." << endl;
		return;
	}
	dispatched = true;
	cout << "🔧 " << name << " dispatched to the scene." << endl;
	notifyCoordinator(Events::FACILITIES_DISPATCHED);
}

void FacilitiesTeam::recall()
{
	if (!dispatched)
	{
		cout << "⚠️ " << "Cannot recall a non-dispatched unit." << endl;
		return;
	}
	if (exitsOpened) exitsOpened = false;
	dispatched = false;
	cout << "↩️ " << name << " recalled." << endl;
}

void FacilitiesTeam::handleEvent(const string& event)
{
	if (event == Events::EVACUATION_ORDERED && dispatched)
	{
		exitsOpened = true;
		cout << "🚪 [Mediator] " << name << " throws open the emergency exits." << endl;
	}
	else if (!dispatched)
	{
		cout << "⚠️ " << name << " is not yet on the scene."  << endl;
	}
}

// ==== MEDICAL TEAM (CONCRETE COLLEAGUE) ==== //

void MedicalTeam::dispatch()
{
	if (dispatched)
	{
		// here we do logic handling for if a unit is already dispatched
		cout << "⚠️ " << name << " is already dispatched. Duplicate order ignored." << endl;
		return;
	}
	dispatched = true;
	cout << "🚑 " << name << " dispatched to the scene." << endl;
	notifyCoordinator(Events::MEDICAL_DISPATCHED);
}

void MedicalTeam::recall()
{
	if (!dispatched)
	{
		cout << "⚠️ " << "Cannot recall a non-dispatched unit." << endl;
		return;
	}
	if (treating) treating = false;
	dispatched = false;
	cout << "↩️ " << name << " recalled." << endl;
}

void MedicalTeam::handleEvent(const string& event)
{
	// medical team on-site treats if the area is secured
	if (event == Events::AREA_SECURED && dispatched)
	{
		treating = true;
		cout << "💉 [Mediator] " << name << " begins treating patients now that the area is secured." << endl;
	}
	else if (!dispatched)
	{
		cout << "⚠️ " << name << " is not yet on the scene."  << endl;
	}
}

#endif // RESPONSEUNIT_CPP