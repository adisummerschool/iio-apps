#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include    <stdio.h>
#include    <iio.h>
#include <QTextEdit>
#include <QTimer>
#include <math.h>
#include <QDebug>


struct iio_context *ctx = NULL;
struct iio_device  *dev = NULL;
struct iio_channel *chan[4];

#define URI "ip:10.76.84.219"
#define DEVICE_NAME "iio-ad5592r"

int MainWindow::initctx(){
    QTextEdit *t = ui->txtStatus;
    QString result;

    ctx = iio_create_context_from_uri("ip:10.76.84.219");
    if(ctx == NULL){
            result.sprintf("No context\n");
            t->append(result);
            return -1;
    }


   dev = iio_context_find_device(ctx, "iio-ad5592r");
   if(dev == NULL){
           result.sprintf("No device");
           t->append(result);
           return -1;
   }
   result.sprintf("Got device %s %lx", DEVICE_NAME , dev);
   t->append(result);



   unsigned int ch =  iio_device_get_channels_count(dev);
   if(ch == NULL){
           result.sprintf("No channels\n");
           t->append(result);
           return -1;
   }
   result.sprintf("Got %lx channels", ch);
   t->append(result);



   for (int i = 0; i < ch; i++){

       chan[i] = iio_device_get_channel(dev, i);
       if(chan[i] == NULL){
               result.sprintf("No channels found/n");
               t->append(result);
               return -1;
       }
       result.sprintf("Got channel %s %lx ", iio_channel_get_id(chan[i]), chan[i]);
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



void MainWindow::read(){
int value[4];

    for (int i = 0; i < 4; i++){
        char *buf;
        buf = (char *) malloc(10);
        iio_channel_attr_read(chan[i], "raw", buf, 10);
        value[i]= atoi(buf);
    }

    int x = value[0] - value[1];

    int y = value[2] - value[3];
    \
    int z = 9.8;

    float r,p;
    calculateRP((float)x,(float)y,(float)z,&r,&p);


    ui -> lblX ->setText(QString::number(x));
    ui -> lblY ->setText(QString::number(y));
    ui -> lblZ ->setText(QString::number(z));

    ui->AI->setPitch(p);
    ui->AI->setRoll(r);
    ui->AI->redraw();


    printf("x = %5d\ty = %5d\n", x, y);


}


void MainWindow::start_stop(){
    start = 1 - start;
    if(start){
        timer->start(10);
        ui->btnRead->setText("Stop");

    }
    else
    {

        ui->btnRead->setText("Start");
        timer->stop();
    }

}




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    timer = new QTimer(this);
    ui->setupUi(this);
    initctx();
    read();
    connect(ui->btnRead, SIGNAL(clicked()),this,SLOT(start_stop()));



    connect(timer, SIGNAL(timeout()), this, SLOT(read()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
