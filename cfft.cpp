#include <QPainter>
#include "cfft.h"

CFft::CFft(QWidget *parent) :
    QWidget(parent)
{
    QPalette palette(CFft::palette());
    palette.setColor(backgroundRole(), Qt::black);
    setPalette(palette);

}



void CFft::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor b(0,0,128);
    painter.setBrush(b);
    painter.fillRect(rect(), Qt::SolidPattern);


}
