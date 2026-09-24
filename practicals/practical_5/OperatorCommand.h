/*
Emmanuel Boateng ()
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 24 September 2026

OperatorCommand.h (Command & Concrete Command, Command)
*/

#ifndef OPERATORCOMMAND_H
#define OPERATORCOMMAND_H

#include <string>
#include <iostream>

#include "Types.h"

using namespace std;

class ResponseUnit;
class AlertSender;
class AccessControlSystem;
class IncidentCoordinator;

class OperatorCommand
{
	public:
		virtual void execute() = 0;
		virtual void undo() = 0;
		virtual string name() const = 0;
		virtual ~OperatorCommand() { };
};

class DispatchUnit: public OperatorCommand
{
	public:
		/// <summary>
		/// unit->dispatch()
		/// </summary>
		void execute() override;
		/// <summary>
		/// unit->recall()
		/// </summary>
		void undo() override;
		/// <summary>
		/// return a readable version of the happenings e.g "Dispatch: Security"
		/// </summary>
		string name() const override;
		DispatchUnit(ResponseUnit* unit);

	private:
		ResponseUnit* unit;
};

class SendAlert: public OperatorCommand
{
	public:
		/// <summary>
		/// notify(message)
		/// if this is successful then coordinate with this, and "ALERT_DELIVERED_" + message
		/// </summary>
		void execute() override;
		/// <summary>
		/// print system advice that alerts cannot be recalled
		/// </summary>
		void undo() override;
		/// <summary>
		/// Alert: message (legacy code #)
		/// note that for all the name functions, take the enum and make the output suitable for the class using conditional logic, rather than outputting the raw enum each time
		/// </summary>
		string name() const override;
		SendAlert(AlertSender* sender, IncidentCoordinator* coordinator, AlertType message);

	private:
		AlertSender* sender;
		AlertType message;
		/// <summary>
		/// this is the last code given by notify
		/// </summary>
		int lastCode = -1;
		IncidentCoordinator* coordinator;
};

class SecureArea: public OperatorCommand
{
	public:
		/// <summary>
		/// lock the area then afterwards ask the coordinator to coordinate this, and AREA _SECURED
		/// </summary>
		void execute() override;
		/// <summary>
		/// unlock the area
		/// </summary>
		void undo() override;
		/// <summary>
		/// e.g. Secure: Front Gates
		/// </summary>
		string name() const override;
		SecureArea(AccessControlSystem* acs, IncidentCoordinator* coordinator, string area);

	private:
		AccessControlSystem* acs;
		string area;
		IncidentCoordinator* coordinator;
};

#endif // OPERATORCOMMAND_H