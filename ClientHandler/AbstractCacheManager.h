#ifndef MILESTONE_2_ABSTRACTCACHEMANAGER_H
#define MILESTONE_2_ABSTRACTCACHEMANAGER_H

#include "CacheManager.h"

template<typename T>
class AbstractCacheManager : public CacheManager<T> {
protected:
    int sizeCacheList{};
    list<string> refrenceList;
    unordered_map<string, T *> mymap;
    string className;
    mutex parallelServerLock;

    virtual void insert(const string key, T *obj, int size) {

        // not present in cache
        parallelServerLock.lock();
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
        } else {
            // present in cache
            auto it = this->refrenceList.begin();
            auto itEnd = this->refrenceList.end();
            while (it != itEnd) {
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
        parallelServerLock.unlock();
    }

    virtual void foreach(void (*f)(T *)) {
        for (const string &key:this->refrenceList) {
            f(this->mymap[key]);
        }
    }

public:
    explicit AbstractCacheManager(const string &cn) {
        this->className = cn;
    }

    virtual ~AbstractCacheManager() {

        auto it = mymap.begin();
        while (it != mymap.end()) {
            delete it->second;
            it++;
        }
    }
};

#endif //MILESTONE_2_ABSTRACTCACHEMANAGER_H
