#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct DictEntry {
    string keyword;
    string partOfSpeech;
    string definition;
};

map<string, vector<DictEntry>> loadDict(const string& filepath, bool& success) {
    map<string, vector<DictEntry>> dictionary;
    ifstream file(filepath);
    success = file.is_open();
    if (!success) return dictionary;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        size_t keywordEnd = line.find("|");
        if (keywordEnd == string::npos) continue;
        string keyword = line.substr(0, keywordEnd);
        string rest = line.substr(keywordEnd + 1);

        stringstream ss(rest);
        string partAndDef;
        while (getline(ss, partAndDef, '|')) {
            size_t sep = partAndDef.find("-=>>");
            if (sep == string::npos) continue;
            string part = partAndDef.substr(0, sep);
            string def = partAndDef.substr(sep + 5);
            // Clean up whitespace
            keyword.erase(0, keyword.find_first_not_of(" "));
            keyword.erase(keyword.find_last_not_of(" ") + 1);
            part.erase(0, part.find_first_not_of(" "));
            part.erase(part.find_last_not_of(" ") + 1);
            def.erase(0, def.find_first_not_of(" "));
            def.erase(def.find_last_not_of(" ") + 1);
            dictionary[keyword].push_back({keyword, part, def});
        }
    }

    return dictionary;
}

bool isPartOfSpeech(const string& word) {
    static const set<string> parts = {
        "noun", "verb", "adjective", "adverb",
        "conjunction", "interjection", "preposition", "pronoun"
    };
    return parts.count(word);
}

string capitalize(string word) {
    if (!word.empty()) word[0] = toupper(word[0]);
    return word;
}

void printHowTo() {
    cout << "|\n"
         << "PARAMETER HOW-TO, please enter:\n"
         << "1. A search key -then 2. An optional part of speech -then\n"
         << "3. An optional 'distinct' -then 4. An optional 'reverse'\n"
         << "|\n";
}

void processQuery(const string& input, const map<string, vector<DictEntry>>& dict) {
    if (input.empty() || input == "!help") {
        printHowTo();
        return;
    }

    stringstream ss(input);
    vector<string> tokens;
    string token;
    while (ss >> token) tokens.push_back(token);

    if (tokens.empty() || tokens.size() > 4) {
        printHowTo();
        return;
    }

    string keyword = tokens[0];
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

    string partOfSpeech;
    bool distinct = false, reverse = false;
    vector<string> errors;

    for (size_t i = 1; i < tokens.size(); ++i) {
        string arg = tokens[i];
        string lowerArg = arg;
        transform(lowerArg.begin(), lowerArg.end(), lowerArg.begin(), ::tolower);

        if (i == 1 && isPartOfSpeech(lowerArg)) partOfSpeech = lowerArg;
        else if (lowerArg == "distinct") distinct = true;
        else if (lowerArg == "reverse") reverse = true;
        else {
            errors.push_back("<The entered " + to_string(i+1) + "th parameter '" + arg + "' is NOT " +
                (i == 1 ? "a part of speech." : "'distinct' or 'reverse'.") + ">\n<The entered " + to_string(i+1) + "th parameter '" + arg + "' was disregarded.>\n<The " + to_string(i+1) + "th parameter should be " + (i == 1 ? "a part of speech or 'distinct' or 'reverse'." : "'distinct' or 'reverse'.") + ">\n");
        }
    }

    auto it = dict.find(keyword);
    if (it == dict.end()) {
        cout << "|\n<NOT FOUND> To be considered for the next release. Thank you.\n|\n";
        printHowTo();
        return;
    }

    vector<string> results;
    set<string> seen;
    for (const auto& entry : it->second) {
        if (partOfSpeech.empty() || entry.partOfSpeech == partOfSpeech) {
            string line = capitalize(entry.keyword) + " [" + entry.partOfSpeech + "] : " + entry.definition;
            if (!distinct || seen.insert(line).second) {
                results.push_back(line);
            }
        }
    }

    if (reverse) std::reverse(results.begin(), results.end());

    for (const auto& e : errors) cout << e;
    if (results.empty()) {
        cout << "|\n<NOT FOUND> To be considered for the next release. Thank you.\n|\n";
        printHowTo();
    } else {
        cout << "|\n";
        for (const auto& r : results) cout << r << "\n";
        cout << "|\n";
    }
}

int main() {
    string filepath = "./Data.CS.SFSU.txt";
    cout << "! Opening data file... " << filepath << endl;
    bool success;
    auto dict = loadDict(filepath, success);

    while (!success) {
        cout << "<!>ERROR<!> ===> File could not be opened.\n";
        cout << "<!>ERROR<!> ===> Provided file path: " << filepath << endl;
        cout << "<!>Enter the CORRECT data file path: ";
        getline(cin, filepath);
        cout << "! Opening data file... " << filepath << endl;
        dict = loadDict(filepath, success);
    }

    cout << "! Loading data...\n! Loading completed...\n";
    cout << "! Closing data file... " << filepath << endl;
    cout << "====== DICTIONARY 340 C++ =====\n";
    cout << "------ Keywords: " << dict.size() << endl;
    int defCount = 0;
    for (const auto& p : dict) defCount += p.second.size();
    cout << "------ Definitions: " << defCount << endl;

    int count = 1;
    string input;
    while (true) {
        cout << "Search [" << count++ << "]: ";
        getline(cin, input);
        if (input == "!q" || input == "!Q") {
            cout << "\n-----THANK YOU-----" << endl;
            break;
        }
        processQuery(input, dict);
    }
    return 0;
}
