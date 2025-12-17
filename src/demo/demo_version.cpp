#include "demo_version.h"
#include "demo_common.h"
#include <qcommon/common.h>

const NetFieldList s_demoOtherNetFieldList_Base[6] =
{
  { &archivedEntityFields, 8u, "archivedEntityFields" },
  { &clientStateFields, 50u, "clientStateFields" },
  { &demoPlayerStateFields, 176u, "demoPlayerStateFields" },
  { &objectiveFields, 9u, "objectiveFields" },
  { &hudElemFields, 43u, "hudElemFields" },
  { &matchStateFields, 15u, "matchStateFields" }
};

const NetFieldList s_demoEntityNetFieldList_Base[22] =
{
  { &entityStateFields, 69u, "entityStateFields" },
  { &playerEntityStateFields, 74u, "playerEntityStateFields" },
  { &corpseEntityStateFields, 68u, "corpseEntityStateFields" },
  { &itemEntityStateFields, 69u, "itemEntityStateFields" },
  { &missileEntityStateFields, 69u, "missileEntityStateFields" },
  { &entityStateFields, 69u, "entityStateFields" },
  { &scriptMoverStateFields, 72u, "scriptMoverStateFields" },
  { &soundBlendEntityStateFields, 68u, "soundBlendEntityStateFields" },
  { &fxStateFields, 68u, "fxStateFields" },
  { &loopFxEntityStateFields, 69u, "loopFxEntityStateFields" },
  { &entityStateFields, 69u, "entityStateFields" },
  { &turretEntityStateFields, 69u, "turretEntityStateFields" },
  { &helicopterEntityStateFields, 71u, "helicopterEntityStateFields" },
  { &planeStateFields, 66u, "planeStateFields" },
  { &vehicleEntityStateFields, 71u, "vehicleEntityStateFields" },
  { &entityStateFields, 69u, "entityStateFields" },
  { &entityStateFields, 69u, "entityStateFields" },
  { &actorStateFields, 69u, "actorStateFields" },
  { &actorStateFields, 69u, "actorStateFields" },
  { &actorStateFields, 69u, "actorStateFields" },
  { &entityStateFields, 69u, "entityStateFields" },
  { &eventEntityStateFields, 69u, "eventEntityStateFields" }
};

const NetFieldList *s_demoOtherNetFieldLists[] = { s_demoOtherNetFieldList_Base };
const NetFieldList *s_demoEntityNetFieldLists[] = { s_demoEntityNetFieldList_Base };


int __cdecl Demo_GetVersion()
{
    if ( Demo_IsIdle() )
        Com_Error(ERR_DROP, "Trying to get version of a demo when the demo system is idle.");
    return demo.header.version;
}

const NetFieldList *__cdecl Demo_GetNetFieldListForType(netFieldTypes_t fieldType)
{
    int netFieldsVersionIndex; // [esp+0h] [ebp-8h]

    netFieldsVersionIndex = 1 - Demo_GetVersion();
    if ( netFieldsVersionIndex < 0 )
        Com_Error(ERR_DROP, "Invalid Version Handling. Grab Bat !!!");
    return &s_demoOtherNetFieldLists[netFieldsVersionIndex][fieldType];
}

const NetFieldList *__cdecl Demo_GetStateFieldListForEntityType(int eType)
{
    int v2; // [esp+0h] [ebp-Ch]
    int netFieldsVersionIndex; // [esp+4h] [ebp-8h]

    netFieldsVersionIndex = 1 - Demo_GetVersion();
    if ( netFieldsVersionIndex < 0 )
        Com_Error(ERR_DROP, "Invalid Version Handling. Grab Bat !!!");
    if ( eType > 21 )
        v2 = 21;
    else
        v2 = eType;
    return &s_demoEntityNetFieldLists[netFieldsVersionIndex][v2];
}

