#pragma once

#include "phys_local.h"
#include <xanim/xanim.h>

const struct cached_simplex_info // sizeof=0x30
{                                       // XREF: phys_gjk_cache_info/r
                                        // phys_gjk_cache_info/r ...
    phys_vec3 m_indices[3];
};

struct phys_memory_heap // sizeof=0x10
{                                       // XREF: phys_contact_manifold_process/r
    char *m_buffer_start;
    char *m_buffer_end;
    char *m_buffer_cur;
    char *m_user_start;
};

struct __declspec(align(16)) contact_manifold_mesh_point // sizeof=0x20
{
    phys_vec3 m_p;
    phys_vec2 m_contact_p;
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
};

struct __declspec(align(16)) phys_contact_manifold // sizeof=0x60
{                                       // XREF: phys_contact_manifold_process/r
                                        // phys_contact_manifold_process/r
    phys_vec3 m_feature_normal;
    phys_vec3 m_feature_hitp;
    phys_vec3 m_feature_hitn;
    float m_feature_distance_eps;
    float m_sin_feautre_angular_eps_sq;
    int m_close_mesh_point_count;
    phys_memory_heap *m_allocator;
    contact_manifold_mesh_point *m_list_mesh_point;
    int m_list_mesh_point_count;
    contact_manifold_mesh_point **m_list_sorted_mesh_point;
    contact_manifold_mesh_point **m_list_contact_point;
    int m_list_contact_point_count;
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
};

struct phys_gjk_geom // sizeof=0x4
{                                       // XREF: gjk_base_t/r
    //phys_gjk_geom_vtbl *__vftable;
    virtual void support(const phys_vec3 *, phys_vec3 *, phys_vec3 *);
    virtual void get_simplex(const cached_simplex_info *, const int, phys_vec3 *, phys_vec3 *);
    virtual void set_simplex(
        const phys_vec3 *simplex_inds,
        int w_set,
        const phys_vec3 *normal,
        cached_simplex_info *cache_info)
    {
        const phys_vec3 *v5; // [esp+4h] [ebp-Ch]
        int i; // [esp+8h] [ebp-8h]

        for (i = 0; i < 4; ++i)
        {
            if ((w_set & (1 << i)) != 0)
            {
                v5 = &simplex_inds[i];
                cache_info->m_indices[0].x = v5->x;
                cache_info->m_indices[0].y = v5->y;
                cache_info->m_indices[0].z = v5->z;
                cache_info = (cached_simplex_info *)((char *)cache_info + 16);
            }
        }
    }
    virtual const phys_vec3 * get_center(const phys_vec3 * result);
    virtual void get_feature(phys_contact_manifold *);
    virtual float get_geom_radius()
    {
        return 0.0f;
    }
    virtual void calc_aabb(const phys_mat44 *, phys_vec3 *, phys_vec3 *);
    virtual bool ray_cast(const phys_vec3 *, const phys_vec3 *, const float, float *, phys_vec3 *)
    {
        return false;
    }
    virtual bool is_polyhedron();
};


class gjk_base_t : phys_gjk_geom // sizeof=0x50
{                                       // XREF: gjk_brush_t/r
public:
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    phys_vec3 m_aabb_mn_loc;
    phys_vec3 m_aabb_mx_loc;
    unsigned int m_gjk_geom_id;
    const phys_mat44 *m_xform_;
    gjk_base_t *m_next_geom;
    unsigned int m_flags;
    int stype;
    int m_contents;
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte

    void __thiscall gjk_base_t::set_xform(gjk_base_t *this, const phys_mat44 *xform);
    void __thiscall gjk_base_t::set_geom_id_new(gjk_base_t *this, unsigned int geom_id);
    void __thiscall gjk_base_t::set_contents(gjk_base_t *this, int contents);

};

struct __declspec(align(16)) gjk_aabb_t : gjk_base_t // sizeof=0x80
{
    phys_vec3 m_center_local;
    phys_vec3 m_dims;
    const struct cbrush_t *m_brush;
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte


    gjk_aabb_t *__cdecl gjk_aabb_t::create(
        const phys_vec3 *center,
        const phys_vec3 *dims,
        int stype,
        gjk_collision_visitor *allocator);
    void __thiscall gjk_aabb_t::support(
        const phys_vec3 *v,
        phys_vec3 *support_vert,
        phys_vec3 *support_ind);
    void __thiscall gjk_aabb_t::get_simplex(
        const cached_simplex_info *cache_info,
        int index_count,
        phys_vec3 *simplex_verts,
        phys_vec3 *simplex_inds);
    const phys_vec3 *__thiscall gjk_aabb_t::get_center(gjk_polygon_cylinder_t *this, phys_vec3 *result);
    void gjk_aabb_t::get_feature(
        const phys_vec3 *a2,
        phys_contact_manifold *cman);
    void __thiscall gjk_aabb_t::calc_aabb(
        const phys_mat44 *xform,
        phys_vec3 *aabb_min,
        phys_vec3 *aabb_max);
    const cbrush_t *__thiscall gjk_aabb_t::get_brush();
    void __cdecl gjk_aabb_t::destroy(gjk_aabb_t *geom);
};

struct BrushWrapper // sizeof=0x60
{
    float mins[3];
    int contents;
    float maxs[3];
    unsigned int numsides;
    cbrushside_t *sides;
    int axial_cflags[2][3];
    int axial_sflags[2][3];
    unsigned int numverts;
    float (*verts)[3];
    cplane_s *planes;
};

struct PhysGeomInfo // sizeof=0x44
{
    BrushWrapper *brush;
    int type;
    float orientation[3][3];
    float offset[3];
    float halfLengths[3];
};

struct PhysGeomList // sizeof=0xC
{
    unsigned int count;
    PhysGeomInfo *geoms;
    int contents;
};

struct gjk_obb_t : gjk_base_t // sizeof=0xA0
{
    phys_vec3 m_dims;
    phys_mat44 m_xform;

    gjk_obb_t *__cdecl gjk_obb_t::create(
        const phys_mat44 *xform,
        const phys_vec3 *dims,
        int stype,
        gjk_collision_visitor *allocator);
    void __userpurge gjk_obb_t::support(
        gjk_obb_t *this@<ecx>,
        int a2@<ebp>,
        const phys_vec3 *v,
        phys_vec3 *support_vert,
        phys_vec3 *support_ind);
    void __userpurge gjk_obb_t::get_simplex(
        gjk_obb_t *this@<ecx>,
        int a2@<ebp>,
        const cached_simplex_info *cache_info,
        int index_count,
        phys_vec3 *simplex_verts,
        phys_vec3 *simplex_inds);
    const phys_vec3 *__thiscall gjk_obb_t::get_center(gjk_obb_t *this, phys_vec3 *result);
    void __userpurge gjk_obb_t::get_feature(gjk_obb_t *this@<ecx>, const phys_vec3 *a2@<ebp>, phys_contact_manifold *cman);
    void __userpurge gjk_obb_t::calc_aabb(
        gjk_obb_t *this@<ecx>,
        int a2@<ebp>,
        const phys_mat44 *xform,
        phys_vec3 *aabb_min,
        phys_vec3 *aabb_max);
    unsigned int __thiscall gjk_obb_t::get_type(gjk_obb_t *this);
    void __cdecl gjk_obb_t::destroy(gjk_cylinder_t *geom);
    char __thiscall gjk_obb_t::is_polyhedron(gjk_query_output *this);
};

struct __declspec(align(16)) phys_contact_manifold // sizeof=0x60
{                                       // XREF: phys_contact_manifold_process/r
                                        // phys_contact_manifold_process/r
    phys_vec3 m_feature_normal;
    phys_vec3 m_feature_hitp;
    phys_vec3 m_feature_hitn;
    float m_feature_distance_eps;
    float m_sin_feautre_angular_eps_sq;
    int m_close_mesh_point_count;
    phys_memory_heap *m_allocator;
    contact_manifold_mesh_point *m_list_mesh_point;
    int m_list_mesh_point_count;
    contact_manifold_mesh_point **m_list_sorted_mesh_point;
    contact_manifold_mesh_point **m_list_contact_point;
    int m_list_contact_point_count;
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte

    void phys_contact_manifold::add_feature_point(phys_contact_manifold *this, const phys_vec3 *p);
};

struct __declspec(align(8)) gjk_brush_t : gjk_base_t // sizeof=0x60
{
    int nverts;
    const float (*verts)[3];
    const cbrush_t *brush;
    // padding byte
    // padding byte
    // padding byte
    // padding byte

    gjk_brush_t *gjk_brush_t::create@<eax>(
        float a1@<ebp>,
        const cbrush_t *brush,
        int stype,
        gjk_collision_visitor *allocator);
    void __thiscall gjk_brush_t::support(
        gjk_brush_t *this,
        const phys_vec3 *v,
        phys_vec3 *support_vert,
        phys_vec3 *support_ind);
    void __thiscall gjk_brush_t::get_simplex(
        gjk_brush_t *this,
        const cached_simplex_info *cache_info,
        int index_count,
        phys_vec3 *simplex_verts,
        phys_vec3 *simplex_inds);
    void gjk_brush_t::get_feature(gjk_brush_t *this@<ecx>, int a2@<ebp>, phys_contact_manifold *cman);
    void gjk_brush_t::calc_aabb(
        gjk_brush_t *this@<ecx>,
        int a2@<ebp>,
        const phys_mat44 *xform,
        phys_vec3 *aabb_min,
        phys_vec3 *aabb_max);
    const cbrush_t *__thiscall gjk_brush_t::get_brush(gjk_brush_t *this);
    unsigned int __thiscall gjk_brush_t::get_type(gjk_brush_t *this);
    void __cdecl gjk_brush_t::destroy(gjk_brush_t *geom);
};

struct __declspec(align(16)) gjk_partition_t : gjk_base_t // sizeof=0x70
{
    int ninds;
    const float (*verts)[3];
    unsigned __int16 *inds;
    const CollisionPartition *partition;
    const CollisionAabbTree *tree;
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte

    gjk_partition_t *__cdecl gjk_partition_t::create(const CollisionAabbTree *tree, gjk_collision_visitor *allocator);
    void __thiscall gjk_partition_t::support(
        gjk_partition_t *this,
        const phys_vec3 *v,
        phys_vec3 *support_vert,
        phys_vec3 *support_ind);
    void __thiscall gjk_partition_t::get_simplex(
        gjk_partition_t *this,
        const cached_simplex_info *cache_info,
        int index_count,
        phys_vec3 *simplex_verts,
        phys_vec3 *simplex_inds);
    const phys_vec3 *__thiscall gjk_brush_t::get_center(gjk_partition_t *this, const phys_vec3 *result);
    void __userpurge gjk_partition_t::get_feature(gjk_partition_t *this@<ecx>, int a2@<ebp>, phys_contact_manifold *cman);
    void __userpurge gjk_partition_t::calc_aabb(
        gjk_partition_t *this@<ecx>,
        unsigned __int16 *a2@<ebp>,
        const phys_mat44 *xform,
        phys_vec3 *aabb_min,
        phys_vec3 *aabb_max);
    unsigned int __thiscall gjk_partition_t::get_type(gjk_partition_t *this);
    void __cdecl gjk_partition_t::destroy(gjk_partition_t *geom);
};

struct gjk_double_sphere_t : gjk_base_t // sizeof=0x90
{
    phys_vec3 m_list_center[2];
    phys_vec3 m_center;
    float m_list_radius[2];
    float m_geom_radius;
    int m_count;

    gjk_double_sphere_t *__thiscall gjk_double_sphere_t::gjk_double_sphere_t(gjk_double_sphere_t *this);
    void __thiscall gjk_double_sphere_t::support(
        gjk_double_sphere_t *this,
        const phys_vec3 *v,
        phys_vec3 *support_vert,
        phys_vec3 *support_ind);
    void __thiscall gjk_double_sphere_t::get_simplex(
        gjk_double_sphere_t *this,
        const cached_simplex_info *cache_info,
        int index_count,
        phys_vec3 *simplex_verts,
        phys_vec3 *simplex_inds);
    void __thiscall gjk_double_sphere_t::set_simplex(
        gjk_double_sphere_t *this,
        const phys_vec3 *simplex_inds,
        int w_set,
        const phys_vec3 *normal,
        cached_simplex_info *cache_info);
    const phys_vec3 *__thiscall gjk_double_sphere_t::get_center(gjk_double_sphere_t *this, phys_vec3 *result);
    void __userpurge gjk_double_sphere_t::get_feature(
        gjk_double_sphere_t *this@<ecx>,
        int a2@<ebp>,
        phys_contact_manifold *cman);
    void __thiscall gjk_double_sphere_t::calc_aabb(
        gjk_double_sphere_t *this,
        const phys_mat44 *xform,
        phys_vec3 *aabb_min,
        phys_vec3 *aabb_max);
    double __thiscall gjk_double_sphere_t::get_geom_radius(gjk_double_sphere_t *this);
    bool __thiscall gjk_double_sphere_t::is_polyhedron(gjk_double_sphere_t *this);
    gjk_double_sphere_t *__cdecl gjk_double_sphere_t::create(
        const phys_vec3 *c0,
        const phys_vec3 *c1,
        float r,
        int stype,
        gjk_collision_visitor *allocator);
    void __cdecl gjk_double_sphere_t::destroy(gjk_double_sphere_t *geom);
};

struct gjk_cylinder_t : gjk_base_t // sizeof=0xA0
{
    int direction;
    float halfHeight;
    float radius;
    float m_geom_radius;
    phys_mat44 xform;

    gjk_cylinder_t *__cdecl gjk_cylinder_t::create(
        int _direction,
        float _halfHeight,
        float _radius,
        const phys_mat44 *_xform,
        int stype,
        gjk_collision_visitor *allocator);
    void __userpurge gjk_cylinder_t::support(
        gjk_cylinder_t *this@<ecx>,
        int a2@<ebp>,
        const phys_vec3 *v,
        phys_vec3 *support_vert,
        phys_vec3 *support_ind);
    const phys_vec3 *__userpurge gjk_cylinder_t::get_dims@<eax>(
        gjk_cylinder_t *this@<ecx>,
        int a2@<ebp>,
        const phys_vec3 *result);
    void __userpurge gjk_cylinder_t::get_simplex(
        gjk_cylinder_t *this@<ecx>,
        int a2@<ebp>,
        const cached_simplex_info *cache_info,
        int index_count,
        phys_vec3 *simplex_verts,
        phys_vec3 *simplex_inds);
    const phys_vec3 *__userpurge gjk_cylinder_t::get_center@<eax>(
        gjk_cylinder_t *this@<ecx>,
        int a2@<ebp>,
        const phys_vec3 *result);
    void __userpurge gjk_cylinder_t::get_feature(gjk_cylinder_t *this@<ecx>, int a2@<ebp>, phys_contact_manifold *cman);
    void __userpurge gjk_cylinder_t::calc_aabb(
        gjk_cylinder_t *this@<ecx>,
        int a2@<ebp>,
        const phys_mat44 *xform_,
        phys_vec3 *aabb_min,
        phys_vec3 *aabb_max);
    unsigned int __thiscall gjk_cylinder_t::get_type(gjk_cylinder_t *this);
    double __thiscall gjk_cylinder_t::get_geom_radius(gjk_cylinder_t *this);
    void __cdecl gjk_cylinder_t::destroy(gjk_cylinder_t *geom);
};

struct gjk_unique_id_database_t // sizeof=0x4
{                                       // XREF: .data:gjk_unique_id_database_t g_gjk_unique_id_database/r
    unsigned int m_counter;


    unsigned int __thiscall gjk_unique_id_database_t::get_unique_id(gjk_unique_id_database_t *this);
};

struct __declspec(align(8)) gjk_polygon_cylinder_t : gjk_base_t // sizeof=0x80
{                                       // XREF: ?render_gjkcc_collision@@YAXAAY02$$CBM00@Z/r
    phys_vec3 m_center;
    float m_polygon_cylinder_radius;
    float m_capsule_radius;
    float m_half_height;
    float m_geom_radius;
    float m_head_offset;
    float m_foot_offset;
    int m_mode;                         // XREF: render_gjkcc_collision(float const (&)[3],float const (&)[3],float const (&)[3])+10/w
    // padding byte
    // padding byte
    // padding byte
    // padding byte

    void __thiscall gjk_polygon_cylinder_t::poly_verts::poly_verts(gjk_polygon_cylinder_t::poly_verts *this);

    gjk_polygon_cylinder_t *__cdecl gjk_polygon_cylinder_t::create(
        float (*mins)[3],
        float (*maxs)[3],
        float radius_adjust,
        int stype,
        gjk_collision_visitor *allocator);
    void __cdecl gjk_polygon_cylinder_t::destroy(gjk_polygon_cylinder_t *geom);
};

PhysGeomList *__cdecl xmodel_get_geomlist(const XModel *model, int bone_index);
char *__thiscall phys_memory_heap::fast_allocate(phys_memory_heap *this, int size, const char *error_msg);

void  phys_aabb_add_point(
    const phys_mat44 *xform,
    const phys_vec3 *point,
    phys_vec3 *aabb_min,
    phys_vec3 *aabb_max);

void  phys_aabb_init_sphere(
        const phys_mat44 *xform,
        const phys_vec3 *center,
        float radius,
        phys_vec3 *aabb_min,
        phys_vec3 *aabb_max);
void  phys_aabb_add_sphere(
        const phys_mat44 *xform,
        const phys_vec3 *center,
        float radius,
        phys_vec3 *aabb_min,
        phys_vec3 *aabb_max);


void  setup_gjk_polygon_cylinder(
        float *mins,
        float *maxs,
        float radius_adjust,
        gjk_polygon_cylinder_t *gjk_cylinder);

void __cdecl destroy_gjk_geom(gjk_aabb_t *geom);
gjk_aabb_t * create_aabb_gjk_geom(
        const float *mn,
        const float *mx,
        int stype,
        gjk_collision_visitor *allocator);
gjk_obb_t * create_obb_gjk_geom@<eax>(
        float (*orientation)[3],
        float *offset,
        float *halfLengths,
        int stype,
        gjk_collision_visitor *allocator);
gjk_brush_t *__cdecl create_brush_gjk_geom(const cbrush_t *brush, int stype, gjk_collision_visitor *allocator);
gjk_double_sphere_t * create_capsule_gjk_geom(
        float *center,
        float radius,
        float halfHeight,
        unsigned int direction,
        int stype,
        gjk_collision_visitor *allocator);
gjk_cylinder_t * create_cylinder_gjk_geom@<eax>(
        float (*rot)[3],
        float *trans,
        float radius,
        float halfHeight,
        int stype,
        gjk_collision_visitor *allocator);
void __cdecl create_brush_model_gjk_geom_r(
        cLeafBrushNode_s *node,
        int *index_base,
        gjk_collision_visitor *allocator,
        int contents_mask);
void __cdecl query_brush_model_gjk_geom(
        unsigned __int16 brushModel,
        int contents_mask,
        gjk_collision_visitor *allocator);
void __thiscall query_brush_model_gjk_geom_visitor::visit(
        query_brush_model_gjk_geom_visitor *this,
        const cbrush_t *brush);
void __thiscall query_brush_model_gjk_geom_visitor::update(
        query_brush_model_gjk_geom_visitor *this,
        const float *_mn,
        const float *_mx,
        int _mask,
        const float *expand_vec);
void __cdecl create_brush_model_gjk_geom(
        unsigned __int16 brushModel,
        int contents_mask,
        gjk_collision_visitor *allocator);
void __cdecl create_xmodel_gjk_geom(
        const XModel *model,
        gjk_collision_visitor *allocator,
        int bone_index,
        unsigned int brush_mask,
        bool b_fallback_to_bounding_box,
        int contents_for_proxy_collision,
        phys_mat44 *worldMat);
void __cdecl create_gjk_geom(
        int localClientNum,
        const centity_s *cent,
        gjk_collision_visitor *allocator,
        bool calc_bone_mats,
        unsigned int brush_mask,
        bool b_fallback_to_bounding_box,
        bool b_use_smallerbox_for_characters);
void __cdecl create_gjk_dobj_geom(
        DObj *obj,
        const cpose_t *pose,
        gentity_s *gent,
        bool calc_bone_mats,
        unsigned int brush_mask,
        bool b_fallback_to_bounding_box,
        int contents_for_proxy_collision,
        gjk_collision_visitor *allocator);
void __cdecl create_gjk_geom(
        gentity_s *gent,
        gjk_collision_visitor *allocator,
        bool calc_bone_mats,
        unsigned int brush_mask,
        bool b_fallback_to_bounding_box);


void __cdecl create_gjk_geom(const Glass *glass, gjk_collision_visitor *allocator, unsigned int brush_mask);
void __cdecl create_gjk_geom(const DynEntityDef *dynEntDef, gjk_collision_visitor *allocator, unsigned int brush_mask);

void __cdecl destroy_gjk_geom(gjk_geom_list_t *gjk_geom_list);
