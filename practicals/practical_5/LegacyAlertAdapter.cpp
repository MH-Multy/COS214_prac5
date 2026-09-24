/*
Emmanuel Boateng ()
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 24 September 2026

LegacyAlertAdapter.cpp (Target/Adaptee/Adapter, Adapter)
*/

#ifndef LEGACYALERTADAPTER_CPP
#define LEGACYALERTADAPTER_CPP

#include "LegacyAlertAdapter.h"

// ==== LEGACY ALERT SYSTEM (ADAPTEE) ==== //

void LegacyAlertSystem::sendLegacyAlert(int code)
{
	throw "Not yet implemented";
}

// ==== LEGACY ALERT ADAPTER (ADAPTER) ==== //

LegacyAlertAdapter::LegacyAlertAdapter(LegacyAlertSystem* legacy)
{
	this->legacy = legacy;
}

int LegacyAlertAdapter::notify(AlertType message)
{
	throw "Not yet implemented";
}

int LegacyAlertAdapter::codeFor(AlertType message)
{
	throw "Not yet implemented";
}

#endif // LEGACYALERTADAPTER_CPP