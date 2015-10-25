#ifndef SHOWWINDOW_H
#define SHOWWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QPainter>

#include "figure.h"

namespace Ui {
class TShowWindow;
}

class TShowWindow : public QWidget
{
    Q_OBJECT
    Figure *f;

public:
    explicit TShowWindow(QWidget *parent = 0,Figure *figure = 0);
    ~TShowWindow();
    void setFigure(Figure *figure);

protected:
    void paintEvent(QPaintEvent*);


private:
    Ui::TShowWindow *ui;
};

#endif // SHOWWINDOW_H
