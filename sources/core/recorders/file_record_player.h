#ifndef FILE_RECORD_PLAYER_H
#define FILE_RECORD_PLAYER_H

#include "record_packet.h"

namespace domain
{
    class FileRecordPlayer
    {
    public:
        FileRecordPlayer();
        virtual ~FileRecordPlayer();

        bool isAvalible() const;

        void open(const QString& filename);
        void close();

        void readAll();
        void clear();

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // FILE_RECORD_PLAYER_H
