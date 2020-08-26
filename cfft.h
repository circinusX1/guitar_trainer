#ifndef CFFT_H
#define CFFT_H

#include <QWidget>

class CFft : public QWidget
{
    Q_OBJECT
public:
    explicit CFft(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);


signals:

public slots:

};

#endif // CFFT_H
