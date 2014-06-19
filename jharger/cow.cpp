#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    if(argc != 3) {
        cerr << "Usage: " << argv[0] << " <filename> <key>" << endl;
        return 1;
    }
    string key(argv[2]);
    string contents;
    ifstream in(argv[1], ios::in | ios::binary);
    if (in)
    {
        in.seekg(0, ios::end);
        contents.resize(in.tellg());
        in.seekg(0, ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
    }

    ofstream out(argv[1], ios::out | ios::binary);
    size_t last = 0;
    size_t pos = contents.find(key, 0);
    int count = 0;
    while(pos != string::npos)
    {
        count ++;
        out << contents.substr(last, pos - last + key.size()) << "(" << count << ")";
        last = pos + key.size();
        pos = contents.find(key, pos + key.size());
    }
    out << contents.substr(last);
    out.close();

	return 0;
}
