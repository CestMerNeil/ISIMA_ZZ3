#pragma once

#include <iostream>

class DeviceObserver
{
private:
    int notificationCount;

public:
    DeviceObserver() : notificationCount(0) {}

    void update(const std::string &message)
    {
        notificationCount++;
        std::cout << message << std::endl;
    }

    inline int getNotificationCount() const { return notificationCount; }
};