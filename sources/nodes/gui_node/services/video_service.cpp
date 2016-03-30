#include "video_service.h"

// Qt
#include <QtMultimedia/QCamera>
#include <QtMultimedia/QCameraInfo>
#include <QDebug>

// Internal
#include "config.h"

using namespace domain;

VideoService::VideoService(QObject* parent):
    QObject(parent),
    m_camera(nullptr),
    m_videoSurface(nullptr)
{
    this->updateSource();
}

void VideoService::setVideoSurface(QAbstractVideoSurface* videoSurface)
{
    if (m_videoSurface == videoSurface) return;
    m_videoSurface = videoSurface;

    this->updateCameraVideoSurface();
}

void VideoService::updateSource()
{
    if (m_camera)
    {
        delete m_camera;
    }

    QCameraInfo info(Config::value("Gui/Video/device").toByteArray());
    if (info.isNull())
    {
        m_camera = nullptr;
    }
    else
    {
        m_camera = new QCamera(info, this);
        this->updateCameraVideoSurface();
    }
}

void VideoService::updateCameraVideoSurface()
{
    if (!m_camera || !m_videoSurface) return;

    m_camera->setViewfinder(m_videoSurface);
    m_camera->start();
}
