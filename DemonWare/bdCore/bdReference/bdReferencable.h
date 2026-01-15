#pragma once


template <typename T>
struct bdReference//<bdByteBuffer> // sizeof=0x4
{                                                                             // XREF: bdRemoteTask/r
    T *m_ptr;
};

struct bdReferencable // sizeof=0x8
{                                                                             // XREF: bdByteBuffer/r
    volatile int m_refCount;

    virtual ~bdReferencable();
};