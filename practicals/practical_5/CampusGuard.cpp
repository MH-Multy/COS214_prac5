/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 27 September 2026

CampusGuard.cpp (Facade)
*/

#ifndef CAMPUSGUARD_CPP
#define CAMPUSGUARD_CPP

#include "CampusGuard.h"

// ==== CAMPUS GUARD (FACADE) ==== //

CampusGuard::CampusGuard() {
	throw "Not yet implemented";
}

Incident& CampusGuard::reportIncident(string area, Severity severity) {
	throw "Not yet implemented";
}

void CampusGuard::resolveIncident(Incident& incident) {
	throw "Not yet implemented";
}

unique_ptr<DispatchStrategy> CampusGuard::strategyFor(Severity severity) {
	throw "Not yet implemented";
}

#endif // CAMPUSGUARD_CPP