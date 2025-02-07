#include "controles_ventana.h"
#include "controles_ui.h"
#include <QLayout>
#include <QDebug>
#include <QPixmap>

ventana_controles::ventana_controles(QWidget *parent) : QDialog(parent), ui(new Ui::controles_ui)
{
    // Configura la interfaz de usuario
    ui->setupUi(this);

    ui->l_img1->setScaledContents(true);

    // Cargar la imagen inicial
    ui->l_img1->setPixmap(QPixmap("controles.png"));

    // Forzar la actualización del layout
    if (this->layout())
    {
        this->layout()->update();
        this->layout()->activate();
    }
}

ventana_controles::~ventana_controles()
{
    // Liberar la memoria de la interfaz de usuario
    delete ui;
}

void ventana_controles::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);

    // Redimensionar manualmente el QLabel para que se ajuste al nuevo tamaño de la ventana
    QSize newSize = this->size() - QSize(60, 60); // Restar los márgenes (30 píxeles en cada lado)
    ui->l_img1->resize(newSize);

    // Escalar la imagen para que se ajuste al nuevo tamaño del QLabel
    ui->l_img1->setPixmap(QPixmap("controles.png").scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
