/*
 * MultiClientServer.cpp
 *
 *  Created on: Oct 22, 2010
 *      Author: dpomian
 *
 * -----------------------------------------------------------------------------
 * | Release  | Date       | Name       | History
 * -----------------------------------------------------------------------------
 * | 0.001    | 21.11.2010 | dumi       | introduce SSL on server side
 * -----------------------------------------------------------------------------
 *
 */

#include "MultiClientServer.h"
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////
//
MultiClientServer::MultiClientServer(int port_)
{
    this->_PORT_ = port_;

    connect (&messageTimer, SIGNAL(timeout()), this, SLOT (sendMessageToAllClients()));
    connect (this, SIGNAL(newConnection()), this, SLOT (handleNewConnection()));
}

////////////////////////////////////////////////////////////
//
MultiClientServer::~MultiClientServer()
{
    stop();
}

////////////////////////////////////////////////////////////
//
void MultiClientServer::stop()
{
    messageTimer.stop();
    close();
    qDeleteAll (clientConnections);
}

////////////////////////////////////////////////////////////
//
void MultiClientServer::start()
{
    qDebug() << "Server started on port: " << this->_PORT_;
    qDebug() << "Listening for incoming connections\n";

    messageTimer.start(1000);
    listen (QHostAddress::LocalHost, this->_PORT_);
}

////////////////////////////////////////////////////////////
// DS: functionality offered by ::incomingConnection().
//     no need for ::handleNewConnection anymore
// void MultiClientServer::handleNewConnection()
// {
//     cout << "MultiClientServer::handleNewConnection()" << endl;

//     while (hasPendingConnections())
//     {
//         QTcpSocket *client = nextPendingConnection();
//         connect (client, SIGNAL (disconnected()), this, SLOT(clientDisconnected()));
//         this->clientConnections.append(qobject_cast<QSslSocket *>(client));

//         qDebug() << "new client connected";
//         qDebug() << "clients logged in: " << clientConnections.length();

//         this->sendHello(qobject_cast<QSslSocket *>(client));
//     }
// }

////////////////////////////////////////////////////////////
//
void MultiClientServer::clientDisconnected()
{
    cout << "MultiClientServer::clientDisconnected()" << endl;

//  QTcpSocket *client = qobject_cast<QTcpSocket *> (sender());
    QSslSocket *client = qobject_cast<QSslSocket *> (sender());
    if (!client)
        return;

    clientConnections.removeAll(client);

    qDebug() << "client disconnected";
    qDebug() << "number of clients: " << clientConnections.length() << endl;

    client->deleteLater();
}

////////////////////////////////////////////////////////////
//
void MultiClientServer::sendHello(QSslSocket *client_)
{
    if (!client_)
        return;

    client_->write("Hello \n");
}

////////////////////////////////////////////////////////////
//
void MultiClientServer::sendMessageToAllClients()
{
//    cout << "MultiClientServer::sendMessageToAllClients()" << endl;

    QString message = QString ("The current time is: %1\n").arg(QTime::currentTime().toString ("hh:mm:ss"));

    foreach (QSslSocket *client, clientConnections)
    {
        client->write (message.toLatin1());
//        cout << ".";
    }
//    cout << endl;
//    cout << "nr of clients: " << clientConnections.length() << endl;

}

////////////////////////////////////////////////////////////
//
void MultiClientServer::incomingConnection(int socketDescriptor)
{
    cout << "MultiClientServer::incomingConnection, sd = " << socketDescriptor << endl;

    QSslSocket *serverSocket = new QSslSocket;
    if (serverSocket->setSocketDescriptor(socketDescriptor))
    {
        connect(serverSocket, SIGNAL(encrypted()), this, SLOT(ready()));
        cout << "will start server encryption now...";

        serverSocket->setLocalCertificate("/home/dumitrus/dumcert.pem");
        serverSocket->setPrivateKey("/home/dumitrus/dumcert.pem");

        serverSocket->startServerEncryption();
        cout << " done." << endl;
//        cout << "waiting for encryption...";
//        serverSocket->ignoreSslErrors();
    }
    else
    {
        delete serverSocket;
    }
}

////////////////////////////////////////////////////////////
//
void MultiClientServer::ready()
{
    cout << "MultiClientServer::ready()" << endl;
//    sendMessageToAllClients();
    QSslSocket *client = qobject_cast<QSslSocket *> (sender());

    connect (client, SIGNAL (disconnected()), this, SLOT(clientDisconnected()));
    this->clientConnections.append(qobject_cast<QSslSocket *>(client));

    qDebug() << "new client connected";
    qDebug() << "clients logged in: " << clientConnections.length();
    this->sendHello(qobject_cast<QSslSocket *>(client));
}
