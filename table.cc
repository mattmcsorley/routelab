#include "table.h"



Table::Table(const Table & rhs) {
    *this = rhs;
}

Table & Table::operator=(const Table & rhs) {
    /* For now,  Change if you add more data members to the class */
    topo = rhs.topo;

    return *this;
}

#if defined(GENERIC)

Table::Table() {
    topo.clear();
}
ostream & Table::Print(ostream &os) const
{
  os << "Generic Table()";
  return os;
}
#endif

#if defined(LINKSTATE)
ostream & Table::Print(ostream &os) const
{
  os << "LinkState Table()";
  /*
        Here is where we will print out the final table i.e. topo ^('')^ <<('') 
  */

  
  return os;
}

Table::Table() {
    topo.clear();
    hopMap.clear();
    hopMapNeedsChanging = true;

}
#endif

#if defined(DISTANCEVECTOR)
ostream & Table::Print(ostream &os) const
{
  os << "DistanceVector Table()";
  return os;
}

Table::Table() {
    topo.clear();
    distanceVector.clear();
    neighborLinks.clear();
    hopMap.clear();
}
#endif
