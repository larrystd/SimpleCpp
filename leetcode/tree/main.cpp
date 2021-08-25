#include  <cstdio>
#include"btree.h"

int main()
{
    {
        JBBinaryTree<int> L,R,a,b,c,d,e;
        a.makeTree(0,&L,&R);
        b.makeTree(1,&L,&R);
        c.makeTree(2,&a,&b);
        d.makeTree(3,&a,&b);
        e.makeTree(4,&c,&d);
        printf("前序遍历：");
        e.preOrder(e._root);
        printf("\n中序遍历：");
        e.inOrder(e._root);
        printf("\n后序遍历：");
        e.postOrder(e._root);
        printf("\n");
    }
    return 0;
}