/*
 * Author:      S.R.
 * Date:        10/2022
 * Purpose:     Non GUI blocking worker thread architecture
 * Source:      https://www.youtube.com/watch?v=UeNNsgnAHbU
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qDebug() << "Main Thread started with: " << QThread::currentThreadId();

    MainWindow w;
    w.show();

    qDebug() << "Done!";

    return app.exec();
}
