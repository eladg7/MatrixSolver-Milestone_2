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
    int sizeCacheList;
    list<string> refrenceList;
    unordered_map<std::string, T> mymap;
    const string className = T::class_name;
    char exceptionBuffer[64] = {0};


public:
    explicit CacheManager(int capacity) {
        sizeCacheList = capacity;
    }

    void insert(string key, T obj) {
        insert(key, obj, true);
    }

    void insert(const string &key, const T &obj, bool toWrite) {
        // not present in cache
        if (mymap.find(key) == mymap.end()) {
            // cache is full
            if (refrenceList.size() == sizeCacheList) {
                // delete least recently used element
                string last = refrenceList.back();
                // Pops the last elmeenty
                refrenceList.pop_back();
                // Erase the last
                mymap.erase(last);
            }

        }
            // present in cache
        else {
            auto it = refrenceList.begin();
            while (it != refrenceList.end()) {
                if ((*it) == key) {
                    refrenceList.erase(it);
                    break;
                } else {
                    ++it;
                }
            }
        }

        // update reference
        refrenceList.push_front(key);
        mymap[key] = obj;
        if (toWrite) {
            writeObjectToFile(obj, key);
        }
    }


    T get(const string &key) {
        T obj;
        auto iter = mymap.find(key);
        if (iter != mymap.end()) {
            obj = iter->second;
        }else{
            obj = readObjectFromFile(key);
        }
        insert(key, obj, false);
        return obj;
    }


    void foreach(void (*f)(T &)) {
        for (string key:refrenceList) {
            f(mymap[key]);
        }
    }

    void writeObjectToFile(const T &obj, const string &key) {
        ofstream fileObj;

        char cwd[256] = {0};
        getcwd(cwd, sizeof(cwd));
        strcat(cwd, "/");
        fileObj.open(cwd + className + "_" + key + ".bin", ios::binary | ios::out);
        if (!fileObj) {
            throw "Error creating file.";
        }

        fileObj.write((char *) &obj, sizeof(obj));
        try {
            fileObj.close();
        } catch (exception &e) {
            throw "Couldn't close file.";
        }
    }

    T readObjectFromFile(const string &key) {
        ifstream fileObj;
        char cwd[256] = {0};
        getcwd(cwd, sizeof(cwd));
        strcat(cwd, "/");

        fileObj.open(cwd + className + "_" + key + ".bin", ios::binary | ios::in);
        if (!fileObj) {
            strcpy(exceptionBuffer, "No object file in system: ");
            strcat(exceptionBuffer, (className + " - " + key).c_str());
            throw exceptionBuffer;
        }
        T obj;
        fileObj.read((char *) &obj, sizeof(obj));
        try {
            fileObj.close();
        } catch (exception &e) {
            throw "Couldn't close file.";
        }

        return obj;
    }

};

#endif //MILESTONE_2_CACHEMANAGER_H
