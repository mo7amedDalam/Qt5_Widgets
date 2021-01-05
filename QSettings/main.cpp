#include <QCoreApplication>
#include <QDebug>
#include <QSettings>
#include <QStringList>


void saveNumbers(QSettings *setting,QString group, QString name, QList<int> numbers) {
    setting->beginGroup(group);
    setting->beginWriteArray(name);
//    foreach(auto nu, numbers){
//        setting->setValue("number",nu);
//    }
    setting->endArray();
    setting->endGroup();
}

//void getNumbers(QSettings *setting,QString group, QString name, QList<int> &numbers) {
//    setting->beginGroup(group);
//    if(!setting->contains(name)) {
//        qWarning() << "Does not contain list " << name << " in " << group;
//        setting->endGroup();
//    }
//    bool ok;
//    int combosize = setting->beginReadArray(name);
//    for (int i = 0;i < combosize; i++)
//    {
//       setting->setArrayIndex(i);
//       int value = setting->value("number").toInt(&ok);
//       if(!ok) {
//           qWarning() << "Failed to convert to int!!!";
//           setting->endArray();
//           setting->endGroup();
//       }
//       numbers.push_back(value);
//       setting->endArray();
//       setting->endGroup();
//    }
//}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Mohamed dalam");
    QCoreApplication::setApplicationName("QSettings");

    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

    QList<int> numbers;
    QList<int> numberSet;

    numberSet.push_back(5);
    numberSet.push_back(6);
    saveNumbers(&settings,"people","Bryan",numberSet);
    //getNumbers(&settings,"people","Bryan",numbers);

    //    foreach(auto nu, numbers){
    //        qInfo() << nu ;
    //    }

    return a.exec();
}
