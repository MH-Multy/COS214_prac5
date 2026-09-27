/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 27 September 2026

OperatorConsole.cpp (Invoker, Command)
*/

#ifndef OPERATORCONSOLE_CPP
#define OPERATORCONSOLE_CPP

#include "OperatorConsole.h"
#include "OperatorCommand.h"

// ==== OPERATOR CONSOLE (INVOKER) ==== //

void OperatorConsole::issueCommand(unique_ptr<OperatorCommand> command)
{
	try
	{
		command->execute();
		cout << "✅ Executed: " << command->name() << endl;
	}
	catch (const exception& e)
	{
		cout << "❌ Command failed: " << e.what() << endl;
		return;
	}
	history.push_back(move(command));
}

void OperatorConsole::cancelLast()
{
	if (history.empty())
	{
		cout << "ℹ️  Nothing to cancel, command history is empty." << endl;
		return;
	}
	cout << "↩️  Cancelling: " << history.back()->name() << endl;
	history.back()->undo();
	history.pop_back();
}

#endif // OPERATORCONSOLE_CPP