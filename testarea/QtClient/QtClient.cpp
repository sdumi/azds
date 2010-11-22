/*
 * QtClient.cpp
 *
 *  Created on: Oct 22, 2010
 *      Author: dpomian
 */

#include "QtClient.h"
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////
//
QtClient::QtClient()
{
    client = new QSslSocket(this);

    connect(client, SIGNAL(connected ()), this, SLOT(clientConnected()));
    connect(client, SIGNAL(readyRead ()), this, SLOT(read()));
    connect(client, SIGNAL(error (QAbstractSocket::SocketError)), this, SLOT (showError()));
    connect(client, SIGNAL(encrypted()), this, SLOT(ready()));
}

////////////////////////////////////////////////////////////
//
QtClient::~QtClient()
{
    client->close();
}

////////////////////////////////////////////////////////////
//
bool QtClient::start(QString address, quint16 port)
{
    QHostAddress addr(address);

    cout << "connecting to: " << address.toStdString() << " port: " << port << endl;
// DS: this is used for plain TCP connections
//    client->connectToHost(addr, port);

// DS: for SSL connections we need to connect via 'connectToHostEncrypted()'
//       which does the handshake for us
    client->connectToHostEncrypted(address, port);

    if (!client)
    {
        cout << "connection failed!" << endl;
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////
//
void QtClient::clientConnected()
{
    cout << "Client connected!"<< endl;
}

////////////////////////////////////////////////////////////
//
void QtClient::read()
{
    QString data(client->readAll());

    cout << data.toStdString() << endl;
}

////////////////////////////////////////////////////////////
//
void QtClient::showError()
{
    cout << "Error: " << client->errorString().toStdString() << endl;
}

////////////////////////////////////////////////////////////
// temporary used by the SSL socket
void QtClient::ready()
{
    cout << "SSL socket is ready." << endl;
}
