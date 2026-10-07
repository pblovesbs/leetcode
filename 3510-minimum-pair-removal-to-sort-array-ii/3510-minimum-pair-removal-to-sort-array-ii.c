#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    long long sum;
    int u;
    int v;
} Pair;

typedef struct {
    Pair* data;
    int size;
    int capacity;
} MinHeap;

void push(MinHeap* heap, long long sum, int u, int v) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = (Pair*)realloc(heap->data, heap->capacity * sizeof(Pair));
    }
    heap->data[heap->size].sum = sum;
    heap->data[heap->size].u = u;
    heap->data[heap->size].v = v;
    int i = heap->size;
    heap->size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap->data[i].sum < heap->data[p].sum || 
           (heap->data[i].sum == heap->data[p].sum && heap->data[i].u < heap->data[p].u)) {
            Pair temp = heap->data[i];
            heap->data[i] = heap->data[p];
            heap->data[p] = temp;
            i = p;
        } else {
            break;
        }
    }
}

Pair pop(MinHeap* heap) {
    Pair res = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    int i = 0;
    while (2 * i + 1 < heap->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (heap->data[left].sum < heap->data[smallest].sum || 
           (heap->data[left].sum == heap->data[smallest].sum && heap->data[left].u < heap->data[smallest].u)) {
            smallest = left;
        }
        if (right < heap->size && 
           (heap->data[right].sum < heap->data[smallest].sum || 
           (heap->data[right].sum == heap->data[smallest].sum && heap->data[right].u < heap->data[smallest].u))) {
            smallest = right;
        }
        if (smallest != i) {
            Pair temp = heap->data[i];
            heap->data[i] = heap->data[smallest];
            heap->data[smallest] = temp;
            i = smallest;
        } else {
            break;
        }
    }
    return res;
}

int minimumPairRemoval(int* nums, int numsSize) {
    if (numsSize <= 1) return 0;
    
    long long* val = (long long*)malloc(numsSize * sizeof(long long));
    int* prev = (int*)malloc(numsSize * sizeof(int));
    int* next = (int*)malloc(numsSize * sizeof(int));
    bool* active = (bool*)malloc(numsSize * sizeof(bool));
    
    int inversions = 0;
    for (int i = 0; i < numsSize; i++) {
        val[i] = nums[i];
        prev[i] = i - 1;
        next[i] = (i == numsSize - 1) ? -1 : i + 1;
        active[i] = true;
        if (i > 0 && nums[i - 1] > nums[i]) {
            inversions++;
        }
    }
    
    if (inversions == 0) {
        free(val); free(prev); free(next); free(active);
        return 0;
    }
    
    MinHeap heap;
    heap.size = 0;
    heap.capacity = numsSize * 3;
    heap.data = (Pair*)malloc(heap.capacity * sizeof(Pair));
    
    for (int i = 0; i < numsSize - 1; i++) {
        push(&heap, val[i] + val[i + 1], i, i + 1);
    }
    
    int ops = 0;
    while (heap.size > 0) {
        Pair p = pop(&heap);
        int u = p.u;
        int v = p.v;
        
        if (!active[u] || !active[v] || next[u] != v) continue;
        
        // This check ensures we discard stale entries where val[u] or val[v] was updated
        if (p.sum != val[u] + val[v]) continue;
        
        if (prev[u] != -1 && val[prev[u]] > val[u]) inversions--;
        if (val[u] > val[v]) inversions--;
        if (next[v] != -1 && val[v] > val[next[v]]) inversions--;
        
        val[u] = val[u] + val[v];
        active[v] = false;
        
        next[u] = next[v];
        if (next[u] != -1) {
            prev[next[u]] = u;
        }
        
        if (prev[u] != -1 && val[prev[u]] > val[u]) inversions++;
        if (next[u] != -1 && val[u] > val[next[u]]) inversions++;
        
        if (prev[u] != -1) {
            push(&heap, val[prev[u]] + val[u], prev[u], u);
        }
        if (next[u] != -1) {
            push(&heap, val[u] + val[next[u]], u, next[u]);
        }
        
        ops++;
        if (inversions == 0) {
            break;
        }
    }
    
    free(val);
    free(prev);
    free(next);
    free(active);
    free(heap.data);
    
    return ops;
}