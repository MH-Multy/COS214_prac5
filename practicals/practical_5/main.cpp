/*
Emmanuel Boateng (23586975)
Mohammadhossein Jafari (25312040)
Jay Macaskill (25198387)

COS 214 (Software Modelling) Practical 5
Last Modified: 27 September 2026

main.cpp (Static tests)
*/

// ===== MEDIATOR ====== //
#include "ResponseUnit.h"
#include "IncidentCoordinator.h"

// ===== FACADE ===== //
#include "CampusGuard.h"

void print_test(bool test, string success, string fail)
{
    if (test) cout << success << "\n";
    else cout << fail << "\n";
}

void test_mediator()
{
    cout << "👤 [STARTING MEDIATOR TESTS] 👤\n";

    SecurityTeam security("Security", nullptr);
    MedicalTeam medical("Medical", nullptr);
    FacilitiesTeam facilities("Facilities", nullptr);

    IncidentResponseDesk coordinator(&security, &medical, &facilities);

    security.setCoordinator(&coordinator);
    medical.setCoordinator(&coordinator);
    facilities.setCoordinator(&coordinator);

    cout << "\n[TESTING DISPATCH]\n";

    security.dispatch();
    print_test(security.isDispatched(), "✅ Dispatch successful", "⚠️ Dispatch failed");
    print_test(!security.isPerimeterSecured(), "✅ Perimeter remains unsecured", "⚠️ Perimeter inexplainably secured");

    security.dispatch(); // double dispatch
    print_test(security.isDispatched(), "✅ Security still dispatched, double-dispatch survived", "⚠️ Double dispatch does not work");

    cout << "\n[TESTING RECALL]\n";
    security.recall();
    print_test(!security.isDispatched(), "✅ Recall successful", "⚠️ Recall did not reset flags");
    print_test(!security.isPerimeterSecured(), "✅ Perimeter remains unsecured", "⚠️ Perimeter inexplainably secured");

    security.recall(); // double recall
    print_test(!security.isDispatched(), "✅ Security still recalled, double-recall survived", "⚠️ Double recall does not work");

// mediator chain must secure perimeter when medical is dispatched

    cout << "\n[TESTING MEDIATOR CHAIN: MEDICAL_DISPATCHED → SECURITY]\n";

    security.dispatch();
    print_test(security.isDispatched(), "✅ Security dispatched", "⚠️ Security not dispatched");
    print_test(!security.isPerimeterSecured(), "✅ Perimeter unsecured before medical dispatch", "⚠️ Perimeter inexplainably secured");

    medical.dispatch();
    print_test(medical.isDispatched(), "✅ Medical dispatched", "⚠️ Medical not dispatched");
    print_test(security.isPerimeterSecured(), "✅ Security secures perimeter now that medical is dispatched", "⚠️ Mediator did not route MEDICAL_DISPATCHED to security");

// medical must treat after the area has been secured

    cout << "\n[TESTING MEDIATOR CHAIN: AREA_SECURED → MEDICAL]\n";

    print_test(!medical.isTreating(), "✅ Medical not yet treating", "⚠️ Medical inexplicably treating");

    coordinator.coordinate(&medical, Events::AREA_SECURED);

    print_test(medical.isTreating(), "✅ Medical begins treating after AREA_SECURED", "⚠️ Mediator did not route AREA_SECURED to medical");

// emergency exits must be opened after alert delivered to evacuate

    cout << "\n[TESTING MEDIATOR CHAIN: ALERT_DELIVERED_EVACUATE → FACILITIES]\n";

    print_test(!facilities.isDispatched(), "✅ Facilities not yet dispatched", "⚠️ Facilities inexplicably dispatched");
    print_test(!facilities.areExitsOpened(), "✅ Exits not yet opened", "⚠️ Exits inexplicably open");

    facilities.dispatch();
    print_test(facilities.isDispatched(), "✅ Facilities dispatched", "⚠️ Facilities not dispatched");

    coordinator.coordinate(&facilities, Events::ALERT_DELIVERED_EVACUATE);

    print_test(facilities.areExitsOpened(), "✅ Facilities opens exits after ALERT_DELIVERED_EVACUATE", "⚠️ Mediator did not route ALERT_DELIVERED_EVACUATE to facilities");

// unknown event is ignored

    cout << "\n[TESTING UNKNOWN EVENT]\n";

    bool securityBefore = security.isPerimeterSecured();
    bool medicalBefore = medical.isTreating();
    bool facilitiesBefore = facilities.areExitsOpened();

    string unknownEvent = "SOME_UNKNOWN_EVENT";
    coordinator.coordinate(nullptr, unknownEvent);

    print_test(security.isPerimeterSecured() == securityBefore, "✅ Security state unchanged by unknown event", "⚠️ Security state changed by unknown event");
    print_test(medical.isTreating() == medicalBefore, "✅ Medical state unchanged by unknown event", "⚠️ Medical state changed by unknown event");
    print_test(facilities.areExitsOpened() == facilitiesBefore, "✅ Facilities state unchanged by unknown event", "⚠️ Facilities state changed by unknown event");

// recall must reset secondary flags

    cout << "\n[TESTING RECALL RESETS SECONDARY STATE]\n";

    // security is currently dispatched and perimeterSecured = true
    print_test(security.isDispatched(), "✅ Security currently dispatched", "⚠️ Security not dispatched before recall test");
    print_test(security.isPerimeterSecured(), "✅ Perimeter currently secured", "⚠️ Perimeter not secured before recall test");

    security.recall();

    print_test(!security.isDispatched(), "✅ Security recalled", "⚠️ Recall did not clear dispatched");
    print_test(!security.isPerimeterSecured(), "✅ Perimeter reset to unsecured by recall", "⚠️ Recall did not reset perimeterSecured");

    // medical currently dispatched and treating = true
    print_test(medical.isDispatched(), "✅ Medical currently dispatched", "⚠️ Medical not dispatched before recall test");
    print_test(medical.isTreating(), "✅ Medical currently treating", "⚠️ Medical not treating before recall test");

    medical.recall();

    print_test(!medical.isDispatched(), "✅ Medical recalled", "⚠️ Recall did not clear dispatched");
    print_test(!medical.isTreating(), "✅ Treating reset to false by recall", "⚠️ Recall did not reset treating");

    // facilities currently dispatched and exitsOpened = true
    print_test(facilities.isDispatched(), "✅ Facilities currently dispatched", "⚠️ Facilities not dispatched before recall test");
    print_test(facilities.areExitsOpened(), "✅ Exits currently open", "⚠️ Exits not open before recall test");

    facilities.recall();

    print_test(!facilities.isDispatched(), "✅ Facilities recalled", "⚠️ Recall did not clear dispatched");
    print_test(!facilities.areExitsOpened(), "✅ Exits reset to closed by recall", "⚠️ Recall did not reset exitsOpened");

    cout << "\n👤 [MEDIATOR TESTS COMPLETE] 👤\n";
}

void test_facade()
{
    cout << "\n✨ [STARTING FACADE TESTS] ✨\n";
    CampusGuard guard;
    cout << "\n[TEST HIGH SEVERITY]\n";
    Incident& high_severity = guard.reportIncident("Library", Severity::HIGH);
    guard.resolveIncident(high_severity);

    cout << "\n[TEST LOW SEVERITY]\n";
    Incident& low_severity = guard.reportIncident("Parking Lot", Severity::LOW);
    guard.resolveIncident(low_severity);

    cout << "\n";
    guard.printLog();

    cout << "\n✨ [FACADE TESTS COMPLETE] ✨\n";
}

void test_adapter()
{

}

void test_strategy()
{

}

void test_observer()
{

}

void test_command()
{

}

void command_mediator_chain()
{
    cout << "\n🎬 [TESTING COMMAND-MEDIATOR CHAIN] 🎬\n";

    SecurityTeam security("Security", nullptr);
    MedicalTeam medical("Medical", nullptr);
    FacilitiesTeam facilities("Facilities", nullptr);
    IncidentResponseDesk coordinator(&security, &medical, &facilities);

    security.setCoordinator(&coordinator);
    medical.setCoordinator(&coordinator);
    facilities.setCoordinator(&coordinator);

    OperatorConsole console;

    console.issueCommand(unique_ptr<DispatchUnit>(new DispatchUnit(&security)));
    console.issueCommand(unique_ptr<DispatchUnit>(new DispatchUnit(&medical)));

    cout << "\n🎬 [COMMAND-MEDIATOR CHAIN TESTING COMPLETE] 🎬\n";
}

void adapter_chain()
{
    cout << "\n🎬 [TESTING ADAPTER CHAIN] 🎬\n";

    LegacyAlertSystem legacy;
    LegacyAlertAdapter adapter(&legacy);
    OperatorConsole console;

    console.issueCommand(unique_ptr<SendAlert>(
    new SendAlert(&adapter, nullptr, AlertType::EVACUATE)));

    cout << "\n🎬 [ADAPTER CHAIN TESTING COMPLETE] 🎬\n";
}

void observer_state()
{
    cout << "\n🎬 [TESTING OBSERVER STATE TRANSITIONS] 🎬\n";

    Incident incident(99, "Demo Area", Severity::HIGH);
    AccessControlSystem acs;
    AccessControlObserver accessObserver(&acs);
    IncidentLogObserver logObserver;

    incident.attach(&accessObserver);
    incident.attach(&logObserver);

    incident.setStatus(Status::ACTIVE);

    incident.setStatus(Status::RESOLVED);
}

void test()
{
    cout << "🧪 CONDUCTING STATIC TESTS OF ALL DESIGN PATTERNS 🧪\n";
    test_mediator();
    test_facade();
    test_strategy();
    test_adapter();
    test_observer();
    test_command();
    command_mediator_chain();
    adapter_chain();
    observer_state();
    cout << "✅ TESTS COMPLETE ✅\n";
}

int main()
{
    test();
    return 0;
}