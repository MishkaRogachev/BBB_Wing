#ifndef FILE_RECORDER_H
#define FILE_RECORDER_H

#include "abstract_recorder.h"

namespace domain
{
    class FileRecorder: public AbstractRecorder
    {
    public:
        FileRecorder();
        ~FileRecorder() override;

        bool isAvalible() const;

        void open(const QString& filename);
        void close();
        void flush();
        void addRecord(const RecordPacket& record) override;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // FILE_RECORDER_H
