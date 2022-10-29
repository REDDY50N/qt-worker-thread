#include "worker.h"
#include <QDebug>
#include <QThread>

/*
 * CTOR
 */
Worker::Worker(QObject *parent) : QObject(parent)
{
    // empty
}

void Worker::computeFactorial(int value)
{
    qDebug() << "Running thread" << QThread::currentThreadId();

    int result = 1;
    for(int i = 1; i <= value; i++)
    {
        emit progressUpdated(i-1, value);
        qDebug() << " Progress of " << QThread::currentThreadId() << " is " << i << "/" << value;

        if( QThread::currentThread()->isInterruptionRequested() )
        {
            qDebug() << "Interrupting now.";
            return;
        }

        QThread::sleep(1);

        result *= i;
    }
    qDebug() << "Thread" << QThread::currentThreadId() << "finished.";

    emit progressUpdated(value, value);
    emit valueComputed(result);
}

void Worker::testEvent()
{
    qDebug() << "Test Event occured! Thread-ID: " << QThread::currentThreadId();
}
