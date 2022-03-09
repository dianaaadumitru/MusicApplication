#pragma once
#include "IFileRepo.h"

// Comma Separate Value - repository -> writes and reads to a text file in CSV format
class CSVRepo : public IFileRepo {
protected:
    void repoFromFile() override;
    void repoToFile() override;

public:

    CSVRepo(const std::string& source);
    ~CSVRepo() ;
    void display() override;
};