#include <iostream>   
#include <fstream>
using namespace std;

void LoadBmp(string filename)
{

				ifstream stream;
                stream.open(filename, ios::binary);
 
                //read 54 byte BMP-header
                short short_2byte_waste = 0;
                int int_4byte_waste = 0;
 
                short type = 0;
                int width = 0;
                int height = 0;
                short bitcount = 0;
                int offsetbitmap = 0;
 
                stream.read(reinterpret_cast<char*>(&type), sizeof(short)); //typ, hier sollte 19778 stehen (das steht für BMP)
                stream.read(reinterpret_cast<char*>(&int_4byte_waste), sizeof(int));     //size
                stream.read(reinterpret_cast<char*>(&short_2byte_waste), sizeof(short)); //reserved1
                stream.read(reinterpret_cast<char*>(&short_2byte_waste), sizeof(short)); //reserved2
                stream.read(reinterpret_cast<char*>(&offsetbitmap), sizeof(int));     //offset bitmpadaten, nur wichtig wenn compression
                stream.read(reinterpret_cast<char*>(&int_4byte_waste), sizeof(int));     //size info header
                stream.read(reinterpret_cast<char*>(&width), sizeof(int)); //textur width
                stream.read(reinterpret_cast<char*>(&height), sizeof(int)); //textur height
                stream.read(reinterpret_cast<char*>(&short_2byte_waste), sizeof(short));  //planes
                stream.read(reinterpret_cast<char*>(&bitcount), sizeof(short)); //farbtiefe
                stream.read(reinterpret_cast<char*>(&int_4byte_waste), sizeof(int));
                stream.read(reinterpret_cast<char*>(&int_4byte_waste), sizeof(int));
                stream.read(reinterpret_cast<char*>(&int_4byte_waste), sizeof(int));
                stream.read(reinterpret_cast<char*>(&int_4byte_waste), sizeof(int));
                stream.read(reinterpret_cast<char*>(&int_4byte_waste), sizeof(int));
                stream.read(reinterpret_cast<char*>(&int_4byte_waste), sizeof(int));
 
                if(type != 19778 || bitcount != 24)
                {
                        stream.close();
 
                        cout<<"koennen wir nicht laden, verdammt!"<<endl;
                }
 
                stream.seekg(offsetbitmap);
 
                unsigned char *pixeldaten = new unsigned char[width*height*3];   //24bit farbtiefe, ein kanal ist 8 bit groß: 24/8 ->3
                stream.read(reinterpret_cast<char*>(pixeldaten), width*height*3);
 
                stream.close();
}