/*
* This file is part of OctoXBPS, an open-source GUI for XBPS.
* Copyright (C) 2013 Alexandre Albuquerque Arnt
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*/

#include "../src/unixcommand.h"
#include "../src/wmhelper.h"
#include "../src/strconstants.h"
#include "../src/argumentlist.h"
#include "mainwindow.h"

#include <QApplication>
#include <QtGui>
#include <QDebug>

int main(int argc, char *argv[])
{  
  bool debugInfo = false;
  ArgumentList *argList = new ArgumentList(argc, argv);

  if (argList->getSwitch("-d"))
  {
    //If user chooses to switch debug info on...
    debugInfo = true;
  }

  if (debugInfo)
  {
    qDebug() << QString("OctoXBPS Notifier - " + StrConstants::getApplicationVersion() +
                  " (" + StrConstants::getQtVersion() + ")");
  }
  if (UnixCommand::isAppRunning("octoxbps-notifier"))
  {
    qDebug() << "Aborting notifier as another instance is already running!";
    return (-1);
  }

  if (!QFile::exists(ctn_PKEXEC_BINARY))
  {
    qDebug() << "Aborting notifier as 'pkexec' binary could not be found! [" << ctn_PKEXEC_BINARY << "]";
    return (-2);
  }

  QApplication a(argc, argv);

  /*QTranslator appTranslator;
  appTranslator.load(":/resources/translations/octoxbps_" +
                     QLocale::system().name());

  a.installTranslator(&appTranslator);*/
  a.setQuitOnLastWindowClosed(false);
  setenv("TERM", "xterm-256color", 1);
  MainWindow w;
  QResource::registerResource("./resources.qrc");

  if (debugInfo)
    w.turnDebugInfoOn();

  return a.exec();
}
