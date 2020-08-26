#include <math.h>
#include <stdio.h>
#include <qmath.h>
#include <qendian.h>
#include <QDebug>
#include "dialog.h"
#include "ui_dialog.h"
#include "gswiget.h"



Generator::Generator(const QAudioFormat &format
    , qint64 durationUs
    , int sampleRate)
{
    if (format.isValid())
    {
        generateData(format, durationUs, sampleRate);
    }
}

void Generator::start()
{
    open(QIODevice::ReadOnly);
}

void Generator::stop()
{
    m_pos = 0;
    close();
}

void Generator::generateData(const QAudioFormat &format, qint64 durationUs, int sampleRate)
{
    const int channelBytes = format.sampleSize() / 8;
    const int sampleBytes = format.channelCount() * channelBytes;
    qint64 length = (format.sampleRate() * format.channelCount() * (format.sampleSize() / 8))
                        * durationUs / 1000000;
    Q_ASSERT(length % sampleBytes == 0);
    Q_UNUSED(sampleBytes) // suppress warning in release builds

    m_buffer.resize(length);
    unsigned char *ptr = reinterpret_cast<unsigned char *>(m_buffer.data());
    int sampleIndex = 0;

    while (length) {
        // Produces value (-1..1)
        const qreal x = sinf(2 * M_PI * sampleRate * qreal(sampleIndex++ % format.sampleRate()) / format.sampleRate());
        for (int i=0; i<format.channelCount(); ++i) {
            if (format.sampleSize() == 8) {
                if (format.sampleType() == QAudioFormat::UnSignedInt) {
                    const quint8 value = static_cast<quint8>((1.0 + x) / 2 * 255);
                    *reinterpret_cast<quint8 *>(ptr) = value;
                } else if (format.sampleType() == QAudioFormat::SignedInt) {
                    const qint8 value = static_cast<qint8>(x * 127);
                    *reinterpret_cast<qint8 *>(ptr) = value;
                }
            } else if (format.sampleSize() == 16) {
                if (format.sampleType() == QAudioFormat::UnSignedInt) {
                    quint16 value = static_cast<quint16>((1.0 + x) / 2 * 65535);
                    if (format.byteOrder() == QAudioFormat::LittleEndian)
                        qToLittleEndian<quint16>(value, ptr);
                    else
                        qToBigEndian<quint16>(value, ptr);
                } else if (format.sampleType() == QAudioFormat::SignedInt) {
                    qint16 value = static_cast<qint16>(x * 32767);
                    if (format.byteOrder() == QAudioFormat::LittleEndian)
                        qToLittleEndian<qint16>(value, ptr);
                    else
                        qToBigEndian<qint16>(value, ptr);
                }
            }

            ptr += channelBytes;
            length -= channelBytes;
        }
    }
}

qint64 Generator::readData(char *data, qint64 len)
{
    qint64 total = 0;
    if (!m_buffer.isEmpty()) {
        while (len - total > 0) {
            const qint64 chunk = qMin((m_buffer.size() - m_pos), len - total);
            memcpy(data + total, m_buffer.constData() + m_pos, chunk);
            m_pos = (m_pos + chunk) % m_buffer.size();
            total += chunk;
        }
    }
    return total;
}

qint64 Generator::writeData(const char *data, qint64 len)
{
    Q_UNUSED(data);
    Q_UNUSED(len);

    return 0;
}

qint64 Generator::bytesAvailable() const
{
    return m_buffer.size() + QIODevice::bytesAvailable();
}


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //connect( ui->lineEdit_3, SIGNAL( textChanged( const QString & ) ), this,  SLOT( partChanged( const QString & ) ) );

    Note *pn = Notes;
    double basefreq  = 440.00;

    //calc oll freqs
    for(int i=0; pn->gamma; pn++)
    {
        pn->index = i++;
        double dpow = pow(2 , pn->semitone / 12.0);
        double f = dpow * basefreq;
        pn->freq = f;
    }

    //pTimer = new QTimer(this);
    //connect(pTimer, SIGNAL(timeout()), this, SLOT(void onTimer()));
    //pTimer->start(100);
    nTimerId = this->startTimer(50);

    ui->tempoSlide->setRange(5,60);

    int valueTempo = 5;

    ui->tempoSlide->setPageStep(valueTempo);// SAVE PROP
    ui->tempoSlide->setValue(valueTempo);
    ui->SCALE->setQpm(valueTempo);

    _init_audio();
}

void Dialog::showEvent ( QShowEvent * event )
{
    int valueTempo = 5;
    on_tempoSlide_valueChanged(valueTempo); // SAVE PROP

    ui->CK1->setChecked(true);
    ui->CK2->setChecked(true);
    ui->CK3->setChecked(true);
    ui->CK4->setChecked(true);
    ui->CK5->setChecked(true);
    ui->CK6->setChecked(true);
    ui->SCALE->generateNotes();

}

Dialog::~Dialog()
{
    killTimer(nTimerId);
    delete ui;
}


void Dialog::onOverNote(const QWidget* src, Note* pNote)
{
    char freq[32];

    if(pNote == 0){
        ui->note->setText(QString(" "));
        ui->FREET->setNote(pNote);

         return;
    }

    ui->note->setText(QString(pNote->note));
    ui->enote->setText(QString(pNote->enote));

    sprintf(freq,"%d/%d",pNote->index , pNote->gamma);
    ui->idx->setText(QString(freq));

    sprintf(freq,"%3.2f Hz",pNote->freq);
    ui->freq->setText(QString(freq));
    ui->FREET->setNote(pNote);



    //beep(100,100);


}

#define SAMPLE_RATE 44100.00
#define DURATION    0.5
#define TG_MAX_VAL  255.0
void Dialog::Beep(double freq)
{
    if(!m_generator.isNull())
        m_generator->stop();
    if(!m_audioOutput.isNull())
        m_audioOutput->stop();

    const int durationSeconds = 1;
    const int toneSampleRateHz = 600;
    m_generator.reset(new Generator(_format, DURATION * 1000000, freq));
    m_audioOutput.reset(new QAudioOutput(_deviceInfo, _format));
    m_audioOutput->setVolume(1.0);
    m_generator->start();
    m_audioOutput->start(m_generator.data());
    //pApp->beep();
}


void Dialog::timerEvent(QTimerEvent *event)
{
    ui->SCALE->advance();
    //usleep(500); //round 2 msecs
}


void Dialog::on_tempoSlide_valueChanged(int value)
{
    char val[32];
    sprintf(val,"%d qpm",value);
    ui->qpm->setText(QString(val));
    ui->SCALE->setQpm(value);
}

void Dialog::on_pushButton_clicked()
{
    ui->SCALE->generateNotes();
}



void Dialog::_init_audio()
{
    QAudioFormat format;
    _deviceInfo = QAudioDeviceInfo::defaultOutputDevice();

    _format.setSampleRate(44100);
    _format.setChannelCount(2);
    _format.setSampleSize(16);
    _format.setCodec("audio/pcm");
    _format.setByteOrder(QAudioFormat::LittleEndian);
    _format.setSampleType(QAudioFormat::SignedInt);

    if (!_deviceInfo.isFormatSupported(_format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        _format = _deviceInfo.nearestFormat(_format);
    }


}
