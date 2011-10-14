#ifndef SWISSGROUP__H
#define SWISSGROUP__H

#include "group.h"

class SwissGroup : public Group
{
  unsigned int _fromPlace;

  void initGroupName();

  public:
    SwissGroup( unsigned int fromPlace,
                Tournament* tourn,
                unsigned int stage,
                PlayerList players );
    SwissGroup(); 
    
    friend QDataStream &operator<<( QDataStream &s, const SwissGroup &g );
    friend QDataStream &operator>>( QDataStream &s, SwissGroup &g );

    QList< Group* > split() const;
    unsigned int fromPlace() const { return _fromPlace; }

    bool isFinal() const 
         { return ( _players.count() == 2 ) && ( _fromPlace == 1 ); }
    bool isHalfFinal() const 
         { return ( _players.count() == 4 ) && ( _fromPlace == 1 ); }
    bool isQuarterFinal() const  
         { return ( _players.count() == 8 ) && ( _fromPlace == 1 ); }
};

#endif // SWISSGROUP__H

