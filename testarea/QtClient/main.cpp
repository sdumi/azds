#include <QtCore>
#include <QCoreApplication>
#include <QDebug>

#include "QtClient.h"

void usage()
{
    qDebug() << "Usage:";
    qDebug() << "\tQtClient <hostname> <port> <ssl_certificatePath>";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc < 4)
    {
        qDebug() << "Insufficient parameters!";
        usage();
        exit(0);
    }

    if (argc > 4)
    {
        qDebug() << "Too many arguments";
        usage();
        exit (0);
    }

    QString hostName (argv[1]);

    QString strPort (argv[2]);
    bool ok;
    int port = strPort.toInt(&ok, 10);

    if (!ok)
    {
        qDebug() << "Invalid port";
        exit (0);
    }

    QtClient *cl = new QtClient ();
    cl->start(hostName, port, argv[3]);


   return a.exec();
}
