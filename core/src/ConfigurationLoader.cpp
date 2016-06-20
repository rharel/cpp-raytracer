#include <iris/ConfigurationLoader.h>


using namespace iris;


ConfigurationLoader::Status ConfigurationLoader::status() const
{
    return status_;
}
const std::string& ConfigurationLoader::status_message() const
{
    return status_message_;
}
