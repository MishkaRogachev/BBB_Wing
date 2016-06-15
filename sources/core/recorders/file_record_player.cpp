#include "file_record_player.h"

// Qt
#include <QFile>

using namespace domain;

class FileRecordPlayer::Impl
{
public:
    QFile file;
    QList<RecordPacket> packets;
};

FileRecordPlayer::FileRecordPlayer():
    d(new Impl())
{}

FileRecordPlayer::~FileRecordPlayer()
{
    delete d;
}

bool FileRecordPlayer::isAvalible() const
{
    return d->file.isOpen();
}

void FileRecordPlayer::open(const QString& filename)
{
    d->file.setFileName(filename);
    d->file.open(QIODevice::ReadOnly);
}

void FileRecordPlayer::close()
{
    d->file.close();
}

void FileRecordPlayer::readAll()
{
    QDataStream stream(&d->file);

    while (d->file.isReadable())
    {
        RecordPacket packet;
        stream >> packet;
        if (packet.timeStamp.isValid()) d->packets.append(packet);
    }
}

void FileRecordPlayer::clear()
{
    d->packets.clear();
}
