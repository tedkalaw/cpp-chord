using namespace std;

class ChordListener{
public:
  int m;
  int stabilizeInterval;
  int fixInterval;
  int logConf;
  ChordListener (int, int, int, int);

private:
  //Vector to store port numbers of the ith process
  vector<int> ports;
};

ChordListener::ChordListener(int bits, int si=0, int fi=0, int lc=0){
  m = bits;
  stabilizeInterval = si;
  fixInterval = fi;
  logConf = lc;
}
