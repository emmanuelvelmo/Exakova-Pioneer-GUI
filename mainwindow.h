#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMouseEvent>
//#include <opencv2/opencv.hpp>
#include "controles_ventana.h"
#include "acerca_de_ventana.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); // Constructor
    ~MainWindow(); // Destructor

protected:
    void resizeEvent(QResizeEvent *event) override; // Sobrescribir el evento de redimension
    bool eventFilter(QObject *obj, QEvent *event) override; // Filtro de eventos para manejar el redimension

private slots:
    // Slots para la barra de menú
    void f_establecer_conexion();
    void f_despegar();
    void f_aterrizar();
    void f_retornar();
    void f_mira();
    void f_controles(); // Abre la ventana de controles al hacer clic en "Ayuda -> Controles"
    void f_guia();
    void f_acerca_de();

    // Slots para las acciones del menú contextual del widget de cámara
    void f_seguir(); // Acción "Seguir"
    void f_detener_seguimiento();
    void f_capturar_imagen(); // Acción "Capturar Imagen"
    void f_capturar_video(); // Acción "Capturar Video"

    // Slots para las acciones del menú contextual de w_mapa
    void f_colocar_pin(); // Acción "Colocar Pin"
    void f_eliminar_pin(); // Acción "Eliminar Pin"
    void f_ir_ubicacion(); // Acción "Ir a Ubicación"
    void f_detener_vuelo(); // Acción "Detener Vuelo"

    // Slot del widget de cámara
    void f_actualizar_frame(); // Slot para actualizar el frame de la cámara

private:
    Ui::MainWindow *ui; // Puntero a la interfaz de usuario generada
    ventana_controles *controles_ventana; // Puntero a la ventana de controles (usando el nuevo nombre de la clase)
    ventana_acerca_de *acerca_de_ventana; // Puntero a la ventana de acerca de (usando el nuevo nombre de la clase)

    // Variables para el redimension de w_mapa
    QPoint posicion_inicio_redimension; // Posición inicial del mouse al comenzar el redimension
    QSize tamano_inicio_redimension; // Tamaño inicial del widget al comenzar el redimension
    bool val_redimension; // Indica si se está redimensionando el widget

    //Captura de video (comentado)
    //QTimer *timer; // Temporizador para capturar frames de la cámara
    //cv::VideoCapture *video_capt; // Objeto de OpenCV para capturar video
};

#endif // MAINWINDOW_H
