int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

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
        if (i > start && candidates[i] == candidates[i - 1]) {
            continue;
        }
        if (target - candidates[i] < 0) {
            break; 
        }

        path[pathLen] = candidates[i];
        backtrack(candidates, candidatesSize, target - candidates[i], i + 1, path, pathLen + 1, res, returnSize, returnColumnSizes);
    }
}

int** combinationSum2(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    qsort(candidates, candidatesSize, sizeof(int), cmp);
    
    *returnSize = 0;
    int maxAnswers = 2000;
    int** res = (int**)malloc(maxAnswers * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxAnswers * sizeof(int));
    int path[100];
    
    backtrack(candidates, candidatesSize, target, 0, path, 0, res, returnSize, returnColumnSizes);
    
    return res;
}