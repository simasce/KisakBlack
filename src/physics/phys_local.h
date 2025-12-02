#pragma once

struct phys_vec2 // sizeof=0x8
{                                       // XREF: contact_manifold_mesh_point/r
                                        // phys_contact_manifold_process::bridge/r ...
    float x;                            // XREF: phys_contact_manifold::generate_convex_poly_internal(void)+59/w
                                        // phys_contact_manifold::generate_convex_poly_internal(void)+70/w ...
    float y;                            // XREF: phys_contact_manifold::generate_convex_poly_internal(void)+68/w
                                        // phys_contact_manifold::generate_convex_poly_internal(void)+7C/w ...
};

struct phys_vec3 // sizeof=0x10
{                                       // XREF: .data:PHYS_X_VEC/r
    float x;                            // XREF: gjkcc_info::update_cg(float const * const,float const * const,bool)+1F2/r
    float y;                            // XREF: gjkcc_info::update_cg(float const * const,float const * const,bool)+209/r
    float z;                            // XREF: gjkcc_info::update_cg(float const * const,float const * const,bool)+221/r
    float w;                            // XREF: standard_query::query(broad_phase_environment_query_input const &,broad_phase_environement_query_results *)+440/r
};

struct phys_mat44 // sizeof=0x40
{                                       // XREF: .data:PHYS_IDENTITY_MATRIX/r
                                        // .data:PHYS_IDENTITY_MATRIX_0/r ...
    phys_vec3 x;                        // XREF: gjk_cylinder_t::get_feature(phys_contact_manifold *)+63/r
    // gjk_cylinder_t::get_feature(phys_contact_manifold *)+70/r ...
    phys_vec3 y;                        // XREF: gjk_cylinder_t::get_feature(phys_contact_manifold *)+95/o
    // SetIdentity(phys_mat44 &)+20/r ...
    phys_vec3 z;                        // XREF: gjk_cylinder_t::get_feature(phys_contact_manifold *):loc_834A44/o
    // SetIdentity(phys_mat44 &)+3B/r ...
    phys_vec3 w;                        // XREF: phys_calc_world_aabb(phys_vec3 const &,phys_vec3 const &,phys_mat44 const &,phys_vec3 *,phys_vec3 *)+10/w
    // create_obb_gjk_geom(float const (* const)[3],float const * const,float const * const,int,gjk_collision_visitor *)+10/w ...
};

template <typename T>
struct phys_link_list_base//<pulse_sum_node> // sizeof=0x4
{                                       // XREF: pulse_sum_node/r
    //pulse_sum_node *m_next_link;
    T *m_next_link;
};

template <typename T>
struct phys_simple_link_list//<contact_point_info> // sizeof=0x4
{                                       // XREF: rigid_body_constraint_contact/r
                                        // rigid_body_constraint_contact/r
    //contact_point_info *m_first;
    T *m_first;
};

char *__cdecl PMM_ALLOC(unsigned int size, unsigned int alignment);
void __cdecl PMM_VALIDATE(char *ptr, unsigned int size, unsigned int alignment);
void __cdecl PMM_FREE(unsigned __int8 *ptr, unsigned int size, unsigned int alignment);

template <typename T>
struct phys_simple_allocator//<phys_heap_gjk_cache_system_avl_tree::phys_gjk_cache_info_internal> // sizeof=0x4
{                                       // XREF: phys_heap_gjk_cache_system_avl_tree/r
    int m_count;

    T *allocate()
    {
        char *slot; // [esp+18h] [ebp-4h]

        slot = PMM_ALLOC(sizeof(T), sizeof(T) <= 36 ? 4 : 16);
        if (!slot)
            return 0;
        ++this->m_count;
        return (T*)slot;
    }

    void free(T *slot)
    {
        if (slot)
        {
            PMM_VALIDATE((char *)slot, sizeof(T), sizeof(T) <= 36 ? 4 : 16);
            --this->m_count;
            PMM_FREE((unsigned __int8 *)slot, sizeof(T), sizeof(T) <= 36 ? 4 : 16);
        }
    }
};

//gjk_aabb_t *__thiscall phys_simple_allocator<gjk_aabb_t>::allocate(phys_simple_allocator<gjk_aabb_t> *this);
//gjk_obb_t *__thiscall phys_simple_allocator<gjk_obb_t>::allocate(phys_simple_allocator<gjk_obb_t> *this);
//gjk_brush_t *__thiscall phys_simple_allocator<gjk_brush_t>::allocate(phys_simple_allocator<gjk_brush_t> *this);
//void __thiscall phys_simple_allocator<gjk_brush_t>::free(phys_simple_allocator<gjk_brush_t> *this, gjk_brush_t *slot);
//gjk_partition_t *__thiscall phys_simple_allocator<gjk_partition_t>::allocate(
//    phys_simple_allocator<gjk_partition_t> *this);
//void __thiscall phys_simple_allocator<gjk_partition_t>::free(
//    phys_simple_allocator<gjk_partition_t> *this,
//    gjk_partition_t *slot);
//gjk_double_sphere_t *__thiscall phys_simple_allocator<gjk_double_sphere_t>::allocate(
//    phys_simple_allocator<gjk_double_sphere_t> *this);
//void __thiscall phys_simple_allocator<gjk_double_sphere_t>::free(
//    phys_simple_allocator<gjk_double_sphere_t> *this,
//    gjk_double_sphere_t *slot);
//gjk_cylinder_t *__thiscall phys_simple_allocator<gjk_cylinder_t>::allocate(phys_simple_allocator<gjk_cylinder_t> *this);
//void __thiscall phys_simple_allocator<gjk_cylinder_t>::free(
//    phys_simple_allocator<gjk_cylinder_t> *this,
//    gjk_cylinder_t *slot);
//gjk_polygon_cylinder_t *__thiscall phys_simple_allocator<gjk_polygon_cylinder_t>::allocate(
//    phys_simple_allocator<gjk_polygon_cylinder_t> *this);
//void __thiscall phys_simple_allocator<gjk_polygon_cylinder_t>::free(
//    phys_simple_allocator<gjk_polygon_cylinder_t> *this,
//    gjk_polygon_cylinder_t *slot);