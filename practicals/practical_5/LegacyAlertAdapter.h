/*
Emmanuel Boateng ()
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 24 September 2026

LegacyAlertAdapter.h (Target/Adaptee/Adapter, Adapter)
*/

#ifndef LEGACYALERTADAPTER_H
#define LEGACYALERTADAPTER_H

#include "Types.h"

using namespace std;

class AlertSender
{
	public:
		/// <summary>
		/// returns the adapted message code
		/// </summary>
		virtual int notify(AlertType message) = 0;
		virtual ~AlertSender() = default;
};

class LegacyAlertSystem
{
	public:
		void sendLegacyAlert(int code);
};

class LegacyAlertAdapter: public AlertSender
{
	public:
		LegacyAlertAdapter(LegacyAlertSystem* legacy);
		/// <summary>
		/// first find the code and then send it to the legacy alert then return the code
		/// </summary>
		int notify(AlertType message) override;

	private:
		/// <summary>
		/// keyed using the AlertType enum
		/// </summary>
		int codeFor(AlertType message);
		LegacyAlertSystem* legacy;
};

#endif // LEGACYALERTADAPTER_H