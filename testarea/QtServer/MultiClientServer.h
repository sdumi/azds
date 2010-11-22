/*
 * MultiClientServer.h
 *
 *  Created on: Oct 22, 2010
 *      Author: dpomian
 *
 * -----------------------------------------------------------------------------
 * | Release  | Date       | Name       | History
 * -----------------------------------------------------------------------------
 * | 0.001    | 22.11.2010 | dumi       | introduce SSL on server side
 * -----------------------------------------------------------------------------
 *
 */

#ifndef MULTICLIENTSERVER_H_
#define MULTICLIENTSERVER_H_

#include <QtNetwork>

class MultiClientServer : public QTcpServer
{
  Q_OBJECT

protected:
  void sendHello (QSslSocket *client);

  // DS: need this to create QSslSockets...
  void incomingConnection(int socketDescriptor);

protected slots:
//  void handleNewConnection ();
  void clientDisconnected ();
  void sendMessageToAllClients();
  void ready();

private:
  int _PORT_;
//  QList <QTcpSocket *> clientConnections;
  QList <QSslSocket *> clientConnections;
  QTimer messageTimer;

public:
  MultiClientServer(int port_);
  ~MultiClientServer();

  void start();
  void stop();
};

#endif /* MULTICLIENTSERVER_H_ */
