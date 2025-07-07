#include <algorithm>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <sstream>
#include <map>
#include <string>
#include <vector>
using namespace std;

struct DictEntry {
    string keyword;
    string partOfSpeech;
    string definition;
};

map<string, vector<DictEntry>> loadDict(const string& filepath, bool& success) {
    // Makes a new HashMap with a string as the key(s)
    // and the vector made of DictEntries as the value(s).
    map<string, vector<DictEntry>> newDictionary;
    ifstream entry_file(filepath);
    success = entry_file.is_open();
    // If entry_file can't be opened
    // Returns empty dictionary.
    if (!success) return newDictionary;

    string entry_line;
    while(getline(entry_file, entry_line)) {
        // Isolates and adds keyword.
        if (entry_line.empty()) continue;
        size_t key_end_index = entry_line.find("|");
        if (key_end_index == string::npos) continue;
        string keyword = entry_line.substr(0, key_end_index);
        string rem_line = entry_line.substr(key_end_index + 1);
        // Isolates parts of speech and corresponding definitions.
        stringstream rem_stream(rem_line);
        string part_and_def;
        // While loop to keep going upon encountering '|'
        while (getline(rem_stream, part_and_def, '|')) {
            size_t sep_index = part_and_def.find("-=>>");
            if (sep_index == string::npos) continue;
            string part = part_and_def.substr(0, sep_index);
            string def = part_and_def.substr(sep_index + 5);
            // Cleans up whitespace.
            keyword.erase(0, keyword.find_first_not_of(" "));
            keyword.erase(keyword.find_last_not_of(" ") + 1);
            part.erase(0, part.find_first_not_of(" "));
            part.erase(part.find_last_not_of(" ") + 1);
            def.erase(0, def.find_first_not_of(" "));
            def.erase(def.find_last_not_of(" ") + 1);
            newDictionary[keyword].push_back({keyword,part,def});
        }
    }
    return newDictionary;
}

bool isPartOfSpeech(const string& word) {
    static const set<string> parts = {
        "noun", "verb", "adjective", "adverb",
        "conjunction", "interjection", "preposition", "pronoun"
    };
    return parts.count(word);
}


int main()
{
    // Intro section: Will check if file exists at location.
    // If not, will ask for new filepath.
    string file_path = "C:\\Users\\MickeyMouse\\AbsolutePath\\DB\\Data.CS.SFSU.txt";
    cout << "! Opening data file... " << file_path << endl;
    bool open_success;
    auto newDict = loadDict(file_path, open_success);

    while (!open_success) {
        cout << "<!>ERROR<!> ===> File could not be opened." << endl;
        cout << "<!>ERROR<!> ===> Provided file path: " << file_path << endl;
        cout << "<!>Enter the CORRECT data file path: ";
        getline(cin, file_path);
        cout << "! Opening data file... " << file_path << endl;
        newDict = loadDict(file_path, open_success);
    }

    cout << "! Loading data...\n! Loading completed..." << endl;
    cout << "! Closing data file... " << file_path << endl;
    cout << "====== DICTIONARY 340 C++ =====" << endl;
    cout << "------ Keywords: " << newDict.size() << endl;
    int defCount = 0;
    for (const auto& pair : newDict) defCount += pair.second.size();
    cout << "------ Definitions: " << defCount << endl;

    int search_count = 1;
    string search_input;
    while (true) {
        cout << "Search [" << search_count++ << "]: ";
        getline(cin, search_input);
        if (search_input == "!q" || search_input == "!Q") {
            cout << "\n-----THANK YOU-----" << endl;
            break;
        }
        processQuery(search_input, newDict);
    }
    return 0;
}
