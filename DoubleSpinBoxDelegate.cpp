#include "DoubleSpinBoxDelegate.h"
#include <QDoubleSpinBox>

DoubleSpinBoxDelegate::DoubleSpinBoxDelegate(QObject *parent)
    : QItemDelegate(parent)
{
}

QWidget *DoubleSpinBoxDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &, const QModelIndex &) const
{
    auto doubleSpinBox = new QDoubleSpinBox(parent);
    doubleSpinBox->setMaximum(+9999999999.99999);
    doubleSpinBox->setMinimum(-9999999999.99999);
    return doubleSpinBox;
}

void DoubleSpinBoxDelegate::setEditorData(QWidget *editor,
    const QModelIndex &index) const
{
    auto doubleSpinBox = static_cast<QDoubleSpinBox *>(editor);
    doubleSpinBox->setValue(index.data().toDouble());
}

void DoubleSpinBoxDelegate::setModelData(QWidget *editor,
    QAbstractItemModel *model, const QModelIndex &index) const
{
    auto doubleSpinBox = static_cast<QDoubleSpinBox *>(editor);
    model->setData(index, doubleSpinBox->value());
}

void DoubleSpinBoxDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}

