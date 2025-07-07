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
  cout << "|\n"
       << " PARAMETER HOW TO, please enter:\n"
       << " 1. A search key -then 2. An optional part of speech -then\n"
       << " 3. An optional 'distinct' -then 4. An optional 'reverse'\n"
       << "|\n";
}

string capitalize(const string &word) {
  if (word.empty())
    return word;
  string result = word;
  result[0] = toupper(word[0]);
  return result;
}

void processQuery(const std::string &input, const Dictionary &dict) {
  if (input == "!help" ||
      input.find_first_not_of(" \t\n\r\f\v") == std::string::npos) {
    printHowTo();
    return;
  }

  std::stringstream ss(input);
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

  // Parse optional parameters
  for (size_t i = 1; i < tokens.size(); ++i) {
    std::string current_token = tokens[i];
    std::transform(current_token.begin(), current_token.end(),
                   current_token.begin(), ::tolower);
    if (isPartOfSpeech(current_token)) {
      partOfSpeechStr = current_token;
    } else if (current_token == "distinct") {
      distinct = true;
    } else if (current_token == "reverse") {
      reverse = true;
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

  std::vector<std::string> results;
  const DictEntries &entries = it->second;

  for (const auto &entry : entries) {
    std::string currentPosStr = posToString(entry.first);
    if (partOfSpeechStr.empty() || currentPosStr == partOfSpeechStr) {
      std::string result =
          capitalize(keyword) + " [" + currentPosStr + "] : " + entry.second;

      bool is_duplicate = false;
      if (distinct) {
        for (const auto &res : results) {
          if (res == result) {
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
  } else {
    std::cout << "\t|\n";
    for (const auto &res : results) {
      std::cout << "\t " << res << "\n";
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
  cout << "====== DICTIONARY 340 C++ =====" << endl;
  cout << "------ Keywords: " << new_dictionary.size() << endl;
  int def_count = 0;
  // TODO Add def_count logic.
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

// word [|part_of_speech -=>> DEF.]
