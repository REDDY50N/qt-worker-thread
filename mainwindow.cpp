#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QThread>
#include <QProgressBar>
#include <QTimer>
#include <QDebug>

#include "worker.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setRange(0, 100);

    m_thread = new QThread();
    m_worker = new Worker();

    // connect signals from worker obj with slots from MainWindow
    connect(m_worker, SIGNAL( valueComputed(int) ),       this, SLOT(computationFinished(int)));
    connect(m_worker, SIGNAL( progressUpdated(int,int) ), this, SLOT(progressUpdated(int,int)));

    // move worker object to new thread and start thread
    m_worker->moveToThread(m_thread);
    m_thread->start();

    qDebug() << "Main thread id is: " << QThread::currentThreadId();
}

MainWindow::~MainWindow()
{
    m_thread->requestInterruption();
    m_thread->quit();
    m_thread->wait();
    delete m_thread;
    delete m_worker;

    delete ui;
}

/*
 *  • Der Haupt-Thread besitzt einen Zeiger auf das Arbeitsobjekt.
 *  • Ein direktes Aufrufen einer Methode des Arbeitsobjekts würde den Haupt-Thread blockieren.
 *  • Daher erfolgt ein Aufruf über eine Queued Connection.
 *      - Der Aufruf wird in einer Event-Queue des Arbeits-Threads gespeichert.
 *      - Bei der nächsten Iteration der Event-Loop wird die entsprechende Methode aufgerufen und der Eintrag aus der Queue entfernt.
 *  • Verbindungen zwischen verschiedenen Threads werden automatisch über Queued Connections abgewickelt.
 *  • Will man eine Slot-Methode aufrufen, ist ein direkter Aufruf zu vermeiden (siehe oben). Stattdessen verwendet man QMetaObject::invokeMethod(...).
 *  s. Folie S. 27
 */
void MainWindow::on_computeButton_clicked()
{
    /* Deactivate button after click,
     * uncomment: multiple succeeding computations can be requested.
    */
    ui->computeButton->setEnabled(false);

    /*
     * call worker thread method: compute
     * method call of compute function moved to worker thread's event loop
     * method is executed when ressources are avaiable
    */
    QMetaObject::invokeMethod(m_worker, "computeFactorial",
                              Q_ARG( int, ui->inputValue->text().toInt() ));
}

/* 40:57 min */
void MainWindow::computationFinished(int value)
{
    ui->resultLabel->setNum(value);
    ui->computeButton->setEnabled(true);
}

void MainWindow::progressUpdated(int item, int numberOfItems)
{
    qDebug() << "Progressupdate" << item << numberOfItems;
    ui->progressBar->setValue( item / (double) numberOfItems * 100.0 );

}
