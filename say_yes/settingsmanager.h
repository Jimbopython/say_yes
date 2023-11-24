#pragma once

#include <QSettings>
#include <QObject>

class SettingsManager : public QObject
{
    Q_OBJECT
public:
    SettingsManager() = default;

    bool alreadyChoseOnce();
    Q_INVOKABLE void setChosen(bool choice);
    Q_INVOKABLE QString getChoice();
private:
    QSettings settings{};
};
