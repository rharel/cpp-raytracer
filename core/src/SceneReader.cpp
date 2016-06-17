#include <iris/SceneReader.h>


using namespace iris;


SceneReader::Status SceneReader::status() const
{
    return status_;
}
const std::string& SceneReader::status_message() const
{
    return status_message_;
}
