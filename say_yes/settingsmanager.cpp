#include "settingsmanager.h"


bool SettingsManager::alreadyChoseOnce()
{
#ifdef NDEBUG
    return settings.value("chosen", false).toBool();
#else
    return false;
#endif
}

void SettingsManager::setChosen(bool choice)
{
    settings.setValue("chosen", true);
    settings.setValue("choice", choice);
}

QString SettingsManager::getChoice()
{
    const auto choice = settings.value("choice", false).toBool();
    return choice ? "YES" : "NO";
}
