#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;


int oprOrder(char c)
{

    if(c == '+' || c == '-') return 1;
    if(c == '*' || c == '/') return 2;
    return 0;
}

int execOpr(char opr, stack<int> & dig)
{
    int rst = 0;
    int n2 = dig.top(); dig.pop();
    int n1 = dig.top(); dig.pop();
    if(opr == '+') rst = n1+n2;
    else if(opr == '-') rst = n1-n2;
    else if(opr == '*') rst = n1*n2;
    else if(opr == '/') rst = n1/n2;
    else cout << "Error opr: " << opr << endl;

    cout << opr << " " << rst << endl;
    dig.push(rst);
    return rst;
}

int processDig(stack<int> & digstk, string & s, int i)
{   

    int dig = 0;
    for(; i < s.size(); i ++)
    {   
        char c = s.at(i);
        if(!(c >= '0' && c <= '9')) break;

        dig = dig*10+(c - '0');
    }
    digstk.push(dig);
    return i-1;
}

void processOpr(stack<int> & digstk, stack<char> & opr, char c)
{
    if(opr.empty() || c == '(') 
    {
        opr.push(c);
        return;
    }
    char oprtop = opr.top();
    if(c == ')')
    {   
        while(!opr.empty() && opr.top() != '(')
        {
            execOpr(oprtop, digstk);
            oprtop = opr.top();
            opr.pop();
        }
        opr.pop();
    }
    else if(oprtop == '(') opr.push(c);
    else if(oprOrder(oprtop) >= oprOrder(c))
    {   
        while(!opr.empty() && oprOrder(opr.top()) >= oprOrder(c))
        {
            execOpr(opr.top(), digstk);
            opr.pop();
        }
        opr.push(c);
    }   
    else if(oprOrder(oprtop) <= oprOrder(c))
    {   
        opr.push(c);
    }   
}



int calculate(string s) {

    stack<char> opr;
    stack<int> digstk;

    // Shunting Yard convert the string to inverse poland 
    for(int i = 0; i < s.size(); i ++) 
    {   
        char c = s.at(i);
        if(!(c >= '0' && c <= '9'))
        {   
            processOpr(digstk, opr, c); 
        }   
        else
        {
            i = processDig(digstk, s, i);
        }
    }

    while(!opr.empty())
    {
        execOpr(opr.top(), digstk);
        opr.pop();

    }

    /*
       for(auto s: ipoland)
       {
       cout << s << " ";
       }
       cout << endl;



       for(int i = 0; i < ipoland.size(); i ++)
       {
       if(ipoland.at(i).size() == 1)
       {
       char o = ipoland.at(i).at(0);
       if(!(o >= '0' && o <= '9'))
       {
       execOpr(o, dig);

       }
       else
       {
       dig.push(stoi(ipoland.at(i)));
       }
       }
       else
       {
       dig.push(stoi(ipoland.at(i)));
       }

       }
     */
    return digstk.top();
}



int main()
{
    //int rst =  calculate("9+(3-1)*3+10/2");
    int rst =  calculate("1*2-3/4+5*6-7*8+9/10");
    cout << "Result: " << rst << endl;
}

