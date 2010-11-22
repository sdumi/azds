/*
 * QtClient.cpp
 *
 *  Created on: Oct 22, 2010
 *      Author: dpomian
 *
 * -----------------------------------------------------------------------------
 * | Release  | Date       | Name       | History
 * -----------------------------------------------------------------------------
 * | 0.001    | 21.11.2010 | dumi       | introduce SSL on client side
 * -----------------------------------------------------------------------------
 *
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
    connect(client, SIGNAL(sslErrors(const QList<QSslError>&)), this, SLOT(errorOccured(const QList<QSslError>&)));
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
    client->setLocalCertificate("/home/dumitrus/dumcert.pem");
    client->setPrivateKey("/home/dumitrus/dumcert.pem");
    client->connectToHostEncrypted(address, port);
    client->ignoreSslErrors();


    if (!client)
    {
        cout << "connection failed!" << endl;
        return false;
    }
    // cout << "waiting for encryption...";
    // if (client->waitForEncrypted())
    // {
    //     cout << " done." << endl;
    // }
    // else
    // {
    //     cout << " failed." << endl;
    //     qDebug()<< "  Failure: " << client->errorString() << endl;
    // }

    return true;
}

////////////////////////////////////////////////////////////
//
void QtClient::clientConnected()
{
    cout << "Client connected!"<< endl;
    cout << "current encryption mode: " << client->mode() << endl;

    if (!client->isEncrypted())
    {
//        cout << "starting client encryption..." << endl;
//        client->startClientEncryption();
    }

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
    QSslCertificate cert = client->peerCertificate();

//    client->write("Hello, world", 13);
    QString data(client->readAll());

    cout << data.toStdString() << endl;
}

////////////////////////////////////////////////////////////
//
void QtClient::errorOccured(const QList<QSslError> &error)
{
    cout << "QtClient::errorOccured" << endl;
}

