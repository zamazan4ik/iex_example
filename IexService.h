#pragma once

#include "CompanyPriceDataStorage.h"

#include <string>
#include <vector>

class IexService
{
public:

    IexService(const std::string& storagePath);

    void serve(const int pollIntervalInSec, const std::vector<std::string>& symbols);

private:
    CompanyPriceDataStorage m_storage;
};
