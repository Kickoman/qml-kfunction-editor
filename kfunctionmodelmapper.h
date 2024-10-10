#ifndef KFUNCTIONMODELMAPPER_H
#define KFUNCTIONMODELMAPPER_H

#include "kfunction.h"

#include <QAbstractTableModel>
#include <QtCharts/QVXYModelMapper>

#include <QDebug>

using DefaultFunction = Function<double>;

class KFunctionDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit KFunctionDataModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {}
    explicit KFunctionDataModel(const DefaultFunction &f, QObject *parent = nullptr) : QAbstractTableModel(parent), function(f) {}
    explicit KFunctionDataModel(const std::string &f, QObject *parent = nullptr) : QAbstractTableModel(parent), function(f) {}

    void setFunction(const DefaultFunction &f) {
        beginResetModel();
        function = f; emit functionUpdated();
        endResetModel();
    }

    void setFunction(const std::string &f) {
        beginResetModel();
        function = f; emit functionUpdated();
        endResetModel();
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return 1000;
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 2;
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        Q_UNUSED(orientation)
        Q_UNUSED(role)
        return section == 0 ? "x" : "y";
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        Q_UNUSED(role)
        double d = 0;
        try {
            d = index.column() == 0 ? getXByIndex(index.row()) : function.run(getXByIndex(index.row()));
        } catch (const std::exception &e) {
            qDebug() << "Function calc error: " << e.what();
            d = 0;
        }

        return d;
    }

    Q_INVOKABLE
    void setRangeStart(double x) {
        beginResetModel();
        rangeStart = x;
        endResetModel();
    }

    Q_INVOKABLE
    void setRangeFinish(double x) {
        beginResetModel();
        rangeFinish = x;
        endResetModel();
    }

    Q_INVOKABLE
    void setPointsCount(double x) {
        beginResetModel();
        points = x;
        endResetModel();
    }

    Q_INVOKABLE
    double getXByIndex(const int index) const {
        const double step = (rangeFinish - rangeStart) / points;
        return rangeStart + step * index;
    }

    Q_INVOKABLE
    void setFunction(const QString &f) {
        qDebug() << "SettingFunction";
        DefaultFunction function;
        try {
            function.set_function(f.toStdString());
            setFunction(f.toStdString());
        } catch (const std::exception &e) {
            qDebug() << "Function error: " << e.what();
        }
    }

signals:
    void functionUpdated();

private:
    DefaultFunction function;

    double rangeStart = 0;
    double rangeFinish = 100;
    double points = 500;
};

#endif // KFUNCTIONMODELMAPPER_H
