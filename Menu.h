#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <GrafoForm.h>

namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
