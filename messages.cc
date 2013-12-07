#include "messages.h"

RoutingMessage::RoutingMessage(const RoutingMessage &rhs) {
    *this = rhs;
}

RoutingMessage & RoutingMessage::operator=(const RoutingMessage & rhs) {
    /* For now.  Change if you add data members to the struct */
    return *this;
}

#if defined(GENERIC)
RoutingMessage::RoutingMessage()
{}
ostream &RoutingMessage::Print(ostream &os) const
{
    os << "Generic RoutingMessage()";
    return os;
}
#endif

#if defined(LINKSTATE)
RoutingMessage::RoutingMessage(int a, int src, int dest, int lat) {
    link_age = a;
    src_node = src;
    dest_node = dest;
    new_latency = lat;
}

ostream &RoutingMessage::Print(ostream &os) const
{
    os << "LinkState RoutingMessage()";
    /*
        ┌─┐ --─┐
        │▒│ /▒/
        │▒│/▒/
        │▒ /▒/─┬─┐
        │▒│▒|▒│▒│
        ┌┴─┴─┐-┘─┘
        │▒┌──┘▒▒▒│
        └┐▒▒▒▒▒▒┌┘
        └┐▒▒▒▒┌┘
    */
    return os;
}
#endif

#if defined(DISTANCEVECTOR)

RoutingMessage::RoutingMessage(int s, map <int, TopoLink> v) {
    sendingNode = s;
    vector = v;
}
ostream &RoutingMessage::Print(ostream &os) const
{
    os << "DistanceVector RoutingMessage()";
    return os;
}
#endif
