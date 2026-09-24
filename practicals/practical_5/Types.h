/*
Emmanuel Boateng ()
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 24 September 2026

Types.h
*/

#ifndef TYPES_H
#define TYPES_H

#include <ctime>
#include <iostream>
#include <string>

using namespace std;

enum class Status
{
    REPORTED,
    ACTIVE,
    RESOLVED
};

enum class Severity
{
    LOW,
    HIGH
};

enum class AlertType
{
    LOCKDOWN,
    EVACUATE,
    MEDICAL_PRIORITY
};

struct LogEntry
{
    time_t timestamp;
    int id;
    Status status;
};

#endif // TYPES_H