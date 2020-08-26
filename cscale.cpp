#include "dialog.h"
#include <string.h>
#include <stdio.h>
//#include <qwidget.h>
#include <QDialog>
#include <QThread>
#include <QPainter>
#include <QMouseEvent>
#include <QTransform>
#include "cscale.h"
#include "ui_dialog.h"
#include "gswiget.h"
#include <algorithm>
#include <set>


#define BORDER      40            // pixels
#define TIMESPAN    5             // seconds along the scale
#define TEMPO      4 // seconds along the scale


class SleeperThread : public QThread
{
    public:
    static void msleep(unsigned long msecs)
    {
    QThread::msleep(msecs);
    }
} St;

CScale::CScale(QWidget *parent) :
    QWidget(parent),mNoteOVer(-1),nCurPlayPos(BORDER),nDrawNow(-1),nDrawNowRem(-1)
{
    QPalette palette(CScale::palette());
    palette.setColor(backgroundRole(), Qt::black);
    setPalette(palette);
    QWidget::setMouseTracking(true);

}

void CScale::showEvent ( QShowEvent * event )
{
    mSecSpan  = (rect().right()-BORDER-rect().left()) / TIMESPAN;
    const int   height   = rect().bottom() - rect().top();
    nInterval = (height-BORDER) / MAX_NOTES;
    nPerSecond = (mSecSpan) / TEMPO;
    pFont = new QFont("System", nInterval);


}

CScale::~CScale()
{
    delete pFont;
}


void CScale::paintEvent(QPaintEvent *)
{
    QPainter        painter(this);
    const QPen      b(Qt::black);
    QPen      g(QColor(210,210,210));
    const int   height   = rect().bottom() - rect().top();

    painter.setFont(*pFont);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::white);


    painter.setPen(g);

    Note* pN = Notes;
    int ym = 10000, yM = 0;

    std::set<int>    horizlines;
    painter.setPen(b);

    for (int i = 0; 0!=pN->gamma; i++, pN++)
    {
        int ypos = height - (nInterval * i) - BORDER;

        if(pN->flag==2){
            ym = std::min(ym, ypos);
            yM = std::max(yM, ypos);
    //        painter.setPen(b);
        }
        else if(pN->flag==1){
            horizlines.insert(i); //painter.setPen(g);
        }

        if(pN->flag==2){
            painter.drawLine(BORDER, ypos, rect().right(), ypos);
        }
        painter.drawText(0, ypos + (nInterval/2), QString(pN->note) );
    }

    painter.setPen(g);
    for(int s = 0; s < TIMESPAN; s++)
    {
        painter.drawLine(BORDER + (s * mSecSpan), ym ,
                         BORDER + (s * mSecSpan), yM);
    }


    if(mNoteOVer>=0){

        int tl = height - (nInterval * mNoteOVer) - BORDER;
        painter.setPen(b);
        painter.setBrush(Qt::black);
        painter.drawEllipse(ptMouse.x(), tl - (nInterval-2), (nInterval*2),( nInterval-2)*2);
    }

    std::vector<int>::iterator bi = mCompositoin.begin();
    for(;bi!=mCompositoin.end();bi++)
    {
        int& i = *bi;

        int ypos = height - (nInterval * i) - BORDER;
        int xpos = BORDER + (bi-mCompositoin.begin()) * nPerSecond;

        painter.setBrush(Qt::red);
        painter.drawEllipse(xpos, ypos - (nInterval-2), (nInterval*2),( nInterval-2)*2);


        if(horizlines.find(i) != horizlines.end()){
           painter.setPen(b);
           painter.drawLine(xpos-nInterval/2, ypos , xpos+nInterval*2+nInterval/2, ypos);
       }
       if(i < 9)
       {
           for(int l=i; l <= 9;l++)
           {
               if(Notes[l].flag)
               {
                    ypos = height - (nInterval * l) - BORDER;
                    painter.drawLine(xpos-nInterval/2, ypos , xpos+nInterval*2+nInterval/2, ypos);
               }
           }
       }
       if(i > 17)
       {
           for(int l=17; l <= i; l++)
           {
               if(Notes[l].flag)
               {
                    ypos = height - (nInterval * l) - BORDER;
                    painter.drawLine(xpos-nInterval/2, ypos , xpos+nInterval*2+nInterval/2, ypos);
               }
           }
       }

    }

    g.setColor(QColor(210,0,0));
    painter.setPen(g);
    painter.drawLine(nCurPlayPos, 0, nCurPlayPos, rect().bottom());

    if(nDrawNowRem>=0)
        painter.drawText(nCurPlayPos+2, 15, QString(Notes[nDrawNowRem].note));

}

void CScale::mouseMoveEvent(QMouseEvent *pme)
{
    const int   height   = rect().bottom() - rect().top();
    const int   nInterval = (height-BORDER) / MAX_NOTES;//COUNT_OF(Notes);
    Dialog * pui = ((Dialog*)parent());

    Note* pN = Notes;
    mNoteOVer=-1;

   // pui->onOverNote(this, 0);
    for (int i = 0; 0!=pN->gamma; i++, pN++)
    {
        int ypos = height - (nInterval * i) - BORDER;

        QRect proxim(0, ypos-nInterval/2, rect().right(), nInterval);
        if(proxim.contains(pme->x(), pme->y()))
        {
            if(mNoteOVer != i){

                pui->onOverNote(this, pN);

                mNoteOVer = i;
                ptMouse.setX(pme->x());
                ptMouse.setY(pme->y());
                break;
            }

        }
    }
    this->repaint();
}

void CScale::mouseDoubleClickEvent(QMouseEvent *pme)
{
}

void CScale::mouseReleaseEvent(QMouseEvent *pme)
{
    if(nDownNote == mNoteOVer)
    {
        mCompositoin.push_back(nDownNote);
    }
}

void CScale::mousePressEvent(QMouseEvent *)
{
    nDownNote = mNoteOVer;
}

void CScale::advance() // 20 times / second
{
    Dialog * pui = ((Dialog*)parent());
    // mQpm are notes / minute
    float nPerSec = (float)mQpm / 60.0f;
    // on sec has mSecSpan pixels

    //nInterval pixels has to be gpassed on nPerSec
    float pixperTimer = ((float)mSecSpan / 20.0f) * nPerSec;

    nCurPlayPos += pixperTimer ;

    static int lastPos = -1;

    int notePos = ((int)nCurPlayPos - BORDER) / nPerSecond;

    if((notePos < mCompositoin.size() && lastPos != notePos) && nDrawNow==-1)
    {
        lastPos = notePos;
        nDrawNow = mCompositoin[notePos];
        pui->onOverNote(this, 0);
        nDrawNowRem = -1;
    }
    else
    {
        if(nDrawNow >= 0)
        {
           pui->onOverNote(this, &Notes[nDrawNow]);
           nDrawNowRem = nDrawNow;
           double frq =  Notes[nDrawNow].freq;
           pui->Beep(frq);
           nDrawNow=-1;
        }
    }


    if(nCurPlayPos > rect().right())
    {
        generateNotes();
        nCurPlayPos = BORDER;
        repaint();
        St.msleep(1500);

    }
    repaint();
}


void CScale::generateNotes()
{
    Dialog * pui = ((Dialog*)parent());

    mCompositoin.clear();


    int enabledcords = 0;
    pui->ui->CK1->isChecked() ? enabledcords |= 0x1  :0;// E + 12
    pui->ui->CK2->isChecked() ? enabledcords |= 0x2  :0;// A + 12
    pui->ui->CK3->isChecked() ? enabledcords |= 0x4  :0;// D + 12
    pui->ui->CK4->isChecked() ? enabledcords |= 0x8  :0;// G + 12
    pui->ui->CK5->isChecked() ? enabledcords |= 0x10 :0;// B + 12
    pui->ui->CK6->isChecked() ? enabledcords |= 0x20 :0;// E + 12

    int notesOnce = TIMESPAN * TEMPO;

    while(mCompositoin.size() < notesOnce && enabledcords)
    {
        for(;;)
        {
            int i = rand() % 6;
            if(enabledcords & (0x1 << i))
            {
                // get arandom note from this to this + 11 semitons
                //int crdIndexrE = CORDS_INDEXS[i] + (rand() % ( 18 - (i * 3)));
                int s = 0;
                int cordStart = CORDS_INDEXS[i];
                int semitones = 0;// Notes[cordStart].semitons;

                do{
                    semitones += Notes[s++].semitons;

                }while(Notes[s].cord == 0);
                semitones-=1;

                int crdIndexrE = cordStart + (rand() % semitones);
                mCompositoin.push_back(crdIndexrE);
                break;
            }
        }
    }
    repaint();

}

