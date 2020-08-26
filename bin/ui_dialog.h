/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created: Wed Apr 13 20:25:15 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QWidget>
#include <freet.h>
#include "cscale.h"

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    Freet *FREET;
    CScale *SCALE;
    QSlider *horizontalSlider;
    QLabel *note;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QCheckBox *CK1;
    QCheckBox *CK2;
    QCheckBox *CK3;
    QCheckBox *CK4;
    QCheckBox *CK5;
    QCheckBox *CK6;
    QLabel *enote;
    QLabel *idx;
    QLabel *freq;
    QLabel *label;
    QSlider *tempoSlide;
    QLabel *qpm;
    QPushButton *pushButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(1410, 817);
        FREET = new Freet(Dialog);
        FREET->setObjectName(QString::fromUtf8("FREET"));
        FREET->setGeometry(QRect(10, 10, 211, 741));
        FREET->setCursor(QCursor(Qt::CrossCursor));
        SCALE = new CScale(Dialog);
        SCALE->setObjectName(QString::fromUtf8("SCALE"));
        SCALE->setGeometry(QRect(240, 20, 941, 301));
        SCALE->setCursor(QCursor(Qt::BlankCursor));
        horizontalSlider = new QSlider(Dialog);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(230, 340, 821, 20));
        horizontalSlider->setOrientation(Qt::Horizontal);
        note = new QLabel(Dialog);
        note->setObjectName(QString::fromUtf8("note"));
        note->setGeometry(QRect(1260, 20, 131, 81));
        QFont font;
        font.setPointSize(36);
        note->setFont(font);
        note->setFrameShape(QFrame::Box);
        note->setFrameShadow(QFrame::Raised);
        note->setAlignment(Qt::AlignCenter);
        note->setIndent(1);
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 770, 191, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        CK1 = new QCheckBox(layoutWidget);
        CK1->setObjectName(QString::fromUtf8("CK1"));

        horizontalLayout->addWidget(CK1);

        CK2 = new QCheckBox(layoutWidget);
        CK2->setObjectName(QString::fromUtf8("CK2"));

        horizontalLayout->addWidget(CK2);

        CK3 = new QCheckBox(layoutWidget);
        CK3->setObjectName(QString::fromUtf8("CK3"));

        horizontalLayout->addWidget(CK3);

        CK4 = new QCheckBox(layoutWidget);
        CK4->setObjectName(QString::fromUtf8("CK4"));

        horizontalLayout->addWidget(CK4);

        CK5 = new QCheckBox(layoutWidget);
        CK5->setObjectName(QString::fromUtf8("CK5"));

        horizontalLayout->addWidget(CK5);

        CK6 = new QCheckBox(layoutWidget);
        CK6->setObjectName(QString::fromUtf8("CK6"));

        horizontalLayout->addWidget(CK6);

        enote = new QLabel(Dialog);
        enote->setObjectName(QString::fromUtf8("enote"));
        enote->setGeometry(QRect(1260, 110, 131, 81));
        enote->setFont(font);
        enote->setFrameShape(QFrame::Box);
        enote->setFrameShadow(QFrame::Raised);
        enote->setAlignment(Qt::AlignCenter);
        enote->setIndent(1);
        idx = new QLabel(Dialog);
        idx->setObjectName(QString::fromUtf8("idx"));
        idx->setGeometry(QRect(1260, 200, 131, 81));
        idx->setFont(font);
        idx->setFrameShape(QFrame::Box);
        idx->setFrameShadow(QFrame::Sunken);
        idx->setAlignment(Qt::AlignCenter);
        idx->setIndent(1);
        freq = new QLabel(Dialog);
        freq->setObjectName(QString::fromUtf8("freq"));
        freq->setGeometry(QRect(1260, 300, 131, 31));
        QFont font1;
        font1.setPointSize(14);
        freq->setFont(font1);
        freq->setFrameShape(QFrame::Box);
        freq->setFrameShadow(QFrame::Sunken);
        freq->setAlignment(Qt::AlignCenter);
        freq->setIndent(1);
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(1190, 10, 72, 19));
        tempoSlide = new QSlider(Dialog);
        tempoSlide->setObjectName(QString::fromUtf8("tempoSlide"));
        tempoSlide->setGeometry(QRect(1200, 40, 21, 291));
        tempoSlide->setOrientation(Qt::Vertical);
        qpm = new QLabel(Dialog);
        qpm->setObjectName(QString::fromUtf8("qpm"));
        qpm->setGeometry(QRect(1180, 250, 72, 19));
        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(230, 370, 106, 29));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        note->setText(QApplication::translate("Dialog", "*", 0, QApplication::UnicodeUTF8));
        CK1->setText(QString());
        CK2->setText(QString());
        CK3->setText(QString());
        CK4->setText(QString());
        CK5->setText(QString());
        CK6->setText(QString());
        enote->setText(QApplication::translate("Dialog", "*", 0, QApplication::UnicodeUTF8));
        idx->setText(QApplication::translate("Dialog", "*", 0, QApplication::UnicodeUTF8));
        freq->setText(QApplication::translate("Dialog", "*", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "Tempo", 0, QApplication::UnicodeUTF8));
        qpm->setText(QString());
        pushButton->setText(QApplication::translate("Dialog", "Generate Notes", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
