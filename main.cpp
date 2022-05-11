//#include <Eigen/Dense>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

// Written by Christopher Wilkes, Cambridge University.
// In future, classes will be used to print vertices, elements and then boundaries in txt not json.
// Arpril 2021

//using Eigen::MatrixXd;
int main() {

// how many elements in each direction
 const int xlen = 94;
 const int ylen = 34;
 const int zlen = 334;

//Length of each element (global)
 double spacing = 0.03;

 const double xorigin = 0.00001;

 double xcoord = xorigin;

 double zorigin = 0.00001;

 double ycoord = 0.00001;
 double zcoord = 0.00001;

double yorigin = 0.00001;

 unsigned counter = 0;
 unsigned size = 0;

 unsigned esize = 0;
 unsigned vsize = 0;

 std::vector<std::vector<std::vector<int> > > mesh;

   // Set up sizes
   mesh.resize(xlen);
   for (int i = 0; i < xlen; ++i) {
     mesh[i].resize(ylen);

     for (int j = 0; j < ylen; ++j)
       mesh[i][j].resize(zlen);
   }

 int indices = 0;

 //(rows - 1)

//create 3D array
 for (unsigned x = 0; x < xlen; ++x) {
   for (unsigned y = 0; y < ylen; ++y) {
     for (unsigned z = 0; z < zlen; ++z) {
       mesh[x][y][z] = indices;
       ++indices;
     }
   }
 }

//calculate the number of elements to add to start of file
 for (unsigned x = 0; x < xlen; ++x) {
   for (unsigned y = 0; y < ylen; ++y) {
     for (unsigned z = 0; z < zlen; ++z) {
       if ((x > 0) && (x < (xlen - 1))) {
         if ((y > 0) && (y < (ylen - 1))) {
           if ((z > 0) && (z < (zlen - 1))) {
             if (y > 1 && (zlen - z) > 2 && (xlen - x) > 2) {
               esize ++;
             }
           }
         }
       }
     }
   }
 }


//! Output file LOCATION IMPORTANT PLEASE CHANGE
std::string vertifilename = "/work/06435/cw646/frontera/frontera/gimp_col_kks/vertices.txt";
std::fstream verfile;
verfile.open(vertifilename, std::ios::out);

//calculate number of vertices
vsize = xlen*ylen*zlen;

//print number of vertices and elements
std::cout << "Vertices: " << vsize << "  Elements: " << esize << '\n';

//write number of vertices and elements to start of file
verfile << vsize << '\t' << esize <<'\n';
//define coordinates 
 for (unsigned x = 0; x < xlen; ++x) {
   for (unsigned y = 0; y < ylen; ++y) {
     for (unsigned z = 0; z < zlen; ++z) {

       //std::array<douable, 3> coord = {xcoord, ycoord, zcoord};

        // write coordinates to file 
       verfile << xcoord<< '\t' << ycoord << '\t' << zcoord << '\n';

       zcoord += spacing;
     }
     zcoord = zorigin;
     ycoord += spacing;
   }
   ycoord = yorigin;
   xcoord += spacing;
   std::cout << xcoord << '\n';
 }

// verfile.close();

 std::cout << "Checkpoint 1" << '\n';

 //std::string elefilename = "elements.txt";
 //std::fstream elefile;
 //elefile.open(elefilename, std::ios::out);

//crete elements by parsing 3D array
 for (unsigned x = 0; x < xlen; ++x) {

   for (unsigned y = 0; y < ylen; ++y) {
     for (unsigned z = 0; z < zlen; ++z) {

       // check node is not on boundaxy of mesh
       if ((x > 0) && (x < (xlen - 1))) {
         if ((y > 0) && (y < (ylen - 1))) {
           if ((z > 0) && (z < (zlen - 1))) {
             // check if rows above and to the side to genexate a GIMP

             //allocate nodes to cell and write to file
             if (y > 1 && (zlen - z) > 2 && (xlen - x) > 2) {
               verfile << mesh[x][y][z]      // 0
                   <<" "<< mesh[x + 1][y][z]         // 1
                   <<" "<< mesh[x + 1][y][z + 1]     // 2
                   <<" "<< mesh[x][y][z + 1]         // 3
                   <<" "<< mesh[x][y - 1][z]         // 4
                   <<" "<< mesh[x + 1][y - 1][z]     // 5
                   <<" "<< mesh[x + 1][y - 1][z + 1] // 6
                   <<" "<< mesh[x][y - 1][z + 1]     // 7
                   <<" "<< mesh[x - 1][y + 1][z - 1] // 8
                   <<" "<< mesh[x][y + 1][z - 1]     // 9
                   <<" "<< mesh[x + 1][y + 1][z - 1] // 10
                   <<" "<< mesh[x + 2][y + 1][z - 1] // 11
                   <<" "<< mesh[x - 1][y + 1][z]     // 12
                   <<" "<< mesh[x][y + 1][z]         // 13
                   <<" "<< mesh[x + 1][y + 1][z]     // 14
                   <<" "<< mesh[x + 2][y + 1][z]     // 15
                   <<" "<< mesh[x - 1][y + 1][z + 1] // 16
                   <<" "<< mesh[x][y + 1][z + 1]     // 17
                   <<" "<< mesh[x + 1][y + 1][z + 1] // 18
                   <<" "<< mesh[x + 2][y + 1][z + 1] // 19
                   <<" "<< mesh[x - 1][y + 1][z + 2] // 20
                   <<" "<< mesh[x][y + 1][z + 2]     // 21
                   <<" "<< mesh[x + 1][y + 1][z + 2] // 22
                   <<" "<< mesh[x + 2][y + 1][z + 2] // 23
                   <<" "<< mesh[x - 1][y][z - 1]     // 24
                   <<" "<< mesh[x][y][z - 1]         // 25
                   <<" "<< mesh[x + 1][y][z - 1]     // 26
                   <<" "<< mesh[x + 2][y][z - 1]     // 27
                   <<" "<< mesh[x - 1][y][z]         // 28
                   <<" "<< mesh[x + 2][y][z]         // 29
                   <<" "<< mesh[x - 1][y][z + 1]     // 30
                   <<" "<< mesh[x + 2][y][z + 1]     // 31
                   <<" "<< mesh[x - 1][y][z + 2]     // 32
                   <<" "<< mesh[x][y][z + 2]         // 33
                   <<" "<< mesh[x + 1][y][z + 2]     // 34
                   <<" "<< mesh[x + 2][y][z + 2]     // 35
                   <<" "<< mesh[x - 1][y - 1][z - 1] // 36
                   <<" "<< mesh[x][y - 1][z - 1]     // 37
                   <<" "<< mesh[x + 1][y - 1][z - 1] // 39
                   <<" "<< mesh[x + 2][y - 1][z - 1] // 39
                   <<" "<< mesh[x - 1][y - 1][z]     // 40
                   <<" "<< mesh[x + 2][y - 1][z]     // 41
                   <<" "<< mesh[x - 1][y - 1][z + 1] // 42
                   <<" "<< mesh[x + 2][y - 1][z + 1] // 43
                   <<" "<< mesh[x - 1][y - 1][z + 2] // 44
                   <<" "<< mesh[x][y - 1][z + 2]     // 45
                   <<" "<< mesh[x + 1][y - 1][z + 2] // 46
                   <<" "<< mesh[x + 2][y - 1][z + 2] // 47
                   <<" "<< mesh[x - 1][y - 2][z - 1] // 48
                   <<" "<< mesh[x][y - 2][z - 1]     // 49
                   <<" "<< mesh[x + 1][y - 2][z - 1] // 50
                   <<" "<< mesh[x + 2][y - 2][z - 1] // 51
                   <<" "<< mesh[x - 1][y - 2][z]     // 52
                   <<" "<< mesh[x][y - 2][z]         // 53
                   <<" "<< mesh[x + 1][y - 2][z]     // 54
                   <<" "<< mesh[x + 2][y - 2][z]     // 55
                   <<" "<< mesh[x - 1][y - 2][z + 1] // 56
                   <<" "<< mesh[x][y - 2][z + 1]     // 57
                   <<" "<< mesh[x + 1][y - 2][z + 1] // 58
                   <<" "<< mesh[x + 2][y - 2][z + 1] // 59
                   <<" "<< mesh[x - 1][y - 2][z + 2] // 60
                   <<" "<< mesh[x][y - 2][z + 2]     // 61
                   <<" "<< mesh[x + 1][y - 2][z + 2] // 62
                   <<" "<< mesh[x + 2][y - 2][z + 2] << '\n'; // 63

             }
           }
         }
       }
     }
   }
   std::cout << x << '\n';
 }

  verfile.close();
 
//elefile.close();

//! Boundaries
std::cout << "Boundaries" << '\n';

// x begin
std::vector<int> x_left_boundaries;
std::vector<int> x_right_boundaries;

x_left_boundaries.resize(3*ylen*zlen);
x_right_boundaries.resize(3*ylen*zlen);

unsigned xl_i = 0;
unsigned xr_i = 0;


//y begin
std::vector<int> y_front_boundaries;
std::vector<int> y_back_boundaries;

y_front_boundaries.resize(3*xlen*zlen);
y_back_boundaries.resize(3*xlen*zlen);

unsigned yf_i = 0;
unsigned yb_i = 0;

//z begin
std::vector<int> z_bot_boundaries;
std::vector<int> z_top_boundaries;

z_bot_boundaries.resize(3*xlen*ylen);
z_top_boundaries.resize(3*xlen*ylen);

unsigned zb_i = 0;
unsigned zt_i = 0;

//calculate the number of elements to add to start of file
    for (unsigned x = 0; x < xlen; ++x) {
        for (unsigned y = 0; y < ylen; ++y) {
            for (unsigned z = 0; z < zlen; ++z) {


                if (x < 3) {
                    // x left
                    x_left_boundaries[xl_i] = mesh[x][y][z];
                    xl_i++;
                } 

                if (x > (xlen - 4)) {
                    // x right
                    x_right_boundaries[xr_i] = mesh[x][y][z];
                    xr_i++;
                } 

                if (y < 3) {
                    // x left
                    y_back_boundaries[yb_i] = mesh[x][y][z];
                    yb_i++;
                } 

                if (y > (ylen - 4)) {
                    // x right
                    y_front_boundaries[yf_i] = mesh[x][y][z];
                    yf_i++;
                } 
                
                if (z < 3) {
                    // x left
                    z_bot_boundaries[zb_i] = mesh[x][y][z];
                    zb_i++;
                } 

                if (z > (zlen - 4)) {
                    // x right
                    z_top_boundaries[zt_i] = mesh[x][y][z];
                    zt_i++;
                } 

              
            }
        }
    }



  //! Output file
  std::string boundaryfileneame = "/work/06435/cw646/frontera/frontera/gimp_col_kks/boundaries.json";
  std::fstream boundaryfile;
  boundaryfile.open(boundaryfileneame, std::ios::out);
  if (boundaryfile.is_open()) {
    unsigned counter = 0;
  
    boundaryfile << "{" << '\n';
    boundaryfile << '\t' << " \"node_sets\" : [ " << '\n';
    boundaryfile << '\t' << '\t' << " { " << '\n';

    // ----------------- X START -------------------------------
    //set 0
    boundaryfile << '\t' << '\t' << " \"id\" : 0," << '\n';
    boundaryfile << '\t' << '\t' << " \"set\" : [";

      //! x left (x_left_boundaries)
      counter = 0;
      for (auto const& boundaries : x_left_boundaries) {
        if (counter < (xl_i-1)) {
          boundaryfile << '\t' << '\t' << '\t' << boundaries  << "," << '\n';
          } else {
            boundaryfile << '\t' << '\t' << '\t' << boundaries;
          }
          counter++;
      }

    boundaryfile << " ]" << '\n';
    boundaryfile << '\t' << '\t' << " }, " << '\n';

    boundaryfile << '\t' << '\t' << " { " << '\n';
    //set 1
    boundaryfile << '\t' << '\t' << " \"id\" : 1," << '\n';
    boundaryfile << '\t' << '\t' << " \"set\" : [";
      
      //! x right (x_right_boundaries)
      counter = 0;
      for (auto const& boundaries : x_right_boundaries) {
        if (counter < (xr_i-1)) {
         boundaryfile << '\t' << '\t'<< '\t' << boundaries << "," << '\n';
          } else {
            boundaryfile << '\t' << '\t' << '\t' << boundaries;
          }
          counter++;
      }
    boundaryfile << " ]" << '\n';
    boundaryfile << '\t' << '\t' << " }, " << '\n';

    // ----------------- X END -------------------------------

    // ----------------- Y START -------------------------------
    boundaryfile << '\t' << '\t' << " { " << '\n';
    //set 2
    boundaryfile << '\t' << '\t' << " \"id\" : 2," << '\n';
    boundaryfile << '\t' << '\t' << " \"set\" : [";
      
      //! x right (y_back_boundaries)
      counter = 0;
      for (auto const& boundaries : y_back_boundaries) {
        if (counter < (yb_i-1)) {
         boundaryfile << '\t' << '\t'<< '\t' << boundaries << "," << '\n';
          } else {
            boundaryfile << '\t' << '\t' << '\t' << boundaries;
          }
          counter++;
      }

    boundaryfile << " ]" << '\n';
    boundaryfile << '\t' << '\t' << " }, " << '\n';

    boundaryfile << '\t' << '\t' << " { " << '\n';
    //set 3
    boundaryfile << '\t' << '\t' << " \"id\" : 3," << '\n';
    boundaryfile << '\t' << '\t' << " \"set\" : [";
      
      //! x right (y_front_boundaries)
      counter = 0;
      for (auto const& boundaries : y_front_boundaries) {
        if (counter < (yf_i-1)) {
         boundaryfile << '\t' << '\t'<< '\t' << boundaries << "," << '\n';
          } else {
            boundaryfile << '\t' << '\t' << '\t' << boundaries;
          }
          counter++;
      }

      
    // ----------------- Y END -------------------------------

    boundaryfile << " ]" << '\n';
    boundaryfile << '\t' << '\t' << " }, " << '\n';

    // ----------------- Z START -------------------------------


    boundaryfile << '\t' << '\t' << " { " << '\n';
    //set 4
    boundaryfile << '\t' << '\t' << " \"id\" : 4," << '\n';
    boundaryfile << '\t' << '\t' << " \"set\" : [";
      
      //! x right (z_bot_boundaries)
      counter = 0;
      for (auto const& boundaries : z_bot_boundaries) {
        if (counter < (zb_i-1)) {
         boundaryfile << '\t' << '\t'<< '\t' << boundaries << "," << '\n';
          } else {
            boundaryfile << '\t' << '\t' << '\t' << boundaries;
          }
          counter++;
      }

    boundaryfile << " ]" << '\n';
    boundaryfile << '\t' << '\t' << " }, " << '\n';

    boundaryfile << '\t' << '\t' << " { " << '\n';
    //set 5
    boundaryfile << '\t' << '\t' << " \"id\" : 5," << '\n';
    boundaryfile << '\t' << '\t' << " \"set\" : [";
      
      //! x right (z_top_boundaries)
      counter = 0;
      for (auto const& boundaries : z_top_boundaries) {
        if (counter < (zt_i-1)) {
         boundaryfile << '\t' << '\t'<< '\t' << boundaries << "," << '\n';
          } else {
            boundaryfile << '\t' << '\t' << '\t' << boundaries;
          }
          counter++;
      }

    //close system
    boundaryfile << " ]" << '\n';
    boundaryfile << '\t' << '\t' << " } " << '\n';

    //close system
    boundaryfile << '\t' << " ]" << '\n';
    boundaryfile << " } " << '\n';
      
    boundaryfile.close();

  } else {
    std::cout << "File not open";
  }


/*
if ((y > 0) && (y < (ylen - 1))) {
                        if ((z > 0) && (z < (zlen - 1))) {
                            if (y > 1 && (zlen - z) > 2 && (xlen - x) > 2) {
                                esize ++;
                            }
                        }
                    }

&& (x < (xlen - 3))*/


 std::cout << "Finish" << '\n';

}
