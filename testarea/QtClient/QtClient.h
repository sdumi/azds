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
 * |          | 22.11.2010 | dumi       | cleanup: remove some unused signals
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

    bool start (QString address, quint16 port, QString certificatePath);

protected slots:
    void clientConnected ();
    void showError ();
    void ready();
    // handle the signal: QSslSocket.sslErrors()
    void errorOccured(const QList<QSslError> &error);

private:
    int port;
    QSslSocket *client;
};

#endif /* QTCLIENT_H_ */
