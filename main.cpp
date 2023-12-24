#include <iostream>
#include <fstream>
#include <cmath>

#define PI 3.14159

using namespace std;

const int WIDTH = 80;
const int HEIGHT = 30;

int wallType = 1;

void DrawSlope(int x1, int y1, int x2, int y2, int pixelArray[WIDTH][HEIGHT]) {
    int deltaX = abs(x2 - x1);
    int deltaY = abs(y2 - y1);
    int x = x1;
    int y = y1;
    int stepX = (x1 < x2) ? 1 : -1;
    int stepY = (y1 < y2) ? 1 : -1;

    pixelArray[x][y] = wallType;

    if (deltaX > deltaY) {
        int decision = 2 * deltaY - deltaX;

        for (int k = 0; k < deltaX; k++) {
            x += stepX;

            if (decision >= 0) {
                y += stepY;
                decision -= 2 * deltaX;
            }

            decision += 2 * deltaY;

            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                pixelArray[x][y] = wallType;
            }
        }
    } else {
        int decision = 2 * deltaX - deltaY;

        for (int k = 0; k < deltaY; k++) {  // Change condition to < deltaY
            y += stepY;

            if (decision >= 0) {
                x += stepX;
                decision -= 2 * deltaY;
            }

            decision += 2 * deltaX;

            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                pixelArray[x][y] = wallType;
            }
        }
    }
}


void drawLine(int x1, int y1, int x2, int y2, int pixelArray[WIDTH][HEIGHT]) {
    int deltaX = abs(x2 - x1);
    int deltaY = abs(y2 - y1);

    if (deltaX > deltaY) {
        int stepX = (x1 < x2) ? 1 : -1;
        for (int j = x1; j != x2; j += stepX) {
            pixelArray[j][y1] = wallType;
        }
    } else {
        int stepY = (y1 < y2) ? 1 : -1;
        for (int i = y1; i != y2; i += stepY) {
            pixelArray[x1][i] = wallType;
        }
    }
}

void drawCircle(int x, int y, int size, int pixelArray[WIDTH][HEIGHT]) {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            double distance = sqrt(pow(i - x, 2) + pow(j - y, 2));

            // Adjust the condition as needed based on the desired circle size
            if (abs(distance - size) < 0.5) {
                pixelArray[i][j] = wallType; // Set pixel to some value, e.g., 1
            }
        }
    }
}

void drawFilledCircle(int x, int y, int size, int pixelArray[WIDTH][HEIGHT]) {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            double distance = sqrt(pow(i - x, 2) + pow(j - y, 2));

            // Adjust the condition as needed based on the desired circle size
            if (distance < size) {
                pixelArray[i][j] = wallType;
            }
        }
    }
}

void drawRect(int x1, int y1, int x2, int y2, int pixelArray[WIDTH][HEIGHT]){

    if(x1 > x2)
        swap(x1, x2);
    if(y1 > y2)
        swap(y1, y2);
    
    for(int i = y1; i < y2; i++){
        for(int j = x1; j < x2; j++){
            if(i == y1) pixelArray[j][i] = wallType;
            if(i > y1 && i < y2 && (j==x1 || j == x2-1)) pixelArray[j][i] = wallType;
            if(i == y2-1) pixelArray[j][i] = wallType;
        }
    }
}

void fillRect(int x1, int y1, int x2, int y2, int pixelArray[WIDTH][HEIGHT]){

    if(x1 > x2)
        swap(x1, x2);
    if(y1 > y2)
        swap(y1, y2);
    
    for(int i = y1; i < y2; i++){
        for(int j = x1; j < x2; j++){
            pixelArray[j][i] = wallType;
        }
    }
}

void getData(int pixelArray[WIDTH][HEIGHT], fstream& file){
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            file >> pixelArray[j][i];
        }
    }
}

void saveData(int pixelArray[WIDTH][HEIGHT], fstream& file){
    for(int i = 0; i<HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            file << pixelArray[j][i] << " ";
        }
        file << endl;
    }
}

void DrawData(int arr[WIDTH][HEIGHT]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cout << arr[j][i];
        }
        cout << endl;
    }
}



void Draw(int arr[WIDTH][HEIGHT]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if(arr[j][i] == 0) cout << " ";
            else cout << "#";
        }
        cout << endl;
    }
}

int MapArray[WIDTH][HEIGHT] = {0};

int main() {
    
    bool run = true;
    int x1, y1, x2, y2, size;
    char EXT;
    
    string directory = "maps/";
    string fileName = "";
    string filePath;

    while(run)
    {
        start:
        system("cls");
        cout << "1-Open File\n";
        cout << "2-Make New File\n";
        cout << "3-Info\n";
        cout << "4-Exit\n";

        int op;
        cin >> op;

        if(op == 1)
        {
            system("cls");
            cout << "Enter file name from \"maps\" folder: ";
            cin >> fileName;
            filePath = directory + fileName;

            fstream file;
            file.open(filePath, ios::in);
            if(file.is_open())
            {
                fileStart:
                getData(MapArray, file);
                system("cls");

                bool run2 = true;
                int tmp;
                cout << "1-Write Map\n";
                cout << "2-See file data\n";
                cout << "3-Exit\n";
                cin >> tmp;

                if(tmp == 1)
                {
                    bool hasSaved = true;
                    drawStart:
                    system("cls");

                    int dOp;

                    cout << "1-DrawSlope(startX, startY, endX, endY)\n";
                    cout << "2-DrawLine(startX, startY, endX, endY)\n";
                    cout << "3-DrawCircle(x, y, size)\n";
                    cout << "4-FillCircle(x, y, size)\n";
                    cout << "5-DrawRect(startX, startY, endX, endY)\n";
                    cout << "6-FillRect(startX, startY, endX, endY)\n";
                    cout << "7-Save\n";
                    cout << "8-Exit\n";
                    cin >> dOp;
                    if(dOp == 1)
                    {
                        op1:
                        Draw(MapArray);
                        cout << "Using DrawSlope(), Enter Input: ";
                        cin >> x1 >> y1 >> x2 >> y2;
                        DrawSlope(x1, y1, x2, y2, MapArray);
                        system("cls");
                        Draw(MapArray);
                        cout << "Exit y/n: ";
                        cin >> EXT;
                        system("cls");
                        hasSaved = false;
                        if(EXT == 'y' || EXT == 'Y')
                            goto drawStart;
                        else
                            goto op1;

                    }
                    else if(dOp == 2)
                    {
                        op2:
                        Draw(MapArray);
                        cout << "Using DrawLine(), Enter Input: ";
                        cin >> x1 >> y1 >> x2 >> y2;
                        drawLine(x1, y1, x2, y2, MapArray);
                        system("cls");
                        Draw(MapArray);
                        cout << "Exit y/n: ";
                        cin >> EXT;
                        system("cls");
                        hasSaved = false;
                        if(EXT == 'y' || EXT == 'Y')
                            goto drawStart;
                        else
                            goto op2;
                    }
                    else if(dOp == 3)
                    {
                        op3:
                        Draw(MapArray);
                        cout << "Using DrawCircle(), Enter Input: ";
                        cin >> x1 >> y1 >> size;
                        drawCircle(x1, y1, size, MapArray);
                        system("cls");
                        Draw(MapArray);
                        cout << "Exit y/n: ";
                        cin >> EXT;
                        system("cls");
                        hasSaved = false;
                        if(EXT == 'y' || EXT == 'Y')
                            goto drawStart;
                        else
                            goto op3;
                    }
                    else if(dOp == 4)
                    {
                        op4:
                        Draw(MapArray);
                        cout << "Using FillCircle(), Enter Input: ";
                        cin >> x1 >> y1 >> size;
                        drawFilledCircle(x1, y1, size, MapArray);
                        system("cls");
                        Draw(MapArray);
                        cout << "Exit y/n: ";
                        cin >> EXT;
                        system("cls");
                        hasSaved = false;
                        if(EXT == 'y' || EXT == 'Y')
                            goto drawStart;
                        else
                            goto op4;
                    }
                    else if(dOp == 5)
                    {
                        op5:
                        Draw(MapArray);
                        cout << "Using DrawRect(), Enter Input: ";
                        cin >> x1 >> y1 >> x2 >> y2;
                        drawRect(x1, y1, x2, y2, MapArray);
                        system("cls");
                        Draw(MapArray);
                        cout << "Exit y/n: ";
                        cin >> EXT;
                        system("cls");
                        hasSaved = false;
                        if(EXT == 'y' || EXT == 'Y')
                            goto drawStart;
                        else
                            goto op5;
                    }
                    else if(dOp == 6)
                    {
                        op6:
                        Draw(MapArray);
                        cout << "Using FillRect(), Enter Input: ";
                        cin >> x1 >> y1 >> x2 >> y2;
                        fillRect(x1, y1, x2, y2, MapArray);
                        system("cls");
                        Draw(MapArray);
                        cout << "Exit y/n: ";
                        cin >> EXT;
                        system("cls");
                        hasSaved = false;
                        if(EXT == 'y' || EXT == 'Y')
                            goto drawStart;
                        else
                            goto op6;
                    }
                    else if(dOp == 7)
                    {
                        getData(MapArray, file);
                        file.close();
                        file.open(filePath, ios::out);

                        saveData(MapArray, file);
                        cout << "File saved!" << endl;
                        hasSaved = true;
                        file.close();
                        file.open(filePath, ios::in);
                        goto drawStart;
                    }
                    else if(dOp == 8)
                    {
                        if(hasSaved == false){
                            cout << "DO YOU WANT TO QUIT WITHOUT SAVING? y/n: ";
                        }
                        else{
                            cout << "Do you want to exit? y/n: ";
                        }
                        cin >> EXT;
                        if(EXT == 'y' || EXT == 'Y')
                            goto fileStart;
                        else 
                            goto drawStart;;
                    }
                }
                else if (tmp == 2)
                {
                    getData(MapArray, file);
                    DrawData(MapArray);
                    cin.get();
                    cin.get();
                    goto fileStart;
                }
                else{
                    goto start;
                }


                cout << "Closing file\n";
                file.close();
            }
            else
            {
                cout << "Error!! File Not Found!" << endl;
            }


        }

        else if(op == 2)
        {
            cout << "Enter the file name you want to create: ";
            cin >> fileName;
            filePath = directory + fileName;
            fstream file(filePath, ios::out);
            if(file.is_open())
            {
                cout << "File created successfully!" << endl;
                file.close();
            }
            else
            {
                cout << "ERROR! File not created" << endl;
            }
            char tmp;
            cout << "Do you want to write the map? y/n: ";
            cin >> tmp;
            
            if(tmp == 'y' || tmp == 'Y')
                goto start;
            else
                goto end;
        }

        if(op == 3)
        {
            system("cls");
            cout << "info1\n";
            cout << "info2\n";
            cout << "\n";
            cout << "\n";
            cout << "\n";
            cout << "info6\n";

            cout << "EXIT y/n: ";
            cin >> EXT;
            if(EXT == 'y' || EXT == 'Y')
                goto end;
            else
                goto start;
        }

        if(op == 4)
            goto end;
    }

    end:

    cin.get();
    // cin.get() this thing keeps the window open at the end of the program
    cin.get();
    return 0;
}
