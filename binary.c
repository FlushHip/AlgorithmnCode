#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
 
#define MAX_SIZE (300000 + 5)
 
typedef struct tagNode {
    int val, id;
}Node;
 
Node nodes[MAX_SIZE];
 
int cmp(const void *a, const void *b)
{
    Node *pa = (Node *)a;
    Node *pb = (Node *)b;
    return pa->val == pa->val ? pa->id - pb->id :
        pa->val - pb->val;
}
 
int main()
{
    int n, m, k;
    while (EOF != scanf("%d", &n)) {
        int i, l, r, mid, L, R;
        memset(nodes, 0, sizeof(nodes));
        for (i = 0; i < n; i++)
            scanf("%d", &nodes[i].val), nodes[i].id = i;
        qsort(nodes, n, sizeof(nodes[0]), cmp);
 
        scanf("%d", &m);
        for (i = 0; i < m; i++) {
            int left, right, lleft, rright;
 
            scanf("%d%d%d", &L, &R, &k);
 
            l = 0, r = n;
            while (l < r) {
                mid = (l + r) / 2;
                if (nodes[mid].val < k)
                    l = mid + 1;
                else
                    r = mid;
            }
            left = l;
 
            l = -1, r = n - 1;
            while (l < r) {
                mid = (l + r + 1) / 2;
                if (nodes[mid].val > k)
                    r = mid - 1;
                else
                    l = mid;
            }
            right = l;
 
            l = left, r = right + 1;
            while (l < r) {
                mid = (l + r) / 2;
                if (nodes[mid].id < L - 1)
                    l = mid + 1;
                else
                    r = mid;
            }
            lleft = l;
 
            l = left - 1, r = right;
            while (l < r) {
                mid = (l + r + 1) / 2;
                if (nodes[mid].id > R - 1)
                    r = mid - 1;
                else
                    l = mid;
            }
            rright = l;
 
            assert(rright + 1 >= lleft);
 
            printf("%d\n", rright - lleft + 1);
        }
    }
    return 0;
}

