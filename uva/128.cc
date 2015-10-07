#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main() {
  int kModule = 34943;
  string input;
  while (getline(cin, input)) {
    if (input[0] == '#') {
      break;
    }
    int crc_value = 0;
    for (int i = 0; i < static_cast<int> (input.length()); ++i) {
      crc_value = ((crc_value << 8) + input[i]) % kModule;
    }
    crc_value = (crc_value << 8) % kModule;
    crc_value = (crc_value << 8) % kModule;
    crc_value = (kModule - crc_value) % kModule;
    cout << hex << noshowbase << uppercase << setfill('0')
         << setw(2) << (crc_value >> 8) << " "
         << setw(2) << (crc_value & 0xFF) << endl;
  }
}
