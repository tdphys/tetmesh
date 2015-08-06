#ifndef __TETMESH_H__
#define __TETMESH_H__

#include<vector>


class TetMesh{

public:

    // standard x y z vertex
    struct vertex
    {
        float x;
        float y;
        float z;
    };

    // tetrahedra struct
    // four vertex indices
    // four half-face indices
    struct tet
    {
        // vertices index
        unsigned v1;
        unsigned v2;
        unsigned v3;
        unsigned v4;

        //half-faces index
        unsigned ha;
        unsigned hb;
        unsigned hc;
        unsigned hd;
    };

    // half face struct
    struct hface
    {
        //vertices index
        unsigned v1;
        unsigned v2;
        unsigned v3;

        // back index to owning tetrahedra 
        unsigned tetp;

        // half-face pair,  -1 if doesn't exist 
        unsigned hpair;
    };

    
    std::vector<vertex> vertices;

    std::vector<tet> tetrahedra;

    std::vector<hface> half_faces;
     
    TetMesh(){}; 


    // expects 3*invertsize floats
    // and 4*intetsize unsigned ints
    
    void fill_verts_and_tets(float * inverts, unsigned invertsize,
                        unsigned * intets, unsigned intetsize);
    
    void build_half_faces();

    void enforce_positive_orientation();

    float compute_tet_orientation(unsigned tetindex); 

    
};

#endif
