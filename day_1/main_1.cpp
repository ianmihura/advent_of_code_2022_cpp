#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    int elf_highest_calories = 0;

    string line;
    ifstream file;
    file.open("day_1/input.txt");
    if (file.is_open()) {

        int elf_current_calories = 0;
        while (getline(file, line)) {
            if (line == "") {
                if (elf_highest_calories < elf_current_calories) {
                    elf_highest_calories = elf_current_calories;
                }
                elf_current_calories = 0;
            } else {
                elf_current_calories += stoi(line);
            } 
        }
    }
    file.close();
    cout << "Elf highest calories: " << elf_highest_calories << endl;
    return 0;
}
