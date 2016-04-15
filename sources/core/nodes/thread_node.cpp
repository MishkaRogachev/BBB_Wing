#include "thread_node.h"

// Qt
#include <QThread>

using namespace domain;

ThreadNode::ThreadNode(AbstractNode* worker, QObject* parent):
    AbstractNode(parent),
    m_worker(worker),
    m_thread(new QThread(this))
{
    m_worker->moveToThread(m_thread);

    connect(m_thread, &QThread::started, m_worker, &AbstractNode::start);
    connect(m_thread, &QThread::finished, m_worker, &AbstractNode::deleteLater);
    connect(m_thread, &QThread::finished, m_thread, &QThread::deleteLater);

    connect(this, &ThreadNode::init, m_worker, &AbstractNode::init);
    connect(this, &ThreadNode::start, m_worker, &AbstractNode::start);
    connect(this, &ThreadNode::stop, m_worker, &AbstractNode::stop);

    m_thread->start();
}

ThreadNode::~ThreadNode()
{
    emit stop();

    m_thread->quit();
    m_thread->wait();
}
/*
void ThreadNode::init()
{
    QMetaObject::invokeMethod(m_worker, "init", Qt::QueuedConnection);
}

void ThreadNode::start()
{
    QMetaObject::invokeMethod(m_worker, "start", Qt::QueuedConnection);
}

void ThreadNode::stop()
{
    QMetaObject::invokeMethod(m_worker, "stop", Qt::QueuedConnection);
}*/
