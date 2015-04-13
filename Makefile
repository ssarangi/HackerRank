matrix: HackerRank/matrix.cpp

%: %.cpp
   g++ -std=c++11 $< -o HackerRank/build/$@
