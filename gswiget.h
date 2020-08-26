#ifndef GSWIGET_H
#define GSWIGET_H

#include <QWidget>

class GSWiget : public QWidget
{
    Q_OBJECT
public:
    explicit GSWiget(QWidget *parent = 0);





signals:

public slots:

};


struct Note
{
    char  enote[4];
    char  note[4];
    double freq;
    bool  diez;
    bool  bemol;
    int   flag;
    int   cord;
    int   index;
    int   semitone;
    int   semitons;
    int   gamma;
};

#define MAX_NOTES     23
#define BASE_INDEX_A4 23
extern Note Notes[MAX_NOTES];

#define COUNT_OF(x_)  (sizeof(x_)/sizeof(x_[0]))
extern int CORDS_INDEXS[];

#endif // GSWIGET_H
