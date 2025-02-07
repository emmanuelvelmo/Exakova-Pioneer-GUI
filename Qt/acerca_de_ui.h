#ifndef ACERCA_DE_UI_H
#define ACERCA_DE_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_acerca_de_ui
{
public:
    QLabel *l_txt1; // Etiqueta para el texto principal
    QLabel *l_txt2; // Etiqueta para el texto secundario
    QVBoxLayout *verticalLayout; // Layout vertical para organizar los widgets
    QSpacerItem *verticalSpacer; // Spacer para ocupar el espacio sobrante

    void setupUi(QDialog *acerca_de_ui)
    {
        // Configurar el nombre del objeto si no está definido
        if (acerca_de_ui->objectName().isEmpty())
            acerca_de_ui->setObjectName(QString::fromUtf8("acerca_de_ui"));

        // Establecer el tamaño inicial de la ventana
        acerca_de_ui->resize(240, 240);

        // Configurar el color de fondo de la ventana
        acerca_de_ui->setStyleSheet(QString::fromUtf8("background-color: rgb(31, 31, 31);"));

        // Crear el layout vertical y configurar sus propiedades
        verticalLayout = new QVBoxLayout(acerca_de_ui);
        verticalLayout->setSpacing(10); // Espaciado entre widgets
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(30, 30, 30, 30); // Márgenes: izquierda, arriba, derecha, abajo

        // Crear y configurar l_txt1 (etiqueta principal)
        l_txt1 = new QLabel(acerca_de_ui);
        l_txt1->setObjectName(QString::fromUtf8("l_txt1"));
        l_txt1->setStyleSheet("color: white;"); // Color del texto
        l_txt1->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop); // Alineación del texto
        l_txt1->setWordWrap(true); // Habilitar ajuste de texto
        l_txt1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum); // Política de tamaño

        // Configurar la fuente para l_txt1
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei")); // Fuente Microsoft YaHei
        font.setPointSize(11); // Tamaño de la fuente
        font.setBold(true); // Texto en negrita
        l_txt1->setFont(font);

        // Agregar l_txt1 al layout
        verticalLayout->addWidget(l_txt1);

        // Crear y configurar l_txt2 (etiqueta secundaria)
        l_txt2 = new QLabel(acerca_de_ui);
        l_txt2->setObjectName(QString::fromUtf8("l_txt2"));
        l_txt2->setStyleSheet("color: white;"); // Color del texto
        l_txt2->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop); // Alineación del texto
        l_txt2->setWordWrap(true); // Habilitar ajuste de texto
        l_txt2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum); // Política de tamaño

        // Configurar la fuente para l_txt2
        QFont font2;
        font2.setFamily(QString::fromUtf8("Microsoft YaHei")); // Fuente Microsoft YaHei
        font2.setPointSize(8); // Tamaño de la fuente más pequeño
        font2.setBold(false); // Texto sin negrita
        l_txt2->setFont(font2);

        // Habilitar la apertura de enlaces externos
        l_txt2->setOpenExternalLinks(true);

        // Agregar l_txt2 al layout
        verticalLayout->addWidget(l_txt2);

        // Agregar un spacer al final para ocupar el espacio sobrante
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        verticalLayout->addItem(verticalSpacer);

        // Traducir la interfaz de usuario
        retranslateUi(acerca_de_ui);

        // Conectar señales y slots automáticamente
        QMetaObject::connectSlotsByName(acerca_de_ui);
    }

    void retranslateUi(QDialog *acerca_de_ui)
    {
        // Establecer el título de la ventana
        acerca_de_ui->setWindowTitle(QApplication::translate("acerca_de_ui", "Acerca de", nullptr));

        // Establecer el texto de l_txt1
        l_txt1->setText(QApplication::translate("acerca_de_ui", "Exakova Pioneer 2025", nullptr));

        // Establecer el texto de l_txt2
        l_txt2->setText(QApplication::translate("acerca_de_ui",
            "<html><head/><body>"
            "<p>Versión 1.0</p>"
            "<p>Copyright© 2025 Exakova Inc.</p>"
            "<p>Todos los derechos reservados</p>"
            "<p>Web: <a href=\"https://github.com/exakova\" style=\"color: #007BFF; text-decoration: underline;\">https://github.com/exakova</a></p>"
            "<p>Email: <a href=\"mailto:exakova@protonmail.com\" style=\"color: #007BFF; text-decoration: underline;\">exakova@protonmail.com</a></p>"
            "</body></html>", nullptr));
    }
};

namespace Ui
{
    class acerca_de_ui: public Ui_acerca_de_ui {};
}

QT_END_NAMESPACE

#endif // ACERCA_DE_UI_H
