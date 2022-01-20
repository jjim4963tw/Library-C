//
// Created by Jim on 2022/1/17.
//

#ifndef FILECLOUD_AS_HASH_MAP_H
#define FILECLOUD_AS_HASH_MAP_H

/**
 * 定義 key - value 結構
 */
typedef struct hash_entry {
    void *key;
    void *value;
    struct hash_entry *next;
} *Entry;

/**
 * 定義列舉的 Boolean 型態
 */
enum _Boolean { True = 1, False = 0 };
typedef enum _Boolean Boolean;

/**
 * 定義 HashMap 結構
 */
typedef struct hashMap *HashMap;

/**
 * 定義 HashCode
 */
typedef int(*HashCode)(HashMap, void *key);

/**
 * 定義判定相等的函數
 */
typedef Boolean(*Equal)(void *key1, void *key2);

/**
 * 定義新增key-value參數的函數
 */
typedef void (*Put)(HashMap hashMap, void *key, void *value);

/**
 * 定義取得key-value參數的函數
 */
typedef void *(*Get)(HashMap hashMap, void *key);

/**
 * 定義刪除key-value參數的函數
 */
typedef Boolean (*Remove)(HashMap hashMap, void *key);

/**
 * 定義清除HashMap 所有內容的函數
 */
typedef void (*Clear)(HashMap hashMap);

/**
 * 定義判斷 Key 是否存在的函數
 */
typedef Boolean (*Exists)(HashMap hashMap, void *key);

typedef struct hashMap {
    // 當前大小
    int size;
    // 有效空間的大小
    int list_size;
    // Hash Function
    HashCode hash_code;
    // 判定相等函數
    Equal equal;
    // 儲存空間
    Entry list;
    // 新增 Key 函數
    Put put;
    // 取得 key 對應 value 函數
    Get get;
    // 刪除 key
    Remove remove;
    // 清空 map
    Clear clear;
    // 判斷key 是否存在
    Exists exists;
    // 決定是否根據當前數據量動態調整大小，預設開啟
    Boolean auto_assign;
} *HashMap;

static int default_hash_code(HashMap hashMap, void *key);

static Boolean default_equal(void * key1, void * key2);

static void default_put(HashMap hashMap, void *key, void *value);

static void *default_get(HashMap hashMap, void *key);

static Boolean default_remove(HashMap hashMap, void *key);

static Boolean default_exists(HashMap hashMap, void *key);

static void default_clear(HashMap hashMap);

HashMap create_hash_map(HashCode hashCode, Equal equal);

static void reset_hash_map(HashMap hashMap, int list_size);


typedef struct iterator {
    Entry entry;
    int count;
    int hash_code;
    HashMap hash_map;
} *Iterator;

Iterator create_iterator(HashMap hashMap);

Boolean has_next(Iterator iterator);

Iterator next(Iterator iterator);

void free_iterator(Iterator *iterator);

#endif //FILECLOUD_AS_HASH_MAP_H
