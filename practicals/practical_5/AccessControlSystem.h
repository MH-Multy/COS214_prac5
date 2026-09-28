/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 27 September 2026

AccessControlSystem.h (Receivers, Command)
*/

#ifndef ACCESSCONTROLSYSTEM_H
#define ACCESSCONTROLSYSTEM_H

#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include <exception>

using namespace std;

class SecureArea;

// Receivers which take part in other patterns
class ResponseUnit; // implement in ResponseUnit.cpp

class AlertSender; // implement in LegacyAlertAdapter.cpp

class AccessControlSystem
{
	private:
        map<string, bool> lockedAreas;

    public:
        /// <summary>
        /// look up the area in lockedAreas, if it is already true throw a logic error since the area is already locked, otherwise set the area to true and return true. make sure you try/catch where this is used and cout in the function with the reason
        /// </summary>
        bool lockArea(const string& area);
        /// <summary>
        /// similar to the lockArea
        /// </summary>
        bool unlockArea(const string& area);
        /// <summary>
        /// return lockedAreas.count(area) && lockedAreas.at(area); (uses early returns)
        /// </summary>
        bool isLocked(const string& area) const;
};

#endif // ACCESSCONTROLSYSTEM_H