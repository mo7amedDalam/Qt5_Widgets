#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    changed = false;
    path = "";
    newFile();
}

void MainWindow::on_actionNew_triggered()
{

}

void MainWindow::on_actionOpen_triggered()
{

}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionSave_as_triggered()
{

}

void MainWindow::on_actionExit_triggered()
{

}

void MainWindow::on_actionCopy_triggered()
{

}

void MainWindow::on_actionCut_triggered()
{

}

void MainWindow::on_actionPaste_triggered()
{

}

void MainWindow::on_actionFind_triggered()
{

}

void MainWindow::on_actionReplace_triggered()
{

}

void MainWindow::on_actionSelect_All_triggered()
{

}

void MainWindow::on_actionZoom_in_triggered()
{

}

void MainWindow::on_actionZoom_out_triggered()
{

}

void MainWindow::on_actionBold_triggered()
{


}

void MainWindow::on_actionItalic_triggered()
{

}

void MainWindow::on_actionUnderline_triggered()
{

}

void MainWindow::on_actionStrike_triggered()
{

}

void MainWindow::on_actionColor_triggered()
{

}

void MainWindow::on_actionFont_triggered()
{

}

void MainWindow::on_actionHelp_triggered()
{

}

void MainWindow::on_actionAbout_triggered()
{

}

void MainWindow::on_textEdit_textChanged()
{
    changed = true;
}

void MainWindow::newFile()
{

}

void MainWindow::openFile()
{

}

void MainWindow::saveFile(QString path)
{

}

void MainWindow::saveFileAs()
{

}

void MainWindow::checksave()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}
