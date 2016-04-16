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

        Q_PROPERTY(QAbstractVideoSurface* videoSurface READ videoSurface
                   WRITE setVideoSurface)

    public:
        explicit VideoService(QObject* parent = nullptr);

        QAbstractVideoSurface* videoSurface() const;

    public slots:
        void setVideoSurface(QAbstractVideoSurface* videoSurface);
        void updateSource();

    protected:
        void updateCameraVideoSurface();

    private:
        QCamera* m_camera;
        QAbstractVideoSurface* m_videoSurface;
    };
}

#endif // VIDEO_SERVICE_H
