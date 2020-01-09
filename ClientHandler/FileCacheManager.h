#ifndef MILESTONE_2_FILECACHEMANAGER_H
#define MILESTONE_2_FILECACHEMANAGER_H

#include "AbstractCacheManager.h"

using namespace std;

template<typename T>
class FileCacheManager : public AbstractCacheManager<T> {

public:
    explicit FileCacheManager(int capacity) {
        this->sizeCacheList = capacity;
    }

    virtual void insert(string key, T obj) {
        insert(key, obj, true);
    }

    void insert(const string &key, const T &obj, bool toWrite) {
        AbstractCacheManager<T>::insert(key, obj);
        if (toWrite) {
            writeObjectToFile(obj, key);
        }
    }

    virtual T get(const string &key) {
        T obj = NULL;
        auto iter = this->mymap.find(key);
        if (iter != this->mymap.end()) {
            obj = iter->second;
        } else {
            obj = readObjectFromFile(key);
        }
        insert(key, obj, false);
        return obj;
    }

    void writeObjectToFile(const T &obj, const string &key) {
        ofstream fileObj;

        char cwd[256] = {0};
        getcwd(cwd, sizeof(cwd));
        strcat(cwd, "/");
        fileObj.open(cwd + this->className + "_" + key + ".bin", ios::binary | ios::out);
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

        fileObj.open(cwd + this->className + "_" + key + ".bin", ios::binary | ios::in);
        if (!fileObj) {
            return NULL;
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


    virtual bool keyExist(const string &key) {
        bool isExist = false;
        string fileName= this->className + "_" + key + ".bin";
        auto iter = this->mymap.find(key);
        if (iter != this->mymap.end()) {
            isExist = true;
        }else if(fexists(fileName.c_str())){
            isExist=true;
        }
        return isExist;
    }

    bool fexists(const char *filename) {
        std::ifstream ifile(filename);
        return (bool)ifile;
    }
};


#endif //MILESTONE_2_FILECACHEMANAGER_H
