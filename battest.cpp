#include <QtCore/QCoreApplication>
#include <QString>
#include <QDebug>

#include <iostream>
#include <vector>

#include <iproviderplugin.h>

#include "battest.hpp"

void print_int(QString const &name, QVariant const &value) {
    qDebug() << "Got " << name << "=" << value.toInt() << "\n";
}

void print_ulonglong(QString const &name, QVariant const &value) {
    qDebug() << "Got " << name << "=" << value.toULongLong() << "\n";
}

void print_bool(QString const &name, QVariant const &value) {
    qDebug() << "Got " << name << "=" << value.toBool() << "\n";
}

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
    Test lvl("Battery.ChargePercentage", print_int);
    Test bars("Battery.ChargeBars", print_int);
    Test timelow("Battery.TimeUntilLow", print_ulonglong);
    Test timefull("Battery.TimeUntilFull", print_ulonglong);
    Test ischg("Battery.IsCharging", print_bool);
    Test onbat("Battery.OnBattery", print_bool);
    Test lowbat("Battery.LowBattery", print_bool);
	return app.exec();
}
