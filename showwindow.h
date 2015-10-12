#ifndef SHOWWINDOW_H
#define SHOWWINDOW_H

#include <QWidget>

namespace Ui {
class TShowWindow;
}

class TShowWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TShowWindow(QWidget *parent = 0);
    ~TShowWindow();

private:
    Ui::TShowWindow *ui;
};

#endif // SHOWWINDOW_H
