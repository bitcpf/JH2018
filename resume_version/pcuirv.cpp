#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>



using namespace std;


class resumeDB
{

    public:

        string get(const string & proID, int version)
        {
            string rst = "{";

            int latestVersion = m_proIDToVersion[proID];
            if(version > latestVersion) 
            {
                cout << "*** Error: latest version is: " << latestVersion << endl;
                return rst;
            }

            rst += proID + ":";
            unordered_map<string, vector<pair<string,int>>> & proIDSkills = m_proIDToSkills[proID];

            for(auto itr: proIDSkills)
            {
                string skillset = "";
                for(auto itr2 : itr.second)
                {
                    if(itr2.second <= version)
                    {
                        skillset += "\"" + itr2.first + "\",";
                    }
                }
                if(skillset.size() > 0)
                {
                    skillset.pop_back();
                    rst += "\"" + itr.first + "\":" + skillset;
                }
            }

            return rst + "}";
        }


        string get(const string & proID, const string & keyField, int version)
        {
            string rst = "";
            int latestVersion = m_proIDToVersion[proID];
            if(version > latestVersion) 
            {
                cout << "*** Error: latest version is: " << latestVersion << endl;
                return rst;
            }

            rst += proID + " " + keyField + ":";
            unordered_map<string, vector<pair<string,int>>> & proIDSkills = m_proIDToSkills[proID];
            vector<pair<string, int>> & items = proIDSkills[keyField];

            for(auto item:items)
            {
                if(item.second <= version)
                {
                    rst += item.first + " ";
                }
            }
            


            return rst;
        }


        void update(const string & proID, const string & keyField, const string & valueField)
        {
            // The first time find proID
            if(m_proIDToVersion.find(proID) == m_proIDToVersion.end())
            {
                cout << "Add new version: " << keyField << " " << valueField << endl;
                m_proIDToVersion[proID] = 1;
                vector<pair<string, int>> items;
                items.push_back(make_pair(valueField,1));
                m_proIDToSkills[proID][keyField] = items;
                return;
            }

            unordered_map<string, vector<pair<string,int>>> & proIDSkills = m_proIDToSkills[proID];
            // if update existing key, version +1
            if(proIDSkills.find(keyField) != proIDSkills.end())
            {
                cout << "Update version " << keyField << " " << valueField << endl;
                int curVersion = m_proIDToVersion[proID];
                proIDSkills[keyField].push_back(make_pair(valueField, curVersion+1));
                m_proIDToVersion[proID] ++;
                return;
            }
            // if add new skill field, no version update
                cout << "Update new skill " << keyField << " " << valueField << endl;
            int curVersion = m_proIDToVersion[proID];
            proIDSkills[keyField].push_back(make_pair(valueField, curVersion));

            return;

        }



    private:
        // profileID to latest version
        unordered_map<string, int> m_proIDToVersion;

        // profileID to key, with version
        unordered_map<string, unordered_map<string, vector<pair<string,int>>>> m_proIDToSkills;


};






int main()
{
    cout << "Resume Version"  << endl;

    resumeDB rdb;
    rdb.update("ABC", "skills", "java");
    rdb.update("ABC", "skills", "python");
    rdb.update("ABC", "education", "usc");


    cout << rdb.get("ABC", 1) << endl;
    cout << rdb.get("ABC", 2) << endl;
    cout << rdb.get("ABC", "skills", 2) << endl;




    return 0;
}
