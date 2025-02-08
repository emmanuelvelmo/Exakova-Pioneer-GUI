#ifndef ACERCA_DE_VENTANA_H
#define ACERCA_DE_VENTANA_H

#include <QDialog>
#include "acerca_de_ui.h" // Incluye la interfaz de usuario generada

class ventana_acerca_de : public QDialog
{
    Q_OBJECT

public:
    explicit ventana_acerca_de(QWidget *parent = nullptr); // Constructor
    ~ventana_acerca_de(); // Destructor

protected:
    void resizeEvent(QResizeEvent *event) override; // Sobrescribir el evento de redimensionamiento

private:
    Ui::acerca_de_ui *ui; // Puntero a la interfaz de usuario generada
};

#endif // ACERCA_DE_VENTANA_H