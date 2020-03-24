/*
ID: neel1
LANG: C++11
TASK: castle
*/


#include <fstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>


using namespace std;

ifstream inpFile("castle.in");
ofstream outFile ("castle.out");

unsigned int castle_w, castle_h;

int floorPlan[50][50];
int roomNum[50][50];
int roomSize[50 * 50];
int curr_room = 0;

bool visit(int row, int col)  {
  if (row < 0 || col < 0 || row >= castle_h || col >= castle_w)
    return false;
  if (roomNum[row][col] != -1) 
    return false;
  roomNum[row][col] = curr_room;
  roomSize[curr_room]++;

  if ((floorPlan[row][col] & 8) == 0)
    visit(row+1, col);
  if ((floorPlan[row][col] & 4) == 0)
    visit(row, col+1);
  if ((floorPlan[row][col] & 2) == 0)
    visit(row-1, col);
  if ((floorPlan[row][col] & 1) == 0)
    visit(row, col-1);  
  return true;
}

int main() {
  int maxRoom = 0;

  inpFile>>castle_w>>castle_h;

  for (int i = 0; i < castle_h; i++) {
    for (int j = 0; j < castle_w; j++) {
      inpFile>>floorPlan[i][j];
      roomNum[i][j] = -1;
      roomSize[i*castle_w+j] = 0;
    }
  }
  for (int i = 0; i < castle_h; i++) {
    for (int j = 0; j < castle_w; j++) {
      cout << floorPlan[i][j] << " ";
    }
    cout << endl;
  }
  for (int i = 0; i < castle_h; i++) {
    for (int j = 0; j < castle_w; j++) {
      bool ret = visit(i, j);
      if (ret) {
        if (maxRoom < roomSize[curr_room])
          maxRoom = roomSize[curr_room];
        curr_room++;
      }
    }
  }
  cout << "Number of Rooms: " << curr_room << endl;
  for (int i = 0; i < curr_room; i++) {
    cout << "RoomSize[" << i << "]=" << roomSize[i] << endl;
  }
  for (int i = 0; i < castle_h; i++) {
    for (int j = 0; j < castle_w; j++) {
      cout << roomNum[i][j] << " ";
    }
    cout << endl;
  }

  cout << "Max Room Size: " << maxRoom << endl;

  int mergeRoom = 0;
  int c_x = 0;
  int c_y = 0;
  char wall ='E';

  for (int j = 0; j < castle_w; j++) {
    for (int i = 0; i < castle_h; i++) {
      if ((i+1 < castle_h) && (roomNum[i][j] != roomNum[i+1][j])) {
        int newRoomSize = roomSize[roomNum[i][j]] + roomSize[roomNum[i+1][j]];
        if (mergeRoom < newRoomSize) {
          mergeRoom = newRoomSize;
          c_x = i+1;
          c_y = j;
          wall = 'N';
        }
      }
      if ((j+1 < castle_w) && (roomNum[i][j] != roomNum[i][j+1])) {
        int newRoomSize = roomSize[roomNum[i][j]] + roomSize[roomNum[i][j+1]];
        if (mergeRoom < newRoomSize) {
          mergeRoom = newRoomSize;
          c_x = i;
          c_y = j;
          wall = 'E';
        }
      } 
    }
  }
  cout << "Merge Room Size: " << mergeRoom << endl;
  cout << (c_x+1) << " " << (c_y+1) << " " << wall << endl;
  outFile << curr_room<< endl<<maxRoom<<endl<<mergeRoom <<endl<<(c_x+1)<< " " << (c_y+1) << " " << wall << endl;
}
