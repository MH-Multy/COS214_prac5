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
	throw "Not yet implemented";
}

void DispatchUnit::undo()
{
	throw "Not yet implemented";
}

string DispatchUnit::name() const
{
	throw "Not yet implemented";
}

// ==== SEND ALERT (CONCRETE COMMAND) ==== //

SendAlert::SendAlert(AlertSender* sender, AlertType message)
{
	this->sender = sender;
	this->message = message;
	this->lastCode = -1;
}

void SendAlert::execute() {
	throw "Not yet implemented";
}

void SendAlert::undo()
{
	throw "Not yet implemented";
}

string SendAlert::name() const
{
	throw "Not yet implemented";
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