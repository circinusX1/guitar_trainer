#ifndef FREET_H
#define FREET_H

#include <QWidget>
struct Note;
class Freet : public QWidget
{
    Q_OBJECT
public:
    explicit Freet(QWidget *parent = 0);
    void setNote(Note* pN);
protected:
    void paintEvent(QPaintEvent *);
    void drawFrets(QPainter& painter);
    void drawNote(QPainter& painter, int, int);


signals:

public slots:

private:
    int FindNote(int cord)const;
    Note* pNote;

};

#endif // FREET_H
