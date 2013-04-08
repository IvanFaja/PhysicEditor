#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include "src/freedrawer.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<FreeDrawer>("GEdit",1,0,"FreeDrawer");
    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/GEditor/main.qml"));
    viewer.showExpanded();
    return app.exec();
}
