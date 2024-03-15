#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Part2_Map.cpp"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

class CampaignEditor
{
private:
    Map campaign;

public:
    CampaignEditor() : campaign(0,0) {}

    void appendMap(Map map)
    {
        campaign.map.insert(campaign.map.end(), map.map.begin(), map.map.end());
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
                // Modify the cell at the cursor
                cout << "Enter a new type for the cell (1, 2, 3): " << endl;
                int newType;
                cin >> newType;
                campaign.(campaign.cursorX, campaign.cursorY, newType);
                break;
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

    void loadCampaign(string filename)
    {
    }

    void saveCampaign(string filename)
    {
    }
};
