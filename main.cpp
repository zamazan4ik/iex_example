#include "CompanyPriceData.h"
#include "CompanyPriceDataStorage.h"
#include "IexService.h"

#include "CLI/CLI.hpp"

#include <fstream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    try
    {
        CLI::App app{"IEX application"};

        const int DefaultPollIntervalInSec = 60;

        std::vector<std::string> symbols;
        int intervalInSec = DefaultPollIntervalInSec;

        app.add_option("-i,--interval", intervalInSec, "Poll interval in seconds");
        app.add_option("-s,--symbols", symbols, "Symbols that we need poll")->required();

        CLI11_PARSE(app, argc, argv);

        // Start a service.
        IexService service{"storage.db"};
        service.serve(intervalInSec, symbols);
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
