/*
 * QtClient.h
 *
 *  Created on: Oct 22, 2010
 *      Author: dpomian
 *
 * -----------------------------------------------------------------------------
 * | Release  | Date       | Name       | History
 * -----------------------------------------------------------------------------
 * | 0.001    | 21.11.2010 | dumi       | introduce SSL on client side
 * -----------------------------------------------------------------------------
 */

#ifndef QTCLIENT_H_
#define QTCLIENT_H_

#include <QtNetwork>
#include <QSslSocket>

class QtClient : public QObject
{
    Q_OBJECT

public:
    QtClient ();
    ~QtClient();

    bool start (QString address, quint16 port);

protected slots:
    void clientConnected ();
    void read ();
    void showError ();
    void ready();
    // handle the signal: QSslSocket.sslErrors()
    void errorOccured(const QList<QSslError> &error);
private:
    int port;
    QSslSocket *client;

};

#endif /* QTCLIENT_H_ */
