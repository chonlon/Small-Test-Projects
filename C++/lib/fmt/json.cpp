#include <rapidjson/rapidjson.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <string_view>
#include <fmt/core.h>

using namespace rapidjson; 

int main() {
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    writer.StartObject();
    writer.Key("Hello");
    writer.String("World");
    writer.EndObject();


    fmt::print("{}", buffer.GetString());
}