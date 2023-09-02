#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Utils

void display_vec(vector<string> vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << ", ";
    }
    cout << endl;
}

void display_vec(vector<char> vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << ", ";
    }
    cout << endl;
}

void display_stack(vector< vector<char> > vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << i+1 << endl;
        for (int j = 0; j < vec[i].size(); j++) {
            cout << vec[i][j] << " ";
        }
        cout << endl;
    }
}

void display_answer(vector< vector<char> > stack) {
    for (int i = 0; i < stack.size(); i++) {
        cout << stack[i][0];
    }
    cout << endl;
}

vector<string> split_str(string str, char separator) {
    stringstream stream(str);
    string segment;
    vector<string> seglist;

    while(getline(stream, segment, separator)){
        seglist.push_back(segment);
    }

    return seglist;
}

// Program

vector< vector<char> > make_stack(vector< vector<char> > stack, string line) {
    for (int i = 0; i < line.length(); i++) {
        if (i%4 == 1 && line[i] != ' ' && !isdigit(line[i])) {
            stack[int(floor(i/4))].push_back(line[i]);
        }
    }
    return stack;
}

vector< vector<char> > apply_many(vector< vector<char> > stack, vector<string> instructions) {
    int origin = stoi(instructions[3]) - 1;
    int destination = stoi(instructions[5]) - 1;
    int quantity = stoi(instructions[1]);

    stack[destination].insert(stack[destination].begin(), stack[origin].begin(), stack[origin].begin() + quantity);
    stack[origin].erase(stack[origin].begin(), stack[origin].begin() + stoi(instructions[1]));

    return stack;
}

vector< vector<char> > apply_one(vector< vector<char> > stack, vector<string> instructions) {
    int origin = stoi(instructions[3]) - 1;
    int destination = stoi(instructions[5]) - 1;

    for (int i = 0; i < stoi(instructions[1]); i++) {
        stack[destination].insert(stack[destination].begin(), stack[origin][0]);
        stack[origin].erase(stack[origin].begin());
    }

    return stack;
}

int main(int argc, char* argv[]) {
    // stack[i][j]; i: stack_number, j: box_id
    vector< vector<char> > stack (9, vector<char>(0));

    string line;
    ifstream file;
    file.open("day_5/input.txt");
    if (file.is_open()) {
        bool isInstructions = false;
        while (getline(file, line)) {
            if (line == "") {
                isInstructions = true;

            } else if (!isInstructions) {
                stack = make_stack(stack, line);

            } else {
                vector<string> instructions = split_str(line, ' ');
                // stack = apply_one(stack, instructions);
                stack = apply_many(stack, instructions);

            }
        }
        display_answer(stack);
        file.close();
    }
    return 0;
}
