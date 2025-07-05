#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <set>

using namespace std;

struct DictEntry {
    string keyword;
    string partOfSpeech;
    string definition;

    DictEntry(string k, string p, string d)
        : keyword(k), partOfSpeech(p), definition(d) {}
};

vector<DictEntry> getAllEntries() {
    return {
        {"arrow", "noun", "Here is one arrow: <IMG> -=>> </IMG>"},
        {"book", "noun", "A set of pages."},
        {"book", "noun", "A written work published in printed or electronic form."},
        {"book", "verb", "To arrange for someone to have a seat on a plane."},
        {"book", "verb", "To arrange something on a particular date."},
        {"distinct", "adjective", "Familiar. Worked in Java."},
        {"distinct", "adjective", "Unique. No duplicates. Clearly different or of a different kind."},
        {"distinct", "adverb", "Uniquely. Written \"distinctly\"."},
        {"distinct", "noun", "A keyword in this assignment."},
        {"distinct", "noun", "A keyword in this assignment."},
        {"distinct", "noun", "A keyword in this assignment."},
        {"distinct", "noun", "An advanced search option."},
        {"distinct", "noun", "Distinct is a parameter in this assignment."},
        {"placeholder", "adjective", "To be updated..."},
        {"placeholder", "adjective", "To be updated..."},
        {"placeholder", "adverb", "To be updated..."},
        {"placeholder", "conjunction", "To be updated..."},
        {"placeholder", "interjection", "To be updated..."},
        {"placeholder", "noun", "To be updated..."},
        {"placeholder", "noun", "To be updated..."},
        {"placeholder", "noun", "To be updated..."},
        {"placeholder", "preposition", "To be updated..."},
        {"placeholder", "pronoun", "To be updated..."},
        {"placeholder", "verb", "To be updated..."},
        {"reverse", "adjective", "On back side."},
        {"reverse", "adjective", "Opposite to usual or previous arrangement."},
        {"reverse", "noun", "A dictionary program's parameter."},
        {"reverse", "noun", "Change to opposite direction."},
        {"reverse", "noun", "The opposite."},
        {"reverse", "noun", "To be updated..."},
        {"reverse", "noun", "To be updated..."},
        {"reverse", "noun", "To be updated..."},
        {"reverse", "noun", "To be updated..."},
        {"reverse", "verb", "Change something to opposite."},
        {"reverse", "verb", "Go back"},
        {"reverse", "verb", "Revoke ruling."},
        {"reverse", "verb", "To be updated..."},
        {"reverse", "verb", "To be updated..."},
        {"reverse", "verb", "Turn something inside out."}
    };
}

map<string, vector<DictEntry>> loadDict() {
    map<string, vector<DictEntry>> newDict;
    for (const auto& entry : getAllEntries()) {
        string key = entry.keyword;
        transform(key.begin(), key.end(), key.begin(), ::tolower);
        newDict[key].push_back(entry);
    }
    return newDict;
}

bool isPartOfSpeech(const string& word) {
    static const set<string> parts = {
        "noun", "verb", "adjective", "adverb",
        "conjunction", "interjection", "preposition", "pronoun"
    };
    return parts.count(word);
}

string capitalize(const string& word) {
    if (word.empty()) return word;
    string result = word;
    result[0] = toupper(result[0]);
    return result;
}

void processQuery(const string& input, map<string, vector<DictEntry>>& queryDict) {
    const string PARAMETER_HOW_TO_MESSAGE =
        "\t|\n"
        "\t PARAMETER HOW-TO, please enter:\n"
        "\t 1. A search key -then 2. An optional part of speech -then\n"
        "\t 3. An optional 'distinct' -then 4. An optional 'reverse'\n"
        "\t|";

    const string PARAMETER_NOT_FOUND_MESSAGE =
        "\t|\n"
        "\t <NOT FOUND> To be considered for the next release. Thank you.\n"
        "\t|";

    if (input.empty() || input == "!help") {
        cout << PARAMETER_HOW_TO_MESSAGE << endl;
        return;
    }

    stringstream ss(input);
    vector<string> tokens;
    string token;
    while (ss >> token) tokens.push_back(token);

    if (tokens.size() > 4) {
        cout << PARAMETER_HOW_TO_MESSAGE << endl;
        return;
    }

    string keyword = tokens[0];
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

    string partOfSpeech;
    bool distinct = false;
    bool reverse = false;
    vector<string> errors;

    if (tokens.size() >= 2) {
        string second = tokens[1];
        transform(second.begin(), second.end(), second.begin(), ::tolower);
        if (isPartOfSpeech(second)) {
            partOfSpeech = second;
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
        string third = tokens[2];
        transform(third.begin(), third.end(), third.begin(), ::tolower);
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

    if (tokens.size() == 4) {
        string fourth = tokens[3];
        transform(fourth.begin(), fourth.end(), fourth.begin(), ::tolower);
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

    auto it = queryDict.find(keyword);
    if (it == queryDict.end()) {
        cout << PARAMETER_NOT_FOUND_MESSAGE << endl;
        cout << PARAMETER_HOW_TO_MESSAGE << endl;
        return;
    }

    vector<string> results;
    set<string> seen;
    for (const auto& entry : it->second) {
        if (partOfSpeech.empty() || entry.partOfSpeech == partOfSpeech) {
            string res = capitalize(entry.keyword) + " [" + entry.partOfSpeech + "] : " + entry.definition;
            if (!distinct || seen.insert(res).second) {
                results.push_back(res);
            }
        }
    }

    if (reverse) std::reverse(results.begin(), results.end());

    for (const auto& e : errors) cout << e << endl;

    if (results.empty()) {
        cout << PARAMETER_NOT_FOUND_MESSAGE << endl;
        cout << PARAMETER_HOW_TO_MESSAGE << endl;
    } else {
        cout << "\t|" << endl;
        for (const auto& r : results) cout << "\t " << r << endl;
        cout << "\t|" << endl;
    }
}

void printDictStats(const map<string, vector<DictEntry>>& dictionary) {
    size_t keywordCount = dictionary.size();
    size_t defCount = 0;
    for (const auto& pair : dictionary) defCount += pair.second.size();
    cout << "----- Keywords: " << keywordCount << endl;
    cout << "----- Definitions: " << defCount << "\n" << endl;
}

int main() {
    cout << "! Loading data..." << endl;
    auto dict = loadDict();
    cout << "! Loading completed...\n" << endl;
    cout << "===== DICTIONARY 340 C++ =====" << endl;
    printDictStats(dict);

    int count = 1;
    string input;
    while (true) {
        cout << "Search [" << count << "]: ";
        getline(cin, input);
        if (input == "!q") {
            cout << "\n-----THANK YOU-----" << endl;
            break;
        }
        processQuery(input, dict);
        count++;
    }

    return 0;
}
