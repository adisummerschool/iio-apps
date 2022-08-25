#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iio.h>
#include <QTimer>
#include <math.h>
#include <qfi/qfi_AI.h>

#define IP_ADDR "ip:10.76.84.219"
#define DEVICE_NAME "iio-ad5592r"
#define ATTR_RAW "raw"


struct iio_context *ctx   = NULL;
struct iio_device *dev = NULL;
int nr_of_channels;
struct iio_channel *chan[4];
bool start;

void MainWindow::init_ctx(){
    QTextEdit *t = ui->txtStatus;
    QString result;

    ctx = iio_create_context_from_uri(IP_ADDR);
    if (!ctx){
        result.sprintf("No context!\n");
        t->append(result);
        return;
    }
    result.sprintf("Context found!\n");
    t->append(result);



    dev = iio_context_find_device(ctx, DEVICE_NAME);
    if(!dev){
        result.sprintf("No device found!\n");
        t->append(result);
        return;
    }
    result.sprintf("Device found!\n");
    t->append(result);
    nr_of_channels = iio_device_get_channels_count(dev);
    for(int i = 0; i < nr_of_channels; i++){

        chan[i] = iio_device_get_channel(dev, i);
        if(!chan[i]){
            result.sprintf("No channels found!\n");
            t->append(result);
            return;
        }
    }

    ui->lblX->setText("X VALUE");
    ui->lblY->setText("Y VALUE");

}

void MainWindow::calculateRP(float x, float y, float z, float *roll, float *pitch){
    int sign = z>0 ? 1 : -1;

    *roll  = atan2( y,   sign *  sqrt(z*z + x*x));
    *pitch = asin( x / sqrt( pow(x,2) + pow(y,2) + pow(z,2) ));

    *pitch = *pitch * (180.0/M_PI);
    *roll = *roll * (180.0/M_PI) ;
}
void MainWindow::read(){
    if(start){
        int raw_data[nr_of_channels];
        for(int i = 0; i < nr_of_channels; i++){
            char buf[10];
            iio_channel_attr_read(chan[i], ATTR_RAW, buf, 10);
            raw_data[i]=atoi(buf);

        }
        int x = raw_data[0]-raw_data[1];
        int y = raw_data[2]-raw_data[3];
        int z=4096-abs(x-y);


        ui->lblX->setText(QString::number(x));
        ui->lblY->setText(QString::number(y));
        ui->lblY->setText(QString::number(z));


        float r,p;
        calculateRP((float)y,(float)x,(float)z,&r,&p);
        ui->AI->setPitch(p);
        ui->AI->setRoll(r);
        ui->AI->redraw();


        qDebug("\nx = %5d\ty = %5d\n", x, y);
    }

}

void MainWindow::start_stop(){
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

