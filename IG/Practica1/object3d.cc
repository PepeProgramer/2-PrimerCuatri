/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include "object3d.h"

using namespace _colors_ne;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_line()
{
    for (unsigned int i=0;i<Triangles.size();i++){
        vertex_1 = Triangles[i]._0;
        vertex_2 = Triangles[i]._1;
        vertex_3 = Triangles[i]._2;
        std::cerr << "pepe: " << Triangles.size() << std::endl;
      glBegin(GL_LINES);
      glVertex3f(Vertices[vertex_1]._0,Vertices[vertex_1]._1,Vertices[vertex_1]._2);
      glVertex3f(Vertices[vertex_2]._0,Vertices[vertex_2]._1,Vertices[vertex_2]._2);
      glEnd();

      glBegin(GL_LINES);
      glVertex3f(Vertices[vertex_2]._0,Vertices[vertex_2]._1,Vertices[vertex_2]._2);
      glVertex3f(Vertices[vertex_3]._0,Vertices[vertex_3]._1,Vertices[vertex_3]._2);
      glEnd();

      glBegin(GL_LINES);
      glVertex3f(Vertices[vertex_1]._0,Vertices[vertex_1]._1,Vertices[vertex_1]._2);
      glVertex3f(Vertices[vertex_3]._0,Vertices[vertex_3]._1,Vertices[vertex_3]._2);

      glEnd();
    }
}


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_fill()
{
    glBegin(GL_TRIANGLES);
    for (unsigned int i=0;i<Triangles.size();i++){
        vertex_1 = Triangles[i]._0;
        vertex_2 = Triangles[i]._1;
        vertex_3 = Triangles[i]._2;
      glVertex3f(Vertices[vertex_1]._0,Vertices[vertex_1]._1,Vertices[vertex_1]._2);
      glVertex3f(Vertices[vertex_2]._0,Vertices[vertex_2]._1,Vertices[vertex_2]._2);
      glVertex3f(Vertices[vertex_3]._0,Vertices[vertex_3]._1,Vertices[vertex_3]._2);
    }
    glEnd();
}


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_chess()
{
    bool color = false;
    glBegin(GL_TRIANGLES);
    for (unsigned int i=0;i<Triangles.size();i++){
        color ? glColor3fv((GLfloat *) &RED) : glColor3fv((GLfloat *) &GREEN);
        color = !color;
        vertex_1 = Triangles[i]._0;
        vertex_2 = Triangles[i]._1;
        vertex_3 = Triangles[i]._2;
      glVertex3f(Vertices[vertex_1]._0,Vertices[vertex_1]._1,Vertices[vertex_1]._2);
      glVertex3f(Vertices[vertex_2]._0,Vertices[vertex_2]._1,Vertices[vertex_2]._2);
      glVertex3f(Vertices[vertex_3]._0,Vertices[vertex_3]._1,Vertices[vertex_3]._2);
    }
    glEnd();
}
