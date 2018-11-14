#define CATCH_CONFIG_MAIN 
#include <catch.hpp>

#include "CompanyPriceDataStorage.h"

/*
 That's a sample test case
*/
TEST_CASE( "Company price data is stored and selecte3d", "[storage]" ) {
    CompanyPriceData etalonData{0, "1", "2", "3", "4"}
    CompanyPriceDataStorage storage("test.db");
    const int id = storage.store(etalonData);
    const CompanyPriceData storedData = storage.read(id);

    CHECK_THAT(etalonData.symbol, Equals(storedData.symbol));
    CHECK_THAT(etalonData.companyName, Equals(storedData.companyName));
    CHECK_THAT(etalonData.logo, Equals(storedData.logo));
    CHECK_THAT(etalonData.price, Equals(storedData.price));
}
