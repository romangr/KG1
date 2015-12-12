#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintDevice>
#include <QPainter>

#include "figure.h"
#include "ruledparabols.h"
#include "showwindow.h"
#include "trianglesurface.h"
#include "lightedsurface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    TShowWindow *showWindow1;


public:
    Figure *fig1;
    TriangleSurface *ts;
    LightedSurface *ls;
    int k;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

signals:
    void updateImage();
public slots:
    void set_coord_clicked();
    void turn_button_clicked();
    void show_button_clicked();
    void autoscale_clicked();
};

#endif // MAINWINDOW_H
