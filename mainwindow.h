#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>

#include "worker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    //void on_computeButton_clicked();

private slots:
    void on_computeButton_clicked();

    //void computationStarted();
    void computationFinished(int value);
    void progressUpdated(int item, int numberOfItems);

private:
    Ui::MainWindow *ui;

    QThread *m_thread;
    Worker *m_worker;


};
#endif // MAINWINDOW_H
