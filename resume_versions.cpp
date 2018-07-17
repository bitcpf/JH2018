#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;
// profileId->filedName->version->fieldValue
unordered_map<string, int> profileVersion;
unordered_map<string, map<string, map<int, string>>> profileSystem;

void update(string profileId, string fieldName, string fieldValue) {
    if(profileVersion.find(profileId) == profileVersion.end()) {
        profileVersion[profileId] = 1;
        //init profile
        map<string, map<int, string>> profile;
        map<int, string> fieldVersion;
        fieldVersion[1] = fieldValue;
        profile[fieldName] = fieldVersion;
        profileSystem[profileId] = profile;
    } else {
        ++profileVersion[profileId];
        if (profileSystem[profileId].find(fieldName) == profileSystem[profileId].end()) {
            //init field
            map<string, map<int, string>> profile = profileSystem[profileId];
            map<int, string> fieldVersion;
            profileSystem[profileId][fieldName][profileVersion[profileId]] = fieldValue;
        } else {
            profileSystem[profileId][fieldName][profileVersion[profileId]] = fieldValue;
        }
    }
}

void get(string profileId, int version) {
    //invalid
    cout << "Profile for " << profileId << " at version " << version << ":" << endl;
    if (profileSystem.find(profileId) == profileSystem.end()) {
        cout << "Invalid request!" << endl;
        return;
    } else if (version <= 0 || version > profileVersion[profileId]) {
        cout << "Invalid request!" << endl;
        return;
    } else {
        map<string, map<int, string>> profile = profileSystem[profileId];
        for (auto& fieldmp : profile) {
            if (fieldmp.second.find(version) != fieldmp.second.end()) {
                cout << fieldmp.first << " - " << fieldmp.second[version] << endl;
            } else {
                string latestValue = "";
                if (fieldmp.second.begin()->first > version) continue;
                map<int, string>::iterator latestIt = fieldmp.second.lower_bound(version);
                latestIt--;
                cout << fieldmp.first << " - " << latestIt->second << endl;
            }
        }
    }
}

void getField(string profileId, int version, string fieldName) {
    cout << fieldName << " for " << profileId << " at version " << version << ":" << endl;
    if (profileSystem.find(profileId) == profileSystem.end()) {
        cout << "Invalid request!" << endl;
        return;
    } else if (version <= 0 || version > profileVersion[profileId]) {
        cout << "Invalid request!" << endl;
        return;
    } else {
        map<string, map<int, string>> profile = profileSystem[profileId];
        if (profile.find(fieldName) == profile.end()) {
            cout << "Invalid request!" << endl;
            return;
        } else if (profile[fieldName].find(version) == profile[fieldName].end()) {
            string latestValue = "";
            if (profile[fieldName].begin()->first > version) {
                cout << "Invalid request!" << endl;
                return;
            }
            map<int, string>::iterator latestIt = profile[fieldName].lower_bound(version);
            latestIt--;
            cout << latestIt->second << endl;
        } else {
            cout << profile[fieldName][version] << endl;
        }
    }
}


int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        string queryType, profileId;
        cin >> queryType >> profileId;
        if (!queryType.compare("update")) {
            string fieldName, fieldValue;
            cin >> fieldName >> fieldValue;
            update(profileId, fieldName, fieldValue);
        } else if (!queryType.compare("get")) {
            int version;
            cin >> version;
            get(profileId, version);
        } else { // getfield
            int version;
            string fieldName;
            cin >> version >> fieldName;
            getField(profileId, version, fieldName);
        }
    }
}