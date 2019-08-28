#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

namespace msm = boost::msm;         //meta state machine
namespace mpl = boost::mpl;         //meta programming library
using namespace msm::front;

vector<string> state_names {
    "off hook"s,
    "connecting"s,
    "connected"s,
    "on hold"s,
    "destroyed"s
};

// Triggers
struct CallDialed {};
struct Hangup {};
struct CallConnected {};
struct PlacedOnHold {};
struct TakenOffHold {};
struct LeftMessage {};
struct PhoneThrownIntoWall {};

struct PhoneStateMachine : state_machine_def<PhoneStateMachine>
{
    bool angry{true};

    struct OffHook : state<> {};
    struct Connecting : state<>
    {   
        template <class Event, class FSM>
        void on_entry(const Event& event, FSM& fsm)
        {
            cout << "We are connecting...\n";
        }
    };

    struct Connected : state<>
    {   
        template <class Event, class FSM>
        void on_entry(const Event& event, FSM& fsm)
        {
            cout << "We are connected...\n";
        }
    };

    struct OnHold : state<>
    {   
        template <class Event, class FSM>
        void on_entry(const Event& event, FSM& fsm)
        {
            cout << "We are on hold...\n";
        }
    };

    struct PhoneDestroyed : state<>
    {   
        template <class Event, class FSM>
        void on_entry(const Event& event, FSM& fsm)
        {
            cout << "We are destroyed...\n";
        }
    };

    struct PhoneBeingDestroyed              //Transition
    {
        template <class EVT, class FSM, class SourceState, class TargetState>
        void operator()(EVT const&, FSM&, SourceState&, TargetState&)
        {
            cout << "Phone breaks into a million pieces" << '\n';
        }
    };

    struct CanDestroyPhone                  //Guard condition
    {
        template <class EVT, class FSM, class SourceState, class TargetState>
        bool operator()(EVT const&, FSM& fsm, SourceState&, TargetState&)
        {
            return fsm.angry;
        }
    };

    struct transition_table : mpl::vector <
        Row<OffHook, CallDialed, Connecting>,
        Row<Connecting, CallConnected, Connected>,
        Row<Connected, PlacedOnHold, OnHold>,
        Row<OnHold, PhoneThrownIntoWall, PhoneDestroyed, PhoneBeingDestroyed, CanDestroyPhone>
    >{};

    typedef OffHook initial_state;

    template <class FSM, class Event>
    void no_transition(Event const& e, FSM&, int state)
    {
        cout << "No transition from state " << state_names[state]
             << " on event " << typeid(e).name() << '\n';
    }
};

int main(int argc, char* argv[])
{

    msm::back::state_machine<PhoneStateMachine> phone;

    auto info = [&](){
        auto i = phone.current_state()[0];
        cout << "The phone is currently " << state_names[i] << '\n';
    };

    info();
    phone.process_event(CallDialed{});
    info();
    phone.process_event(CallConnected{});
    info();
    phone.process_event(PlacedOnHold{});
    info();
    phone.process_event(PhoneThrownIntoWall{});
    info();

    // No more transitions, if we try to process an event we get a call to no_transition
    phone.process_event(CallDialed{});

    return 0;
}