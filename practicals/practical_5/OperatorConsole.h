/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 27 September 2026

OperatorConsole.h (Invoker, Command)
*/

#ifndef OPERATORCONSOLE_H
#define OPERATORCONSOLE_H

#include <memory>
#include <vector>

#include "OperatorCommand.h"

using namespace std;

class OperatorConsole
{
	public:
		/// <summary>
		/// try execute, catch exception { print that the command failed and the error and early return } then push back the command to the history
		/// also print the name after executing (in try block), this will allow for legacy codes to show where applicable
		/// when using this function, catch appropriately
		/// </summary>
		void issueCommand(unique_ptr<OperatorCommand> command);
		/// <summary>
		/// if history is empty print an advice message and return else undo the item at the back and pop the history vector
		/// </summary>
		void cancelLast();

	private:
		vector<unique_ptr<OperatorCommand> > history;
};

#endif // OPERATORCONSOLE_H