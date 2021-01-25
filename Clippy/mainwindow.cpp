#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    setCentralWidget(ui->listView);
    changed = false;
    path = "";
    model.setStringList(list);
    ui->listView->setModel(&model);
    connect(&timer, &QTimer::timeout, this, &MainWindow::timeout);
    timer.setInterval(500);
    timer.start();
}

void MainWindow::on_actionNew_triggered()
{
    checkSaved();
    list.clear();
    path.clear();
    changed = false;
    model.setStringList(list);
}

void MainWindow::on_actionOpen_triggered()
{
    checkSaved();
    QString tmp;
    tmp = QFileDialog::getOpenFileName(this,"Open File");
    if(tmp.isEmpty()) return;

    path = tmp;
    path.clear();

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Error",file.errorString());
        return;
    }

    QTextStream stream(&file);
    while(!stream.atEnd())
    {
        list.append(stream.readLine());
    }

    file.close();
    changed = false;
    model.setStringList(list);
    ui->statusbar->showMessage("Opened",2000);
}

void MainWindow::on_actionSave_triggered()
{
    QFile file(path);
    if(path.isEmpty())
    {
        on_actionSaveas_triggered();
        return;
    }

    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this,"Error",file.errorString());
        return;
    }

    //QDataStream instead to load and save multi-line
    QTextStream stream(&file);
    foreach(QString line, list)
    {
        stream << line << "\r\n";
    }
    file.close();
    changed = false;
    ui->statusbar->showMessage("Saved",2000);
}

void MainWindow::on_actionSaveas_triggered()
{
    QString tmp = QFileDialog::getSaveFileName(this,"Save File");
    if(tmp.isEmpty()) return;

    path = tmp;
    on_actionSave_triggered();
}

void MainWindow::on_actionStart_triggered()
{
    timer.start();
    ui->statusbar->showMessage("Listening to the clipboard", 2000);
}

void MainWindow::on_actionStop_triggered()
{

    timer.stop();
    ui->statusbar->showMessage("Manual mode", 2000);
}

void MainWindow::on_actionCopy_triggered()
{
    QClipboard *clipboard = QApplication::clipboard();
    int index = ui->listView->currentIndex().row();

    clipboard->setText(list.at(index));
    ui->statusbar->showMessage("Copied", 2000);
}

void MainWindow::on_actionCut_triggered()
{
    QClipboard *clipboard = QApplication::clipboard();
    int index = ui->listView->currentIndex().row();

    clipboard->setText(list.at(index));
    list.removeAt(index);
    model.setStringList(list);
    changed = true;

    ui->statusbar->showMessage("Cutted", 2000);
}

void MainWindow::on_actionPaste_triggered()
{
    timeout();
}

void MainWindow::on_actionDelete_triggered()
{
    int index = ui->listView->currentIndex().row();
    list.removeAt(index);
    model.setStringList(list);
    changed = true;
    ui->statusbar->showMessage("Deleted", 2000);
}

void MainWindow::timeout()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    QString data = clipboard->text();
    if(data.compare(this->last))
    {
        last = data;
        qDebug() << "YES: " << last;
        if(!list.contains(last))
        {
            list.append(last);
            model.setStringList(list);
            changed = true;
            ui->statusbar->showMessage("Added form the clipboard",2000);
        }
    }
}

void MainWindow::checkSaved()
{
    if(!changed) return;
    QMessageBox::StandardButton btn = QMessageBox::question(this,"Save Changes?","Would like to save your  changes?");
    if(btn == QMessageBox::StandardButton::Yes) on_actionSave_triggered();
}
