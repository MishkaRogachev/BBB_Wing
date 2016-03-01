#include "ui_node.h"

// Qt
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>
#include <QDebug>

// Internal
#include "board_service.h"

#include "subscriber.h"

inline void initResources()
{
    Q_INIT_RESOURCE(qml);
    Q_INIT_RESOURCE(resources);
}

using namespace domain;

class UiNode::Impl
{
public:
    BoardService boardService;
    QQuickView view;
    Subscriber sub;
};

UiNode::UiNode(QObject* parent):
    AbstractNode(parent),
    d(new Impl())
{
    initResources();

    d->view.rootContext()->setContextProperty("boardService", &d->boardService);
    d->view.setSource(QUrl(QStringLiteral("qrc:/qml/Views/MainView.qml")));
    d->view.setResizeMode(QQuickView::SizeRootObjectToView);

    QObject::connect(d->view.engine(), &QQmlEngine::quit,
                     qApp, &QGuiApplication::quit);
}

UiNode::~UiNode()
{
    delete d;
}

void UiNode::init()
{
    d->sub.connectTo("ipc://transceiver");
     
    d->sub.subscribe("");
    connect(&d->sub, &Subscriber::received, this, &UiNode::onSubReceived);
}

void UiNode::exec()
{
    d->view.showFullScreen();
}

void UiNode::onSubReceived(const QString& topic, const QByteArray& data)
{
//    if (topic == "alt_status")
//    else if (topic == "alt_altitude")
//    else if (topic == "alt_temperature")
//    else if (topic == "ins_status")
    if (topic == "ins_pitch") d->boardService.setPitch(data.toFloat());
    else if (topic == "ins_roll") d->boardService.setRoll(data.toFloat());
    else if (topic == "ins_yaw") d->boardService.setYaw(data.toFloat());
//    else if (topic == "sns_status")
//    else if (topic == "sns_latitude")
//    else if (topic == "sns_longitude")
//    else if (topic == "sns_velocity")
//    else if (topic == "sns_climb")

    // TODO: impl
}
