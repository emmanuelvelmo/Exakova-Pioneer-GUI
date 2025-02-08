#ifndef CONTROLES_VENTANA_H
#define CONTROLES_VENTANA_H

#include <QDialog>
#include "controles_ui.h" // Incluye la interfaz de usuario generada

class ventana_controles : public QDialog // Cambiar el nombre de la clase
{
    Q_OBJECT

public:
    explicit ventana_controles(QWidget *parent = nullptr); // Constructor
    ~ventana_controles(); // Destructor

protected:
    void resizeEvent(QResizeEvent *event) override; // Sobrescribir el evento de redimensionamiento

private:
    Ui::controles_ui *ui; // Puntero a la interfaz de usuario generada
};

#endif // CONTROLES_VENTANA_H
