//
// Created by Andry on 2/11/21.
//
// LGPL if wont BSD write me.

#include "core/MediaPlayer.h"
#include "core/Instance.h"
#include "AudioDevice.h"
#include <vlc/vlc.h>

//
//libvlc_audio_output_set

AudioDevice::AudioDevice(VlcMediaPlayer *vlcMediaPlayer):
                         _vlcMediaPlayer(vlcMediaPlayer) {}

AudioDevice::~AudioDevice()
{
}

/// libvlc_audio_output_device_enum
std::vector<DeviceInfo> AudioDevice::GetListDevice(){
    std::vector<DeviceInfo> result;
    auto mp = _vlcMediaPlayer->core();
    libvlc_audio_output_device_t *aouts = libvlc_audio_output_device_enum(mp);
    for (libvlc_audio_output_device_t *e = aouts; e != NULL; e = e->p_next)
    {
        auto temp = DeviceInfo() = {std::string(e->psz_device), std::string(e->psz_description)};
        result.push_back(temp);
    }
    libvlc_audio_output_device_list_release( aouts );
    return result;
}

/// libvlc_audio_output_device_get
std::string AudioDevice::GetCurrentDevice()
{
    auto temp = libvlc_audio_output_device_get(_vlcMediaPlayer->core());
    return std::string(temp);
}

/// libvlc_audio_output_device_set
void AudioDevice::SetOutputDevice(std::string name)
{
    auto mp = _vlcMediaPlayer->core();
    libvlc_audio_output_device_set( mp, NULL, name.c_str() );
}

/// result = "Dummy audio output" ,"HAL AudioUnit output","File audio output", "Audio memory output"
/// libvlc_audio_output_list_get
std::vector<DeviceInfo> AudioDevice::GetWtfList(VlcInstance *instance)
{
    std::vector<DeviceInfo> result;
    auto mp = instance->core();
    libvlc_audio_output_t *aouts = libvlc_audio_output_list_get(mp);
    for (libvlc_audio_output_t *e = aouts; e != NULL; e = e->p_next)
    {
        auto temp = DeviceInfo() = {std::string(e->psz_name), std::string(e->psz_description)};
        result.push_back(temp);
    }
    libvlc_audio_output_list_release( aouts );
    return result;
}

/// libvlc_audio_output_set
void AudioDevice::SetOutputWtf(std::string name)
{
    auto mp = _vlcMediaPlayer->core();
    libvlc_audio_output_set( mp, name.c_str() );
}
