#include <vector>
#include <iostream>
#include <fstream>
#include <string>
//#include "Part2_Map.cpp"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

void saveMap(Map map, string& filename) {
    cout<< "inside of save map"<< endl;
    cout << "filename" << filename<< endl;
    ofstream file(filename);
    if (file.is_open()) {

      cout<< "inside of open file in save map"<< endl;

        for (int j = 0; j < map.getHeight(); ++j) {
            for (int i = 0; i < map.getWidth(); ++i) {

                file << map.getElement(j, i);
            }
            file << endl;
        }
        file.close();

    } else {
        cout << "Unable to open file." << endl;
    }
}
Map readMapFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<int> > map;
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
        vector<int> row;
        for (char c : line) {
            //cout << c << endl;
            int value = c - '0';
            //cout << value << endl;
            // cout << c << endl;
            // switch(c) {
            //     case '':
            //         value = 1;
            //         break;
            //     case 'x':
            //         value = 2;
            //         break;
            //     case '|':
            //         value = 3;
            //         break;
            //     default:
            //         break;
            // }
            row.push_back(value);

        }
        // string choice;
        //cout<< map[0][0] << endl;
        // cin>> choice;
        map.push_back(row);

        }
        //map.push_back(row);
    }
    file.close();

    // turn to map
    Map mapConverted = Map(map, filename);


    return mapConverted;

}

class CampaignEditor
{
private:

public:
    Map campaign;

    CampaignEditor() : campaign() {}

    void appendMap(Map map)
    {
        //campaign.map.insert(campaign.map.end(), map.map.begin(), map.map.end());
        campaign = map;

        // Create a MapObserver instance and pass the Map reference to it
        MapObserver observer(campaign);
        // Add the observer to the map
        campaign.addObserver(&observer);
    }

    void start()
    {
    }

    int update()
    {
        // Interactive loop
        char input;
        string filename;

        while (true)
        {
            cout << "Enter a hotkey [q]uit, [c]reate a new map + [width],[height],[s]ave, l[o]ad, [m]odify + (1,2,3) to change type, hjkl to move cursor: ";

            switch (input)
            {
            case 'q':
                // Quit the program
                return 0;
            case 's':
                // Save the campaign
                cout << "Enter a filename: ";
                cin >> filename;
                saveCampaign(filename);
                cout << "CampaignEditor saved." << endl;
                break;
            case 'o':
                // Load a campaign
                cout << "Enter a filename: ";
                cin >> filename;
                loadCampaign(filename);
                cout << "CampaignEditor loaded." << endl;
                break;
            case 'm':
                // // Modify the cell at the cursor
                // cout << "Enter a new type for the cell (1, 2, 3): " << endl;
                // int newType;
                // cin >> newType;
                // campaign.(campaign.cursorX, campaign.cursorY, newType);
                // break;
            case 'h':
                // Move the cursor left
                campaign.moveCharacter(-1, 0);
                break;
            case 'j':
                // Move the cursor down
                campaign.moveCharacter(0, 1);
                break;
            case 'k':
                // Move the cursor up
                campaign.moveCharacter(0, -1);
                break;
            case 'l':
                // Move the cursor right
                campaign.moveCharacter(1, 0);
                break;
            default:
                cout << "Invalid hotkey. Try again." << endl;
                break;
            }

            draw();
        }

        return 0;
    }

    void draw()
    {
        printf("\033c"); // clears terminal
        campaign.printMap();
    }

    Map loadCampaign(string filename)
    {
      // MapDirector director = MapDirector();
      // director.readMapFromFile(filename);
      return readMapFromFile(filename);
    }

    void saveCampaign(string filename)
    {

      cout << "inside of save campagin, filename is " <<filename << endl;
      string filename2 =  "data/maps/" + filename;
      saveMap(campaign,filename2);
    }
};
