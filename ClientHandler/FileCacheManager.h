#ifndef MILESTONE_2_FILECACHEMANAGER_H
#define MILESTONE_2_FILECACHEMANAGER_H

#include "AbstractCacheManager.h"

using namespace std;

template<typename T>
class FileCacheManager : public AbstractCacheManager<T> {
private:
    stringstream _stringstream;
    hash<string> hasher;

    bool is_digits(const std::string &str) {
        return all_of(str.begin(), str.end(), ::isdigit);
    }

    string hashedToString(string key) {
        string temp;
        if (!is_digits(key)) {
            _stringstream << this->hasher(key);
            temp = _stringstream.str();
            stringstream().swap(_stringstream);
        } else {
            temp = key;
        }
        return temp;
    }

public:
    explicit FileCacheManager(int capacity, const string &className) : AbstractCacheManager<T>(className) {
        this->sizeCacheList = capacity;
    }

    virtual void insert(string key, T obj) {
        insert(key, obj, true);
    }

    void insert(const string &key, const T &obj, bool toWrite) {
        string hashedKey = hashedToString(key);

        AbstractCacheManager<T>::insert(hashedKey, obj);
        if (toWrite) {
            writeObjectToFile(obj, hashedKey);
        }
    }

    virtual T get(const string &key) {
        string hashedKey = hashedToString(key);
        T obj;
        auto iter = this->mymap.find(hashedKey);
        if (iter != this->mymap.end()) {
            obj = iter->second;
        } else {
            obj = readObjectFromFile(hashedKey);
        }
        insert(hashedKey, obj, false);
        return obj;
    }

    void writeObjectToFile(const T &obj, const string &key) {
        string hashedKey = hashedToString(key);
        ofstream fileObj;

        char cwd[256] = {0};
        getcwd(cwd, sizeof(cwd));
        strcat(cwd, "/");
        fileObj.open(cwd + this->className + "_" + hashedKey + ".bin", ios::binary | ios::out);
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
        string hashedKey = hashedToString(key);
        ifstream fileObj;
        char cwd[256] = {0};
        getcwd(cwd, sizeof(cwd));
        strcat(cwd, "/");

        fileObj.open(cwd + this->className + "_" + hashedKey + ".bin", ios::binary | ios::in);
        if (!fileObj) {
            return NULL;
        }
        T obj;
        if (!fileObj.read((char *) &obj, sizeof(obj))) {
            cerr << "Couldn't read object from file." << endl;
        };
        try {
            fileObj.close();
        } catch (exception &e) {
            throw "Couldn't close file.";
        }

        return obj;
    }


    virtual bool keyExist(const string &key) {
        string hashedKey = hashedToString(key);
        bool isExist = false;
        string fileName = this->className + "_" + hashedKey + ".bin";
        auto iter = this->mymap.find(hashedKey);
        if (iter != this->mymap.end() || fexists(fileName.c_str())) {
            isExist = true;
        }
        return isExist;
    }

    bool fexists(const char *filename) {
        std::ifstream ifile(filename);
        return (bool) ifile;
    }
};


#endif //MILESTONE_2_FILECACHEMANAGER_H
