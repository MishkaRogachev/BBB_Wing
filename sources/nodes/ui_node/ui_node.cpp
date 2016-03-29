#include "ui_node.h"

// Qt
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>
#include <QDebug>

// Internal
#include "core.h"

#include "subscriber.h"
#include "publisher.h"

#include "board_service.h"
#include "ground_service.h"

inline void initResources()
{
    Q_INIT_RESOURCE(qml);
    Q_INIT_RESOURCE(resources);
}

using namespace domain;

class UiNode::Impl
{
public:
    QQuickView view;
    Subscriber sub;
    Publisher pub;

    BoardService boardService;
    GroundService groundService;
};

UiNode::UiNode(QObject* parent):
    AbstractNode(parent),
    d(new Impl())
{
    initResources();

    d->pub.bind(endpoints::gui);

    d->view.rootContext()->setContextProperty("boardService", &d->boardService);
    d->view.rootContext()->setContextProperty("groundService", &d->groundService);
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
    d->sub.connectTo(endpoints::groundGateway);
    d->sub.subscribe(topics::data);
    connect(&d->sub, &Subscriber::received, this, &UiNode::onSubReceived);
}

void UiNode::start()
{
    d->view.showFullScreen();
}

void UiNode::onSubReceived(const QString& topic, const QByteArray& data)
{
    if (topic == topics::altPacket)
        d->boardService.updateAltData(AltPacket::fromByteArray(data));
    else if (topic == topics::snsPacket)
        d->boardService.updateSnsData(SnsPacket::fromByteArray(data));
    else if (topic == topics::insPacket)
        d->boardService.updateInsData(InsPacket::fromByteArray(data));
    else if (topic == topics::connectionStatusPacket)
        d->groundService.updateConnectionStatus(
                    ConnectionStatusPacket::fromByteArray(data));
}
