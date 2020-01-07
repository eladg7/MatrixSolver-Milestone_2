#ifndef MILESTONE_2_CACHEMANAGER_H
#define MILESTONE_2_CACHEMANAGER_H
#include <list>
#include <string>

#include<iostream>
#include <fstream>
#include <unistd.h>
#include <unordered_map>
#include <cstring>

using namespace std;

template<typename T>
class CacheManager {
protected:
    int sizeCacheList{};
    list<string> refrenceList;
    unordered_map<std::string, T> mymap;
    const string className = T::class_name;
    char exceptionBuffer[64] = {0};

public:
    virtual void insert(string key, T obj)=0;
    virtual T get(const string &key)=0;
    virtual void foreach(void (*f)(T &))=0;


};

#endif //MILESTONE_2_CACHEMANAGER_H
