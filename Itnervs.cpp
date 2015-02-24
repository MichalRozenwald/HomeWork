#include<iostream>
#include<algorithm>
#include<vector>

struct Segment {
  double begin, end, wight;
};

bool CompareSegm(Segment s1, Segment s2) {
  return ((s1.end < s2.end) || (s1.begin < s2.begin && s1.end == s2.end));
}

bool CompareSegmBetter(Segment s1, Segment s2) {
  return (s1.end <= s2.begin);
}

int PriviousSegm(int current, std::vector<Segment>& intervs) {
  auto it = lower_bound(intervs.begin(), (intervs.begin() + current), intervs[current], CompareSegmBetter);
  int index = it - intervs.begin() - 1;
  return index;
}

std::vector<int> PreviousForEach(std::vector<Segment>& intervs) {
  std::vector<int> result;
  for(int i = 0; i < intervs.size(); i++) {
    result.push_back(PriviousSegm(i, intervs));
  }
  return result;
}

double Compute_OPT(int n, std::vector<Segment>& intervs, std::vector<int>& p) {
  std::vector<double> opt;
  opt.push_back(0);
  if(n == 0) {return 0;}
  opt.push_back((intervs[0]).wight);
  for (int j = 2; j < n+1; j++){
    double j_opt;
    if (p[j-1] != -1) {
    j_opt = std::max((intervs[j-1]).wight + opt[p[j-1] + 1], opt[j-1]);
    } else {j_opt = std::max((intervs[j-1]).wight, opt[j-1]);}
    opt.push_back(j_opt);
  }
  return opt[n];
}


int main() {
  int n;
  std::cin >> n;
  std::vector<Segment> intervs;
  for(int i = 0; i < n; i++) {
    Segment new_inter;
    std::cin >> new_inter.begin >> new_inter.end >> new_inter.wight;
    intervs.push_back(new_inter);
  }
  std::sort(intervs.begin(), intervs.end(), CompareSegm);
  std::vector<int> p = PreviousForEach(intervs);
  double result = Compute_OPT(n, intervs, p);
  printf("%.4f", result);

}
