#ifndef CSCALE_H
#define CSCALE_H

#include <QWidget>
#include <QPoint>
#include <QFont>
#include <vector>


class CScale : public QWidget
{
    Q_OBJECT
public:
    explicit CScale(QWidget *parent = 0);
    ~CScale();

    void SetCord(const QString& cord);
    void SetNote(const QString& cord);
    void advance();
    void setQpm(int value){mQpm = value;};
    void generateNotes();
protected:
    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);


signals:

public slots:
    void showEvent ( QShowEvent * event );

private:

    int             nDrawNowRem;
    int             nDrawNow;
    int             nIotePos;
    int             mNoteOVer;
    QPoint          ptMouse;
    float           nCurPlayPos;
    int             nDownNote;
    std::vector<int>     mCompositoin;
    QFont           *pFont;
    int             mSecSpan;
    int             nInterval;
    int             nPerSecond;
    int             mQpm;
};

#endif // CSCALE_H
