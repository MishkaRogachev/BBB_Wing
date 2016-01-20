#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "base_transport.h"

namespace domain
{
    class Publisher: public BaseTransport
    {
        Q_OBJECT

    public:
        Publisher(const QString& endpoint, QObject* parent = nullptr);
    };
}

#endif // PUBLISHER_H
