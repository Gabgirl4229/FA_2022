#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }
  
  void heapify(int n, int root) {
    int min = root;
 //set the min as the root

    int left = 2 * root + 1;
    int right = 2 * root + 2;
 
    if (left < n && data_[left] < data_[min])
        min = left;
 //if left child is less than min, min=left

    if (right < n && data_[right] < data_[min])
        min = right;
 //if right child is less than min, min=right

    if (min != root) {
        swap(data_[root], data_[min]);
        swaps_.push_back(make_pair(data_[root], data_[min]));
        heapify(n, min);
    }
   //if min is not root, swap min and root
   //call heapify recursively
}

  void GenerateSwaps() {
    swaps_.clear();

    //build heap and call heapify
    for (int i = data_.size() / 2 - 1; i >= 0; i--)
        heapify(data_.size(), i);
 
    for (int i = data_.size() - 1; i > 0; i--) {
        swap(data_[0], data_[i]);
	//move current root to end
        swaps_.push_back(make_pair(data_[0], data_[i]));
        heapify(i, 0); //call heapify
    }
    
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
