#include <stdio.h>
#include <iio.h>
#include <QTimer>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <math.h>

struct iio_context *ctx;
struct iio_device *dev;
struct iio_channel *ch[4];

#define URI "ip:10.76.84.219"
#define DEV_NAME "iio-ad5592r"

#define ATTR_NAME_RAW "raw"

void MainWindow::init_ctx() {
    QString result;

    ctx = iio_create_context_from_uri(URI);
    if (ctx == 0) {
        result.sprintf("error no context found\n");
        ui->txtStatus->setText(result);
        return;
    }

    dev = iio_context_find_device(ctx, DEV_NAME);
    if (dev == 0) {
        result.sprintf("error no device found\n");
        ui->txtStatus->setText(result);
        return;
    }
    printf("device %s found\n", DEV_NAME);

    int nr_device_channels = iio_device_get_channels_count(dev);

    for (int i = 0; i < nr_device_channels; i++) {
        ch[i] = iio_device_get_channel(dev, i);
    }
}

void MainWindow::calculateRP(float x, float y, float z, float *roll, float *pitch) {
    int sign = z>0 ? 1 : -1;

    *roll  = atan2( y,   sign *  sqrt(z*z + x*x));
    *pitch = asin( x / sqrt( pow(x,2) + pow(y,2) + pow(z,2) ));

    *pitch = *pitch * (180.0/M_PI);
    *roll = *roll * (180.0/M_PI) ;
}

void MainWindow::read() {
    int data[4];
    for (int i = 0; i < 4; i++) {
        char buf[10];
        iio_channel_attr_read(ch[i], ATTR_NAME_RAW, buf, 10);
        data[i] = atoi(buf);
    }
    int y = data[0] - data[1];
    int x = data[2] - data[3];

    int z = 9.8;

    float r, p;

    calculateRP(x, y, z, &r, &p);

    ui->lbX->setText(QString::number(x));
    ui->lbY->setText(QString::number(y));
    ui->lbZ->setText(QString::number(z));
    ui->AI->setPitch(p);
    ui->AI->setRoll(r);
    ui->AI->redraw();

    qDebug("x = %5d\ty = %5d\n", x, y);
}

void MainWindow::startTimer() {
    timer->start();
}

void MainWindow::stopTimer() {
    timer->stop();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_ctx();

//    connect(ui->btnRead, &QPushButton::pressed, this, &MainWindow::read);

//    connect(ui->btnRead, SIGNAL(clicked()), this, SLOT(read()));

    timer = new QTimer(0);
    timer->setInterval(500);
    connect(timer, &QTimer::timeout, this, &MainWindow::read);

    connect(ui->btnRead, SIGNAL(clicked()), this, SLOT(startTimer()));
    connect(ui->btnReadStop, SIGNAL(clicked()), this, SLOT(stopTimer()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

