#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
template <typename T>

// Utils

void display_vec(vector<T> vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << ", ";
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

class Stack {
    public:
        vector< vector<char> > stack;
        vector<char>& operator[] (int i) {
            return stack[i];
        }

        Stack() {
            stack = vector< vector<char> > (9, vector<char>(0));
        };

        void display() {
            for (int i = 0; i < stack.size(); i++) {
                cout << i+1 << endl;
                for (int j = 0; j < stack[i].size(); j++) {
                    cout << stack[i][j] << " ";
                }
                cout << endl;
            }
        };
        void answer() {
            for (int i = 0; i < stack.size(); i++) {
                cout << stack[i][0];
            }
            cout << endl;
        };
};

Stack make_stack(Stack stack, string line) {
    for (int i = 0; i < line.length(); i++) {
        if (i%4 == 1 && line[i] != ' ' && !isdigit(line[i])) {
            stack[int(floor(i/4))].push_back(line[i]);
        }
    }
    return stack;
}

Stack apply_many(Stack stack, vector<string> instructions) {
    int origin = stoi(instructions[3]) - 1;
    int destination = stoi(instructions[5]) - 1;
    int quantity = stoi(instructions[1]);

    stack[destination].insert(stack[destination].begin(), stack[origin].begin(), stack[origin].begin() + quantity);
    stack[origin].erase(stack[origin].begin(), stack[origin].begin() + stoi(instructions[1]));

    return stack;
}

Stack apply_one(Stack stack, vector<string> instructions) {
    int origin = stoi(instructions[3]) - 1;
    int destination = stoi(instructions[5]) - 1;

    for (int i = 0; i < stoi(instructions[1]); i++) {
        stack[destination].insert(stack[destination].begin(), stack[origin][0]);
        stack[origin].erase(stack[origin].begin());
    }

    return stack;
}

int main(int argc, char* argv[]) {
    Stack stack;
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
        stack.answer();
        file.close();
    }
    return 0;
}
