#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

class Line
{
    public:
        int ln;
        bool control;
        bool comment;
        int indentation;

        Line(const string & s, int l) 
        {
            indentation = 0;
            control = false;
            comment = false;
            ln = l;
            process(s);
        }
    private:
        void process(const string &s)
        {
            if(s.front() == '#') comment = true;
            if(s.back() == ':') control = true;
            int cnt = 0;
            for(auto c:s)
            {
                if(c == ' ') indentation ++;
                else break;
            }
        }
};

int py_validate(const vector<string>& lines)
{
    stack<Line> s;

    for(int i = 0; i < lines.size(); i ++)
    {
        Line cur = Line(lines.at(i),i);
        if(cur.comment) continue;
        if(s.empty()) s.push(cur);
        else
        {
            Line top = s.top();
            if(top.control)
            {
                if(top.indentation < cur.indentation) s.push(cur);
                else
                {
                    return cur.ln;
                }
            }
            // top is regular
            else
            {
                if(top.indentation == cur.indentation) s.push(cur);
                else if(top.indentation < cur.indentation)
                {
                    return cur.ln;
                }
                // top no control, and cur indentation < top indentation
                else
                {
                    while(!s.empty())
                    {
                        if(s.top().indentation == cur.indentation) 
                        {
                            break;
                        }
                        else if(s.top().indentation > cur.indentation) s.pop();
                        else
                        {
                            return cur.ln;
                        }
                    }
                    if(s.empty()) return cur.ln;
                    s.push(cur);
                }
            }
        }
    }
    if(s.top().control) return s.top().ln;

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
        cout << "Invalid line num is " << line_num +1 << endl;
    } else {
        cout << "Valid python!" << endl;
    }
}
