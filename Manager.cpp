#include "Manager.h"

Manager::Manager(QObject *parent)
    : QObject{parent}
{}

Settings* Manager::settings()
{
    return &m_settings;
}
