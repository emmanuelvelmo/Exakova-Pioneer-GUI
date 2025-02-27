#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QImage>
#include <QPixmap>
#include <QMouseEvent>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
//#include <opencv2/opencv.hpp>
#include "controles_ventana.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // Configurar la interfaz de usuario generada por Qt Designer
    ui->setupUi(this);

    // Inicializar el puntero a nullptr
    controles_ventana = nullptr;
    acerca_de_ventana = nullptr;

    // Configuración de la ventana principal
    setWindowTitle("Exakova Pioneer");
    resize(640, 400);
    setWindowState(Qt::WindowMaximized);

    // Establecer el color de fondo del widget de mapa a gris
    ui->w_mapa->setStyleSheet("background-color: grey;");

    // Configurar widget de cámara para que ocupe toda la ventana (con un margen superior)
    ui->w_camara->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Configurar widget de mapa para que esté en la esquina superior derecha
    ui->w_mapa->setGeometry(width() - ui->w_mapa->width(), ui->l_margen->height(), ui->w_mapa->width(), ui->w_mapa->height());

    // Configurar barra superior (negra) para que ocupe todo el ancho de la ventana
    ui->l_margen->setGeometry(0, 0, width(), ui->l_margen->height());

    // Ajustar labels de batería para que estén en la esquina superior derecha
    int ancho_l_azul = ui->l_azul->width();
    int ancho_layout2 = ui->horizontalLayoutWidget_2->width();
    int posicion_x_l_azul = width() - ancho_l_azul;
    int posicion_x_layout2 = posicion_x_l_azul + (ancho_l_azul - ancho_layout2) / 2;

    ui->l_azul->setGeometry(posicion_x_l_azul, 0, ancho_l_azul, ui->l_azul->height());
    ui->horizontalLayoutWidget_2->setGeometry(posicion_x_layout2, 0, ancho_layout2, ui->horizontalLayoutWidget_2->height());

    // Configurar label de estado
    ui->l_estado->setText("No conectado");
    ui->l_estado->setStyleSheet("color: black; background-color: red; padding: 1px;");

    // Conectar la acciónes de la barra de menú
    connect(ui->actionEstablecer_Conexion, &QAction::triggered, this, &MainWindow::f_establecer_conexion);
    connect(ui->actionDespegar, &QAction::triggered, this, &MainWindow::f_despegar);
    connect(ui->actionAterrizar, &QAction::triggered, this, &MainWindow::f_aterrizar);
    connect(ui->actionRetornar, &QAction::triggered, this, &MainWindow::f_retornar);
    connect(ui->actionMira, &QAction::triggered, this, &MainWindow::f_mira);
    connect(ui->actionControles, &QAction::triggered, this, &MainWindow::f_controles);
    connect(ui->actionGuia, &QAction::triggered, this, &MainWindow::f_guia);
    connect(ui->actionAcerca_De_Exakova_Pioneer, &QAction::triggered, this, &MainWindow::f_acerca_de);

    // Conectar las acciones del menú contextual de widget de cámara
    connect(ui->actionSeguir, &QAction::triggered, this, &MainWindow::f_seguir);
    connect(ui->actionDetener_Seguimiento, &QAction::triggered, this, &MainWindow::f_detener_vuelo);
    connect(ui->actionCapturar_Imagen, &QAction::triggered, this, &MainWindow::f_capturar_imagen);
    connect(ui->actionCapturar_Video, &QAction::triggered, this, &MainWindow::f_capturar_video);

    // Agregar acciones al menú contextual del widget de cámara
    ui->w_camara->addAction(ui->actionSeguir);
    ui->w_camara->addAction(ui->actionDetener_Seguimiento);
    ui->w_camara->addAction(ui->actionCapturar_Imagen);
    ui->w_camara->addAction(ui->actionCapturar_Video);

    // Estilos para widget de cámara y su menú contextual
    ui->w_camara->setStyleSheet(R"(
        /* Estilo del widget w_camara */
        QLabel#w_camara
        {
            background-color: black; /* Fondo negro para el widget */
        }

        /* Estilo del menú contextual */
        QLabel#w_camara QMenu
        {
            background-color: #292a2b; /* Fondo gris oscuro */
            color: white; /* Texto blanco */
            border: 1px solid #1b1b1b; /* Borde gris más oscuro */
            padding: 0px; /* Sin padding adicional */
        }

        QLabel#w_camara QMenu::item
        {
            padding: 4px 24px 4px 24px; /* Padding: arriba, derecha, abajo, izquierda */
            background-color: transparent; /* Fondo transparente por defecto */
        }

        QLabel#w_camara QMenu::item:selected
        {
            background-color: #235c96; /* Fondo azul */
            border: 1px solid #50a0f0; /* Borde azul más claro */
            padding: 4px 24px 4px 23px; /* Padding izquierdo reducido en 1px */
        }

        QLabel#w_camara QMenu
        {
            box-shadow: 2px 2px 6px rgba(0, 0, 0, 0.5); /* Sombra */
        }
    )");

    // Conectar las acciones del menú contextual de w_mapa
    connect(ui->actionColocar_Pin, &QAction::triggered, this, &MainWindow::f_colocar_pin);
    connect(ui->actionEliminar_Pin, &QAction::triggered, this, &MainWindow::f_eliminar_pin);
    connect(ui->actionIr_A_Ubicacion, &QAction::triggered, this, &MainWindow::f_ir_ubicacion);
    connect(ui->actionDetener_Vuelo, &QAction::triggered, this, &MainWindow::f_detener_vuelo);

    // Agregar acciones al menú contextual del widget de mapa
    ui->w_mapa->addAction(ui->actionColocar_Pin);
    ui->w_mapa->addAction(ui->actionEliminar_Pin);
    ui->w_mapa->addAction(ui->actionIr_A_Ubicacion);
    ui->w_mapa->addAction(ui->actionDetener_Vuelo);

    // Estilos para widget de mapa y su menú contextual
    ui->w_mapa->setStyleSheet(R"(
        /* Estilo del widget w_mapa */
        QWidget#w_mapa
        {
            background-color: grey; /* Fondo gris para el widget */
        }

        /* Estilo del menú contextual */
        QWidget#w_mapa QMenu
        {
            background-color: #292a2b; /* Fondo gris oscuro */
            color: white; /* Texto blanco */
            border: 1px solid #1b1b1b; /* Borde gris más oscuro */
            padding: 0px; /* Sin padding adicional */
        }

        QWidget#w_mapa QMenu::item
        {
            padding: 4px 16px 4px 24px; /* Padding: arriba, derecha, abajo, izquierda */
            background-color: transparent; /* Fondo transparente por defecto */
        }

        QWidget#w_mapa QMenu::item:selected
        {
            background-color: #235c96; /* Fondo azul */
            border: 1px solid #50a0f0; /* Borde azul más claro */
            padding: 4px 16px 4px 23px; /* Padding izquierdo reducido en 1px */
        }

        QWidget#w_mapa QMenu
        {
            box-shadow: 2px 2px 6px rgba(0, 0, 0, 0.5); /* Sombra */
        }
    )");

    // Habilitar el seguimiento del mouse para widget de mapa
    ui->w_mapa->setMouseTracking(true);
    ui->w_mapa->installEventFilter(this);

    // Inicializar variables de redimension
    val_redimension = false;
}

MainWindow::~MainWindow()
{
    delete ui;

    if (controles_ventana)
    {
        delete controles_ventana; // Liberar la memoria de la ventana de controles
    }

    if (acerca_de_ventana)
    {
        delete acerca_de_ventana; // Liberar la memoria de la ventana de controles
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    // Llamar a la implementación base
    QMainWindow::resizeEvent(event);

    // Obtener la altura de margen superior
    int altura_margen = ui->l_margen->height();

    // Ajustar el tamaño de widget de cámara para que ocupe toda la ventana, con un margen superior
    ui->w_camara->setGeometry(0, altura_margen, width(), height() - altura_margen);

    // Mantener widget de mapa en la esquina superior derecha, con un margen superior
    ui->w_mapa->setGeometry(width() - ui->w_mapa->width(), ui->l_margen->height(), ui->w_mapa->width(), ui->w_mapa->height());

    // Ajustar margen superior para que ocupe todo el ancho de la ventana
    ui->l_margen->setGeometry(0, 0, width(), altura_margen);

    // Configurar labels de batería para que estén en la esquina superior derecha
    int ancho_l_azul = ui->l_azul->width();
    int ancho_layout2 = ui->horizontalLayoutWidget_2->width();
    int posicion_x_l_azul = width() - ancho_l_azul;
    int posicion_x_layout2 = posicion_x_l_azul + (ancho_l_azul - ancho_layout2) / 2;

    ui->l_azul->setGeometry(posicion_x_l_azul, 0, ancho_l_azul, ui->l_azul->height());
    ui->horizontalLayoutWidget_2->setGeometry(posicion_x_layout2, 0, ancho_layout2, ui->horizontalLayoutWidget_2->height());

    // Calcular el ancho del texto en label de estado
    QFontMetrics metricas(ui->l_estado->font());
    int ancho_texto = metricas.horizontalAdvance(ui->l_estado->text());

    // Ajustar el tamaño de label de estado al ancho del texto
    ui->l_estado->setFixedWidth(ancho_texto + 7);

    // Actualizar la posición de la mira (l_mira)
    int ancho_camara = ui->w_camara->width();
    int alto_camara = ui->w_camara->height();
    int ancho_mira = ui->l_mira->width();
    int alto_mira = ui->l_mira->height();

    // Calcular la nueva posición de la mira
    int pos_x = (ancho_camara / 2) - (ancho_mira / 2);
    int pos_y = (alto_camara / 2) - (alto_mira / 2) + 6;

    // Mover la mira a la nueva posición
    ui->l_mira->move(pos_x, pos_y);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->w_mapa)
    {
        if (event->type() == QEvent::MouseMove)
        {
            QMouseEvent *evento_mouse = static_cast<QMouseEvent*>(event);
            QPoint posicion_mouse = evento_mouse->pos();

            // Verificar si el mouse está en la esquina inferior izquierda
            if (posicion_mouse.x() < 10 && posicion_mouse.y() > ui->w_mapa->height() - 10)
            {
                // Cambiar el cursor a un cursor de redimension diagonal
                ui->w_mapa->setCursor(Qt::SizeBDiagCursor); // Usar Qt::SizeBDiagCursor
            }
            else
            {
                // Restaurar el cursor por defecto
                ui->w_mapa->setCursor(Qt::ArrowCursor);
            }

            // Si estamos redimensionando, ajustar el tamaño del widget
            if (val_redimension)
            {
                QPoint delta = evento_mouse->globalPos() - posicion_inicio_redimension;

                // Calcular el nuevo tamaño proporcionalmente
                QSize nuevo_tamano = tamano_inicio_redimension + QSize(-delta.x(), delta.y());

                // Obtener la relación de aspecto original (ancho / alto)
                qreal relacion_aspecto = static_cast<qreal>(tamano_inicio_redimension.width()) / tamano_inicio_redimension.height();

                // Ajustar el nuevo tamaño para mantener la relación de aspecto
                if (nuevo_tamano.width() < nuevo_tamano.height() * relacion_aspecto)
                {
                    // Si el ancho es demasiado pequeño, ajustar el alto
                    nuevo_tamano.setHeight(nuevo_tamano.width() / relacion_aspecto);
                }
                else
                {
                    // Si el alto es demasiado pequeño, ajustar el ancho
                    nuevo_tamano.setWidth(nuevo_tamano.height() * relacion_aspecto);
                }

                // Asegurarse de que el tamaño no sea menor que un mínimo
                nuevo_tamano = nuevo_tamano.expandedTo(QSize(100, 100)); // Tamaño mínimo de 100x100

                // Obtener las dimensiones de la ventana principal
                int ancho_maximo = width() - 20; // Margen de 10 píxeles a cada lado
                int alto_maximo = height() - ui->l_margen->height() - 20; // Margen de 10 píxeles arriba y abajo

                // Ajustar el tamaño para que no exceda los límites de la ventana
                if (nuevo_tamano.width() > ancho_maximo)
                {
                    nuevo_tamano.setWidth(ancho_maximo);
                    nuevo_tamano.setHeight(ancho_maximo / relacion_aspecto);
                }
                if (nuevo_tamano.height() > alto_maximo)
                {
                    nuevo_tamano.setHeight(alto_maximo);
                    nuevo_tamano.setWidth(alto_maximo * relacion_aspecto);
                }

                // Redimensionar el widget
                ui->w_mapa->resize(nuevo_tamano);

                // Mover el widget para que permanezca en la esquina superior derecha
                ui->w_mapa->move(width() - ui->w_mapa->width(), ui->l_margen->height());
            }
        }
        else if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *evento_mouse = static_cast<QMouseEvent*>(event);
            QPoint posicion_mouse = evento_mouse->pos();

            // Verificar si el mouse está en la esquina inferior izquierda
            if (posicion_mouse.x() < 10 && posicion_mouse.y() > ui->w_mapa->height() - 10)
            {
                // Iniciar el redimension
                posicion_inicio_redimension = evento_mouse->globalPos();
                tamano_inicio_redimension = ui->w_mapa->size();
                val_redimension = true;
            }
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            // Detener el redimension
            val_redimension = false;
        }
    }

    return QMainWindow::eventFilter(obj, event);
}

// Funciones de la barra de menú
void MainWindow::f_establecer_conexion()
{
    //


}

void MainWindow::f_despegar()
{
    //


}

void MainWindow::f_aterrizar()
{
    //


}

void MainWindow::f_retornar()
{
    //


}

void MainWindow::f_mira()
{
    // Alternar la visibilidad de la mira
    bool mira_visible = ui->l_mira->isVisible();

    ui->l_mira->setVisible(!mira_visible);
}

void MainWindow::f_controles()
{
    // Verificar si la ventana ya está creada
    if (!controles_ventana)
    {
        controles_ventana = new ventana_controles(this); // Crear una nueva instancia usando el nuevo nombre de la clase

        controles_ventana->setWindowTitle("Controles"); // Nombre de la ventana
        controles_ventana->setAttribute(Qt::WA_DeleteOnClose); // Liberar memoria al cerrar la ventana

        connect(controles_ventana, &QDialog::finished, this, [this]()
        {
            controles_ventana = nullptr; // Restablecer el puntero cuando la ventana se cierre
        });
    }

    controles_ventana->show(); // Mostrar la ventana
}

void MainWindow::f_guia()
{
    // Obtener la ruta del directorio donde se encuentra el ejecutable
    QString ruta_ejecutable = QDir::currentPath();

    // Construir la ruta completa al archivo guía.pdf
    QString ruta_pdf = ruta_ejecutable + "/Guía.pdf";

    // Abrir el archivo PDF con el programa predeterminado del sistema
    QDesktopServices::openUrl(QUrl::fromLocalFile(ruta_pdf));
}

void MainWindow::f_acerca_de()
{
    // Verificar si la ventana ya está creada
    if (!acerca_de_ventana)
    {
        acerca_de_ventana = new ventana_acerca_de(this); // Crear una nueva instancia usando el nuevo nombre de la clase

        acerca_de_ventana->setWindowTitle("Acerca de Exakova Pioneer"); // Nombre de la ventana
        acerca_de_ventana->setAttribute(Qt::WA_DeleteOnClose); // Liberar memoria al cerrar la ventana

        connect(acerca_de_ventana, &QDialog::finished, this, [this]()
        {
            acerca_de_ventana = nullptr; // Restablecer el puntero cuando la ventana se cierre
        });
    }

    acerca_de_ventana->show(); // Mostrar la ventana
}

// Funciones del menú contextual del widget de cámara
void MainWindow::f_seguir()
{
    //


}

void MainWindow::f_detener_seguimiento()
{
    //


}

void MainWindow::f_capturar_imagen()
{
    //


}

void MainWindow::f_capturar_video()
{
    //


}

// Funciones del menú contextual del widget de mapa
void MainWindow::f_colocar_pin()
{
    //


}

void MainWindow::f_eliminar_pin()
{
    //


}

void MainWindow::f_ir_ubicacion()
{
    //


}

void MainWindow::f_detener_vuelo()
{
    //


}

// Función para actualizar frame de video
void MainWindow::f_actualizar_frame()
{
    //cv::Mat val_frame;
    //*video_capt >> val_frame; // Capturar un frame de la cámara

    // Convertir el frame de OpenCV a QImage
    //cv::cvtColor(val_frame, val_frame, cv::COLOR_BGR2RGB); // Convertir de BGR a RGB
    //QImage qimg(val_frame.data, val_frame.cols, val_frame.rows, val_frame.step, QImage::Format_RGB888);

    // Escalar la imagen para que se ajuste al tamaño del widget de la cámara
    //QPixmap pixmap = QPixmap::fromImage(qimg);
    //pixmap = pixmap.scaled(ui->w_camara->size(), Qt::KeepAspectRatio);

    // Mostrar el QImage en el widget de la cámara
    //ui->w_camara->setPixmap(pixmap);
}
