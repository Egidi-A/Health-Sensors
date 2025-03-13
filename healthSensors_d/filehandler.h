#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "./MODELLO/SensoriCollection.h"
#include <string>

class FileHandler {
public:
    void salvaDati(const SensoriCollection* collezione, const std::string& percorsoFile);
    SensoriCollection* caricaDati(const std::string& percorsoFile);
};

#endif // FILEHANDLER_H
