/*
Emmanuel Boateng ()
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 24 September 2026

OperatorCommand.cpp (Command & Concrete Command, Command)
*/

#ifndef OPERATORCOMMAND_CPP
#define OPERATORCOMMAND_CPP

#include <exception>
#include <string>
#include <iostream>

using namespace std;

#include "OperatorCommand.h"

// ==== DISPATCH UNIT (CONCRETE COMMAND) ==== //

DispatchUnit::DispatchUnit(ResponseUnit* unit)
{
	this->unit = unit;
}

void DispatchUnit::execute()
{
	unit->dispatch();
}

void DispatchUnit::undo()
{
	unit->recall();
}

string DispatchUnit::name() const
{
	return "Dispatch unit name: " unit->getName();
}

// ==== SEND ALERT (CONCRETE COMMAND) ==== //

SendAlert::SendAlert(AlertSender* sender, AlertType message)
{
	this->sender = sender;
	this->message = message;
	this->lastCode = -1;
}

void SendAlert::execute() {
	lastCode = sender->notify(message);
	if (lastCode != -1 || lastCode != 404) // a valid code has been returned
	{
		cout << "ALERT_DELIVERED_" << name();
	}
	else
	{
		cout << "ALERT_NOT_DELIVERED";
	}
}

void SendAlert::undo()
{
	cout << "System alerts can not be recalled";
}

string SendAlert::name() const
{
	string messageName;
	switch (message)
	{
		case AlertType::LOCKDOWN:
			messageName = "LOCKDOWN";
			break;
		case AlertType::EVACUATE:
			messageName = "EVACUATE";
			break;
		case AlertType::MEDICAL_PRIORITY:
			messageName = "MEDIACL_PRIORITY";
			break;
	}
	return "Alert: " + messageName + " (code: " + to_string(lastCode) + ")";
}

// ==== SECURE AREA (CONCRETE COMMAND) ==== //

SecureArea::SecureArea(AccessControlSystem* acs, string area)
{
	this->acs = acs;
	this->area = area;
}

void SecureArea::execute()
{
	throw "Not yet implemented";
}

void SecureArea::undo()
{
	throw "Not yet implemented";
}

string SecureArea::name() const
{
	throw "Not yet implemented";
}

#endif // OPERATORCOMMAND_CPP