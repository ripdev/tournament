#include <QDebug>
#include <math.h>

#include "tournament.h"
#include "rrgroup.h"

/** Round robin games are followed first always
 */
RRGroup::RRGroup( QString name, PlayerList players )
 : Group( name, 0, players ) 
{
  roundRobin();
}

void RRGroup::roundRobin()
{
  _matches.clear();

  for ( int i = 0; i < _players.count(); i ++ ) {
    for ( int j = i + 1; j < _players.count(); j ++ ) {
      qDebug() << __FUNCTION__ << _players.at( i ).name() << _players.at( j ).name(); 
      _matches << Match( _players.at( i ), _players.at( j ) );
    }
  }
}

void RRGroup::addPlayer( Player player )
{
  // note that there are some matches can be completed
  // to the moment of addition of new player. 
  for ( int i = 0; i < _players.count(); i ++ ) {
    qDebug() << __FUNCTION__ << _players.at( i ).name() << player.name(); 
    _matches << Match( _players.at( i ), player );
  }
  
  Group::addPlayer( player );
}

/** returns required matches count to play for completion of group */
unsigned int RRGroup::matchesCount( unsigned int )
{
  // todo: formula?
  return 0; 
}

/** Serialization operators
  */
QDataStream &operator<<( QDataStream &s, const RRGroup &g )
{
  s << dynamic_cast< const Group& >( g );

  return s;
}

QDataStream &operator>>( QDataStream &s, RRGroup &g )
{
  s >> dynamic_cast< Group& >( g );
  
  return s;
}

/** print a group results into table in CSV format
 */
QString RRGroup::csvResult( QChar sep ) const
{
  QString ret;
  QTextStream out( &ret );

  out << name() << sep;
	for ( int i = 0; i < _players.count(); i ++ ) {
    out << QString::number( i + 1 ) << sep;
  }

  // TODO: translate
  out << "Place" << endl;

  // number of players = row count
  for ( int i = 0; i < _players.count(); i ++ ) { 
    Player a = _players.at( i );
		out << a.name() << sep;
		for ( int j = 0; j < _players.count(); j ++ ) {
		  if ( i == j ) {
        out << sep; 
			} else {
			  Player b = _players.at( j );
			  Match m = matchList( a, b ).at( 0 );
				if ( ! ( m.playerA() == a ) ) {
				  m.swapPlayers(); 
				}
			  out << m.toString() << sep; 
			}
		}

    out << QString::number( playerPlace( a ) ) << endl;  
  }

	return ret;
}

