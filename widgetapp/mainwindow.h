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

    int initctx();
public Q_SLOTS:
    void read();

    void start_stop();

private:
    Ui::MainWindow *ui;
    void calculateRP(float x, float y, float z, float *roll, float *pitch);
    QTimer *timer;
    bool start;


};
#endif // MAINWINDOW_H
