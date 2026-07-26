#include "DayNightManager.h"

void DayNightManager::SetDay()
{
    state = TimeState::Day;
}

void DayNightManager::SetNight()
{
    state = TimeState::Night;
}

void DayNightManager::Toggle()
{
    if (state == TimeState::Day)
        state = TimeState::Night;
    else
        state = TimeState::Day;
}

bool DayNightManager::IsDay() const
{
    return state == TimeState::Day;
}

bool DayNightManager::IsNight() const
{
    return state == TimeState::Night;
}