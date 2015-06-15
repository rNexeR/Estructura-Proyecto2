#include "Menu.h"
#include "ui_Menu.h"

Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButton_clicked()
{
    GrafoForm* ventana = new GrafoForm();
    ventana->show();
}

void Menu::on_pushButton_2_clicked()
{
    OrdenamientoForm* ventana = new OrdenamientoForm();
    ventana->show();
}
