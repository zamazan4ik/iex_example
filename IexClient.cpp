#include "IexClient.h"

#include "IEX.h"

#include "json/reader.h"
#include "json/value.h"
#include "json/writer.h"

CompanyPriceData IexClient::pollCompanyPriceData(const std::string& symbol)
{
    Json::StreamWriterBuilder m_jsonBuilder;

    Json::Value jsonCompany = IEX::stocks::company(symbol);
    Json::Value jsonLogo = IEX::stocks::logo(symbol);
    Json::Value jsonPrice = IEX::stocks::price(symbol);

    CompanyPriceData priceData{
        0, 
        symbol,
        Json::writeString(m_jsonBuilder, jsonCompany["companyName"]), 
        Json::writeString(m_jsonBuilder, jsonLogo["url"]),
        Json::writeString(m_jsonBuilder, jsonPrice)
        };

    return priceData;
}
