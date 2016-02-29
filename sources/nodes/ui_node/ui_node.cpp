#include "ui_node.h"

// Qt
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QDebug>

// Internal
#include "subscriber.h"

void initResources()
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
};

UiNode::UiNode(QObject* parent):
    AbstractNode(parent),
    d(new Impl())
{}

UiNode::~UiNode()
{
    delete d;
}

void UiNode::init()
{
    initResources();

    d->view.setSource(QUrl(QStringLiteral("qrc:/qml/Views/MainView.qml")));
    d->view.setResizeMode(QQuickView::SizeRootObjectToView);

    QObject::connect(d->view.engine(), &QQmlEngine::quit,
                     qApp, &QGuiApplication::quit);

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
    // TODO: impl
}
