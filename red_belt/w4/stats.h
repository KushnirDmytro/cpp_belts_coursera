#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
using namespace std;

enum class UriT{
    ROOT,
    ORDER,
    PRODUCT,
    BASKET,
    HELP,
    UNKNOWN
};

enum class MethodT{
    GET,
    SET,
    POST,
    DELETE,
    UNKNOWN
};

static constexpr size_t N_URIS = static_cast<size_t>(UriT::UNKNOWN) + 1;
static constexpr size_t N_METHODS = static_cast<size_t>(MethodT::UNKNOWN) + 1;




class Stats {
public:

    Stats(){
        uri_stat.fill(0);
        methods_stat.fill(0);
    }

  void AddMethod(string_view method);
  void AddUri(string_view uri);
  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;
private:
    array<size_t , static_cast<size_t>(UriT::UNKNOWN)> uri_stat;
    array<size_t , static_cast<size_t>(MethodT::UNKNOWN)> methods_stat;

    map<string_view, int > METHODS_COUNT{
            {"GET", 0},
            {"PUT", 0},
            {"POST", 0},
            {"DELETE", 0},
            {"UNKNOWN", 0}
    };
    map<string_view, int> URI_COUNT{
            {"/", 0},
            {"/order", 0},
            {"/product", 0},
            {"/basket", 0},
            {"/help", 0},
            {"unknown", 0}
    };
};

HttpRequest ParseRequest(string_view line);