#ifndef ABSTRACT_RECORDER_H
#define ABSTRACT_RECORDER_H

#include "record_packet.h"

namespace domain
{
    class AbstractRecorder
    {
    public:
        AbstractRecorder();
        virtual ~AbstractRecorder();

        virtual bool isAvalible() const = 0;

        virtual void addRecord(const RecordPacket& record) = 0;
    };
}

#endif // ABSTRACT_RECORDER_H
