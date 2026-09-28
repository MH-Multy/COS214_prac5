/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 27 September 2026

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
    EVACUATE
};

struct LogEntry
{
    time_t timestamp;
    int id;
    Status status;
};

// minimises typos
namespace Events
{
    const string MEDICAL_DISPATCHED = "MEDICAL_DISPATCHED";
    const string AREA_SECURED = "AREA_SECURED";
    const string ALERT_DELIVERED_EVACUATE = "ALERT_DELIVERED_EVACUATE";
    const string ALERT_DELIVERED_LOCKDOWN = "ALERT_DELIVERED_LOCKDOWN";
    const string EVACUATION_ORDERED = "EVACUATION_ORDERED";
    const string SECURITY_DISPATCHED = "SECURITY_DISPATCHED";
    const string FACILITIES_DISPATCHED = "FACILITIES_DISPATCHED";
}

#endif // TYPES_H