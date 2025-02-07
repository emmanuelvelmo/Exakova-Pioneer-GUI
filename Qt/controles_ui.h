/********************************************************************************
** Form generated from reading UI file 'controles.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CONTROLES_UI_H
#define CONTROLES_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_controles_ui
{
public:
    QLabel *l_img1;

    void setupUi(QDialog *controles_ui)
    {
        if (controles_ui->objectName().isEmpty())
            controles_ui->setObjectName(QString::fromUtf8("controles_ui"));
        controles_ui->resize(405, 303);
        controles_ui->setStyleSheet(QString::fromUtf8("background-color: rgb(31, 31, 31);"));
        l_img1 = new QLabel(controles_ui);
        l_img1->setObjectName(QString::fromUtf8("label"));
        l_img1->setGeometry(QRect(30, 30, 345, 243));
        l_img1->setPixmap(QPixmap(QString::fromUtf8("controles.png")));
        l_img1->setScaledContents(true);
        l_img1->setWordWrap(false);

        retranslateUi(controles_ui);

        QMetaObject::connectSlotsByName(controles_ui);
    } // setupUi

    void retranslateUi(QDialog *controles_ui)
    {
        controles_ui->setWindowTitle(QApplication::translate("controles_ui", "Dialog", nullptr));
        l_img1->setText(QString());
    } // retranslateUi

};

namespace Ui
{
    class controles_ui: public Ui_controles_ui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CONTROLES_UI_H
