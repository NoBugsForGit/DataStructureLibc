#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CAPACITY 100

// 哈希表条目结构
typedef struct HashTableEntry
{
    int key;
    char *value;
    struct HashTableEntry *next;
} HashTableEntry;

// 哈希表结构
typedef struct HashTable
{
    HashTableEntry **buckets;
    int capacity;
} HashTable;

// 哈希函数
static int hash(int key, int capacity)
{
    return key % capacity;
}

// 创建哈希表
HashTable *createHashTable(int capacity)
{
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    table->capacity = capacity;
    table->buckets = (HashTableEntry **)malloc(capacity * sizeof(HashTableEntry *));
    for (int i = 0; i < capacity; ++i)
    {
        table->buckets[i] = NULL;
    }
    return table;
}

// 删除哈希表
void deleteHashTable(HashTable *table)
{
    for (int i = 0; i < table->capacity; i++)
    {
        HashTableEntry *entry = table->buckets[i];
        while (entry != NULL)
        {
            HashTableEntry *temp = entry;
            entry = entry->next;
            free(temp->value);
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}

// 插入键值对
bool insert(HashTable *table, int key, const char *value)
{
    int bucketIndex = hash(key, table->capacity);
    HashTableEntry *newEntry = (HashTableEntry *)malloc(sizeof(HashTableEntry));
    if (!newEntry)
        return false;

    newEntry->key = key;
    newEntry->value = strdup(value);
    newEntry->next = table->buckets[bucketIndex];
    table->buckets[bucketIndex] = newEntry;

    return true;
}

// 删除键值对
bool delete_key(HashTable *table, int key)
{
    int bucketIndex = hash(key, table->capacity);
    HashTableEntry *entry = table->buckets[bucketIndex];
    HashTableEntry *prev = NULL;

    while (entry != NULL && entry->key != key)
    {
        prev = entry;
        entry = entry->next;
    }

    if (entry == NULL)
        return false; // 未找到键

    if (prev == NULL)
    {
        table->buckets[bucketIndex] = entry->next;
    }
    else
    {
        prev->next = entry->next;
    }

    free(entry->value);
    free(entry);
    return true;
}

// 查找值
char *search(HashTable *table, int key)
{
    int bucketIndex = hash(key, table->capacity);
    HashTableEntry *entry = table->buckets[bucketIndex];

    while (entry != NULL)
    {
        if (entry->key == key)
        {
            return entry->value;
        }
        entry = entry->next;
    }

    return NULL; // 未找到键
}
