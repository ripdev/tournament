#ifndef TOURNAMENT__H
#define TOURNAMENT__H

#include <QObject>
#include "playerlist.h"
#include "rrgroup.h"
#include "tournprops.h"
#include "tournalgo.h"
#include "tourndata.h"

class SwissGroup;
class QFile;

#define TOURN_MAGIC_NUMBER 0xfaeb1640

class Tournament : public QObject {
  Q_OBJECT;

  public:
    Tournament( PlayerList players, QString category,
                unsigned int groupCnt = 4); 
    Tournament( TournProps props ); 
    Tournament(  );

    void groupChanged( Group* g );
 
    static Tournament* fromFile( QString fileName );
    bool save( QString fname );
    bool save( QFile* f );
    void saveAsCSV( QString fname );
    QString totalRatingAsCSV( QChar sep );

    void setFileName( QString fn ) { _fileName = fn; }
    QString fileName( ) const { return _fileName; }

    const TournAlgo * algo_const() const { return _algo; }
    const TournData * data_const() const { return _data; }
    TournAlgo * algo() const { return _algo; }
    TournData * data() const { return _data; }

    void update( );

  signals:
    void newSwissGroupCreated( SwissGroup* g );
    void tournamentChanged( Tournament* t );

  public slots:
    
  protected:
    unsigned int _magic;
    /**< Used for identification of validity of tournament object*/

    TournAlgo *_algo;
    TournData *_data;

    QString _fileName;
    /*<< file which corresponds to this tournament */

    bool isValid() const { return _magic == TOURN_MAGIC_NUMBER; }

    friend QDataStream &operator>>(QDataStream &, Tournament&);
    friend QDataStream &operator<<(QDataStream &, const Tournament&);
};

#endif // TOURNAMENT__H

