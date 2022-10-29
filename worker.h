#ifndef WORKER_H
#define WORKER_H

#include <QObject>


/* Hint:
 * worker class is not derived from QThread
 * but have to be derived from QObject!
*/

class Worker : public QObject
{   
    Q_OBJECT
public:
    // Worker(); => Standard CTOR
    explicit Worker(QObject *parent = nullptr);

signals:
    void valueComputed(int value);
    void progressUpdated(int item, int itemCount);

private slots:
    void testEvent();

public:
    void computeSomething(int value);
    Q_INVOKABLE void computeFactorial(int value);
};

#endif // WORKER_H
