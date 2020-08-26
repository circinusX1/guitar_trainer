#include <stdio.h>
#include "dialog.h"
#include <QPainter>
#include <QDialog>
#include "freet.h"
#include "gswiget.h"
#include "ui_dialog.h"

#define FRETS       20
#define CORDS       6
#define BORDER      20
#define SCORDS      "EBGDAE"

Freet::Freet(QWidget *parent) : QWidget(parent), pNote(0)
{
    QPalette palette(Freet::palette());
    palette.setColor(backgroundRole(), Qt::black);
    setPalette(palette);
}


void Freet::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), Qt::black);

    drawFrets(painter);

}


void Freet::drawFrets(QPainter& painter)
{
    QPen pen(QBrush(QColor(255,255,255)), 1.0f);
    int dots[] = {2,4,6,8,11,14,16,18,0};
    int d = 0;
    int fretStep = ( rect().right() - rect().left()-(BORDER<<1)) / FRETS;
    int stringStep =  ( rect().bottom() - rect().top() - (BORDER<<1) ) / (CORDS-1);
    int mid = ( rect().bottom() - rect().top() ) / 2;
    int delta = ( rect().bottom() - rect().top() ) / 4;
    int bot = rect().bottom();

    painter.setPen(pen);
    for(int i = 0; i < FRETS; i++)
    {
        float xf = i * fretStep + (BORDER * 2);
        painter.drawLine(xf, BORDER, xf, rect().bottom()-BORDER);
        if(i==dots[d]){
            if(i<11){
                pen.setColor(QColor(128,0,0));
                painter.setBrush(QBrush(Qt::darkRed));
            }else{
                pen.setColor(QColor(200,0,0));
                painter.setBrush(QBrush(Qt::darkRed));
            }
            xf += (fretStep / 4);
            if(i==11)
            {
                painter.drawEllipse(xf, (mid-(stringStep-8)/2)-delta, stringStep-8 , stringStep-8 );
                painter.drawEllipse(xf, (mid-(stringStep-8)/2)+delta, stringStep-8 , stringStep-8 );
                //fretStep-=(fretStep/6);
            }
            else {
                painter.drawEllipse(xf, mid-(stringStep-8)/2, stringStep-8 , stringStep-8 );
            }

            d++;
            pen.setColor(QColor(255,255,255));
            painter.setPen(pen);
            painter.drawText((xf-fretStep/2)+16, rect().bottom()-5 ,QString::number(i+1));

        }
    }

    pen.setBrush(QBrush(QColor(255,255,0)));
    painter.setPen(pen);
    Note* pN = Notes;
    char nl[32];
    for(int k = 0; pN->gamma; pN++)
    {

        if(pN->cord>0){
            pen.setWidth((float)(CORDS-k) / 1.7f);
            painter.setPen(pen);
            int yc = bot - (BORDER + (k * stringStep ));

            painter.drawLine(BORDER*2,  yc , rect().right()-BORDER, yc);

            painter.drawText(BORDER-2, yc ,QString(pN->note));
            sprintf(nl,"%d",pN->index);
            painter.drawText(BORDER-15, yc, QString(nl));
            ++k;
        }
    }

    drawNote(painter, stringStep, fretStep );
}

void Freet::setNote(Note* pN)
{
    pNote = pN;
    this->repaint();
}

int Freet::FindNote(int cord)const
{
    Note* pN = Notes;
    for(; pN->gamma;pN++)
    {
        if(pN->cord == cord){
            return pN->index;
        }
    }
    return -1;
}


void Freet::drawNote(QPainter& painter, int stringStep, int fretStep)
{
    if(pNote==0)     return;
    int bot = rect().bottom();

    Dialog * pui = ((Dialog*)parent());

    int enabledcords = 0;
    pui->ui->CK1->isChecked() ? enabledcords |= 0x1  :0;// E + 12
    pui->ui->CK2->isChecked() ? enabledcords |= 0x2  :0;// A + 12
    pui->ui->CK3->isChecked() ? enabledcords |= 0x4  :0;// D + 12
    pui->ui->CK4->isChecked() ? enabledcords |= 0x8  :0;// G + 12
    pui->ui->CK5->isChecked() ? enabledcords |= 0x10 :0;// B + 12
    pui->ui->CK6->isChecked() ? enabledcords |= 0x20 :0;// E + 12

    bool found = false;
    for(int i=0; i < CORDS ;i++) //low to high
    {
//        if((enabledcords & (0x1 << i)) == 0)
  //          painter.setBrush(QColor(Qt::darkGray));
    //    else


        //
        // find note for this cord
        //
        int index = FindNote(i+1);            // note for this cord
        //int tones = pNote->index - index;   // curent pressed note index, down the cord

        if(pNote->index==-1 || pNote->index < index)
            continue;


        int downthecord = 0;
        for(int ddc = index; ddc < pNote->index; ddc++)
        {
            downthecord += Notes[ddc].semitons;
        }
        if(found){
            if((enabledcords & (0x1 << i)) == 0)
               painter.setBrush(QColor(Qt::darkGray));
            else
                painter.setBrush(QColor(Qt::green));
        }else{
            if((enabledcords & (0x1 << i)) == 0)
               painter.setBrush(QColor(Qt::darkGray));
            else
                painter.setBrush(QColor(Qt::darkGreen));
        }

        //downthecord &= 7;
        int yc = bot - (BORDER + (i * stringStep));
        int xc = (BORDER*2) + ((downthecord * fretStep) - fretStep/2) + fretStep/3;

        painter.drawEllipse(xc-10, yc-10, 21,21);
        painter.drawText(xc-3, yc+6, QString(pNote->note));
        found = true;
    }
}



