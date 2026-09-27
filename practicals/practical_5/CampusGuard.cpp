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

CampusGuard::CampusGuard()
{
	security = unique_ptr<SecurityTeam>(new SecurityTeam("Security Team", nullptr));
	medical = unique_ptr<MedicalTeam>(new MedicalTeam("Medical Team", nullptr));
	facilities = unique_ptr<FacilitiesTeam>(new FacilitiesTeam("Facilities", nullptr));

	coordinator = unique_ptr<IncidentResponseDesk>(new IncidentResponseDesk(security.get(), medical.get(), facilities.get()));

	security->setCoordinator(coordinator.get());
	medical->setCoordinator(coordinator.get());
	facilities->setCoordinator(coordinator.get());

	acs = unique_ptr<AccessControlSystem>(new AccessControlSystem);
	legacySystem = unique_ptr<LegacyAlertSystem>(new LegacyAlertSystem);
	alertSender = unique_ptr<LegacyAlertAdapter>(new LegacyAlertAdapter(legacySystem.get()));
	accessObserver = unique_ptr<AccessControlObserver>(new AccessControlObserver(acs.get()));
	logObserver = unique_ptr<IncidentLogObserver>(new IncidentLogObserver);
	console = unique_ptr<OperatorConsole>(new OperatorConsole);
}

Incident& CampusGuard::reportIncident(string area, Severity severity)
{
	incidents.push_back(unique_ptr<Incident>(new Incident(nextId++, area, severity)));
	Incident& incident = *incidents.back();

	incident.attach(accessObserver.get());
	incident.attach(logObserver.get());

	cout << "\n🚨🚨🚨 New Incident #" << incident.getId() << " reported @ " << area << " 🚨🚨🚨" << endl;

	strategy = strategyFor(severity);
	cout << "🧭 Dispatch strategy selected: " << strategy->label() << endl;

	vector<ResponseUnit*> units = strategy->selectUnits(security.get(), medical.get(), facilities.get());
	for (size_t i = 0; i < units.size(); i ++)
	{
		console->issueCommand(unique_ptr<DispatchUnit>(new DispatchUnit(units[i])));
	}

	console->issueCommand(unique_ptr<SecureArea>(new SecureArea(acs.get(), coordinator.get(), area)));
	console->issueCommand(unique_ptr<SendAlert>(new SendAlert(alertSender.get(), coordinator.get(), strategy->alertMessage())));
	incident.setStatus(Status::ACTIVE);

	strategy = nullptr;
	return incident;
}

void CampusGuard::resolveIncident(Incident& incident)
{
	cout << "\n✅ Resolving Incident #" << incident.getId() << " ✅" << endl;

	incident.setStatus(Status::RESOLVED);

	// units stand down
	// have the isDispatched check because if we recall a not dispatched unit, there is
	// an error message, so only recall if dispatched already. undo is responsible for recalling
	// no matter what
	if (security->isDispatched()) security->recall();
	if (medical->isDispatched()) medical->recall();
	if (facilities->isDispatched()) facilities->recall();
}

unique_ptr<DispatchStrategy> CampusGuard::strategyFor(Severity severity)
{
	if(severity == Severity::HIGH) return unique_ptr<DispatchStrategy>(new HighSeverity());
	return unique_ptr<DispatchStrategy>(new LowSeverity());
}

void CampusGuard::printLog() const { logObserver->printLog(); }

#endif // CAMPUSGUARD_CPP