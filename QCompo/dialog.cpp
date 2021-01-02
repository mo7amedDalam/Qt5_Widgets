#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    init();
    load();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_ComInput_currentIndexChanged(int index)
{
    ui->LblOutput->setText(ui->ComInput->currentText());
}

void Dialog::on_BtnApply_clicked()
{
    QSettings settings("QCompo", "MyApp");
    settings.setValue("settings", ui->ComInput->currentIndex());

    QMessageBox::information(this,"Saved","Selection saved, please close and re-open the application");
}

void Dialog::init()
{
    ui->ComInput->setCurrentIndex(0);
    ui->LblOutput->setText(ui->ComInput->currentText());
}

void Dialog::load()
{
    QSettings settings("QCompo", "MyApp");
    QVariant value = settings.value("settings",0);

    bool ok;
    int index = value.toInt(&ok);
    if(!ok)
    {
        QMessageBox::critical(this,"Loading Error","Error loading selection!");
        return;
    }

    if(index < ui->ComInput->count())
    {
        ui->ComInput->setCurrentIndex(index);
    }
    else
    {
        ui->ComInput->setCurrentIndex(0);
    }
}
