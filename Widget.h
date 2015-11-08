#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui
{
class Widget;
}

class QStandardItemModel;

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void on_ordenSpinBox_valueChanged(int arg1);
    void on_inversaPushButton_clicked();
    void on_quitarAplicacionPushButton_clicked();
private:
    void setValueAt(QStandardItemModel *model, int ix, int jx,
                    double value) const;
    double getValueAt(QStandardItemModel *model, int ix, int jx) const;
    double **toDoublePointer(QStandardItemModel *model) const;
    double **createNewMatrix(int order) const;
    void inverseMatrix(double **a, double **ia, int order) const;
    void toModel(QStandardItemModel *model, double **a, int order) const;
    void deleteMatrix(double **a, int order) const;
    void getMinor(double **src, double **dest, int row, int col,
                  int order) const;
    double calculateDeterminant(double **a, int order) const;

    Ui::Widget *ui;
    QStandardItemModel *mModelA;
    QStandardItemModel *mModelIA;
};

#endif // WIDGET_H
