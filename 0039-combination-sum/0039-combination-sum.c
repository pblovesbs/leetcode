void backtrack(int* candidates, int candidatesSize, int target, int start, int* path, int pathLen, int** res, int* returnSize, int** returnColumnSizes) {
    if (target == 0) {
        res[*returnSize] = (int*)malloc(pathLen * sizeof(int));
        for (int i = 0; i < pathLen; i++) {
            res[*returnSize][i] = path[i];
        }
        (*returnColumnSizes)[*returnSize] = pathLen;
        (*returnSize)++;
        return;
    }

    for (int i = start; i < candidatesSize; i++) {
        if (target - candidates[i] >= 0) {
            path[pathLen] = candidates[i];
            backtrack(candidates, candidatesSize, target - candidates[i], i, path, pathLen + 1, res, returnSize, returnColumnSizes);
        }
    }
}

int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    int** res = (int**)malloc(150 * sizeof(int*));
    *returnColumnSizes = (int*)malloc(150 * sizeof(int));
    int path[40];
    
    backtrack(candidates, candidatesSize, target, 0, path, 0, res, returnSize, returnColumnSizes);
    
    return res;
}