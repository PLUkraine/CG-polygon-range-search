#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>

#include "geometrysearchplugin.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3, 3);

    qmlRegisterType<GeometrySearchPlugin>("SceneRenderer", 1, 0, "GeometrySearchPlugin");

    // create window
    QQuickView view;
    view.setTitle("Geometry Search");
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setFormat(format);
    view.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    view.show();

    // make Qt.quit() in QML exit application
    QObject::connect(view.engine(), SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));

    return app.exec();
}
