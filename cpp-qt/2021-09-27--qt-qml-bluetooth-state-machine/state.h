#ifndef STATE_H
#define STATE_H

#include <QObject>
#include <QString>

//enum class State {
//    Initial = 0,
//    Discovering,
//    Discovered,
//};

namespace State {
Q_NAMESPACE
enum StateType { Initial = 0, Discovery, Connecting, Connected };
Q_ENUM_NS(StateType)
} // namespace State

inline QString stateToString(State::StateType state)
{
    using namespace State;
    switch (state) {
    case Initial:
        return "Initial";
    case Discovery:
        return "Discovery";
    case Connecting:
        return "Connecting";
    case Connected:
        return "Connected";
        //    case State:::
        //        return "";
        //    case State:::
        //        return "";
        //    case State:::
        //        return "";
        //    case State:::
        //        return "";
        //    case State:::
        //        return "";
        //    case State:::
        //        return "";
        //    case State:::
        //        return "";
    default:
        return "unknown";
    }
}

#endif // STATE_H
