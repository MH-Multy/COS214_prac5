/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 27 September 2026

AccessControlSystem.cpp (Receivers, Command)
*/

#ifndef ACCESSCONTROLSYSTEM_CPP
#define ACCESSCONTROLSYSTEM_CPP

#include "AccessControlSystem.h"

#include "ResponseUnit.h"
#include "LegacyAlertAdapter.h"
#include "OperatorCommand.h"

bool AccessControlSystem::lockArea(const string& area)
{
    if (lockedAreas.count(area) && lockedAreas.at(area))
        throw logic_error("area '" + area + "' is already locked");

    lockedAreas[area] = true;
    return true;
}

bool AccessControlSystem::unlockArea(const string& area)
{
    if (!lockedAreas.count(area) || !lockedAreas.at(area)) 
		throw logic_error("area '" + area + "' is already unlocked");

    lockedAreas[area] = false;
    return true;
}

bool AccessControlSystem::isLocked(const string& area) const
{
    return lockedAreas.count(area) && lockedAreas.at(area);
}

#endif // ACCESSCONTROLSYSTEM_CPP