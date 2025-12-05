#pragma once
#include <qcommon/msg_mp.h>
#include <bgame/bg_local.h>
#include <qcommon/net_chan_mp.h>

struct serverCommandsHeader_t
{
    int rover;
    int sequence;
    int sent;
};

struct serverCommands_s
{
    serverCommandsHeader_t header;
    char buf[8192];
    int commands[256];
};

struct client_t
{
    int state;
    serverCommands_s reliableCommands;
    usercmd_s lastUsercmd;
    struct gentity_s *gentity;
    playerState_s frames[1];
    netchan_t netchan;
};