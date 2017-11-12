//******************************************************************************
// class to read ply files of triangles
//
// Domingo Martín Perandres (c) 2003-2013
//
// Gnu Public Licence
//******************************************************************************


#ifndef _FILE_PLY_H
#define _FILE_PLY_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "vertex.h"

class _file_ply
{
public:

  _file_ply(){}
  int open(const string &File_name);
  void read(vector<_vertex3f> &Vertices, vector<_vertex3i> &Triangles);
  void close();

private:
  void get_token(std::istringstream &Line_stream1,std::string &Token1);
  bool get_new_line(std::ifstream &File,std::istringstream &Line_stream);

  std::ifstream File;
};

#endif // _FILE_PLY_H
