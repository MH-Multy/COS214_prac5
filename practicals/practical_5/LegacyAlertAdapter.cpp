/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 27 September 2026

LegacyAlertAdapter.cpp (Target/Adaptee/Adapter, Adapter)
*/

#ifndef LEGACYALERTADAPTER_CPP
#define LEGACYALERTADAPTER_CPP

#include "LegacyAlertAdapter.h"

// ==== LEGACY ALERT SYSTEM (ADAPTEE) ==== //

void LegacyAlertSystem::sendLegacyAlert(int code)
{
	cout << "📟 [Legacy Panel] Siren code " << code << " triggered on the old alert panel." << endl;
}

// ==== LEGACY ALERT ADAPTER (ADAPTER) ==== //

LegacyAlertAdapter::LegacyAlertAdapter(LegacyAlertSystem* legacy)
{
	this->legacy = legacy;
}

int LegacyAlertAdapter::notify(AlertType message)
{
	int code = codeFor(message);
	legacy->sendLegacyAlert(code);
	return code;
}

int LegacyAlertAdapter::codeFor(AlertType message)
{
	switch (message)
	{
		case AlertType::LOCKDOWN:
			return 1;
		case AlertType::EVACUATE:
			return 2;
	}
	cout << "⚠️ Unkown AlertType sent, no match found" << endl;
	return 404;
}

#endif // LEGACYALERTADAPTER_CPP