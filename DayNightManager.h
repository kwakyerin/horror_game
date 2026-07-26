#pragma once

enum class TimeState
{
    Day,
    Night
};

class DayNightManager
{
public:
    void SetDay();
    void SetNight();

    void Toggle();

    bool IsDay() const;
    bool IsNight() const;

private:
    TimeState state = TimeState::Day;
};