#include "tetmesh.h"



void TetMesh::fill_verts_and_tets(float *inverts,  unsigned invertsize,
                             unsigned * intets, unsigned intetsize)
{

    vertices.resize(invertsize);
    for(unsigned iter = 0;iter < invertsize;iter++) 
    {
        vertices[iter].x = inverts[invertsize*3];        
        vertices[iter].y = inverts[invertsize*3 + 1];        
        vertices[iter].z = inverts[invertsize*3 + 2];        
    }

    tetrahedra.resize(intetsize);
    for(unsigned iter = 0; iter < intetsize; iter++)
    {
        tetrahedra[iter].v1 = intets[intetsize*4];            
        tetrahedra[iter].v2 = intets[intetsize*4 + 1];            
        tetrahedra[iter].v3 = intets[intetsize*4 + 2];            
        tetrahedra[iter].v4 = intets[intetsize*4 + 3];            
    } 

}

void TetMesh::enforce_positive_orientation()
{
    for( unsigned iter = 0; iter < tetrahedra.size(); iter++)
    {
        if( compute_tet_orientation( iter ) < 0)
        {
            // if negative, swap the first two vertices to get a positive
            // orientation
           
            unsigned hold = tetrahedra[iter].v1;
            tetrahedra[iter].v1 = tetrahedra[iter].v2;
            tetrahedra[iter].v2 = hold;
        }
    }
}

float TetMesh::compute_tet_orientation(unsigned tetindex) 
{
    tet intet = tetrahedra[tetindex];

    vertex v1,v2,v3,v4;

    v1 = vertices[intet.v1];
    v2 = vertices[intet.v2];
    v3 = vertices[intet.v3];
    v4 = vertices[intet.v4];

    // return the following determinant:
    // | v1.x v1.y v1.z 1 |        
    // | v2.x v2.y v2.z 1 |
    // | v3.x v3.y v3.z 1 |
    // | v4.x v4.y v4.z 1 |
   
    // recurse down into 3x3 determinants
    float d1 = v1.x*(  v2.y*(v3.z - v4.z) - v2.z*(v3.y - v4.y) + ( v3.y*v4.z - v4.y*v3.z) );

    float d2 = v1.y*(  v2.x*(v3.z - v4.z) - v2.z*(v3.x - v4.x) + ( v3.x*v4.z - v4.x*v3.z) );

    float d3 = v1.z*(  v2.x*(v3.y - v4.y) - v2.y*(v3.x - v4.x) + ( v3.x*v4.y - v4.x*v3.y) );

    float d4 = v2.x*(  v3.y*v4.z - v3.z*v4.y) - v2.y*(v3.x*v4.z - v3.z*v4.x) + v2.z*(v3.x*v4.y - v3.y*v4.x ); 

    return d1 - d2 + d3 - d4;

}



     


    

