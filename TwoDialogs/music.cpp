#include "music.h"

Music::Music()
{

}

QString Music::album() const
{
    return mAlbum;
}

void Music::setAlbum(const QString &album)
{
    mAlbum = album;
}

QString Music::artist() const
{
    return mArtist;
}

void Music::setArtist(const QString &artist)
{
    mArtist = artist;
}

QString Music::notes() const
{
    return mNotes;
}

void Music::setNotes(const QString &notes)
{
    mNotes = notes;
}

QDate Music::release() const
{
    return mRelease;
}

void Music::setRelease(const QDate &release)
{
    mRelease = release;
}
