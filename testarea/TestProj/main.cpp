#include <QtCore>
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "yet another test project... :D";
	
    return a.exec();
}
