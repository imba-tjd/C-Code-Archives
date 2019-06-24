// https://leetcode.com/submissions/detail/132646062/
#include <stdio.h>
#include <stdlib.h>

struct hash_item_s {
    int key;
    int value;
    struct hash_item_s *next;
};

typedef struct hash_item_s hash_item_t;

struct hash_table_s {
    hash_item_t **array;
};

typedef struct hash_table_s hash_table_t;

#define TABLE_SIZE 1023

void put(hash_table_t *table, int key, int value) {
    size_t index = (size_t)key;
    index = index % TABLE_SIZE;
    if (table->array[index] == NULL) {
        hash_item_t *item = malloc(sizeof(hash_item_t));
        item->key = key;
        item->value = value;
        item->next = NULL;
        table->array[index] = item;
    } else {
        hash_item_t *item = table->array[index];
        hash_item_t *prev = NULL;
        while(item != NULL) {
            if (item->key == key) {
                item->value = value;
                break;
            }
            prev = item;
            item = item->next;
        }
        if (item == NULL) {
            hash_item_t *newitem = malloc(sizeof(hash_item_t));
            newitem->key = key;
            newitem->value = value;
            newitem->next = NULL;
            prev->next = newitem;
        }
    }
}

int get(hash_table_t *table, int key) {
    size_t index = (size_t)key;
    index = index % TABLE_SIZE;
    if (table->array[index]==NULL) {
        return -1;
    } else {
        hash_item_t *item = table->array[index];
        while(item != NULL) {
            if (item->key == key) {
                return item->value;
            }
            item = item->next;
        }
        return -1;
    }
}

int contains(hash_table_t *table, int key) {
    size_t index = (size_t)key;
    index = index % TABLE_SIZE;
    if (table->array[index]==NULL) {
        return 0;
    } else {
        hash_item_t *item = table->array[index];
        while(item != NULL) {
            if (item->key == key) {
                return 1;
            }
            item = item->next;
        }
        return 0;
    }
}

void free_table(hash_table_t *table) {
    for (int i=0;i<TABLE_SIZE;i++) {
        if (table->array[i] != NULL) {
            hash_item_t *item = table->array[i];
            while(item != NULL) {
                hash_item_t *next = item->next;
                free(item);
                item = next;
            }
        }
    }
    free(table->array);
    free(table);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target) {
    int i;
    int *result;
    hash_table_t *table = malloc(sizeof(hash_table_t));
    table->array = calloc(TABLE_SIZE, sizeof(hash_item_t*));

    result = malloc(sizeof(int) * 2);

    for(i=0;i<numsSize;i++) {
        if (contains(table, target - nums[i])) {
            result[0] = get(table, target - nums[i]);
            result[1] = i;
        } else {
            put(table, nums[i], i);
        }
    }

    //free_table(table);
    return result;
}
