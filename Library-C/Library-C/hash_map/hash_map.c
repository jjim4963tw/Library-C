//
// Created by Jim on 2022/1/17.
//

#include "hash_map.h"
#include <stdlib.h>
#include <string.h>

/**
 * Hash Table Function：單獨鍊表法
 */
static int default_hash_code(HashMap hashMap, void *key) {
    char *k = (char *) key;
    unsigned long h = 0;
    while (*k) {
        h = (h << 4) + *k++;
        unsigned long g = h & 0xF0000000L;
        if (g) {
            h ^= g >> 24;
        }
        h &= ~g;
    }
    return h % hashMap->list_size;
}

void reset_hash_map(HashMap hashMap, int list_size) {
    if (list_size < 8) {
        return;
    }

    Entry temp_list = (Entry) malloc(hashMap->size * sizeof(struct hash_entry));

    Iterator iterator = create_iterator(hashMap);
    int length = hashMap->size;
    for (int index = 0; has_next(iterator); index++) {
        // 取出所有 key-value
        iterator = next(iterator);

        temp_list[index].key = calloc(strlen(iterator->entry->key) + 1, sizeof(char));
        strncpy(temp_list[index].key, iterator->entry->key, strlen(iterator->entry->key));

        temp_list[index].value = calloc(strlen(iterator->entry->value) + 1, sizeof(char));
        strncpy(temp_list[index].value, iterator->entry->value, strlen(iterator->entry->value));

        temp_list[index].next = NULL;
    }
    free_iterator(&iterator);

    // 清除原有 key-value data
    hashMap->size = 0;
    for (int index = 0; index < hashMap->list_size; index++) {
        Entry current = &hashMap->list[index];
        free(current->key);
        free(current->value);
        current->key = current->value = NULL;

        if (current->next != NULL) {
            while (current->next != NULL) {
                Entry temp_entry = current->next->next;
                free(current->next);
                current->next = temp_entry;
            }
        }
    }

    // 重新配置記憶體大小
    hashMap->list_size = list_size;
    Entry relist = (Entry) realloc(hashMap->list, hashMap->list_size * sizeof(struct hash_entry));
    if (relist != NULL) {
        hashMap->list = relist;
        relist = NULL;
    }

    // 初始化
    for (int index = 0; index < hashMap->list_size; index++) {
        hashMap->list[index].key = NULL;
        hashMap->list[index].value = NULL;
        hashMap->list[index].next = NULL;
    }

    // 將所有 key-value 重新寫入記憶體中
    for (int index = 0; index < length; index++) {
        hashMap->put(hashMap, temp_list[index].key, temp_list[index].value);
    }

    free(temp_list);
}

void default_put(HashMap hashMap, void *key, void *value) {
    if (hashMap->auto_assign && hashMap->size >= hashMap->list_size) {
        /**
         * 記憶體擴充至原有的 2 倍
         * 擴充需考慮的為當前儲存的數據與儲存空間的大小關係，用來改善衝突導致的索引變慢問題。
         * 當size > list_size時，因Hash函數為了不越界，會將計算出的HashCode取餘數，導致HashCode的數量最多 = list_size，超過此個數並定會衝突，索引速度就越接近O(n)。
         */
        reset_hash_map(hashMap, hashMap->list_size * 2);
    }

    int index = hashMap->hash_code(hashMap, key);
    if (hashMap->list[index].key == NULL) {
        // 當該記憶體位址為NULL時，直接存入key-value
        hashMap->size++;

        hashMap->list[index].key = calloc(strlen(key) + 1, sizeof(char));
        strncpy(hashMap->list[index].key, key, strlen(key));

        hashMap->list[index].value = calloc(strlen(value) + 1, sizeof(char));
        strncpy(hashMap->list[index].value, value, strlen(value));
    } else {
        Entry current_entry = &hashMap->list[index];
        while (current_entry != NULL) {
            if (hashMap->equal(key, current_entry->key)) {
                current_entry->value = value;
                return;
            }
            current_entry = current_entry->next;
        }

        // 當發生衝突時，則創建節點指到對應位址的 next 上
        Entry entry = (struct hash_entry *) malloc(sizeof(struct hash_entry));

        entry->key = calloc(strlen(key) + 1, sizeof(char));
        strncpy(entry->key, key, strlen(key));

        entry->value = calloc(strlen(value) + 1, sizeof(char));
        strncpy(entry->value, value, strlen(value));

        entry->next = hashMap->list[index].next;
        hashMap->list[index].next = entry;
        hashMap->size++;
    }
}

void *default_get(HashMap hashMap, void *key) {
    int index = hashMap->hash_code(hashMap, key);
    Entry entry = &hashMap->list[index];
    while (entry->key != NULL && !hashMap->equal(entry->key, key)) {
        entry = entry->next;
    }
    return entry->value;
}

Boolean default_remove(HashMap hashMap, void *key) {
    int index = hashMap->hash_code(hashMap, key);
    Entry entry = &hashMap->list[index];
    if (entry->key == NULL) {
        return False;
    }
    Boolean result = False;
    if (hashMap->equal(entry->key, key)) {
        hashMap->size--;
        if (entry->next != NULL) {
            Entry temp = entry->next;
            entry->key = temp->key;
            entry->value = temp->value;
            entry->next = temp->next;
            free(temp);
        } else {
            free(entry->key);
            free(entry->value);
            entry->key = entry->value = NULL;
        }
        result = True;
    } else {
        Entry p = entry;
        entry = entry->next;
        while (entry != NULL) {
            if (hashMap->equal(entry->key, key)) {
                hashMap->size--;
                p->next = entry->next;
                free(entry);
                result = True;
                break;
            }
            p = entry;
            entry = entry->next;
        };
    }

    // 如果空间占用不足一半，则释放多余内存
    if (result && hashMap->auto_assign && hashMap->size < hashMap->list_size / 2) {
        reset_hash_map(hashMap, hashMap->list_size / 2);
    }
    return result;
}

Boolean default_exists(HashMap hashMap, void *key) {
    int index = hashMap->hash_code(hashMap, key);
    Entry entry = &hashMap->list[index];
    if (entry->key == NULL) {
        return False;
    }
    if (hashMap->equal(entry->key, key)) {
        return True;
    }
    if (entry->next != NULL) {
        do {
            if (hashMap->equal(entry->key, key)) {
                return True;
            }
            entry = entry->next;

        } while (entry != NULL);
        return False;
    } else {
        return False;
    }
}

Boolean default_equal(void *key1, void *key2) {
    return strcmp((char *) key1, (char *) key2) ? False : True;
}

void default_clear(HashMap hashMap) {
    for (int i = 0; i < hashMap->list_size; i++) {
        Entry entry = hashMap->list[i].next;
        while (entry != NULL) {
            Entry next = entry->next;
            free(entry);
            entry = next;
        }
        hashMap->list[i].next = NULL;
    }
    free(hashMap->list);
    hashMap->list = NULL;
    hashMap->size = -1;
    hashMap->list_size = 0;
}

/**
 * 使用開放定址法初始化 HashMap
 */
HashMap create_hash_map(HashCode hashCode, Equal equal) {
    // 為散列表分配空間
    // 有些编譯器不支持為struct HashTable 分配空間，聲稱這是一個不完全的結構，
    // 可使用一个指向HashTable的指針為之分配空間。
    // 如：sizeof(Probe)，Probe作为HashTable在typedef定義的指針。
    HashMap hash_map = (struct hashMap *) malloc(sizeof(struct hashMap));
    hash_map->size = 0;
    
    // 散列表大小为一个質数
    hash_map->list_size = 8;
    hash_map->hash_code = hashCode == NULL ? default_hash_code : hashCode;
    hash_map->equal = equal == NULL ? default_equal : equal;
    hash_map->exists = default_exists;
    hash_map->get = default_get;
    hash_map->put = default_put;
    hash_map->remove = default_remove;
    hash_map->clear = default_clear;
    hash_map->auto_assign = True;
    
    // 分配表所有地址的空間
    hash_map->list = (Entry) malloc(hash_map->list_size * sizeof(struct hash_entry));

    // 地址初始為空
    Entry p = hash_map->list;
    for (int i = 0; i < hash_map->list_size; i++) {
        p[i].key = p[i].value = p[i].next = NULL;
    }
    return hash_map;
}


Iterator create_iterator(HashMap hashMap) {
    Iterator iterator = (struct iterator *) malloc(sizeof(struct iterator));
    iterator->hash_map = hashMap;
    iterator->count = 0;
    iterator->hash_code = -1;
    iterator->entry = NULL;
    return iterator;
}

Boolean has_next(Iterator iterator) {
    return iterator->count < iterator->hash_map->size ? True : False;
}

Iterator next(Iterator iterator) {
    if (has_next(iterator)) {
        if (iterator->entry != NULL && iterator->entry->next != NULL) {
            iterator->count++;
            iterator->entry = iterator->entry->next;
            return iterator;
        }
        while (++iterator->hash_code < iterator->hash_map->list_size) {
            Entry entry = &iterator->hash_map->list[iterator->hash_code];
            if (entry->key != NULL) {
                iterator->count++;
                iterator->entry = entry;
                break;
            }
        }
    }
    return iterator;
}

void free_iterator(Iterator *iterator) {
    free(*iterator);
    *iterator = NULL;
}
