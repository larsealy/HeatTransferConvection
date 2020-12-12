#ifndef MYSETTINGS_H
#define MYSETTINGS_H

#include <QDialog>

namespace Ui {
class MySettings;
}

class MySettings : public QDialog
{
    Q_OBJECT

public:
    explicit MySettings(QWidget *parent = nullptr);
    ~MySettings();

    QString getMinimumText();
    QString getMaximumText();

private:
    Ui::MySettings *ui;
};

#endif // MYSETTINGS_H
