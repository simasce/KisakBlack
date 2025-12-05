#pragma once
#include <live/live_storage.h>

struct __declspec(align(4)) dwFileTask // sizeof=0xE0
{                                       // XREF: .data:s_fetchPlaylistsFileTask/r
                                        // dwFileOperationInfo/r
    dwFileTask();

    char *m_filename;                   // XREF: SV_AP_GetControlFile(void)+31/w
    // LiveStorage_FetchOnlineWAD(int)+16A/w
    bdFileData m_fileData;              // XREF: _dynamic_atexit_destructor_for__s_finfo__+D/o
    // _dynamic_atexit_destructor_for__s_onlineWADFileInfo__+D/o ...
    bdLobbyErrorCode m_error;
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    unsigned __int64 m_fileID;
    unsigned int m_fileSize;
    unsigned int m_bufferSize;
    bdFileInfo m_fileInfo;              // XREF: _dynamic_atexit_destructor_for__s_finfo__+3/o
    // _dynamic_atexit_destructor_for__s_onlineWADFileInfo__+3/o ...
    void *m_buffer;
    bool m_optional;
    // padding byte
    // padding byte
    // padding byte
};
//dwFileTask *__thiscall dwFileTask::dwFileTask(dwFileTask *this);


void __cdecl dwReadFileFailure(TaskRecord *task);
void __cdecl dwReadFileSuccess(TaskRecord *task);
TaskRecord *__cdecl dwReadFile(int localControllerIndex, dwFileTask *const fileTask);
TaskRecord *__cdecl dwReadFileInternal(int localControllerIndex, dwFileTask *const fileTask, unsigned __int64 ownerUID);
TaskRecord *__cdecl dwReadUserFile(int localControllerIndex, dwFileTask *const fileTask);
TaskRecord *__cdecl dwReadUserFileByUserID(int localControllerIndex, dwFileTask *const fileTask, unsigned __int64 xuid);
void __cdecl dwDeleteFileFailure(TaskRecord *task);
TaskRecord *__cdecl dwDeleteFile(int localControllerIndex, char *filename);
void __cdecl dwWriteFileFailure(TaskRecord *task);
TaskRecord *__cdecl dwWriteFile(
                int localControllerIndex,
                char *filename,
                unsigned __int8 *data,
                unsigned int dataSize,
                bdFileInfo *fileInfo,
                unsigned __int64 ownerID);
TaskRecord *__cdecl dwFileShareGetListing(int localControllerIndex, dwFileShareListTask *const fsTask);
TaskRecord *__cdecl dwFileShareGetRating(int localControllerIndex, dwFileShareGetRatingTask *const fsTask);
TaskRecord *__cdecl dwFileShareGetTopRated(int localControllerIndex, dwFileShareGetTopRatedTask *const fsTask);
char __cdecl dwFileShareLocationToCollectionID(fileShareLocation location, unsigned int *collectionID);
TaskRecord *__cdecl dwFileShareSearch(int localControllerIndex, dwFileShareSearchTask *const fsTask);
TaskRecord *__cdecl dwFileShareGetDescriptors(int localControllerIndex, dwFileShareDescriptorsTask *const fsTask);
TaskRecord *__cdecl dwFileShareGetDescriptorsFromPooledStorage(
                int localControllerIndex,
                dwFileShareDescriptorsTask *const fsTask);
TaskRecord *__cdecl dwFileShareGetDescriptorsFromUserStorage(
                int localControllerIndex,
                dwFileShareDescriptorsTask *const fsTask);
TaskRecord *__cdecl dwFileShareReadFile(int controllerIndex, dwFileShareReadFileTask *const fsTask);
TaskRecord *__cdecl dwFileShareReadPooledStorageFile(int controllerIndex, dwFileShareReadFileTask *const fsTask);
TaskRecord *__cdecl dwFileShareReadUserStorageFile(int controllerIndex, dwFileShareReadFileTask *const fsTask);
TaskRecord *__cdecl dwFileShareRemoveFile(int controllerIndex, dwFileShareRemoveTask *const fsTask);
TaskRecord *__cdecl dwFileShareTransferFile(int controllerIndex, dwFileShareTransferTask *const fsTask);
TaskRecord *__cdecl dwFileShareGetSummary(int controllerIndex, dwFileShareSummaryTask *const fsTask);
TaskRecord *__cdecl dwFileShareSetPooledSummary(int controllerIndex, dwFileShareSummaryTask *const fsTask);
TaskRecord *__cdecl dwFileShareSetUserSummary(int controllerIndex, dwFileShareSummaryTask *const fsTask);
TaskRecord *__cdecl dwFileShareSetSummary(int controllerIndex, dwFileShareSummaryTask *const fsTask);
TaskRecord *__cdecl dwFileShareWriteFile(int controllerIndex, dwFileShareWriteFileTask *const fsTask);
TaskRecord *__cdecl dwFileShareWritePooledStorageFile(int controllerIndex, dwFileShareWriteFileTask *const fsTask);
TaskRecord *__cdecl dwFileShareWriteUserStorageFile(int controllerIndex, dwFileShareWriteFileTask *const fsTask);
void __cdecl dwFileShareGetProgress(
                int localControllerIndex,
                unsigned int *bytes,
                float *dataRate,
                fileShareLocation location);
void __cdecl dwFileShareGetProgressPooled(int localControllerIndex, unsigned int *bytes, float *dataRate);
void __cdecl dwFileShareGetProgressUser(int localControllerIndex, unsigned int *bytes, float *dataRate);
void __cdecl dwFileShareAbortOperation(int localControllerIndex, fileShareLocation location);
void __cdecl dwFileShareAbortOperationPooled(int localControllerIndex);
void __cdecl dwFileShareAbortOperationUser(int localControllerIndex);
unsigned int __cdecl dwFileShareGetLastHTTPError(int localControllerIndex, fileShareLocation location);
unsigned int __cdecl dwFileShareGetLastHTTPErrorPooled(int localControllerIndex);
unsigned int __cdecl dwFileShareGetLastHTTPErrorUser(int localControllerIndex);
TaskRecord *__cdecl dwFileShareSubmitRating(int localControllerIndex, dwFileShareSubmitRatingTask *const fsTask);
