#include "ui_node.h"

// Qt
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>
#include <QDebug>

// Internal
#include "topics.h"
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
//    if (topic == topics::altimeterStatus)
    if (topic == topics::altimeterAltitude) d->boardService.setAltitude(data.toFloat());
//    else if (topic == topics::altimeterTemperature)
//    else if (topic == topics::insStatus)
    else if (topic == topics::insPitch) d->boardService.setPitch(data.toFloat());
    else if (topic == topics::insRoll) d->boardService.setRoll(data.toFloat());
    else if (topic == topics::insYaw) d->boardService.setYaw(data.toFloat());
//    else if (topic == topics::snsStatus)
    else if (topic == topics::snsLatitude) d->boardService.setLatitude(data.toFloat());
    else if (topic == topics::snsLongitude) d->boardService.setLongitude(data.toFloat());
    else if (topic == topics::snsVelocity) d->boardService.setVelocity(data.toFloat());
//    else if (topic == topics::snsClimb)

    // TODO: board service noverto to uiService(?) with dynamic properties
}
