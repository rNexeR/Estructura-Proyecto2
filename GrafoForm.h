#ifndef GRAFOFORM_H
#define GRAFOFORM_H
#include "Grafo.h"

#include <QWidget>

namespace Ui {
class GrafoForm;
}

class GrafoForm : public QWidget
{
    Q_OBJECT

public:
    explicit GrafoForm(QWidget *parent = 0);
    ~GrafoForm();

private slots:
    void on_zoomIn_clicked();

    void on_zoomOut_clicked();

private:
    Ui::GrafoForm *ui;
    double currentScale, scaleMin, scaleFactor;
};

#endif // GRAFOFORM_H
