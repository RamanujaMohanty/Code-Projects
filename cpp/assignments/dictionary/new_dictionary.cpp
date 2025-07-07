#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
using namespace std;

enum PartsOfSpeech
{
    noun,
    adjective,
    adverb,
    conjunction,
    interjection,
    preposition,
    pronoun,
    verb
};

using DictEntry = pair<PartsOfSpeech, string>;
using DictEntries = vector<DictEntry>;
using Dictionary = map<string, DictEntries>;


Dictionary loadDict(const string& filepath, bool& success)
{
    Dictionary newDict;
    ifstream entry_file(filepath);
    success = entry_file.is_open();
    if (!success) return newDict;

    string entry_line;
    while (getline(entry_file, entry_line))
    {
        if (entry_line.empty()) continue;
        size_t key_end_index = entry_line.find('|');
        if (key_end_index == string::npos) continue;
        string keyword = entry_line.substr(0, key_end_index);
        string rem_line = entry_line.substr(key_end_index + 1);

        DictEntries de;
        stringstream line_stream(rem_line);
        string part_and_def;
        while (getline(line_stream, part_and_def, '|')) {
            size_t sep_index = part_and_def.find("-=>>");
            if (sep_index == string::npos) break;
            string part = part_and_def.substr(0, sep_index);
            string def = part_and_def.substr(sep_index + 5);
            // Clean up whitespace
            keyword.erase(0, keyword.find_first_not_of(" "));
            keyword.erase(keyword.find_last_not_of(" ") + 1);
            part.erase(0, part.find_first_not_of(" "));
            part.erase(part.find_last_not_of(" ") + 1);
            def.erase(0, def.find_first_not_of(" "));
            def.erase(def.find_last_not_of(" ") + 1);
        }
    }
    return newDict;
}

void printHowTo()
{
    cout << "|\n"
         << " PARAMETER HOW TO, please enter:\n"
         << " 1. A search key -then 2. An optional part of speech -then\n"
         << " 3. An optional 'distinct' -then 4. An optional 'reverse'\n"
         << "|\n";
}

string capitalize(const string& word)
{
    if (word.empty()) return word;
    string result = word;
    result[0] = toupper(word[0]);
    return result;
}

void processQuery(const string& input, const Dictionary& dict)
{
    if (input.empty() || input == "help")
    {
        printHowTo();
        return;
    }

    stringstream line_stream(input);
    vector<string> tokens;
    string token;
    while (line_stream >> token) tokens.push_back(token);

    if (tokens.empty() || tokens.size() > 4)
    {
        printHowTo();
        return;
    }

    string keyword = tokens[0];
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

    string part_of_speech;
    bool distinct = false, reverse = false;
    vector<string> errors;

    for (size_t ii = 1; ii < tokens.size(); ++ii)
    {
        string arg = tokens[ii];
        string lower_arg = arg;
        transform(lower_arg.begin(), lower_arg.end(), lower_arg.begin(), ::tolower);
    }

    // if ()
}


int main()
{
    string file_path = "C:\\Users\\MickeyMouse\\AbsolutePath\\DB\\Data.CS.SFSU.txt";
    cout << "! Opening data file... " << file_path << endl;
    bool open_success;
    Dictionary new_dictionary = loadDict(file_path, open_success);

    while (!open_success)
    {
        cout << "<!>ERROR<!> ===> File could not be opened." << endl;
        cout << "<!>ERROR<!> ===> Provided file path: " << file_path << endl;
        cout << "<!>Enter the CORRECT data file path: ";
        getline(cin, file_path);
        cout << "! Opening data file... " << file_path << endl;
        new_dictionary = loadDict(file_path, open_success);
    }

    cout << "! Loading data...\n! Loading completed..." << endl;
    cout << "! Closing data file... " << file_path << endl;
    cout << "====== DICTIONARY 340 C++ =====" << endl;
    cout << "------ Keywords: " << new_dictionary.size() << endl;
    int def_count = 0;
    // TODO Add def_count logic.
    cout << "------ Definitions: " << def_count << endl;

    int search_count = 1;
    string search_input;
    while (true)
    {
        cout << "Search [" << search_count++ << "]: ";
        getline(cin, search_input);
        if (search_input == "!q" || search_input == "!Q")
        {
            cout << "\n-----THANK YOU-----" << endl;
            break;
        }
        processQuery(search_input, new_dictionary);
    }
    return 0;
}

// word [|part_of_speech -=>> DEF.]
