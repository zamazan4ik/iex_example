#include "IexService.h"
#include "IexClient.h"
#include "CompanyPriceData.h"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

IexService::IexService(const std::string& storagePath) :
    m_storage(storagePath)
{
}

void IexService::serve(const int pollIntervalInSec, const std::vector<std::string>& symbols)
{
    IexClient iexClient;

    while (true)
    {
        for(const auto& symbol : symbols)
        {
            std::cout << symbol << std::endl;
            const CompanyPriceData priceData = iexClient.pollCompanyPriceData(symbol);
            m_storage.store(priceData);
        }

        std::this_thread::sleep_for(std::chrono::seconds(pollIntervalInSec));
    }
}
