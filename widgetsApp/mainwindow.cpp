#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <iio.h>
#include <QtConcurrentRun>
#include "qpainter.h"
#include <QPaintEvent>

#define GOOD_TRSH 50
#define SLIGHT_TRSH 500

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ctx = NULL;
	device = NULL;

	ui->progressBar->setRange(-4096, 4096);
	ui->progressBar_2->setRange(-4096, 4096);
	ui->progressBar_3->setRange(-4096, 4096);

	QFuture<void> future = QtConcurrent::run(std::mem_fn(&MainWindow::start), this);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
	if (!(x > -5000 && x < 5000 && y >  -5000 && y < 5000)) return;
	QWidget::paintEvent(event);

	QPainter p(this);
	p.setBrush(Qt::green);

	int w = 20;
	int h = 20;
	QRect r(0,0,w, h);
	QRect l(0,0,0.5,700);
	QRect l2(0,0,650,0.5);

	long long temp_x = 0.08 * (x + 4095) + 28;
	long long temp_y = -0.08 * (y - 4095) - 5;
	qDebug() << temp_x << " " << temp_y << '\n';

	r.moveCenter(QPoint(temp_x,temp_y));
	l.moveCenter(QPoint(355,350));
	l2.moveCenter(QPoint(350,325));

	p.drawEllipse(l);
	p.drawEllipse(l2);
	p.drawEllipse(r);
}

void MainWindow::start()
{
	ctx = iio_create_context_from_uri("ip:10.76.84.217");
	if (ctx == NULL) {
		printf("No context\n");
		return;
	}

	device = iio_context_find_device(ctx, "ad5592r");
	if (device == NULL) {
		printf("No device\n");
		return ;
	}

	struct iio_channel  *chan;
	bool x_ok = false, y_ok = false;

	while (1) {
		x_ok = 0;
		y_ok = 0;
		long long values[4];

		for(int i =0;i < 4; i++) {
			chan = iio_device_get_channel(device, i);
			iio_channel_attr_read_longlong(chan, "raw", &values[i]);
		}

		x = values[0] - values[1];
		y = values[2] - values[3];

		Q_EMIT ui->progressBar->setValue(x);
		Q_EMIT ui->progressBar_2->setValue(y);
		Q_EMIT ui->progressBar_3->setValue(y);

		if(x < GOOD_TRSH && x > -GOOD_TRSH) {
			x_ok = true;
		}

		if(y < GOOD_TRSH && y > -GOOD_TRSH) {
			y_ok = true;
		}

		Q_EMIT repaint();
	}

}

MainWindow::~MainWindow()
{
	delete ui;
}

