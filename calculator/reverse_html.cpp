#include <iostream>
#include <string>

using namespace std;

void reverse_str(string::iterator iter, size_t size)
{
    string::iterator end = iter + size - 1;
    for (int i = 0; i < size/2; i++) {
        swap(*iter++, *end--);
    }
}

void reverse_html(string& html)
{
    reverse_str(html.begin(), html.size());
    string::iterator begin;
    for (auto iter = html.begin(); iter != html.end(); iter++) {
        if (*iter == ';') {
            begin = iter;
        } else if (*iter == '&') {
            reverse_str(begin, std::distance(begin, iter) + 1);
        }
    }
}

int main(int argc, char** argv)
{
    string html("ni hao&lt; ya&gt;&;");
    reverse_html(html);
    cout << html << endl;
}