#include "editor.h"
#include "ui_editor.h"

Editor::Editor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Editor)
{
    ui->setupUi(this);
}

Editor::~Editor()
{
    delete ui;
}

void Editor::on_buttonBox_accepted()
{
    mMusic.setAlbum(ui->txtAlbum->text());
    mMusic.setArtist(ui->txtArtist->text());
    mMusic.setNotes(ui->txtNotes->toPlainText());
    mMusic.setRelease(ui->deRelease->date());
    accept();
}

void Editor::on_buttonBox_rejected()
{
    reject();
}

Music Editor::music() const
{
    return mMusic;
}

void Editor::setMusic(const Music &music)
{
    mMusic = music;

    ui->txtArtist->setText(mMusic.artist());
    ui->txtAlbum->setText(mMusic.album());
    ui->txtNotes->setPlainText(mMusic.notes());
    ui->deRelease->setDate(mMusic.release());
}
