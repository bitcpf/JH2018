#include <iostream>
#include <vector>





using namespace std;

class Node {
    char[] chars = new char[5];  
    int len;
    Node * next;
    public:
        Node (){
    }
}
class UnRolledList {
    Node * head;
    int totalLen;
    public:
        UnRolledList(Node head, int  total){
            this.head= head;
            this.totalLen= total;
        }

        void insert(char ch, int idx)
        {
            Node * node = head;
            int total = totalLen;
            if(node == null || total <0 || index > total)
            {
                return;
            }
            while(node != null && node.len < total)
            {
                node = node->next;
                total -= node.len;
            }

            if(node == null)
            {
                return;
            }
            if(node->len < 5)
            {
                for(int i = node->len; i > total; i --)
                {
                    node->chars[i] = node->chars[i-1];
                }
                node->chars[total] = ch;
            }
            else
            {
                Node newNode = new Node();
                
            }
        }

}


int main()
{



    return 0;
}
