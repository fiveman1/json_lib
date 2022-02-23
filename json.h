#ifndef UTIL_JSON_H_
#define UTIL_JSON_H_

#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>

#include "picojson.h"

class JsonObject;
// class JsonArray;

class JsonValue {
public:

    JsonValue() = default;

    JsonValue(picojson::value val) : val(std::move(val)) {}

    JsonValue(double d) : val(d) {}

    JsonValue(int i) : val(static_cast<double>(i)) {}

    JsonValue(const std::string& s) : val(s) {}

    JsonValue(const char* s) : val(s) {}

    JsonValue(bool b) : val(b) {}

    JsonValue(const JsonObject& o);

    picojson::value& GetValue() { return val; }

    const picojson::value& GetValue() const { return val; }

    operator double() { return Get<double>(); }

    JsonValue& operator=(double d) { Set(d); return *this; }

    operator int() { return static_cast<int>(Get<double>()); }

    JsonValue& operator=(int i) { Set(static_cast<double>(i)); return *this; }

    operator std::string() { return Get<std::string>(); }

    JsonValue& operator=(const std::string& s) { Set(s); return *this; }

    JsonValue& operator=(const char* s) { Set(s); return *this; }

    operator bool() { return Get<bool>(); }

    JsonValue& operator=(bool b) { Set(b); return *this; }

    JsonValue& operator=(const JsonObject& o);

    std::string ToString() const { return val.serialize(); }

protected:
    template<class T>
    T Get() { return val.get<T>(); }

    template<class T>
    void Set(const T& t) { val = picojson::value(t); }

    picojson::value val;
};

class JsonObject {

public:

    JsonObject() = default;

    JsonObject(const picojson::object& obj) {
        for (const auto& kv : obj) {
            map[kv.first] = kv.second;
        }
    }

    JsonObject(const JsonValue& val) {
        for (const auto& kv : val.GetValue().get<picojson::object>()) {
            map[kv.first] = kv.second;
        }
    }

    JsonValue& operator[](const std::string& key) { return map[key]; }

    const JsonValue& operator[](const std::string& key) const { return map.at(key); }

    picojson::object GetObject() const {
        picojson::object obj;
        for (const auto& kv : map) {
            obj[kv.first] = kv.second.GetValue();
        }
        return obj;
    }

    std::string ToString() const { return picojson::value(GetObject()).serialize(); }

protected:
    std::unordered_map<std::string, JsonValue> map;
};

inline JsonValue& JsonValue::operator=(const JsonObject& o) {
    Set(o.GetObject());
    return *this;
}

inline JsonValue::JsonValue(const JsonObject &o) : val(o.GetObject()) {}

inline std::ostream& operator<<(std::ostream& os, const JsonObject& obj) {
    os << obj.ToString();
    return os;
}

//inline std::ostream& operator<<(std::ostream& os, const JsonArray& array) {
//    os << array.ToString();
//    return os;
//}

inline std::ostream& operator<<(std::ostream& os, const JsonValue& val) {
    os << val.ToString();
    return os;
}

#endif //UTIL_JSON_H_
