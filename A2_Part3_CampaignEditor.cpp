#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Part2_Map.cpp"

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
using std::cin;

class Campaign
{

public:
    vector<Map> maps;
    int canvasWidth = 80;
    int canvasHeight = 20;
    vector<vector<int> > canvas;
    int cursorX = 0;
    int cursorY = 0;

    Campaign()
    {
        canvas = vector<vector<int> >(canvasWidth, vector<int>(canvasHeight, 0));
    }

    void addMap(Map map)
    {
        maps.push_back(map);
    }

    void moveCursor(int x, int y)
    {
        // Check if the cursor will be out of bounds after moving
        if (cursorX + x < 0 || cursorX + x >= canvasWidth || cursorY + y < 0 || cursorY + y >= canvasHeight)
        {
            cout << "Cursor will be out of bounds." << endl;
            return;
        }
        cursorX += x;
        cursorY += y;
    }

    void printCanvas()
    {
        for (int i = 0; i < canvasHeight; i++)
        {
            for (int j = 0; j < canvasWidth; j++)
            {
                // Cursor position represented by 'O'
                if (cursorX == j && cursorY == i)
                {
                    cout << "o  ";
                }
                else if (canvas[j][i] == 1)
                {
                    cout << ".  ";
                }
                else if (canvas[j][i] == 2)
                {
                    cout << "x  ";
                }
                else if (canvas[j][i] == 3)
                {
                    cout << "|  ";
                } else {
                    // Empty canvas cell
                    cout << "   ";
                }
            }
            cout << endl;
        }
    }

    void saveCampaign(string filename)
    {
        ofstream file(filename);
        if (file.is_open())
        {
            for (int i = 0; i < canvasHeight; i++)
            {
                for (int j = 0; j < canvasWidth; j++)
                {
                    file << canvas[j][i] << " ";
                }
                file << endl;
            }
        }
        else
        {
            cout << "Unable to open file." << endl;
        }
    }

    // Load a campaign from a file
    void loadCampaign(string filename)
    {
        ifstream file(filename);
        if (file.is_open())
        {
            for (int i = 0; i < canvasHeight; i++)
            {
                for (int j = 0; j < canvasWidth; j++)
                {
                    file >> canvas[j][i];
                }
            }
        }
        else
        {
            cout << "Unable to open file." << endl;
        }
        file.close();
    }

    bool isValid()
    {
        return true;
    }

    void changeCellType (int x, int y, int newType)
    {
        canvas[x][y] = newType;
    }
};

int main()
{
    Map map1(10, 10);
    Map map2(15, 15);
    Map map3(9, 15);

    Campaign campaign;
    campaign.addMap(map1);
    campaign.addMap(map2);
    campaign.addMap(map3);

    // Accumulate starting positions for each map to render them next to each other
    int startingPosAcc = 0;

    // Add the maps to the canvas
    for (int i = 0; i < campaign.maps.size(); i++)
    {
        Map map = campaign.maps[i];
        int mapSizeX = map.getMap().size();
        int mapSizeY = map.getMap()[0].size();

        int startX = startingPosAcc;

        // Copy the map onto the canvas
        for (int x = 0; x < mapSizeX; x++)
        {
            for (int y = 0; y < mapSizeY; y++)
            {
                campaign.canvas[startX + x][y] = map.getMap()[x][y];
            }
        }
        startingPosAcc += mapSizeX;
    }

    // Print the canvas initially
    campaign.printCanvas();

    // Interactive loop
    char input;
    while (true)
    {
        cout << "Enter a hotkey [q]uit, [s]ave, l[o]ad, [m]odify + (1,2,3) to change type, hjkl to move cursor: ";
        cin >> input;
        cout << "X: " << campaign.cursorX << " Y: " << campaign.cursorY <<endl;

        string filename;
        switch (input)
        {
            case 'q':
                // Quit the program
                return 0;
            case 's':
                // Save the campaign
                cout << "Enter a filename: ";
                cin >> filename;
                campaign.saveCampaign(filename);
                cout << "Campaign saved." << endl;
                break;
            case 'o':
                // Load a campaign
                cout << "Enter a filename: ";
                cin >> filename;
                campaign.loadCampaign(filename);
                cout << "Campaign loaded." << endl;
                break;
            case 'm':
                // Modify the cell at the cursor
                cout << "Enter a new type for the cell (1, 2, 3): " << endl;;
                int newType;
                cin >> newType;
                campaign.changeCellType(campaign.cursorX, campaign.cursorY, newType);
                break;
            case 'h':
                // Move the cursor left
                campaign.moveCursor(-1, 0);
                break;
            case 'j':
                // Move the cursor down
                campaign.moveCursor(0, 1);
                break;
            case 'k':
                // Move the cursor up
                campaign.moveCursor(0, -1);
                break;
            case 'l':
                // Move the cursor right
                campaign.moveCursor(1, 0);
                break;
            default:
                cout << "Invalid hotkey. Try again." << endl;
                break;
        }
        // Reprint canvas to reflect changes
        campaign.printCanvas();
    }

    return 0;
}
