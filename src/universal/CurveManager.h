#pragma once
#include "curve.h"

struct cCurveManager // sizeof=0x0
{
    int __cdecl GetFreeCurve();
    void __cdecl AddNodeToCurve(unsigned int curve, float *p);
    void __cdecl AddNodeToCurve(unsigned int curve, float *p, float t);
    void __cdecl SortCurve(unsigned int curve, float *p, bool is_increasing_sort_order);
    void __cdecl BuildCurve(unsigned int curve);
    void __cdecl FreeCurve(unsigned int curve);
    void __cdecl SetCurveBSpline(unsigned int curve);
    void __cdecl SetCurveDraw(unsigned int curve, const float *color);
    void __cdecl GetPos(unsigned int curve, float t, float *p);
    double __cdecl GetCurveLength(unsigned int curve);

    cCurve mCurves[4];
    int levelNotifyFunc;
};