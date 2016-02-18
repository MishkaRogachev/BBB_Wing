// Qt
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;
    view.setSource(QUrl("qrc:/qml/Views/Main.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.showFullScreen();

    return app.exec();
}
