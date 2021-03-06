// reading a text file
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    int x;

    // declare
    ifstream newFile("example.txt");

    // open
    if (newFile.is_open())
    {
        // read from file
        while (!newFile.eof())
        {
            // only works with tab separated values
            newFile >> x;
            cout << x << endl;
        }

        // close
        newFile.close();
    }
    else {
        cout << "Unable to open file";
    }

    return 0;
}