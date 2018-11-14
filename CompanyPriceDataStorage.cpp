#include "CompanyPriceDataStorage.h"

CompanyPriceDataStorage::CompanyPriceDataStorage(const std::string& dbFilePath) : 
    m_storage(make_storage_query(dbFilePath))
{
    m_storage.sync_schema();
    m_storage.remove_all<CompanyPriceData>();
}

void CompanyPriceDataStorage::store(const CompanyPriceData& data)
{
    m_storage.insert(data);
}

CompanyPriceData CompanyPriceDataStorage::read(int id)
{
    auto rows = m_storage.select(
        sqlite_orm::columns(&CompanyPriceData::id, &CompanyPriceData::symbol, &CompanyPriceData::companyName, &CompanyPriceData::logo, &CompanyPriceData::price), 
        sqlite_orm::where(sqlite_orm::is_equal(&CompanyPriceData::id, id))
        );

    for(auto &row : rows) {
        CompanyPriceData data{std::get<0>(row), std::get<1>(row), std::get<2>(row), std::get<3>(row), std::get<4>(row)};
        return data;
    }

    throw std::runtime_error("Entity not found");
}
