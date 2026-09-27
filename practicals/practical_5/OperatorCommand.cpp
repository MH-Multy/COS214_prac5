/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 26 September 2026

OperatorCommand.cpp (Command & Concrete Command, Command)
*/

#ifndef OPERATORCOMMAND_CPP
#define OPERATORCOMMAND_CPP

using namespace std;

#include "OperatorCommand.h"
#include "ResponseUnit.h"
#include "LegacyAlertAdapter.h"
#include "AccessControlSystem.h"

// ==== DISPATCH UNIT (CONCRETE COMMAND) ==== //

DispatchUnit::DispatchUnit(ResponseUnit* unit)
{
	this->unit = unit;
}

void DispatchUnit::execute()
{
	if (this->unit == nullptr)
	{
		cout << "⚠️ [DispatchUnit] Refused: no unit assigned" << endl;
		return;
	}

	// without this guard a repeated dispatch silently re-sends a unit that is
	// already deployed, and a later undo recalls it from the wrong incident
	if (this->dispatched)
	{
		cout << "⚠️ [DispatchUnit] Refused: " << this->unit->getName()
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
		cout << "⚠️ [DispatchUnit] Nothing to undo: no unit was dispatched" << endl;
		return;
	}

	this->unit->recall();
	this->dispatched = false;
}

string DispatchUnit::name() const
{
	if (this->unit == nullptr)
	{
		return "🚨 Dispatch: (no unit)";
	}

	return "🚨 Dispatch: " + this->unit->getName();
}

// ==== SEND ALERT (CONCRETE COMMAND) ==== //

SendAlert::SendAlert(AlertSender* sender, IncidentCoordinator* coordinator, AlertType message)
{
	this->sender = sender;
	this->message = message;
	this->coordinator = coordinator;
	this->lastCode = -1;
}

void SendAlert::execute()
{
	if (this->sender == nullptr)
	{
		cout << "⚠️ [SendAlert] Refused: no alert service configured" << endl;
		return;
	}

	if (this->lastCode != -1)
	{
		cout << "⚠️ [SendAlert] Refused: this alert has already been issued" << endl;
		return;
	}

	this->lastCode = this->sender->notify(this->message);

	if (this->lastCode == -1 || this->lastCode == 404)
	{
		cout << "❌ ALERT_NOT_DELIVERED" << endl;
		this->lastCode = -1;
		return;
	}

	cout << "✅ ALERT_DELIVERED " << name() << endl;

	// on successful delivery, tell the mediator so it can route to the right team
	if (this->coordinator != nullptr)
    {
		switch (this->message)
		{
			case AlertType::EVACUATE:
				this->coordinator->coordinate(nullptr, Events::ALERT_DELIVERED_EVACUATE);
				break;
			case AlertType::LOCKDOWN:
				this->coordinator->coordinate(nullptr, Events::ALERT_DELIVERED_LOCKDOWN);
				break;
		}
	}
}

void SendAlert::undo()
{
	if (this->lastCode == -1)
	{
		cout << "[SendAlert] Nothing to undo: no alert was delivered" << endl;
		return;
	}

	cout << "🚫 [SendAlert] Alerts cannot be recalled once broadcast; alert code "
	     << this->lastCode << " remains in effect" << endl;
}

string SendAlert::name() const
{
	string messageName;
	switch (this->message)
	{
		case AlertType::LOCKDOWN:
			messageName = "🔒 Lockdown";
			break;
		case AlertType::EVACUATE:
			messageName = "🏃 Evacuate";
			break;
		default:
			messageName = "⚠️ Unknown";
			break;
	}

	return "📢 Alert: " + messageName + " (legacy code: " + to_string(this->lastCode) + ")";
}

// ==== SECURE AREA (CONCRETE COMMAND) ==== //

SecureArea::SecureArea(AccessControlSystem* acs, IncidentCoordinator* coordinator, string area)
{
	this->acs = acs;
	this->area = area;
	this->coordinator = coordinator;
	this->secured = false;
}

void SecureArea::execute()
{
	if (this->acs == nullptr)
	{
		cout << "⚠️ [SecureArea] Refused: no access-control system" << endl;
		return;
	}

	if (this->secured)
	{
		cout << "⚠️ [SecureArea] Refused: " << this->area
		     << " was already secured by this command" << endl;
		return;
	}

	try
	{
		this->acs->lockArea(this->area);
		this->secured = true;
		if(coordinator) coordinator->coordinate(nullptr, Events::AREA_SECURED);
	}
	catch (const exception& e)
	{
		cout << "ℹ️ [SecureArea] Could not secure " << this->area << ": " << e.what() << endl;
	}
	catch (...)
	{
		cout << "⚠️ [SecureArea] Could not secure " << this->area << endl;
	}
}

void SecureArea::undo()
{
	if (!this->secured)
	{
		cout << "⚠️ [SecureArea] Nothing to undo: " << this->area
		     << " was never secured by this command" << endl;
		return;
	}

	try
	{
		this->acs->unlockArea(this->area);
		this->secured = false;
		cout << "🔓 Area released (" << this->area << ")" << endl;
	}
	catch (const exception& e)
	{
		cout << "ℹ️ [SecureArea] Could not release " << this->area << ": " << e.what() << endl;
	}
	catch (...)
	{
		cout << "⚠️ [SecureArea] Could not release " << this->area << endl;
	}
}

string SecureArea::name() const
{
	return "🔐 Secure: " + this->area;
}

#endif // OPERATORCOMMAND_CPP