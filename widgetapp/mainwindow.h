#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int init_ctx();

public Q_SLOTS:  //functii care pot fi chemate direct/slots
    void read();
    void start_stop();
    void calculateRP(float x, float y, float z, float *roll, float *pitch);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    bool start;
};
#endif // MAINWINDOW_H
