#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

void CodifyPosition(const string& previous, int row, int column,
                    char kind_move, int dimension, string* move_coded) {
  *move_coded = previous;
  if (kind_move == '+') {
    (*move_coded)[(row - 1) * dimension + column - 1] = '1';
  } else {
    (*move_coded)[(row - 1) * dimension + column - 1] = '0';
  }
}

void CalculateMirrorPosition(const string& move_coded,
                             int dimension, string* rotation) {
  // Calculate mirror image of the position.
  for (int i = 0; i < dimension; ++i) {
    for (int j = 0; j < dimension; j++) {
      (*rotation)[i * dimension + j] =
          move_coded[i * dimension + dimension - j - 1];
    }
  }
}

// This function calculate a 90 degrees solution + mirror.
void Calculate90DegreesRotation(const string& move_coded,
                                int dimension, string* rotation) {
  // Calculate pattern rotated 180 degrees.
  for (int i = 0; i < dimension; ++i) {
    for (int j = 0; j < dimension; j++) {
      (*rotation)[i * dimension + j] = move_coded[j * dimension + i];
    }
  }
}

// Add the 8 possible positions.
void CalculatePossiblePositions(const string& move_coded, int dimension,
                                set<string>* possible_positions) {
  (*possible_positions).insert(move_coded);
  int string_size = dimension * dimension;
  string rotation(string_size, '0');
  string normalized_move(string_size, '0');

  for (int i = 0; i < 4; ++i) {
    CalculateMirrorPosition(move_coded, dimension, &rotation);
    normalized_move = rotation;
    (*possible_positions).insert(normalized_move);
    // Undo mirror.
    CalculateMirrorPosition(move_coded, dimension, &rotation);
    normalized_move = rotation;
    (*possible_positions).insert(normalized_move);
    // Rotate 90 degrees.
    Calculate90DegreesRotation(normalized_move, dimension, &rotation);
    normalized_move = rotation;
  }
}

void NormalizeMoveCoded(const string& move_coded,
                        int dimension, string* normalized_move) {
  set<string> possible_positions;
  CalculatePossiblePositions(move_coded, dimension, &possible_positions);
  *normalized_move = *possible_positions.begin();
}

void PrintWinner(int i) {
  if (i % 2 == 0) {
    cout << "Player 2 wins on move " << i + 1 << endl;
  } else {
    cout << "Player 1 wins on move " << i + 1 << endl;
  }
}

int main() {
  int dimension;
  while (cin >> dimension, dimension) {
    set<string> positions;
    int number_pieces = 0;
    string previous(dimension * dimension, '0');
    bool game_finished = false;
    bool start_analysing = false;
    for (int i = 0; i < 2 * dimension; ++i) {
      int row, column;
      char kind_move;
      cin >> row >> column >> kind_move;
      if (game_finished) {
        continue;
      }
      if (kind_move == '-') {
        start_analysing = true;
        --number_pieces;
      } else {
        ++number_pieces;
      }
      string move_coded(dimension * dimension, '0');
      CodifyPosition(previous, row, column, kind_move, dimension, &move_coded);
      string normalized_move(dimension * dimension, '0');
      NormalizeMoveCoded(move_coded, dimension, &normalized_move);
      previous = move_coded;
      if (number_pieces == 0) {
        game_finished = true;
        PrintWinner(i);
      }
      if (start_analysing) {
        if (positions.count(normalized_move) > 0) {
          game_finished = true;
          PrintWinner(i);
        }
      }
      positions.insert(normalized_move);
    }
    if (!game_finished) {
      cout << "Draw" << endl;
    }
  }
}
