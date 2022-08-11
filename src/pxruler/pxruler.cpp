// pxruler.cpp
//
// GUI Ruler
//
//   (C) Copyright 2022 Fred Gleason <fredg@paravelsystems.com>
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License version 2 as
//   published by the Free Software Foundation.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public
//   License along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#include <QApplication>
#include <QPainter>

#include "cmdswitch.h"
#include "pxruler.h"

MainWidget::MainWidget()
  : QMainWindow(NULL,Qt::CustomizeWindowHint|Qt::WindowTitleHint|Qt::WindowCloseButtonHint|Qt::WindowStaysOnTopHint)
{
  d_orientation=Qt::Horizontal;

  CmdSwitch *cmd=new CmdSwitch("pxruler",PXRULER_USAGE);
  for(unsigned i=0;i<cmd->keys();i++) {
    if(cmd->key(i)=="--direction") {
      if(cmd->value(i).toLower()=="horz") {
	d_orientation=Qt::Horizontal;
      }
      else {
	if(cmd->value(i).toLower()=="vert") {
	  d_orientation=Qt::Vertical;
	}
	else {
	  fprintf(stderr,"pxruler: invalid direction\n");
	  exit(1);
	}
      }
      cmd->setProcessed(i,true);
    }
    if(!cmd->processed(i)) {
      fprintf(stderr,"pxruler: unrecognized option \"%s\"\n",
	      cmd->key(i).toUtf8().constData());
      exit(1);
    }
  }
  setWindowTitle("pxRuler");

  if(d_orientation==Qt::Horizontal) {
    setMinimumWidth(200);
    setMinimumHeight(sizeHint().height());
    setMaximumHeight(sizeHint().height());
  }
  else {
    setMinimumHeight(200);
    setMinimumWidth(sizeHint().width());
    setMaximumWidth(sizeHint().width());
  }
}


QSize MainWidget::sizeHint() const
{
  if(d_orientation==Qt::Horizontal) {
    return QSize(400,135);
  }
  return QSize(160,400);
}


void MainWidget::paintEvent(QPaintEvent *e)
{
  int h=size().height();
  int w=size().width();
  QPainter *p=new QPainter(this);

  p->setPen(palette().color(QPalette::WindowText));
  p->setFont(QFont(font().family(),24,QFont::Normal));


  if(d_orientation==Qt::Vertical) {
    p->translate(160,0);
    p->rotate(90);
    h=size().width();
    w=size().height();
  }

  p->drawText((w-p->fontMetrics().width(tr("Pixel Ruler")))/2,50,
	      tr("Pixel Ruler"));
  p->setFont(font());
  for(int i=0;i<w;i+=10) {
    p->drawLine(i,h-10,i,h);
  }
  for(int i=0;i<w;i+=50) {
    p->drawLine(i,h-20,i,h);
  }
  for(int i=0;i<w;i+=100) {
    p->drawLine(i,h-30,i,h);
    p->drawText(i+5,h-25,QString::asprintf("%dpx",i));
  }

  delete p;
}


int main(int argc,char *argv[])
{
  QApplication a(argc,argv);
  MainWidget *w=new MainWidget();
  w->show();

  return a.exec();
}
