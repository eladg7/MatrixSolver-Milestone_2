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

    virtual void insert(string key, T *obj, int size) {
        insert(key, obj, true, size);
    }

    void insert(const string &key, T *obj, bool toWrite, int size) {
        string hashedKey = hashedToString(key);

        AbstractCacheManager<T>::insert(hashedKey, obj, size);
        if (toWrite) {
            writeObjectToFile(obj, hashedKey, size);
        }
    }

    virtual T* get(const string &key) {
        string hashedKey = hashedToString(key);
        T *obj;
        auto iter = this->mymap.find(hashedKey);
        if (iter != this->mymap.end()) {
            obj = iter->second;
        } else {
            obj = (T *) readObjectFromFile(hashedKey);
        }
        insert(hashedKey, obj, false);
        return obj;
    }

    void writeObjectToFile(T *obj, const string &key, int sizeBytes) {
        string hashedKey = hashedToString(key);
        ofstream fileObj;

        char cwd[256] = {0};
        getcwd(cwd, sizeof(cwd));
        strcat(cwd, "/");
        fileObj.open(cwd + this->className + "_" + hashedKey + ".bin", ios::binary | ios::out);
        if (!fileObj) {
            throw "Error creating file.";
        }

        fileObj.write((char *) obj, sizeBytes);
        try {
            fileObj.close();
        } catch (exception &e) {
            throw "Couldn't close file.";
        }
    }

    char *readObjectFromFile(const string &key) {
        string hashedKey = hashedToString(key);
        ifstream fileObj;
        char cwd[256] = {0};
        getcwd(cwd, sizeof(cwd));
        strcat(cwd, "/");

        fileObj.open(cwd + this->className + "_" + hashedKey + ".bin", ios::binary | ios::in);
        if (!fileObj) {
            cerr << "Couldn't open file to read." << endl;
        }

        //get bytes in file to predict size of object
        streampos fsize = fileObj.tellg();
        fileObj.seekg(0, std::ios::end);
        fsize = fileObj.tellg() - fsize;
        fileObj.seekg(0, std::ios::beg);
        char *obj = new char[(int) fsize + 1];
        memset(obj, 0, (int)fsize + 1);

        if (!fileObj.read((char *) obj, fsize)) {
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
