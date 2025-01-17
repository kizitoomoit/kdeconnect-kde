/**
 * Copyright 2018 Simon Redman <simon@ergotech.com>
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

#include "conversationmessage.h"

#include <QVariantMap>


ConversationMessage::ConversationMessage(const QVariantMap& args)
    : m_eventField(args[QStringLiteral("event")].toInt()),
      m_body(args[QStringLiteral("body")].toString()),
      m_address(args[QStringLiteral("address")].toString()),
      m_date(args[QStringLiteral("date")].toLongLong()),
      m_type(args[QStringLiteral("type")].toInt()),
      m_read(args[QStringLiteral("read")].toInt()),
      m_threadID(args[QStringLiteral("thread_id")].toLongLong()),
      m_uID(args[QStringLiteral("_id")].toInt())
{
}

ConversationMessage::ConversationMessage (const qint32& eventField, const QString& body,
                                          const QString& address, const qint64& date,
                                          const qint32& type, const qint32& read,
                                          const qint64& threadID,
                                          const qint32& uID)
    : m_eventField(eventField)
    , m_body(body)
    , m_address(address)
    , m_date(date)
    , m_type(type)
    , m_read(read)
    , m_threadID(threadID)
    , m_uID(uID)
{
}

ConversationMessage::ConversationMessage(const ConversationMessage& other)
    : m_eventField(other.m_eventField)
    , m_body(other.m_body)
    , m_address(other.m_address)
    , m_date(other.m_date)
    , m_type(other.m_type)
    , m_read(other.m_read)
    , m_threadID(other.m_threadID)
    , m_uID(other.m_uID)
{
}

ConversationMessage::~ConversationMessage() { }

ConversationMessage& ConversationMessage::operator=(const ConversationMessage& other)
{
    this->m_eventField = other.m_eventField;
    this->m_body = other.m_body;
    this->m_address = other.m_address;
    this->m_date = other.m_date;
    this->m_type = other.m_type;
    this->m_read = other.m_read;
    this->m_threadID = other.m_threadID;
    this->m_uID = other.m_uID;
    return *this;
}

QVariantMap ConversationMessage::toVariant() const
{
    return {
        {QStringLiteral("event"), m_eventField},
        {QStringLiteral("body"), m_body},
        {QStringLiteral("address"), m_address},
        {QStringLiteral("date"), m_date},
        {QStringLiteral("type"), m_type},
        {QStringLiteral("read"), m_read},
        {QStringLiteral("thread_id"), m_threadID},
        {QStringLiteral("_id"), m_uID},
    };
}

QDBusArgument &operator<<(QDBusArgument &argument, const ConversationMessage &message)
{
    argument.beginStructure();
    argument << message.eventField()
             << message.body()
             << message.address()
             << message.date()
             << message.type()
             << message.read()
             << message.threadID()
             << message.uID();
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, ConversationMessage &message)
{
    qint32 event;
    QString body;
    QString address;
    qint64 date;
    qint32 type;
    qint32 read;
    qint64 threadID;
    qint32 uID;

    argument.beginStructure();
    argument >> event;
    argument >> body;
    argument >> address;
    argument >> date;
    argument >> type;
    argument >> read;
    argument >> threadID;
    argument >> uID;
    argument.endStructure();

    message = ConversationMessage(event, body, address, date, type, read, threadID, uID);

    return argument;
}

void ConversationMessage::registerDbusType()
{
    qDBusRegisterMetaType<ConversationMessage>();
    qRegisterMetaType<ConversationMessage>();
}
