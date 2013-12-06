#include "table.h"

Table::Table() {
    topo.clear();
    hopMap.clear();
    hopMapNeedsChanging = true;
}

Table::Table(const Table & rhs) {
    *this = rhs;
}

Table & Table::operator=(const Table & rhs) {
    /* For now,  Change if you add more data members to the class */
    topo = rhs.topo;

    return *this;
}

#if defined(GENERIC)
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
    map<int, map<int, TopoLink> >::const_iterator row = topo.begin();

    while (row != topo.end()) {
        map<int, TopoLink>::const_iterator col = (*row).second.begin();
        os << "Row=" << (*row).first;

        while (col != (*row).second.end()) {
            os << " Col=" << (*col).first << " dist=" << (*col).second.distance
<< " age=" << (*col).second.age << " cost=" << (*col).second.cost << endl;
            col++;
        }
        row++;
    }

    

  return os;
}

void Table::find(int *src, int *dest) {
    
    int maxCost = -1;
    map<int, map<int, TopoLink> >::const_iterator itr;

    for(itr = topo.begin(); itr != topo.end(); ++itr ) {
        map<int, TopoLink >::const_iterator itr2;
        for(itr2=(itr)->second.begin(); itr2 != (itr)->second.end(); ++itr2) {
            if(itr2->second.visited) {
                if(maxCost < 0) {
                    *src = itr->first;
                    *dest = itr2->first;
                    maxCost = itr2->second.distance;
                }
                else if(maxCost > itr2->second.distance) {
                    *src = itr->first;
                    *dest = itr2->first;
                    maxCost = itr2->second.distance;
                }
            }
        }
    }
}
#endif

#if defined(DISTANCEVECTOR)
ostream & Table::Print(ostream &os) const
{
  os << "DistanceVector Table()";
  return os;
}
#endif
