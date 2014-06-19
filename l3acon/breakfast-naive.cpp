#include <iostream>
#include <fstream>
#include <string>
#include <vector>

////////////////////
//
// Matt Fernandez 2014
//
// l3acon@gmail.com
//
// for best breakfast compile with -O3
//

#define CHAR_COUNTERS 128

using namespace std;

char* incs( char *s)
{
  int i, tail, len;
  for(i = 0; s[i] != '\0'; ++i)
	;
  len = i;
  for( tail = len  - 1; tail >= 0 && s[tail] == '9'; tail--)
	;
  if( tail < 0 )
  {
	//if( len + 2 > CHAR_COUNTERS )
	//  s = realloc(s, (len + 2) << 1);
	s[0] = '1';
	for(i = 1; i <= len; ++i)
	  s[i] = '0';
	s[len + 1] = '\0';
  }
  else
  {
	for( i = len - 1; i > tail; --i)
	  s[i] = '0';
	s[tail] ++;
  }
}
 

void link_sausage(char* in, int size, vector<char> &out, char* key, const int keysize, char* str)
{
  int curr = 0;

  for(unsigned long long i = 0; i < size - keysize; ++i)
  {
	out.push_back(in[i]);
	for(int j = 0; j < keysize + 1; ++j)
	{
	  if(j == keysize)
	  {
		curr ++;
		for(int k = 1; k < keysize; ++k)
		  out.push_back(in[i+k]);
		i += keysize - 1;
		out.push_back('(');
		for(unsigned short k = 0; str[k] != '\0'; ++k)
		  out.push_back(str[k]);
		out.push_back(')');
	  }
	  if(key[j] != in[j+i])
		break;
	}
  }
}

int main(int argc, char**argv)
{
  if( argc <= 2)
  {
	cout<<"Specify text file and key\n";
	return -1;
  }

  ifstream ifile(argv[1]);
  string key = argv[2];

  if(!ifile)
  {
	cout<<"Invalid filename\n"; 
	return -1;
  }	

  char* window = new char[key.size()];
  for(int i = 0; i < key.size(); ++i)
	window[i] = key[i];

  ifile.seekg(0, ifile.end);
  long size = ifile.tellg();
  ifile.seekg(0);

  char* contents = new char[size]; 	
  ifile.read(contents, size);
  ifile.close();
  
  vector<char> duf;
  char* str = (char*) malloc(CHAR_COUNTERS);

  str[0] = '\0';
  link_sausage(contents, size, duf, window, key.size(), str);
  
  ofstream ofile(argv[1]);
  ofile.write(duf.data(), duf.size());
  ofile.close();
}


