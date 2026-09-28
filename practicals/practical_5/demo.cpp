/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 29 September 2026

demo.cpp (Interactive, dynamic demo)
*/

#ifdef CAMPUSGUARD_DEMO

#include <iostream>
#include <memory>
#include <string>

#include "CampusGuard.h"

using namespace std;

string name = "";
bool autoMode = false;
bool inputClosed = false;

string ask(const string& prompt)
{
	cout << prompt << flush;
	string line;
	if (!getline(cin, line))
	{
		inputClosed = true;
		return "";
	}
	return line;
}

int askChoice(const string& prompt, int lo, int hi)
{
	while (true)
	{
		string line = ask(prompt);
		if (inputClosed) return -1;
		if (line.size() == 1 && line[0] >= '0' + lo && line[0] <= '0' + hi) return line[0] - '0';
		cout << "❓ Please enter a number from " << lo << " to " << hi << ".\n";
	}
}

void pressEnterToContinue()
{
	if (autoMode) return;
	ask("\nPress Enter to continue...");
}

void title(const string& text) { cout << "\n" << text << "\n"; }
void say(const string& text) { cout << "\n🎙️  " << text << "\n"; }

struct Squad
{
	SecurityTeam security;
	MedicalTeam medical;
	FacilitiesTeam facilities;
	IncidentResponseDesk desk;
	AccessControlSystem acs;
	LegacyAlertSystem legacy;
	LegacyAlertAdapter adapter;
	OperatorConsole console;

	Squad() : security("Security Team", nullptr), medical("Medical Team", nullptr), facilities("Facilities", nullptr), desk(&security, &medical, &facilities), adapter(&legacy)
	{
		security.setCoordinator(&desk);
		medical.setCoordinator(&desk);
		facilities.setCoordinator(&desk);
	}
};

void reportIncident(CampusGuard& guard, Incident*& open, string area, Severity severity)
{
	title("🚨 FACADE 🚨");
	say("One call, guard.reportIncident(), runs the whole workflow. Watch every pattern light up.");
	open = &guard.reportIncident(area, severity);
	say("Incident #" + to_string(open->getId()) + " is now ACTIVE.");
	if (severity == Severity::LOW) say("Medical was not sent for a low-severity incident, hence 'not yet on the scene' above.");
	else say("The double-lock message above is the Observer being refused: the SecureArea command had already locked the door.");
}

void reportMenu(CampusGuard& guard, Incident*& open)
{
	if (open != nullptr)
	{
		say("🚧 Campus has one main team of each kind, and they are still out on Incident #" + to_string(open->getId()) + ". Resolve it first (option 2).");
		return;
	}
	string area = ask("\n📍 Where is it? (Enter = Library): ");
	if (inputClosed) return;
	if (area.empty()) area = "Library";
	cout << "  1. 🟡 Low severity\n  2. 🔥 High severity\n";
	Severity severity = askChoice("Severity: ", 1, 2) == 2 ? Severity::HIGH : Severity::LOW;
	reportIncident(guard, open, area, severity);
}

void resolveIncident(CampusGuard& guard, Incident*& open)
{
	title("✅ RESOLVE ✅");
	if (open == nullptr)
	{
		say("Nothing to resolve. Report an incident first.");
		return;
	}
	guard.resolveIncident(*open);
	open = nullptr;
	say("The doors reopened, the teams stood down, and the logger wrote it all down:");
	guard.printLog();
}

void demoCommand()
{
	title("🎮 COMMAND 🎮");
	say("Every operator action is an object, so it can be run, remembered and undone.");
	Squad s;
	s.console.issueCommand(unique_ptr<DispatchUnit>(new DispatchUnit(&s.security)));
	s.console.issueCommand(unique_ptr<DispatchUnit>(new DispatchUnit(&s.medical)));
	s.console.issueCommand(unique_ptr<SecureArea>(new SecureArea(&s.acs, &s.desk, "Library")));

	say("Wrong call! Cancelling the last three commands, then one more with nothing left:");
	s.console.cancelLast();
	s.console.cancelLast();
	s.console.cancelLast();
	s.console.cancelLast();
}

void demoMediator()
{
	title("🕸️  MEDIATOR 🕸️");
	say("The teams never talk to each other. They only talk to the IncidentResponseDesk.");
	Squad s;
	s.security.dispatch();
	say("Medical arrives. Security has no idea Medical exists, the desk tells it:");
	s.medical.dispatch();
	say("The area is secured. The desk tells Medical:");
	s.desk.coordinate(nullptr, Events::AREA_SECURED);
	say("An evacuation alert is delivered. The desk tells Facilities:");
	s.facilities.dispatch();
	s.desk.coordinate(nullptr, Events::ALERT_DELIVERED_EVACUATE);

	cout << "\n📋 Perimeter secured: " << (s.security.isPerimeterSecured() ? "yes" : "no")
	<< " | Treating: " << (s.medical.isTreating() ? "yes" : "no")
	<< " | Exits open: " << (s.facilities.areExitsOpened() ? "yes" : "no") << "\n";
}

void demoAdapter()
{
	title("🔌 ADAPTER 🔌");
	say("CampusGuard speaks AlertType. The old alert panel only understands numbers.");
	Squad s;
	cout << "\n🗣️  CampusGuard says LOCKDOWN...\n";
	int lockdownCode = s.adapter.notify(AlertType::LOCKDOWN);
	cout << "🔁 The adapter translated it to code " << lockdownCode << ".\n";
	cout << "\n🗣️  CampusGuard says EVACUATE...\n";
	int evacuateCode = s.adapter.notify(AlertType::EVACUATE);
	cout << "🔁 The adapter translated it to code " << evacuateCode << ".\n";

	say("Sent as a command, a delivered alert also reaches the mediator. Facilities is on scene, so it opens the exits:");
	s.facilities.dispatch();
	s.console.issueCommand(unique_ptr<SendAlert>(new SendAlert(&s.adapter, &s.desk, AlertType::EVACUATE)));
	say("And an alert, once broadcast, cannot be taken back:");
	s.console.cancelLast();
}

void demoObserver()
{
	title("👁️  OBSERVER 👁️");
	say("An Incident broadcasts its status. One listener locks doors, the other keeps a log.");
	AccessControlSystem acs;
	AccessControlObserver doors(&acs);
	IncidentLogObserver logger;
	Incident incident(42, "Chemistry Lab", Severity::HIGH);
	incident.attach(&doors);
	incident.attach(&logger);

	say("Status becomes ACTIVE:");
	incident.setStatus(Status::ACTIVE);
	cout << "🚪 Chemistry Lab is " << (acs.isLocked("Chemistry Lab") ? "🔒 locked" : "🔓 unlocked") << ".\n";
	say("Same status again, nobody is bothered:");
	incident.setStatus(Status::ACTIVE);
	say("Status becomes RESOLVED:");
	incident.setStatus(Status::RESOLVED);
	cout << "🚪 Chemistry Lab is " << (acs.isLocked("Chemistry Lab") ? "🔒 locked" : "🔓 unlocked") << ".\n\n";
	logger.printLog();
}

void demoStrategy()
{
	title("🧭 STRATEGY 🧭");
	say("Severity decides who goes and which alert is sent. CampusGuard's code never changes, only the strategy object does.");
	SecurityTeam security("Security Team", nullptr);
	MedicalTeam medical("Medical Team", nullptr);
	FacilitiesTeam facilities("Facilities", nullptr);
	LegacyAlertSystem legacy;
	LegacyAlertAdapter adapter(&legacy);

	unique_ptr<DispatchStrategy> strategies[2];
	strategies[0].reset(new LowSeverity());
	strategies[1].reset(new HighSeverity());

	for (int i = 0; i < 2; i ++)
	{
		cout << "\n" << strategies[i]->label() << "\n";
		vector<ResponseUnit*> units = strategies[i]->selectUnits(&security, &medical, &facilities);
		cout << "   Teams sent: " << units.size() << "\n";
		say("The strategy's decision is then sent through the adapter:");
		adapter.notify(strategies[i]->alertMessage());
	}
}
void demoFailures()
{
	title("💥 FAILURE CASES 💥");
	say("Invalid operations are never silently ignored. Each one is reported and the system carries on.");
	Squad s;

	cout << "\n1️⃣  Security and Medical are on scene:\n";
	s.console.issueCommand(unique_ptr<DispatchUnit>(new DispatchUnit(&s.security)));
	s.console.issueCommand(unique_ptr<DispatchUnit>(new DispatchUnit(&s.medical)));

	cout << "\n2️⃣  Dispatch Medical again (one team covers campus, and it is busy):\n";
	s.console.issueCommand(unique_ptr<DispatchUnit>(new DispatchUnit(&s.medical)));

	cout << "\n3️⃣  Secure the Library twice:\n";
	s.console.issueCommand(unique_ptr<SecureArea>(new SecureArea(&s.acs, &s.desk, "Library")));
	s.console.issueCommand(unique_ptr<SecureArea>(new SecureArea(&s.acs, &s.desk, "Library")));

	cout << "\n4️⃣  Recall a team that was never sent:\n";
	s.facilities.recall();

	cout << "\n5️⃣  Cancel with nothing to cancel:\n";
	OperatorConsole empty;
	empty.cancelLast();

	cout << "\n6️⃣  Unlock a door that is not locked:\n";
	try { s.acs.unlockArea("Car Park"); }
	catch (const exception& e) { cout << "ℹ️  Access control refused: " << e.what() << "\n"; }
}

void everything(CampusGuard& guard, Incident*& open)
{
	autoMode = true;

	if (open == nullptr)
	{
		reportIncident(guard, open, "Library", Severity::HIGH);
		resolveIncident(guard, open);
		reportIncident(guard, open, "Parking Lot B", Severity::LOW);
		resolveIncident(guard, open);
	}
	else if (open != nullptr)
	{
		say ("An incident is still open! Resolve it first if you want to see the full Facade scenario here.");
	}
	demoCommand();
	demoMediator();
	demoAdapter();
	demoObserver();
	demoStrategy();
	demoFailures();

	autoMode = false;
}

void run()
{
	cout << "  ___                        ___  \n"
			" (o o)                      (o o) \n"
			"(  V  )  Campus Guard Demo (  V  )\n"
			"--m-m------------------------m-m--\n\n";

	name = ask("What is your name?\n");
	if (inputClosed) return;
	if (name.empty()) name = "Operator";

	CampusGuard guard;
	Incident* open = nullptr;

	if (name == "demo")
	{
		cout << "\n🎬 QUICK DEMO MODE 🎬\nRunning all demonstrations automatically...\n";
		everything(guard, open);
		return;
	}

	cout << "\n👋 Welcome, " << name << ". The campus is in your hands.\n";
	pressEnterToContinue();
	if (inputClosed) return;

	int choice;
	do
	{
		cout << "\n🏫 ═════ CAMPUSGUARD CONTROL ROOM ═════ 🏫\n"
				"1. 🚨 Report an incident   (Facade)\n"
				"2. ✅ Resolve the incident (Observer log)\n"
				"3. 🎮 Command\n"
				"4. 🕸️  Mediator\n"
				"5. 🔌 Adapter\n"
				"6. 👁️  Observer\n"
				"7. 🧭 Strategy\n"
				"8. 💥 Failure cases\n"
				"9. 🎬 Everything at once\n"
				"0. 🚪 Exit\n\n";
		choice = askChoice(name + " > ", 0, 9);
		if (inputClosed) break;

		switch (choice)
		{
			case 1: reportMenu(guard, open); pressEnterToContinue(); break;
			case 2: resolveIncident(guard, open); pressEnterToContinue(); break;
			case 3: demoCommand(); pressEnterToContinue(); break;
			case 4: demoMediator(); pressEnterToContinue(); break;
			case 5: demoAdapter(); pressEnterToContinue(); break;
			case 6: demoObserver(); pressEnterToContinue(); break;
			case 7: demoStrategy(); pressEnterToContinue(); break;
			case 8: demoFailures(); pressEnterToContinue(); break;
			case 9: everything(guard, open); pressEnterToContinue(); break;
			case 0: cout << "\nGoodbye, " << name << "! 👋\n"; break;
		}
	} while (choice != 0);
}

int main()
{
	run();
	if (inputClosed)
	{
		cout << "\n\n🏁 Input closed, shutting down cleanly. 🏁\n";
	}
	return 0;
}

#endif // CAMPUSGUARD_DEMO