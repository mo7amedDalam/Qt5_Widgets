#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->plainTextEdit);

    wire();
    setupStatusBar();
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
    updateStatusBar("New File");
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
    updateStatusBar(fileName);
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
    updateStatusBar(fileName);
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
    int pos = cursor.position();
    cursor.clearSelection();
    cursor.setPosition(pos,QTextCursor::MoveMode::KeepAnchor);
    ui->plainTextEdit->setTextCursor(cursor);
}


void MainWindow::on_actionToolbar_top_triggered()
{
    addToolBar(Qt::ToolBarArea::TopToolBarArea,ui->toolBar);
}

void MainWindow::on_actionToolbar_bottom_triggered()
{
    addToolBar(Qt::ToolBarArea::BottomToolBarArea,ui->toolBar);

}

void MainWindow::on_actionToolbar_left_triggered()
{
    addToolBar(Qt::ToolBarArea::LeftToolBarArea,ui->toolBar);

}

void MainWindow::on_actionToolbar_right_triggered()
{
    addToolBar(Qt::ToolBarArea::RightToolBarArea,ui->toolBar);

}

void MainWindow::on_actionToolbar_floatable_toggled(bool arg1)
{
    ui->toolBar->setFloatable(arg1);
}

void MainWindow::on_actionToolbar_movable_toggled(bool arg1)
{
    ui->toolBar->setMovable(arg1);
}

void MainWindow::setupStatusBar()
{
    QLabel *lblIcon = new QLabel(this);
    lblIcon->setPixmap(QPixmap(":/files/images/new.png"));
    ui->statusbar->addWidget(lblIcon);

    QLabel *lblStatus = new QLabel(this);
    lblStatus->setText("Not Saved:");
    ui->statusbar->addWidget(lblStatus);

    QLabel *lblFile = new QLabel(this);
    lblFile->setText("New");
    ui->statusbar->addWidget(lblFile);
}

void MainWindow::updateStatusBar(QString msg)
{
    foreach(QObject* obj, ui->statusbar->children())
       {
           qDebug() << obj;
       }

    QLabel *lblIcon = qobject_cast<QLabel*>(ui->statusbar->children().at(1));
    QLabel *lblStaus = qobject_cast<QLabel*>(ui->statusbar->children().at(2));
    QLabel *lblFile = qobject_cast<QLabel*>(ui->statusbar->children().at(4));

    if(saved)
    {
        lblIcon->setPixmap(QPixmap(":/files/images/save.png"));
        lblStaus->setText("Saved:");
    }
    else
    {
        lblIcon->setPixmap(QPixmap(":/files/images/new.png"));
        lblStaus->setText("Not Saved:");
    }

    lblFile->setText(fileName);
}


void MainWindow::on_plainTextEdit_textChanged()
{
    saved = false;
    if(fileName.isEmpty()){
        updateStatusBar("New File");
    }
    else {
        updateStatusBar(fileName);
    }
}
