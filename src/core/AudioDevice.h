//
// Created by Andry on 2/11/21.
//
// LGPL if wont BSD write me.

#ifndef VLC_QT_AUDIODEVICE_H
#define VLC_QT_AUDIODEVICE_H

class VlcMediaPlayer;
class VlcInstance;

#include <vector>
#include <string>

struct DeviceInfo{
    std::string deviceName;
    std::string description;
};

class AudioDevice
{

public:
    AudioDevice(VlcMediaPlayer *vlcMediaPlayer);
    ~AudioDevice();
    std::vector<DeviceInfo> GetListDevice();
    void SetOutputDevice(std::string name);
    std::string GetCurrentDevice();

    std::vector<DeviceInfo> GetWtfList(VlcInstance *instance);
    void SetOutputWtf(std::string name);

private:
    VlcMediaPlayer *_vlcMediaPlayer;
};

#endif //VLC_QT_AUDIODEVICE_H
