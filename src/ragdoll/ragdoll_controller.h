#pragma once

struct cpose_t;
struct RagdollBody;

const cpose_t *__cdecl Ragdoll_HandleBody(const cpose_t *pose);
struct BoneOrientation *__cdecl Ragdoll_BodyBoneOrientations(struct RagdollBody *body);
struct BoneOrientation *__cdecl Ragdoll_BodyPrevBoneOrientations(struct RagdollBody *body);
void __cdecl Ragdoll_DoControllers(const cpose_t *pose, const struct DObj *obj, int *partBits);
