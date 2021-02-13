#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QImage>
#include <QString>
#include <QFileDialog>
#include <QDebug>
#include <QRgb>
#include <vector>
#include <QIntValidator>

static std::vector<QString> textPixel;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_label=new QLabel(ui->widget);
    QObject::connect(ui->pushButton_setImage,&QPushButton::clicked,this,&MainWindow::setImage);
    QIntValidator* iv=new QIntValidator(ui->lineEdit);
    iv->setRange(5,1080);
    ui->lineEdit->setValidator(iv);
    ui->lineEdit->setText("40");
    textPixel.push_back(QString::fromLocal8Bit("一"));
    textPixel.push_back(QString::fromLocal8Bit("乙"));
    textPixel.push_back(QString::fromLocal8Bit("大"));
    textPixel.push_back(QString::fromLocal8Bit("丙"));
    textPixel.push_back(QString::fromLocal8Bit("交"));
    textPixel.push_back(QString::fromLocal8Bit("羽"));
    textPixel.push_back(QString::fromLocal8Bit("拜"));
    textPixel.push_back(QString::fromLocal8Bit("慧"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setImage()
{
    int pix=ui->lineEdit->text().toInt();
    int t=static_cast<const QIntValidator*>(ui->lineEdit->validator())->bottom();
    if(t>pix)
    {
        pix=t;
        ui->lineEdit->setText(std::to_string(pix).data());
    }

    QString imgPath=QFileDialog::getOpenFileName(this,"Choose Image","","Image File(*.png *.jpg *.bmp)");
    if(imgPath.size()==0)
    {
        return;
    }
    ui->textBrowser->clear();
    QImage q(imgPath);
    m_label->resize(ui->widget->size());
    m_label->setPixmap(QPixmap::fromImage(q.scaled(m_label->size(),Qt::KeepAspectRatio)));
    m_label->show();

    q=q.convertToFormat(QImage::Format_Grayscale8);
    q=q.scaledToWidth(pix);
    q.invertPixels();
    for(int i=0;i<q.height();++i)
    {
        for(int j=0;j<q.width();++j)
        {
            ui->textBrowser->insertPlainText(textPixel[qRed(q.pixel(j,i))/32]);
            //qDebug()<<qRed(q.pixel(i,j));
        }
        ui->textBrowser->insertPlainText("\n");
    }

}
