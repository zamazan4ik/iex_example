#include "IEX.h"

#include "CLI/CLI.hpp"

#include "json/reader.h"
#include "json/value.h"
#include "json/writer.h"

#include "sqlite_orm/sqlite_orm.h"

#include <chrono>
#include <fstream>
#include <string>
#include <thread>
#include <vector>

struct Price
{
    int id;
    std::string jsonPrice;
};

void service(const int pollIntervalInSec, const std::vector<std::string>& symbols)
{
    auto storage = sqlite_orm::make_storage(":memory:",
                       sqlite_orm::make_table("users",
                           sqlite_orm::make_column("id", &Price::id, sqlite_orm::autoincrement(),
                               sqlite_orm::primary_key()),
                            sqlite_orm::make_column("jsonPrice", &Price::jsonPrice)));

    while (true)
    {
        for(const auto& symbol : symbols)
        {
            Json::Value jsonPrice = IEX::stocks::price(symbol);
            Json::Value jsonLogos = IEX::stocks::logo(symbol);

            Json::StreamWriterBuilder builder;
            const std::string output = Json::writeString(builder, jsonPrice);

            Price price{1, output };

            storage.insert(price);
        }

        std::this_thread::sleep_for(std::chrono::seconds(pollIntervalInSec));
    }
}

Json::Value parseJson(const std::string& inputFilename)
{
    Json::Value root;
    Json::Reader reader;
    std::ifstream test(inputFilename, std::ifstream::binary);
    bool parsingSuccessful = reader.parse(test, root, false);
    if (!parsingSuccessful)
    {
        // Rewrite error handling
        std::cout << reader.getFormattedErrorMessages() << "\n";
    }

    return root["symbols"];
}

std::vector<std::string> parseSymbols(const std::string& inputFilename)
{
    Json::Value root = parseJson(inputFilename);
    std::vector<std::string> result;

    for(int i = 0; i < root.size(); ++i)
    {
        result.push_back(root[i].asString());
    }

    return result;
}

int main(int argc, char* argv[])
{
    try
    {
        CLI::App app{"IEX application"};

        const int DefaultPollIntervalInSec = 60;

        int intervalInSec = DefaultPollIntervalInSec;
        std::string inputFilenameWithCompanies;
        app.add_option("-i,--interval", intervalInSec, "Poll interval in seconds");
        app.add_option("-s,--symbols", inputFilenameWithCompanies, "Symbols which we need poll")->required();

        CLI11_PARSE(app, argc, argv);

        const auto symbols = parseSymbols(inputFilenameWithCompanies);

        service(intervalInSec, symbols);
    }
    catch (const std::exception& e)
    {
        std::cerr << "[main]: An exception was thrown: " << e.what();
    }
    catch (...)
    {
        std::cerr << "[main]: Some unknown exception was thrown";
    }
}
#pragma clang diagnostic pop