#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->plainTextEdit);

    wire();
    newFile();
    saved = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::wire(){
    connect(ui->actionNew,&QAction::triggered,this,&MainWindow::newFile);
    connect(ui->actionOpen,&QAction::triggered,this,&MainWindow::openFile);
    connect(ui->actionPaste,&QAction::triggered,this,&MainWindow::newFile);
    connect(ui->actionSave,&QAction::triggered,this,&MainWindow::saveFile);
    connect(ui->actionSave_as,&QAction::triggered,this,&MainWindow::saveFileAs);
    connect(ui->actionExit,&QAction::triggered,this,&MainWindow::close);
    connect(ui->actionCopy,&QAction::triggered,ui->plainTextEdit,&QPlainTextEdit::copy);
    connect(ui->actionCut,&QAction::triggered,ui->plainTextEdit,&QPlainTextEdit::cut);
    connect(ui->actionPaste,&QAction::triggered,ui->plainTextEdit,&QPlainTextEdit::paste);
    connect(ui->actionSelect_all,&QAction::triggered,ui->plainTextEdit,&QPlainTextEdit::selectAll);
    connect(ui->actionSelect_None,&QAction::triggered,this,&MainWindow::selectNone);
}

void MainWindow::newFile()
{
    ui->plainTextEdit->clear();
    fileName.clear();
    saved = {false};
    ui->statusbar->showMessage("New File");
}

void MainWindow::openFile()
{
    QString temp = QFileDialog::getOpenFileName(this,"Open File",QString(),"Text Files (*txt);;All Files (*,*)");

    if(temp.isEmpty()) return;

    fileName = temp;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        newFile();
        QMessageBox::critical(this,"Error", file.errorString());
        return;
    }
    QTextStream stream(&file);
    ui->plainTextEdit->setPlainText(stream.readAll());
    file.close();

    saved = {true};
    ui->statusbar->showMessage(fileName);
}

void MainWindow::saveFile()
{
    if(fileName.isEmpty())
    {
        saveFileAs();
        return;
    }

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this,"Error", file.errorString());
        return;
    }

    QTextStream stream(&file);
    stream << ui->plainTextEdit->toPlainText();
    file.close();

    saved = true;
    ui->statusbar->showMessage(fileName);
}

void MainWindow::saveFileAs()
{
    QString temp = QFileDialog::getSaveFileName(this,"Save File",QString(),"Text Files (*txt);;All Files (*,*)");
    if(temp.isEmpty()) return;
    fileName = temp;
    saveFile();
}

void MainWindow::selectNone()
{
    QTextCursor cursor = ui->plainTextEdit->textCursor();
    cursor.setPosition(0,QTextCursor::MoveMode::KeepAnchor);
    ui->plainTextEdit->setTextCursor(cursor);
}

