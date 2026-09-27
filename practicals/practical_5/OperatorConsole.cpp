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

void OperatorConsole::issueCommand(unique_ptr<OperatorCommand> command) {
	throw "Not yet implemented";
}

void OperatorConsole::cancelLast() {
	throw "Not yet implemented";
}

#endif // OPERATORCONSOLE_CPP