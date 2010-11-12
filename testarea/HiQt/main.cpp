#include <QtCore>
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
	
    qDebug() << "hi qt";

    return a.exec();
}
