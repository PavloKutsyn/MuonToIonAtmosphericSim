#include "EventAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"

EventAction::EventAction()
: G4UserEventAction()
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{}

void EventAction::EndOfEventAction(const G4Event*)
{}


/*This EventAction class doesn't do much in its current form.
 *It's possible to fill the BeginOfEventAction and EndOfEventAction
 *methods with custom code that you want to run at the beginning and
 *end of each event, respectively. You can access the information
 *about the event through the provided G4Event object. For example,
 *you can access the generated particles, their properties,
 *and their trajectories.*/
