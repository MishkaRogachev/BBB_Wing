#ifndef VIDEO_SERVICE_H
#define VIDEO_SERVICE_H

#include <QObject>

class QAbstractVideoSurface;
class QCamera;

namespace domain
{
    class VideoService: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QAbstractVideoSurface* videoSurface WRITE setVideoSurface)

    public:
        explicit VideoService(QObject* parent = nullptr);

    public slots:
        void setVideoSurface(QAbstractVideoSurface* videoSurface);

    private:
        QCamera* m_camera;
    };
}

#endif // VIDEO_SERVICE_H
