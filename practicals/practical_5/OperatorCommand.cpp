/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 28 September 2026

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
	// a refused command throws, so OperatorConsole reports it as failed and
	// never records it in the history (a refusal must not look like a success)
	if (this->unit == nullptr)
		throw runtime_error("no unit assigned");

	if (this->dispatched)
		throw runtime_error(this->unit->getName() + " has already been dispatched by this command");

	// one main team of each kind covers campus: if it is busy, it lets us know
	if (this->unit->isDispatched())
		throw runtime_error(this->unit->getName() + " is busy, it is already on the scene");

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
		throw runtime_error("no alert service configured");

	if (this->lastCode != -1)
		throw runtime_error("this alert has already been issued");

	this->lastCode = this->sender->notify(this->message);

	if (this->lastCode == -1 || this->lastCode == 404)
	{
		this->lastCode = -1;
		throw runtime_error("ALERT_NOT_DELIVERED");
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
		throw runtime_error("no access-control system");

	if (this->secured)
		throw runtime_error(this->area + " was already secured by this command");

	// lockArea throws if the area is already locked, OperatorConsole reports it
	this->acs->lockArea(this->area);
	this->secured = true;
	if (coordinator) coordinator->coordinate(nullptr, Events::AREA_SECURED);
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