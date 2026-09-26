/*
Emmanuel Boateng (u23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 26 September 2026

OperatorCommand.cpp (Command & Concrete Command, Command)
*/

#ifndef OPERATORCOMMAND_CPP
#define OPERATORCOMMAND_CPP

#include <exception>
#include <string>
#include <iostream>

using namespace std;

#include "OperatorCommand.h"
#include "ResponseUnit.h"
#include "LegacyAlertAdapter.h"
#include "AccessControlSystem.h"

// ==== DISPATCH UNIT (CONCRETE COMMAND) ==== //

DispatchUnit::DispatchUnit(ResponseUnit* unit)
{
	this->unit = unit;
	this->dispatched = false;
}

void DispatchUnit::execute()
{
	if (this->unit == nullptr)
	{
		cout << "[DispatchUnit] refused: no unit assigned" << endl;
		return;
	}

	// without this guard a repeated dispatch silently re-sends a unit that is
	// already deployed, and a later undo recalls it from the wrong incident
	if (this->dispatched)
	{
		cout << "[DispatchUnit] refused: " << this->unit->getName()
		     << " has already been dispatched by this command" << endl;
		return;
	}

	this->unit->dispatch();
	this->dispatched = true;
}

void DispatchUnit::undo()
{
	if (!this->dispatched)
	{
		cout << "[DispatchUnit] nothing to undo: no unit was dispatched" << endl;
		return;
	}

	this->unit->recall();
	this->dispatched = false;
}

string DispatchUnit::name() const
{
	if (this->unit == nullptr)
	{
		return "Dispatch: (no unit)";
	}

	return "Dispatch: " + this->unit->getName();
}

// ==== SEND ALERT (CONCRETE COMMAND) ==== //

SendAlert::SendAlert(AlertSender* sender, AlertType message)
{
	this->sender = sender;
	this->message = message;
	this->lastCode = -1;
}

void SendAlert::execute()
{
	if (this->sender == nullptr)
	{
		cout << "[SendAlert] refused: no alert service configured" << endl;
		return;
	}

	if (this->lastCode != -1)
	{
		cout << "[SendAlert] refused: this alert has already been issued" << endl;
		return;
	}

	this->lastCode = this->sender->notify(this->message);

	// both sentinels must fail for the code to be valid, so this is a conjunction;
	// with || the condition is true for every possible value
	if (this->lastCode != -1 && this->lastCode != 404)
	{
		cout << "ALERT_DELIVERED_" << name() << endl;
	}
	else
	{
		cout << "ALERT_NOT_DELIVERED" << endl;
		this->lastCode = -1;
	}
}

void SendAlert::undo()
{
	if (this->lastCode == -1)
	{
		cout << "[SendAlert] nothing to undo: no alert was delivered" << endl;
		return;
	}

	cout << "[SendAlert] system alerts cannot be recalled; alert code "
	     << this->lastCode << " remains in effect" << endl;
}

string SendAlert::name() const
{
	string messageName;
	switch (this->message)
	{
		case AlertType::LOCKDOWN:
			messageName = "LOCKDOWN";
			break;
		case AlertType::EVACUATE:
			messageName = "EVACUATE";
			break;
		case AlertType::MEDICAL_PRIORITY:
			messageName = "MEDICAL_PRIORITY";
			break;
	}

	return "Alert: " + messageName + " (code: " + to_string(this->lastCode) + ")";
}

// ==== SECURE AREA (CONCRETE COMMAND) ==== //

SecureArea::SecureArea(AccessControlSystem* acs, string area)
{
	this->acs = acs;
	this->area = area;
	this->secured = false;
}

void SecureArea::execute()
{
	if (this->acs == nullptr)
	{
		cout << "[SecureArea] refused: no access-control system" << endl;
		return;
	}

	if (this->secured)
	{
		cout << "[SecureArea] refused: " << this->area
		     << " was already secured by this command" << endl;
		return;
	}

	try
	{
		this->acs->lockArea(this->area);
		this->secured = true;
		cout << "AREA_SECURED " << this->area << endl;
	}
	catch (const exception& e)
	{
		cout << "[SecureArea] could not secure " << this->area << ": " << e.what() << endl;
	}
	catch (...)
	{
		cout << "[SecureArea] could not secure " << this->area << endl;
	}
}

void SecureArea::undo()
{
	if (!this->secured)
	{
		cout << "[SecureArea] nothing to undo: " << this->area
		     << " was never secured by this command" << endl;
		return;
	}

	try
	{
		this->acs->unlockArea(this->area);
		this->secured = false;
		cout << "AREA_RELEASED " << this->area << endl;
	}
	catch (const exception& e)
	{
		cout << "[SecureArea] could not release " << this->area << ": " << e.what() << endl;
	}
	catch (...)
	{
		cout << "[SecureArea] could not release " << this->area << endl;
	}
}

string SecureArea::name() const
{
	return "Secure: " + this->area;
}

#endif // OPERATORCOMMAND_CPP
