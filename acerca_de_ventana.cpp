#include "acerca_de_ventana.h"
#include "acerca_de_ui.h"
#include <QLayout>
#include <QDebug>
#include <QPixmap>
#include <QFont>

ventana_acerca_de::ventana_acerca_de(QWidget *parent) : QDialog(parent), ui(new Ui::acerca_de_ui)
{
    // Configura la interfaz de usuario
    ui->setupUi(this);

    // Forzar la actualización del layout
    if (this->layout())
    {
        this->layout()->update();
        this->layout()->activate();
    }
}

ventana_acerca_de::~ventana_acerca_de()
{
    // Liberar la memoria de la interfaz de usuario
    delete ui;
}

void ventana_acerca_de::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
}
