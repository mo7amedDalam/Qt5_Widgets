#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QPushButton *button = new QPushButton("Edit",this);
    ui->buttonBox->addButton(button, QDialogButtonBox::ButtonRole::ActionRole);
    connect(button,&QPushButton::clicked,this,&Dialog::onEdit);

    mMusic.setArtist("Monir");
    mMusic.setAlbum("Younis");
    mMusic.setRelease(QDate(2008,1,1));
    mMusic.setNotes("I LOVE THIS SONG!");
    load();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::load()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->setReadOnly(true);

    QString data;
    data.append("Artist: " + mMusic.artist() + "\r\n");
    data.append("Album: " + mMusic.album() + "\r\n");
    data.append("Release: " + mMusic.release().toString() + "\r\n");
    data.append("Notes: " + mMusic.notes() + "\r\n");

    ui->plainTextEdit->setPlainText(data);
}


void Dialog::on_buttonBox_accepted()
{
    accept();
}

void Dialog::on_buttonBox_rejected()
{
    reject();
}

void Dialog::onEdit()
{
    Editor *editor = new Editor(this);
    editor->setMusic(mMusic);
    editor->exec();

    mMusic = editor->music();

    load();

    delete editor;
}
