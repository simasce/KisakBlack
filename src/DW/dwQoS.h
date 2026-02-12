#pragma once

#include <DemonWare/bdCore/bdReference/bdReferencable.h>
#include <DemonWare/bdCore/bdSocket/bdAddr.h>
#include <client_mp/cl_main_mp.h>

struct bdQoSRemoteAddr // sizeof=0x1C
{                                       // XREF: dwQoSMultiProbeListener/r
                                        // ?addProbe@dwQoSMultiProbeListener@@QAEXVbdQoSRemoteAddr@@@Z/r ...
    bdReference<bdCommonAddr> m_addr;
    bdSecurityID m_id;                  // XREF: dwQoSMultiProbeListener::addProbe(bdQoSRemoteAddr)+6C/r
                                        // dwQoSMultiProbeListener::addProbe(bdQoSRemoteAddr)+6F/r
    bdSecurityKey m_key;                // XREF: dwQoSMultiProbeListener::addProbe(bdQoSRemoteAddr)+7B/o
};

struct bdQoSProbeListener // sizeof=0x4
{                                       // XREF: dwQoSMultiProbeListener/r
    //bdQoSProbeListener_vtbl *__vftable;

    virtual ~bdQoSProbeListener() = default;
};

const struct bdQoSProbeInfo // sizeof=0x24
{                                       // XREF: dwQoSMultiProbeListener/r
    bdReference<bdCommonAddr> m_addr;
    bdAddr m_realAddr;
    float m_latency;
    unsigned __int8 *m_data;
    unsigned int m_dataSize;
    bool m_disabled;
    // padding byte
    // padding byte
    // padding byte
    unsigned int m_bandwidthDown;
    unsigned int m_bandwidthUp;
};

struct dwQoSMultiProbeListener : bdQoSProbeListener // sizeof=0x8EA4
{                                       // XREF: .data:s_qoslistener/r
    bdQoSRemoteAddr m_probeAddrs[500];
    bool m_probeSucceeded[500];
    unsigned int m_numProbes;
    bdQoSProbeInfo m_successes[500];
    bdSecurityID m_successIDs[500];
    unsigned int m_numSuccesses;
    unsigned int m_numFailures;

    dwQoSMultiProbeListener();
    ~dwQoSMultiProbeListener() = default;

    void addProbe(bdQoSRemoteAddr addr);
    void onQoSProbeSuccess(const bdQoSProbeInfo *info);
    void onQoSProbeFail(bdReference<bdCommonAddr> addr);
    void clean();
    int  complete();
};



bdQoSProbeInfo *__thiscall bdQoSProbeInfo::operator=(bdQoSProbeInfo *this, const bdQoSProbeInfo *__that);

bdQoSRemoteAddr *__thiscall bdQoSRemoteAddr::bdQoSRemoteAddr(bdQoSRemoteAddr *this, const bdQoSRemoteAddr *__that);
void __cdecl dwStartQoSProbes(dwQoSMultiProbeListener *listener, unsigned int numProbes, bdQoSRemoteAddr *serverAddrs);
void __cdecl dwClearQoSProbes();
void __thiscall bdReference<bdCommonAddr>::operator=(bdReference<bdRemoteTask> *this, bdRemoteTask *p);
