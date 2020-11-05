/// FileIO.h: file reading and writing header
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 
using namespace std;

class FileIO
{
public:
    // Reads a supplied filename contents and returns a string array
    static vector<string>* fileRead(string filename)
    {
        ifstream file;
        file.open(filename);

        if (!file.is_open())
        {
            cout << "Error opening " << filename << endl;
            return nullptr;
        }

        vector<string>* file_text = new vector<string>();
        string line;
        while (getline(file, line))
        {
            file_text->push_back(line);
        }
        file.close();
        return file_text;
    }

    // Writes a file with a supplied array of string values as append or overwrite
    static bool fileWrite(string filename, vector<string>* data, bool isAppend)
    {
        ofstream file;
        if (isAppend)
            file.open(filename, ios_base::app);
        else
            file.open(filename);

        if (!file.is_open())
        {
            cout << "Error opening " << filename << endl;
            return false;
        }

        for (string s : *data)
        {
            file << s << endl;
        }
        file.close();
        return true;
    }
};


