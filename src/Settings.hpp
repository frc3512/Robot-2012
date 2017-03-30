// Copyright (c) FRC Team 3512, Spartatroniks 2012-2017. All Rights Reserved.

#pragma once

#include <map>
#include <string>

class Settings {
public:
    explicit Settings(std::string fileName);
    virtual ~Settings();

    // Updates list of values from given file
    void update();

    /* Returns value associated with the given key
     * Returns "NOT_FOUND" if there is no entry for that name-value pair
     */
    std::string getValueFor(const std::string& key);

    // Saves all name-value pairs to external file with the given name
    void saveToFile(const std::string& fileName);

private:
    std::string m_fileName;
    std::map<std::string, std::string> m_values;

    // Used when processing strings from external file
    std::string m_rawStr;

    // Used when stepping through m_rawStr
    size_t m_index;

    std::string extractDataFromString(const bool& isName);
};