#ifndef KFUNCTIONQMLWRAPPER_H
#define KFUNCTIONQMLWRAPPER_H

#include "kfunction.h"

#include <QObject>
#include <QtQml/qqmlregistration.h>

/**
 * @brief Wrapper for kfunction for QML
 * Should be registered with QML_VALUE_TYPE(kfunction)
 * and specified in CMakeLists like this
 * qt_add_qml_module(appqml-kfunction-editor
 *      URI QmlKfunctionEditor
 *      VERSION 1.0
 *      QML_FILES
 *          Main.qml
 *          KFunctionQmlView.qml
 *          KFunctionQmlEditor.qml
 *      SOURCES
 *          kfunctionqmlwrapper.h
 */
class KFunctionQmlWrapper
{
    Q_GADGET
    QML_VALUE_TYPE(kfunction)
public:
    KFunctionQmlWrapper() = default;
    explicit KFunctionQmlWrapper(const KFunctionQmlWrapper& other) : function_(other.function_) {}
    explicit KFunctionQmlWrapper(const QString &source) : function_(source.toStdString())
    {}

    Q_INVOKABLE
    void set_function(const QString &source) {
        auto newFunction = Function<double>();
        try {
            newFunction.set_function(source.toStdString());
            function_ = newFunction;
        } catch (const std::exception &e) {

        }
    }

    Q_INVOKABLE
    double run(const double xvalue) const {
        try {
            return function_.run(xvalue);
        } catch (const std::exception &e) {
            return 0.0;
        }
    }

private:
    Function<double> function_;
};

#endif // KFUNCTIONQMLWRAPPER_H
