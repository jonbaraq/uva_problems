#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
typedef long long int64;

// Class to handle additions with big numbers.
class BigNumber {
 public:
  BigNumber();
  BigNumber(int64);
  BigNumber(const BigNumber&);
  BigNumber& operator+=(const BigNumber&);
  BigNumber operator+(const BigNumber&) const;
  bool operator==(const BigNumber&) const;
  string StringValue() const;

 private:
  int64 GetValue(int) const;

  vector<int64> value_;
  static int64 kLimit;
  static int kNumberDigits;
};

int64 BigNumber::kLimit = 100000000000000000LL;
int BigNumber::kNumberDigits = 17;

BigNumber::BigNumber() : value_(1, 0LL) {
}

// Creates BigNumber instance from a int64 initial value.
BigNumber::BigNumber(int64 initial_value) {
  if (initial_value > kLimit) {
    value_.resize(2);
    value_[1] = initial_value / kLimit;
    value_[0] = initial_value % kLimit;
  } else {
    value_.resize(1);
    value_[0] = initial_value;
  }
}

BigNumber::BigNumber(const BigNumber& big_number) {
  value_ = big_number.value_;
}

string BigNumber::StringValue() const {
  stringstream ss;
  ss << value_[static_cast<int> (value_.size()) - 1];
  for (int i = static_cast<int> (value_.size()) - 2; i >= 0; --i) {
    ss << setfill('0') << setw(kNumberDigits) << value_[i];
  }
  return ss.str();
}

BigNumber& BigNumber::operator+=(const BigNumber& b) {
  if (static_cast<int>(b.value_.size()) > static_cast<int>(value_.size())) {
    value_.resize(static_cast<int>(b.value_.size()), 0);
  }
  int carry = 0;
  for (int i = 0; i < static_cast<int>(value_.size()); ++i) {
    value_[i] += b.GetValue(i) + carry;
    if (value_[i] > kLimit) {
      value_[i] -= kLimit;
      carry = 1;
    } else {
      carry = 0;
    }
  }
  if (carry) {
    value_.push_back(carry);
  }
  return *this;
}

BigNumber BigNumber::operator+(const BigNumber& b) const {
  BigNumber result(*this);
  result += b;
  return result;
}

bool BigNumber::operator==(const BigNumber& b) const {
  return value_ == b.value_;
}

int64 BigNumber::GetValue(int position) const {
  if (position < static_cast<int>(value_.size())) {
    return value_[position];
  }
  return 0LL;
}

void DisplayFibonacciNumber(int number, vector<BigNumber>& fibonacci_vector) {
  int size = static_cast<int>(fibonacci_vector.size());
  while (number >= size) {
    fibonacci_vector.push_back(fibonacci_vector[size - 1] +
                               fibonacci_vector[size - 2]);
    ++size;
  }
  cout << "The Fibonacci number for " << number << " is "
       << fibonacci_vector[number].StringValue() << endl;
}

int main() {
  vector<BigNumber> fibonacci_vector(1);
  fibonacci_vector.push_back(1);
  int number;
  while (cin >> number) {
    DisplayFibonacciNumber(number, fibonacci_vector);
  }
}
