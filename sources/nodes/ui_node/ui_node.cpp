#include "ui_node.h"

// Qt
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlProperty>
#include <QDebug>

// Internal
#include "topics.h"
#include "subscriber.h"

#include "board_service.h"

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

    BoardService boardService;
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
}
