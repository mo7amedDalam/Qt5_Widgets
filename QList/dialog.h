#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QSettings>
#include <QVariant>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_BtnAdd_clicked();

private:
    Ui::Dialog *ui;
    void init();
    void load();
    void save();
};
#endif // DIALOG_H
