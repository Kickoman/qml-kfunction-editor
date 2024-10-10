#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "kfunctionmodelmapper.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const DefaultFunction function("sin(x)");
    auto functionDataModel = new KFunctionDataModel(function);
    auto dataModelMapper = new QVXYModelMapper();
    dataModelMapper->setModel(functionDataModel);
    dataModelMapper->setXColumn(0);
    dataModelMapper->setYColumn(1);
    dataModelMapper->setRowCount(functionDataModel->rowCount());
    engine.rootContext()->setContextProperty("kfunctionDataModelMapper", dataModelMapper);

    const QUrl url(QStringLiteral("qrc:/QmlKfunctionEditor/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
