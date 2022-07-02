#include<iostream>
#include<set>
#include<map>
#include<fstream>
#include<string>
#include<algorithm>


std::string strreplace(std::string orgString, std::string search, std::string replace, std::set<std::string> &result)
{
    std::string temp = orgString;
    // Discovered ::tolower from:
    // https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case
    std::transform(orgString.begin(), orgString.end(), orgString.begin(), ::tolower);
    std::transform(search.begin(), search.end(), search.begin(), ::tolower);
    for (size_t pos = 0; ; pos += replace.length())
    {
        pos = orgString.find(search, pos);
        if (pos == std::string::npos)
            break;
        result.insert(temp.substr(pos, search.length()));
        temp.erase(pos, search.length());
        temp.insert(pos, replace);
        orgString = temp;
        std::transform(orgString.begin(), orgString.end(), orgString.begin(), ::tolower);
    }
    return temp;
}
std::set<std::string> ReplacementCensor(std::string input, std::string output, std::map<std::string,std::string> bad_to_good) {
    std::set<std::string> result;
    std::ifstream inputFile(input);
    std::ofstream outputFile(output);
    std::string line;
    getline(inputFile, line);
    for (auto it = bad_to_good.begin(); it != bad_to_good.end(); it++) {
            line = strreplace(line, it->first, it->second, result);
    }
    outputFile << line;
    while (getline(inputFile, line)) {
        outputFile << std::endl;
        for (auto it = bad_to_good.begin(); it != bad_to_good.end(); it++) {
            line = strreplace(line, it->first, it->second,result);
        }
        outputFile << line;
    }
    inputFile.close();
    outputFile.close();
    return result;
}