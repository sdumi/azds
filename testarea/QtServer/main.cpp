#include <QtCore>
#include <QCoreApplication>
#include <QDebug>
#include "MultiClientServer.h"

/* displays usage */
void usage ()
{
    qDebug() << "Usage:";
    qDebug() << "\tQtServer <port> <ssl_certificatePath>";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc < 3)
    {
        qDebug() << "insufficient arguments";
        usage();
        exit(0);
    }

    if (argc > 3)
    {
        qDebug() << "too many arguments";
        usage();
        exit(0);
    }

    QString option (argv[1]);
    if (option == "--help" || option == "/?")
    {
        usage();
        exit(0);
    }

    bool ok;
    int port = option.toInt (&ok, 10);
    if (!ok)
    {
        qDebug() << "invalid port!!";
        exit(0);
    }


    MultiClientServer *server = new MultiClientServer (port, argv[2]);
    server->start();

    return a.exec();
}
