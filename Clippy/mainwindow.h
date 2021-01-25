#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QClipboard>
#include <QStringListModel>
#include <QList>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveas_triggered();
    void on_actionStart_triggered();
    void on_actionStop_triggered();
    void on_actionCopy_triggered();
    void on_actionCut_triggered();
    void on_actionPaste_triggered();
    void on_actionDelete_triggered();
    void timeout();

private:
    Ui::MainWindow *ui;
    QTimer timer;
    QString last;
    QStringListModel model;
    QStringList list;
    QString path;
    bool changed;

    void init();
    void checkSaved();
};
#endif // MAINWINDOW_H
