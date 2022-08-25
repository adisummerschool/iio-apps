#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <stdio.h>
#include <iio.h>
#include<QTimer>
#include<math.h>

#define URI "ip:10.76.84.212"
#define DEVICE_NAME "ad5592r"

struct iio_context *ctx = NULL;
struct iio_device *dev = NULL;
struct iio_channel *chan[4];
bool start;

int MainWindow::init_ctx() {
    QTextEdit *t = ui->txt_status;
    QString result;

    ctx = iio_create_context_from_uri(URI);
    if(ctx == NULL) {
        result.sprintf("No context");
        t->append(result);
        return -1;
    }

    dev = iio_context_find_device(ctx, DEVICE_NAME);
    if(dev == NULL) {
        result.sprintf("No device");
        t->append(result);
        return -1;
    }
    result.sprintf("Got device %s %lx", DEVICE_NAME, dev);
    t->append(result);

    int nr_chan;
    nr_chan = iio_device_get_channels_count(dev);
    result.sprintf("IIO device has %u channels:", nr_chan);
    t->append(result);

    for (int i=0; i < nr_chan; i++) {

        chan[i] = iio_device_get_channel(dev, i);
        if(chan[i] == NULL) {
            result.sprintf("Channel not found");
            t->append(result);
            return -1;
        }
        result.sprintf("Got channel %s %lx", iio_channel_get_id(chan[i]), chan[i]);
        t->append(result);
    }
}
void MainWindow::calculateRP(float x, float y, float z, float *roll, float *pitch){
    int sign = z>0 ? 1 : -1;

    *roll  = atan2( y,   sign *  sqrt(z*z + x*x));
    *pitch = asin( x / sqrt( pow(x,2) + pow(y,2) + pow(z,2) ));

    *pitch = *pitch * (180.0/M_PI);
    *roll = *roll * (180.0/M_PI) ;
}



void MainWindow::read() {
    int values[4];
    for (int i=0; i < 4; i++) {
               char *buf;
               buf = (char*)malloc(10);
               iio_channel_attr_read(chan[i], "raw", buf, 10);
               values[i] = atoi(buf);
               free(buf);
    }

   int x = values[0] - values[1];
   int y = values[2] - values[3];

   int z = 4096 - abs(x)- abs(y);

   float r,p;
   calculateRP((float)y,(float)x,(float)z,&r,&p);

   ui->lblX->setText(QString::number(x));
   ui->lblY->setText(QString::number(y));
   ui->lblZ->setText(QString::number(z));

   ui->AI->setPitch(p);
   ui->AI->setRoll(r);
   ui->AI->redraw();


   qDebug("x = %4d\ty = %4d\n", x, y);

}

void MainWindow::start_stop(){

    if(start){
        ui->btnRead->setText("Start");
        timer->stop();
    }
    else{

        timer->start(100);
        ui->btnRead->setText("Stop");
    }
     start = !start;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    timer = new QTimer(this);
    ui->setupUi(this);
    init_ctx();
    read();
    connect(ui->btnRead, SIGNAL(clicked()), this, SLOT(start_stop()));
    connect(timer, SIGNAL(timeout()), this, SLOT(read()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
