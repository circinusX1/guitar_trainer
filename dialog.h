#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <QIODevice>
#include <QTimer>
#include <QByteArray>
#include <math.h>
#include <QAudioOutput>
#include <QIODevice>
#include <QScopedPointer>



//#include <QtGui/QApplication>
class QApplication;



struct Note;
namespace Ui {
    class Dialog;
}


class Generator : public QIODevice
{
    Q_OBJECT

public:
    Generator(const QAudioFormat &format, qint64 durationUs, int sampleRate);

    void start();
    void stop();

    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;
    qint64 bytesAvailable() const override;

private:
    void generateData(const QAudioFormat &format, qint64 durationUs, int sampleRate);

private:
    qint64 m_pos = 0;
    QByteArray m_buffer;
};

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void onOverNote(const QWidget* src, Note* pN );
    void setApp(QApplication* p){pApp=p;}
    void Beep(double freq);
    Ui::Dialog  *ui;
protected: //events
    void timerEvent(QTimerEvent *event);

public slots:
    void showEvent ( QShowEvent * event );

private:
    void        _init_audio();
    int         nTimerId;


protected slots:



private slots:

    void on_tempoSlide_valueChanged(int value);
    void on_pushButton_clicked();


private:

    QApplication* pApp;
    QScopedPointer<Generator> m_generator;
    QScopedPointer<QAudioOutput> m_audioOutput;
    QAudioFormat _format;
    QAudioDeviceInfo _deviceInfo;
};

#endif // DIALOG_H
