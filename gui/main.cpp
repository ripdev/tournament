#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef __USE_GNU
#define __USE_GNU
#endif

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <cxxabi.h>

#if QT_VERSION >= 0x050000
#  include <QtWidgets/QApplication>
#else
#  include <QApplication>
#endif

#include <QProcess>
#include <QTranslator>
#include <QTextCodec>
#include <QDebug>
#include <QFile>

#include "playerlist.h"
#include "playertable.h"
#include "tournwidget.h"
#include "mainwindow.h"
#include "about.h"

int main(int argc, char *argv[])
{
  QApplication a( argc, argv );

  QLocale::setDefault( QLocale::C );

  LeagueMainWindow * w = new LeagueMainWindow();
  w->setWindowIcon( QIcon( ":/images/ball.png" ) );
  w->resize( 600, 600 );
  w->show();

  return a.exec();
}
