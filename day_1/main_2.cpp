#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    vector<int> elves;

    string line;
    ifstream file;
    file.open("day_1/input.txt");
    if (file.is_open()) {

        int elf_current = 0;
        while (getline(file, line)) {
            if (line == "") {
                elves.push_back(elf_current);
                elf_current = 0;
            } else {
                elf_current += stoi(line);
            } 
        }
    }
    file.close();

    sort(elves.begin(), elves.end(), greater<int>());
    int total = elves[0] + elves[1] + elves[2];
    cout << "Elf highest calories: " << total << endl;
    return 0;
}
