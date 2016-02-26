// Qt
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>

// Internal
#include "scheduler_node.h"
#include "debug_node.h"
#include "workstation_transceiver_node.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    using namespace domain;

    SchedulerNode scheduler;

    scheduler.addNodeFrequency(new DebugNode(), 10);
    scheduler.addNodeFrequency(new WorkstationTransceiverNode(), 5);

    scheduler.init();
    scheduler.exec();

    QQuickView view;
    view.setSource(QUrl(QStringLiteral("qrc:/qml/Views/MainView.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.showFullScreen();
    QObject::connect(view.engine(), &QQmlEngine::quit,
                     &app, &QGuiApplication::quit);

    return app.exec();
}
