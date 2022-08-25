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
	void start();

private:
	Ui::MainWindow *ui;
	struct iio_context *ctx;
	struct iio_device  *device;
	void paintEvent(QPaintEvent *event);

	long long x, y;
};
#endif // MAINWINDOW_H
