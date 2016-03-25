#ifndef GROUND_SERVICE_H
#define GROUND_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "connection_status_packet.h"

namespace domain
{
    class GroundService: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(bool airEnabled READ isAirEnabled NOTIFY airEnabledChanged)
        Q_PROPERTY(bool wireEnabled READ isWireEnabled NOTIFY wireEnabledChanged)
        Q_PROPERTY(int pps READ pps NOTIFY ppsChanged)
        Q_PROPERTY(int badPackets READ badPackets NOTIFY badPacketsChanged)

    public:
        explicit GroundService(QObject* parent = nullptr);

        bool isAirEnabled() const;
        bool isWireEnabled() const;
        int pps() const;
        int badPackets() const;

    public slots:
        void updateConnectionStatus(const ConnectionStatusPacket& packet);

    signals:
        void airEnabledChanged(bool airEnabled);
        void wireEnabledChanged(bool wireEnabled);
        void ppsChanged(int pps);
        void badPacketsChanged(int badPackets);

    private:
        bool m_airEnabled;
        bool m_wireEnabled;
        int m_pps;
        int m_badPackets;
    };
}

#endif // GROUND_SERVICE_H
