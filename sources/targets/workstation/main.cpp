// Qt
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;
    view.setSource(QUrl("qrc:/qml/Views/MainView.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.showFullScreen();
    QObject::connect(view.engine(), &QQmlEngine::quit,
                     &app, &QGuiApplication::quit);

    return app.exec();
}
