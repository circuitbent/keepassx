/*
*  Copyright (C) 2010 Felix Geyer <debfx@fobos.de>
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 2 or (at your option)
*  version 3 of the License.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KEEPASSX_HASHEDBLOCKSTREAM_H
#define KEEPASSX_HASHEDBLOCKSTREAM_H

#include "LayeredStream.h"
#include "core/Endian.h"
#include "crypto/CryptoHash.h"

class HashedBlockStream : public LayeredStream
{
    Q_OBJECT

public:
    explicit HashedBlockStream(QIODevice* baseDevice);
    HashedBlockStream(QIODevice* baseDevice, qint32 blockSize);

    void close();

protected:
    qint64 readData(char* data, qint64 maxSize);
    qint64 writeData(const char* data, qint64 maxSize);

private:
    void init();
    bool readHashedBlock();
    bool writeHashedBlock();

    static const QSysInfo::Endian BYTEORDER;
    qint32 m_blockSize;
    QByteArray m_buffer;
    int m_bufferPos;
    quint32 m_blockIndex;
    bool m_eof;
};

#endif // KEEPASSX_HASHEDBLOCKSTREAM_H