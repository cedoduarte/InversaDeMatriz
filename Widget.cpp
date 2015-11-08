#include "Widget.h"
#include "ui_Widget.h"
#include "DoubleSpinBoxDelegate.h"
#include <QStandardItemModel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mModelA = new QStandardItemModel(this);
    mModelIA = new QStandardItemModel(this);
    ui->tableViewA->setModel(mModelA);
    ui->tableViewIA->setModel(mModelIA);
    ui->tableViewA->setItemDelegate(new DoubleSpinBoxDelegate(this));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_ordenSpinBox_valueChanged(int arg1)
{
    mModelA->setRowCount(arg1);
    mModelA->setColumnCount(arg1);
    mModelIA->setRowCount(arg1);
    mModelIA->setColumnCount(arg1);
}

void Widget::on_inversaPushButton_clicked()
{
    const int orden = mModelA->rowCount();
    double **a = toDoublePointer(mModelA);
    double **ia = createNewMatrix(orden);
    inverseMatrix(a, ia, orden);
    toModel(mModelIA, ia, orden);
    deleteMatrix(a, orden);
    deleteMatrix(ia, orden);
}

void Widget::on_quitarAplicacionPushButton_clicked()
{
    close();
}

void Widget::setValueAt(QStandardItemModel *model, int ix, int jx,
                        double value) const
{
    if (!model->item(ix, jx)) {
        model->setItem(ix, jx, new QStandardItem(QString::number(value)));
    } else {
        model->item(ix, jx)->setText(QString::number(value));
    }
}

double Widget::getValueAt(QStandardItemModel *model, int ix, int jx) const
{
    if (!model->item(ix, jx)) {
        return 0.0;
    }
    return model->item(ix, jx)->text().toDouble();
}

double **Widget::toDoublePointer(QStandardItemModel *model) const
{
    const int orden = model->rowCount();
    double **a = new double*[orden];
    for (int ix = 0; ix < orden; ++ix) {
        a[ix] = new double[orden];
        for (int jx = 0; jx < orden; ++jx) {
            a[ix][jx] = getValueAt(model, ix, jx);
        }
    }
    return a;
}

double **Widget::createNewMatrix(int order) const
{
    double **a = new double*[order];
    for (int ix = 0; ix < order; ++ix) {
        a[ix] = new double[order];
    }
    return a;
}

void Widget::inverseMatrix(double **a, double **ia, int order) const
{
    double det = 1.0 / calculateDeterminant(a, order);
    double *temp = new double[(order-1)*(order-1)];
    double **minor = new double*[order-1];
    for (int ix = 0; ix < order-1; ++ix) {
        minor[ix] = temp + (ix * (order - 1));
    }
    for (int jx = 0; jx < order; ++jx) {
        for (int ix = 0; ix < order; ++ix) {
            getMinor(a, minor, jx, ix, order);
            ia[ix][jx] = det * calculateDeterminant(minor, order-1);
            if ((ix+jx) % 2 == 1) {
                ia[ix][jx] = -ia[ix][jx];
            }
        }
    }
    delete[] temp;
    delete[] minor;
}

void Widget::toModel(QStandardItemModel *model, double **a, int order) const
{
    for (int ix = 0; ix < order; ++ix) {
        for (int jx = 0; jx < order; ++jx) {
            setValueAt(model, ix, jx, a[ix][jx]);
        }
    }
}

void Widget::deleteMatrix(double **a, int order) const
{
    for (int ix = 0; ix < order; ++ix) {
        delete[] a[ix];
    }
    delete[] a;
}

void Widget::getMinor(double **src, double **dest, int row, int col,
                      int order) const
{
    int colCount = 0;
    int rowCount = 0;
    for (int ix = 0; ix < order; ++ix) {
        if (ix != row) {
            colCount = 0;
            for (int jx = 0; jx < order; ++jx) {
                if (jx != col) {
                    dest[rowCount][colCount] = src[ix][jx];
                    ++colCount;
                }
            }
            ++rowCount;
        }
    }
}

double Widget::calculateDeterminant(double **a, int order) const
{
    if (order == 1) {
        return a[0][0];
    }
    double det = 0.0;
    double **minor = new double*[order-1];
    for (int ix = 0; ix < order - 1; ++ix) {
        minor[ix] = new double[order-1];
    }
    for (int ix = 0; ix < order; ++ix) {
        getMinor(a, minor, 0, ix, order);
        det += (ix % 2 == 1 ? -1.0 : 1.0)
                * a[0][ix]
                * calculateDeterminant(minor, order-1);
    }
    for (int ix = 0; ix < order - 1; ++ix) {
        delete[] minor[ix];
    }
    delete[] minor;
    return det;
}
