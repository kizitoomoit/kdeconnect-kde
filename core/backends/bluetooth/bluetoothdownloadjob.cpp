/*
 * Copyright 2016 Saikrishna Arcot <saiarcot895@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "bluetoothdownloadjob.h"

BluetoothDownloadJob::BluetoothDownloadJob(const QBluetoothAddress& remoteAddress, const QVariantMap& transferInfo, QObject* parent)
    : QObject(parent)
    , mRemoteAddress(remoteAddress)
    , mTransferUuid(QBluetoothUuid(transferInfo.value(QStringLiteral("uuid")).toString()))
    , mSocket(new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol))
{
}

QSharedPointer<QIODevice> BluetoothDownloadJob::payload() const
{
    return mSocket.staticCast<QIODevice>();
}

void BluetoothDownloadJob::start()
{
    connect(mSocket.data(), &QBluetoothSocket::disconnected, mSocket.data(), &QBluetoothSocket::readyRead);
    connect(mSocket.data(), &QBluetoothSocket::disconnected, mSocket.data(), &QBluetoothSocket::readChannelFinished);
    mSocket->connectToService(mRemoteAddress, mTransferUuid, QIODevice::ReadOnly);
}
