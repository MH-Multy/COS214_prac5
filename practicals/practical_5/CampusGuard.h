/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 27 September 2026

CampusGuard.h (Facade)
*/

#ifndef CAMPUSGUARD_H
#define CAMPUSGUARD_H

#include <memory>
#include <string>
#include <vector>

using namespace std;

#include "Types.h"
#include "ResponseUnit.h"
#include "OperatorConsole.h"
#include "OperatorCommand.h"
#include "LegacyAlertAdapter.h"
#include "AccessControlSystem.h"
#include "IncidentObserver.h"
#include "Incident.h"
#include "DispatchStrategy.h"

class CampusGuard
{
	public:
		CampusGuard();
		/// <summary>
		/// when we report an incident we first create a new incident and add it to the incidents vector. we also need to attach the observers for campus guard to the new incident
		/// the strategyFor will give a dispatch strategy, based on the severity, change the strategy attribute of the class and use that, for memory/safety sake, after an incident is reported, null it again at the end of the function
		/// after observers are attached, set status to reported to allow observers a chance to respond, then later after the incident has been handled set to active
		/// we then print the label of the selected dispatch strategy (cout "Dispatch strategy selected: " + strategy->label()) then select units from it
		/// for each selected unit, we then get a dispatch unit from it and issue command on that
		/// the area then gets locked down (with secure area class, based on acs) then we issue command on that
		/// then use the adapter (send alert based on the alertsender with alerttype which we get from the strategy), then issue command on the send alert
		/// the incident must be set to active (triggers observers)
		/// lastly return the new incident
		/// </summary>
		Incident& reportIncident(string area, Severity severity);
		/// <summary>
		/// take the incident and set its status to resolved, that will cause the observers to react
		/// </summary>
		void resolveIncident(Incident& incident);

	private:
		/// <summary>
		/// using severity struct determine whether to use high or low strategy (severity struct says high or low)
		/// </summary>
		unique_ptr<DispatchStrategy> strategyFor(Severity severity);
		unique_ptr<OperatorConsole> console;
		unique_ptr<IncidentResponseDesk> coordinator;
		unique_ptr<SecurityTeam> security;
		unique_ptr<MedicalTeam> medical;
		unique_ptr<FacilitiesTeam> facilities;
		unique_ptr<AccessControlSystem> acs;
		unique_ptr<LegacyAlertSystem> legacySystem;
		unique_ptr<LegacyAlertAdapter> alertSender;
		unique_ptr<AccessControlObserver> accessObserver;
		unique_ptr<IncidentLogObserver> logObserver;
		vector<unique_ptr<Incident> > incidents;
		/// <summary>
		/// this will be the id of the next reported incident
		/// </summary>
		int nextId = 0;
		unique_ptr<DispatchStrategy> strategy;
};

#endif // CAMPUSGUARD_H