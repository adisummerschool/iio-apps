#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <stdio.h>
#include <iio.h>
#include <unistd.h>
#include <math.h>

struct iio_context *ctx = NULL;
struct iio_device *dev = NULL;
struct iio_channel *ch[4];

#define URI         "ip:10.76.84.217"
#define DEVICE_NAME "ad5592r"

int MainWindow::init_ctx()
{
    ctx = iio_create_context_from_uri(URI);
    QString result;

    if(ctx == NULL)
    {
        result.sprintf("No context");
        ui->txtStatus->append(result);

        return -1;
    }

    const char *p;

    p = iio_context_get_attr_value(ctx, "hw_carrier");

    int nr_ctx_attrs;
    nr_ctx_attrs = iio_context_get_attrs_count(ctx);

    result.sprintf("%d context attributes found", nr_ctx_attrs);
    ui->txtStatus->append(result);

    int i;

    for(i = 0; i < nr_ctx_attrs; i++)
    {
        const char *name, *value;
        iio_context_get_attr(ctx, i, &name, &value);

        result.sprintf("ctxattr[%d] - name:%lx %s - value %lx %s", i, name, name, value, value);
        ui->txtStatus->append(result);
    }

    dev = iio_context_find_device(ctx, DEVICE_NAME);

    if(dev == NULL)
    {
        result.sprintf("No device");
        ui->txtStatus->append(result);

        return -2;
    }

    result.sprintf("Got device %s %lx", DEVICE_NAME, dev);
    ui->txtStatus->append(result);

    unsigned int chan_count = iio_device_get_channels_count(dev);

    int values[4];

    for(i = 0; i < chan_count; i++)
    {
        ch[i] = iio_device_get_channel(dev, i);

        if(ch[i] == NULL)
        {
            result.sprintf("Channel not found");
            ui->txtStatus->append(result);

            return -3;
        }

        result.sprintf("Got channel %s %lx", iio_channel_get_id(ch[i]), ch[i]);
        ui->txtStatus->append(result);
    }

    return 0;
}

void MainWindow::calculateRP(float x, float y, float z, float &roll, float &pitch){
    int sign = z>0 ? 1 : -1;

    roll  = atan2( y,   sign *  sqrt(z*z + x*x));
    pitch = asin( x / sqrt( pow(x,2) + pow(y,2) + pow(z,2) ));

    pitch = pitch * (180.0/M_PI);
    roll = roll * (180.0/M_PI) ;
}

void MainWindow::read()
{
    int i;
    int values[4];

    for(i = 0; i < 4; i++)
    {
        char *buf;
        buf = (char*) malloc(10);
        iio_channel_attr_read(ch[i], "raw", buf, 10);
        values[i] = atoi(buf);
        qDebug("The value: %lld\n", values[i]);
        free(buf);
    }

    int y = values[0] - values[1];
    int x = values[2] - values[3];
    int z = 4096 - abs(x) - abs(y);

    float r;
    float p;

    calculateRP((float) y, (float) x, (float) z, r, p);

    ui->lblX->setText(QString::number(x));
    ui->lblY->setText(QString::number(y));
    ui->lblZ->setText(QString::number(z));


    ui->AI->setPitch(p);
    ui->AI->setRoll(r);
    ui->AI->redraw();
}

void MainWindow::start_stop()
{
    if(start)
    {
        ui->btnRead->setText("Start");
        timer->stop();
    }
    else
    {
        timer->start();
        ui->btnRead->setText("Stop");
    }

    start = !start;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_ctx();
    read();
    timer = new QTimer(this);
    timer->setInterval(250);

    connect(ui->btnRead, SIGNAL(clicked()), this, SLOT(start_stop()));
    connect(timer, SIGNAL(timeout()), this, SLOT(read()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

