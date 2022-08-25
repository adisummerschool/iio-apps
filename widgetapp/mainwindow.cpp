#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <stdio.h>
#include <iio.h>
#include <QDebug>
#include <math.h>
#include <qfi/qfi_AI.h>

struct iio_context *ctx = NULL; //def context
struct iio_device *dev = NULL; //def device
struct iio_channel *ch [4]; // def channel

bool start;

#define URI "ip:10.76.84.217"
#define DEVICE_NUME "ad5592r"

int MainWindow::init_ctx(){
    QTextEdit *t = ui->txtStatus;
    QString result;

    ctx = iio_create_context_from_uri("ip:10.76.84.217"); //context
             result.sprintf("%x\n", ctx);
              if(ctx == NULL){   // verificare conctarea placa
                  result.sprintf("No contex\n");
                  t->append(result);
                  return -1;
              }


    dev = iio_context_find_device(ctx, DEVICE_NUME); //afisare device
             if(dev == NULL){   // verificare conctarea placa
                 result.sprintf("No device\n");
                 t->append(result);
                 return -1;
             }
             result.sprintf("Go device %s %lx\n", DEVICE_NUME, dev);
             t->append(result);


    unsigned int chan_count = iio_device_get_channels_count(dev); //afisare canale
              for(int i = 0; i < chan_count; i++){
                  ch[i] = iio_device_get_channel(dev, i);
                  if(ch[i] == NULL){   // verificare conctarea channel
                      result.sprintf("Channel not found\n");
                      t->append(result);
                      return -1;
                  }
                  result.sprintf("Go channel %s %lx \n", iio_channel_get_id(ch[i]), ch[i]);
                  t->append(result);
              }



    return 0;
}

void MainWindow::calculateRP(float x, float y, float z, float *roll, float *pitch){
    int sign = z>0 ? 1 : -1;

    *roll  = atan2( y,   sign *  sqrt(z*z + x*x));
    *pitch = asin( x / sqrt( pow(x,2) + pow(y,2) + pow(z,2) ));

    *pitch = *pitch * (180.0/M_PI);
    *roll = *roll * (180.0/M_PI) ;
}


void MainWindow::read(){
    int values[4];  //citire x, y
    for(int i = 0; i<4 ;i++){
        char *buf;
        buf = (char*) malloc(10);
        iio_channel_attr_read(ch[i],"raw",buf, 10);
        values[i]= atoi(buf);
        free(buf);
    }
    int x=values[0]-values[1];
    int y=values[2]-values[3];
    int z= 4096 - abs(x)-abs(y);

    float r,p;
        calculateRP((float)x,(float)y,(float)z,&r,&p);

    ui->lblx->setText(QString::number(x)); //citire x,y in label
    ui->lbly->setText(QString::number(y));
    ui->lblz->setText(QString::number(z));

    ui->AI->setPitch(p);
    ui->AI->setRoll(r);
    ui->AI->redraw();


    qDebug("x=%5d       y=%5d\n",x,y);

}

void MainWindow::start_stop(){  //buton start/stop

    if(start){
        ui->btnRead->setText("Start");
        timer->stop();

    }
    else{
        timer->start(10);
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
    connect(ui->btnRead, SIGNAL(clicked()),this, SLOT(read()) );  //timer
    connect(ui->btnRead, SIGNAL(clicked()), this, SLOT(start_stop()));
        connect(timer, SIGNAL(timeout()), this, SLOT(read()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

