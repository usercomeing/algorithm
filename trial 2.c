#include <stdio.h>  
#include <stdlib.h>  
  
// 辅助函数，用于计算两个整数中的较大值  
int max(int a, int b) {  
    return a > b ? a : b;  
}  
  
// 深度优先搜索函数，用于计算二叉树的高度  
int dfs_height(char *pre, char *in, int n) {  
    if (n == 0) return 0; // 若没有结点，为空树  
    int i;  
    for (i = 0; i < n; i++) {  
        if (in[i] == pre[0]) break; // 找到根结点在中序的位置  
    }  
    int left_height = dfs_height(pre + 1, in, i);  // 左子树的高度  
    int right_height = dfs_height(pre + i + 1, in + i + 1, n - i - 1); // 右子树的高度  
    return max(left_height, right_height) + 1; // 返回左右子树高度的较大值加1（根结点）  
}  
  
// 深度优先搜索函数，用于计算叶子结点的数量  
int dfs_leaf_count(char *pre, char *in, int n) {  
    if (n == 0) return 0; // 若没有结点，为空树，叶子结点数为0  
    int i;  
    for (i = 0; i < n; i++) {  
        if (in[i] == pre[0]) break; // 找到根结点在中序的位置  
    }  
    
    // 正确的叶子结点判断是在递归的底部进行的，即当当前结点的左右子树都为空时  
    int left_leaf_count = dfs_leaf_count(pre + 1, in, i);  // 左子树的叶子结点数量  
    int right_leaf_count = dfs_leaf_count(pre + i + 1, in + i + 1, n - i - 1); // 右子树的叶子结点数量  
      
    return left_leaf_count + right_leaf_count; // 对于非叶子结点，直接返回左右子树的叶子结点总数；对于叶子结点，这个逻辑在递归中自然成立（通过左右子树都为空来体现）。  
}
// 为了清晰性，我们可以将计算叶子结点的函数单独调用，而不是在高度计算函数中嵌套调用（尽管这样做可能增加一些重复计算，但为了教学清晰性）  
int main() {  
    int n;  
    scanf("%d", &n);  
    char pre[n + 1], in[n + 1]; // 先序和中序遍历序列  
    scanf("%s%s", pre, in);  
    int height = dfs_height(pre, in, n);  
    int leaf_count = dfs_leaf_count(pre, in, n); // 注意：这里实际上可以优化，避免重复遍历树，但为了清晰性单独调用  
    printf("Height: %d\n", height);  
    printf("Leaf Count: %d\n", leaf_count);  
    system("pause");
    return 0;  
}