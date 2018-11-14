#pragma once

#include "CompanyPriceData.h"

#include "sqlite_orm/sqlite_orm.h"

#include <string>

template <typename... Args>
auto make_storage_query(const std::string& dbFilePath) {
    return sqlite_orm::make_storage(dbFilePath,
                        sqlite_orm::make_table("COMPANY_DATA",
                            sqlite_orm::make_column("ID", &CompanyPriceData::id, sqlite_orm::autoincrement(), sqlite_orm::primary_key()),
                            sqlite_orm::make_column("SYMBOL", &CompanyPriceData::symbol),
                            sqlite_orm::make_column("COMPANY_NAME", &CompanyPriceData::companyName),
                            sqlite_orm::make_column("LOGO", &CompanyPriceData::logo),
                            sqlite_orm::make_column("PRICE", &CompanyPriceData::price)
                            ));
}

class CompanyPriceDataStorage
{
public:
    CompanyPriceDataStorage(const std::string& dbFilePath);

    void store(const CompanyPriceData& data);
    CompanyPriceData read(int id);

private:
    decltype(make_storage_query("")) m_storage;
};
