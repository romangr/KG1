#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "figure.h"
#include "showwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    TShowWindow *showWindow1;
    Figure *fig1;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void set_coord_clicked();
    void turn_button_clicked();
    void show_button_clicked();
};

#endif // MAINWINDOW_H
