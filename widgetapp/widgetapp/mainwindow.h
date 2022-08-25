#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer *timer;

    void init_ctx();
    Q_SLOT
    void read();
    Q_SLOT
    void startTimer();
    Q_SLOT
    void stopTimer();

private:
    Ui::MainWindow *ui;
    void calculateRP(float x, float y, float z, float *roll, float *pitch);

};
#endif // MAINWINDOW_H
