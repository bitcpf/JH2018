#include <iostream>
#include <string>

using namespace std;


void reverse_str(string & str, int l, int r)
{
    while(l < r)
    {
        swap(str.at(l),str.at(r));
        l ++;
        r --;
    }
}


void reverse_html(string & html)
{
    int r = html.size()-1;
    reverse_str(html, 0,r);
    cout << "r total : " << html << endl;
    int start;
    int end;
    for(int i = 0; i < html.size(); i ++)
    {
        while(i < html.size() && html.at(i)!=';')
        {
            i ++;
        }
        start = i;
        while(i < html.size() && html.at(i)!='&')
        {
            i ++;
        }
        end = i;
        if(end < html.size())
        {
            reverse_str(html, start, end);
        }
    }
}

int main(int argc, char** argv)
{
    string html("ni hao&lt; ya&gt;&;");
    cout << html << endl;
    reverse_html(html);
    cout << html << endl;
}
