#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

struct Line {
    int num = 0;
    int indentation = 0;
    bool control = false;
    void process(const string& line, int line_num) {
        num = line_num;
        bool start = true;
        for (auto iter = line.begin(); iter != line.end(); iter++) {
            if (*iter == ' ') {
                if (start) {
                    indentation++;
                }
            }  else {
                start = false;
            }
        }
        if (line.back() == ':') {
            control = true;
        }
    }
};

int py_validate(const vector<string>& lines)
{
    stack<Line> s;
    int line_num = 0;
    for (const auto& line_str: lines) {
        line_num++;
        Line line;
        line.process(line_str, line_num);
        if (!s.empty()) {
            auto top = s.top();
            if (top.control) {
                if (line.indentation <= top.indentation) {
                    return line_num;
                } else {
                    s.push(line);
                }
            } else {
                if (line.indentation == top.indentation) {
                    s.push(line);
                } else if (line.indentation < top.indentation) {
                    while (!s.empty()) {
                        if (line.indentation == s.top().indentation) {
                            break;
                        } else if (line.indentation < s.top().indentation) {
                            s.pop();
                        } else {
                            return line_num;
                        }
                    }
                    if (s.empty()) {
                        return line_num;
                    }
                    s.push(line);
                } else {
                    return line_num;
                }
            }
        } else {
            s.push(line);
        }
    }
    if (s.top().control) {
        return s.top().num;
    }
    return -1;
}

int main(int argc, char** argv)
{
    ifstream input(argv[1]);
    vector<string> lines;
    string line;
    while(getline(input, line)) {
        lines.push_back(line);
    }
    input.close();
    int line_num = py_validate(lines);
    if (line_num != -1) {
        cout << "Invalid line num is " << line_num << endl;
    } else {
        cout << "Valid python!" << endl;
    }
}
