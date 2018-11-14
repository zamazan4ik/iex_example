#pragma once

#include <string>

#include "CompanyPriceData.h"

class IexClient
{
public:
    CompanyPriceData pollCompanyPriceData(const std::string& symbol);
};
