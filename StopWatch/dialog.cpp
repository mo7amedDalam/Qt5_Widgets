#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QPushButton *btnStart = new QPushButton("Start", this);
    QPushButton *btnStop = new QPushButton("Stop", this);

    ui->buttonBox->addButton(btnStart,QDialogButtonBox::ButtonRole::ActionRole);
    ui->buttonBox->addButton(btnStop,QDialogButtonBox::ButtonRole::ActionRole);

    connect(btnStart,&QPushButton::clicked,this,&Dialog::start);
    connect(btnStop,&QPushButton::clicked,this,&Dialog::stop);

    timer.setInterval(100);
    connect(&timer,&QTimer::timeout,this,&Dialog::timeOut);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_buttonBox_accepted()
{
    accept();
}

void Dialog::timeOut()
{
    stoped = QTime::currentTime();

    qint64 time = started.msecsTo(stoped);
    qint64 h = time / 1000 / 60 /60;
    qint64 m = (time / 1000 / 60) - (h * 60);
    qint64 s = (time / 1000) - (m * 60);
    qint64 ms = time - (s + ((m + (h * 60))* 60)) * 1000;

    const QString diff = QString("%1:%2:%3:%4")
            .arg(h,2,10,QChar('0'))
            .arg(m,2,10,QChar('0'))
            .arg(s,2,10,QChar('0'))
            .arg(ms,4,10,QChar('0'));

    ui->label->setText(diff);
}

void Dialog::start()
{
    started = QTime::currentTime();
    timer.start();
}

void Dialog::stop()
{
    stoped = QTime::currentTime();
    timer.stop();
}
