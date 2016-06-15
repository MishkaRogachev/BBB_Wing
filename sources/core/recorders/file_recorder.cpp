#include "file_recorder.h"

// Qt
#include <QFile>
#include <QFileInfo>
#include <QDir>

using namespace domain;

class FileRecorder::Impl
{
public:
    QFile file;
};

FileRecorder::FileRecorder():
    d(new Impl())
{}

FileRecorder::~FileRecorder()
{
    delete d;
}

bool FileRecorder::isAvalible() const
{
    return d->file.isOpen();
}

void FileRecorder::open(const QString& filename)
{
    QFileInfo info(filename);
    QString path = info.path();
    if (!QDir(path).exists()) QDir(path).mkpath(".");

    d->file.setFileName(filename);
    d->file.open(QIODevice::Append);
}

void FileRecorder::close()
{
    d->file.close();
}

void FileRecorder::flush()
{
    d->file.flush();
}

void FileRecorder::addRecord(const RecordPacket& record)
{
    d->file.write(record.toByteArray());
}
