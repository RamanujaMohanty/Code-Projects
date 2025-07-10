#include <algorithm>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

enum PartsOfSpeech {
    noun,
    adjective,
    adverb,
    conjunction,
    interjection,
    preposition,
    pronoun,
    verb
};

PartsOfSpeech stringToPos(const std::string &pos_str) {
    if (pos_str == "noun")
        return PartsOfSpeech::noun;
    if (pos_str == "adjective")
        return PartsOfSpeech::adjective;
    if (pos_str == "adverb")
        return PartsOfSpeech::adverb;
    if (pos_str == "conjunction")
        return PartsOfSpeech::conjunction;
    if (pos_str == "interjection")
        return PartsOfSpeech::interjection;
    if (pos_str == "preposition")
        return PartsOfSpeech::preposition;
    if (pos_str == "pronoun")
        return PartsOfSpeech::pronoun;
    if (pos_str == "verb")
        return PartsOfSpeech::verb;

    // Unkown type.
    throw std::invalid_argument("Invalid part of speech: " + pos_str);
}

std::string posToString(PartsOfSpeech pos) {
    switch (pos) {
        case PartsOfSpeech::noun:
            return "noun";
        case PartsOfSpeech::adjective:
            return "adjective";
        case PartsOfSpeech::adverb:
            return "adverb";
        case PartsOfSpeech::conjunction:
            return "conjunction";
        case PartsOfSpeech::interjection:
            return "interjection";
        case PartsOfSpeech::preposition:
            return "preposition";
        case PartsOfSpeech::pronoun:
            return "pronoun";
        case PartsOfSpeech::verb:
            return "verb";
    }
    return "unkown";
}

bool isPartOfSpeech(const std::string &pos_str) {
    if (pos_str == "noun" || pos_str == "adjective" || pos_str == "adverb" ||
        pos_str == "conjunction" || pos_str == "interjection" ||
        pos_str == "preposition" || pos_str == "pronoun" || pos_str == "verb") {
        return true;
    }
    return false;
}

using DictEntry = pair<PartsOfSpeech, string>;
using DictEntries = vector<DictEntry>;
using Dictionary = map<string, DictEntries>;

// Helper function for case-insensitive string comparison
bool areStringsEqualIgnoreCase(const std::string& a, const std::string& b) {
    return a.size() == b.size() &&
           std::equal(a.begin(), a.end(), b.begin(), b.end(),
                      [](char char_a, char char_b) {
                          return std::tolower(static_cast<unsigned char>(char_a)) ==
                                 std::tolower(static_cast<unsigned char>(char_b));
                      });
}


Dictionary loadDict(const string &filepath, bool &success) {
    Dictionary newDict;
    ifstream entry_file(filepath);
    success = entry_file.is_open();
    if (!success)
        return newDict;

    string entry_line;
    while (getline(entry_file, entry_line)) {
        if (entry_line.empty())
            continue;
        size_t key_end_index = entry_line.find('|');
        if (key_end_index == string::npos)
            continue;
        string keyword = entry_line.substr(0, key_end_index);
        keyword.erase(0, keyword.find_first_not_of(" "));
        keyword.erase(keyword.find_last_not_of(" ") + 1);
        string rem_line = entry_line.substr(key_end_index + 1);

        newDict[keyword] = {};
        stringstream line_stream(rem_line);
        string part_and_def;
        for (string part_and_def; getline(line_stream, part_and_def, '|');) {
            size_t sep_index = part_and_def.find("-=>>");
            if (sep_index == string::npos)
                continue;
            string part = part_and_def.substr(0, sep_index);
            string def = part_and_def.substr(sep_index + 5);
            // Clean up whitespace
            part.erase(0, part.find_first_not_of(" "));
            part.erase(part.find_last_not_of(" ") + 1);
            def.erase(0, def.find_first_not_of(" "));
            def.erase(def.find_last_not_of(" ") + 1);
            newDict[keyword].push_back({stringToPos(part), def});
        }
    }
    return newDict;
}

void printHowTo() {
    cout << "\t|\n"
         << "\t PARAMETER HOW TO, please enter:\n"
         << "\t 1. A search key -then 2. An optional part of speech -then\n"
         << "\t 3. An optional 'distinct' -then 4. An optional 'reverse'\n"
         << "\t|\n";
}

string capitalize(const string &word) {
    if (word.empty())
        return word;
    string result = word;
    result[0] = toupper(word[0]);
    return result;
}

void processQuery(const std::string &input, const Dictionary &dict)
{
    string lower_input = input;
    std::transform(lower_input.begin(), lower_input.end(), lower_input.begin(), ::tolower);

    if (lower_input == "!help" ||
        lower_input.find_first_not_of(" \t\n\r\f\v") == std::string::npos) {
        printHowTo();
        return;
    }

    std::stringstream ss(lower_input);
    std::string token;
    std::vector<std::string> tokens;
    while (ss >> token) {
        tokens.push_back(token);
    }

    if (tokens.empty())
        return;

    if (tokens.size() > 4) {
        printHowTo();
        return;
    }

    std::string keyword = tokens[0];
    std::string partOfSpeechStr;
    bool distinct = false;
    bool reverse = false;
    std::vector<std::string> errors;

    if (tokens.size() >= 2) {
        std::string second = tokens[1];
        if (isPartOfSpeech(second)) {
            partOfSpeechStr = second;
        } else if (second == "distinct") {
            distinct = true;
        } else if (second == "reverse") {
            reverse = true;
        } else {
            errors.push_back("\t|");
            errors.push_back("\t <The entered 2nd parameter '" + tokens[1] + "' is NOT a part of speech.>");
            errors.push_back("\t <The entered 2nd parameter '" + tokens[1] + "' is NOT 'distinct'.>");
            errors.push_back("\t <The entered 2nd parameter '" + tokens[1] + "' is NOT 'reverse'.>");
            errors.push_back("\t <The entered 2nd parameter '" + tokens[1] + "' was disregarded.>");
            errors.push_back("\t <The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>");
            errors.push_back("\t|");
        }
    }
    if (tokens.size() >= 3) {
        std::string third = tokens[2];
        if (third == "distinct") {
            distinct = true;
        } else if (third == "reverse") {
            reverse = true;
        } else {
            errors.push_back("\t|");
            errors.push_back("\t <The entered 3rd parameter '" + tokens[2] + "' is NOT 'distinct'.>");
            errors.push_back("\t <The entered 3rd parameter '" + tokens[2] + "' is NOT 'reverse'.>");
            errors.push_back("\t <The entered 3rd parameter '" + tokens[2] + "' was disregarded.>");
            errors.push_back("\t <The 3rd parameter should be 'distinct' or 'reverse'.>");
            errors.push_back("\t|");
        }
    }
    if (tokens.size() >= 4) {
        std::string fourth = tokens[3];
        if (fourth == "reverse") {
            reverse = true;
        } else {
            errors.push_back("\t|");
            errors.push_back("\t <The entered 4th parameter '" + tokens[3] + "' is NOT 'reverse'.>");
            errors.push_back("\t <The entered 4th parameter '" + tokens[3] + "' was disregarded.>");
            errors.push_back("\t <The 4th parameter should be 'reverse'.>");
            errors.push_back("\t|");
        }
    }

    auto it = dict.find(keyword);
    if (it == dict.end()) {
        std::cout
            << "\t|\n"
            << "\t <NOT FOUND> To be considered for the next release. Thank you.\n"
            << "\t|\n";
        printHowTo();
        return;
    }

    // Print any generated errors
    for (const auto &error : errors) {
        std::cout << error << std::endl;
    }

    DictEntries sorted_entries = it->second;

    std::sort(sorted_entries.begin(), sorted_entries.end(),
              [](const DictEntry& a, const DictEntry& b) {
              return posToString(a.first) < posToString(b.first);
              }
    );


    std::vector<std::string> results;
    const DictEntries &entries = sorted_entries;

    for (const auto &entry : entries) {
        std::string currentPosStr = posToString(entry.first);
        if (partOfSpeechStr.empty() || currentPosStr == partOfSpeechStr) {
            std::string result =
                capitalize(keyword) + " [" + currentPosStr + "] : " + entry.second;

            bool is_duplicate = false;
            if (distinct) {
                for (const auto &res : results) {
                    // MODIFIED: Use case-insensitive comparison for the distinct check.
                    if (areStringsEqualIgnoreCase(res, result)) {
                        is_duplicate = true;
                        break;
                    }
                }
            }

            if (!is_duplicate) {
                results.push_back(result);
            }
        }
    }

    if (reverse) {
        std::reverse(results.begin(), results.end());
    }

    if (results.empty()) {
        std::cout
            << "\t|\n"
            << "\t <NOT FOUND> To be considered for the next release. Thank you.\n"
            << "\t|\n";
        printHowTo();
    } else {
        std::cout << "\t|\n";
        for (const auto &res : results) {
            // MODIFIED: Removed extra space to match sample output's alignment.
            std::cout << "\t" << res << "\n";
        }
        std::cout << "\t|\n";
    }
}

int main() {
    string file_path =
        "C:\\Users\\MickeyMouse\\AbsolutePath\\DB\\Data.CS.SFSU.txt";
    cout << "! Opening data file... " << file_path << endl;
    bool open_success;
    Dictionary new_dictionary = loadDict(file_path, open_success);

    while (!open_success) {
        cout << "<!>ERROR<!> ===> File could not be opened." << endl;
        cout << "<!>ERROR<!> ===> Provided file path: " << file_path << endl;
        cout << "<!>Enter the CORRECT data file path: ";
        getline(cin, file_path);
        cout << "! Opening data file... " << file_path << endl;
        new_dictionary = loadDict(file_path, open_success);
    }

    cout << "! Loading data...\n! Loading completed..." << endl;
    cout << "! Closing data file... " << file_path << endl;
    cout << "\n====== DICTIONARY 340 C++ =====" << endl;
    cout << "------ Keywords: " << new_dictionary.size() << endl;
    int def_count = 0;
    for (const auto& entry: new_dictionary) def_count += entry.second.size();
    cout << "------ Definitions: " << def_count << endl;

    int search_count = 1;
    string search_input;
    while (true) {
        cout << "Search [" << search_count++ << "]: ";
        getline(cin, search_input);
        if (search_input == "!q" || search_input == "!Q") {
            cout << "\n-----THANK YOU-----" << endl;
            break;
        }
        processQuery(search_input, new_dictionary);
    }
    return 0;
}
