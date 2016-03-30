#include "video_service.h"

// Qt
#include <QtMultimedia/QCamera>

using namespace domain;

VideoService::VideoService(QObject* parent):
    QObject(parent),
    m_camera(new QCamera("/dev/video1", this))
{}

void VideoService::setVideoSurface(QAbstractVideoSurface* videoSurface)
{
    m_camera->setViewfinder(videoSurface);
    if (videoSurface) m_camera->start();
}
