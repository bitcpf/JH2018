#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdlib.h>



using namespace std;

class songList
{
    public:
        songList() {}
        songList(vector<pair<int, int>> & songs)
        {
            for(auto song : songs)
            {
                m_AlbumToTracks[song.first].push_back(song.second);
            }
        }
        
        vector<pair<int,int>> getShuffer()
        {
            vector<pair<int, int>> rst;
            for(auto album: m_AlbumToTracks)
            {
                vector<int> & tracks = album.second;
                for(int i = 0; i < tracks.size(); i ++)
                {
                    int randnum = rand() % (tracks.size()-i);
                    rst.push_back(make_pair(album.first, tracks.at(randnum)));
                    swap(tracks.at(randnum), tracks.at(tracks.size()-1-i));
                }
            }

            return rst;
        }



    private:
        unordered_map<int, vector<int>> m_AlbumToTracks;

};





int main()
{

    vector<pair<int,int>> songs;
    songs.push_back(make_pair(1,4));
    songs.push_back(make_pair(2,1));
    songs.push_back(make_pair(1,2));
    songs.push_back(make_pair(2,3));
    songs.push_back(make_pair(2,2));
    songs.push_back(make_pair(1,3));
    songs.push_back(make_pair(1,1));


    songList songStream(songs);

    vector<pair<int, int>> songOrder = songStream.getShuffer();

    for(auto song: songOrder)
    {
        cout << song.first << " " << song.second << endl;
    }




    return 0;

}
