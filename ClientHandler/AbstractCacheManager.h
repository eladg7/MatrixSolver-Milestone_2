#ifndef MILESTONE_2_ABSTRACTCACHEMANAGER_H
#define MILESTONE_2_ABSTRACTCACHEMANAGER_H

#include "CacheManager.h"

template<typename T>
class AbstractCacheManager : public CacheManager<T> {
public:
    explicit AbstractCacheManager(const string &cn) {
        this->className = cn;
    }

protected:
    int sizeCacheList{};
    list<string> refrenceList;
    unordered_map<string, T*> mymap;
    string className;
    char exceptionBuffer[64] = {0};

    virtual void insert(const string &key, T *obj,int size) {
        // not present in cache
        if (this->mymap.find(key) == this->mymap.end()) {
            // cache is full
            if (this->refrenceList.size() == this->sizeCacheList) {
                // delete least recently used element
                string last = this->refrenceList.back();
                // Pops the last elmeenty
                this->refrenceList.pop_back();
                // Erase the last
                this->mymap.erase(last);
            }

        }
            // present in cache
        else {
            auto it = this->refrenceList.begin();
            while (it != this->refrenceList.end()) {
                if ((*it) == key) {
                    this->refrenceList.erase(it);
                    break;
                } else {
                    ++it;
                }
            }
        }

        // update reference
        this->refrenceList.push_front(key);
        this->mymap[key] = obj;
    }

    virtual void foreach(void (*f)(T* )) {
        for (const string& key:this->refrenceList) {
            f(this->mymap[key]);
        }
    }

};

#endif //MILESTONE_2_ABSTRACTCACHEMANAGER_H
