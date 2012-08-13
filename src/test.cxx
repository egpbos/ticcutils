#include <string>
#include <iostream>

#include "ticcutils/StringOps.h"
#include "ticcutils/PrettyPrint.h"

#define assert_eq( XX, YY ) test_eq<typeof XX>( __func__, __LINE__, XX, YY )
#define assert_true( YY ) test_true( __func__, __LINE__, (YY) )

using namespace std;
using namespace TiCC;

const string OK = "\033[1;32m OK  \033[0m";
const string FAIL = "\033[1;31m  FAILED  \033[0m";

int tests = 0;
int fails = 0;

template <typename T>
void test_eq( const char* F, int L, 
	      const T& s1, const T& s2 ){
  cout << "test: " << F << " ";
  ++tests;
  if ( s1 != s2 ){
    ++fails;
    cerr << FAIL << endl;
    cerr << F << "(), line " << L << " : '" << s1 << "' != '" 
	 << s2 << "'" << endl;
  }
  else {
    cerr << OK << endl;
  }
}

void test_true( const char* F, int L, bool b ){
  cout << "test: " << F << " ";
  ++tests;
  if ( !b ){
    ++fails;
    cerr << FAIL << endl;
    cerr << F << "(), line " << L << " : '"  << b << "' != TRUE" << endl;
  }
  else {
    cerr << "OK" << endl;
  }
}

void test_trim(){
  string val = " aha ";
  string res = trim(val);
  assert_eq( res, "aha" );
  assert_eq( string(""), trim(" \r ") );
  assert_true( "A" == trim("A") );
  assert_true( "AHA" == trim("AHA") );
  assert_true( "AHA" == trim("AHA\r\n") );
}

void test_trim_front(){
  string val = " aha ";
  string res = trim_front(val);
  assert_eq( res, "aha " );
}

void test_trim_back(){
  string val = " aha ";
  string res = trim_back(val);
  assert_eq( res, " aha" );
}

void test_format_non_ascii(){
  string val = "ø en €";
  string res = format_nonascii(val);
  assert_eq( res, "-0xffc3--0xffb8- en -0xffe2--0xff82--0xffac-" );
}

void test_split(){
  string line = "De kat krabt de krullen\n van de   trap.";
  vector<string> res;
  int cnt = split( line, res );
  //  cerr << "after split: " << res << endl;
  assert_eq( cnt, 8 );
  assert_eq( res[5], "van" );
}

void test_split_at(){
  string line = "Derarekatrarekrabtrarederarekrullen\nrarevanrarederaretrap.";
  vector<string> res;
  int cnt = split_at( line, res, "rare" );
  assert_eq( cnt, 8 );
  //  cerr << "after split: " << res << endl;
  assert_eq( res[5], "van" );
}

void test_split_at_first(){
  string line = "De.kat,krabt:de;krullen?van.,;.;de!trap.";
  vector<string> res;
  int cnt = split_at_first_of( line, res, ".,?!:;" );
  assert_eq( cnt, 8 );
  //  cerr << "after split: " << res << endl;
  assert_eq( res[5], "van" );
}

void test_to_upper(){
  string line = "Een CamelCapped Zin.";
  to_upper( line );
  assert_eq( line, "EEN CAMELCAPPED ZIN." );
}

void test_to_lower(){
  string line = "Een CamelCapped Zin.";
  to_lower( line );
  assert_eq( line, "een camelcapped zin." );
}

void test_uppercase(){
  string line = "Een CamelCapped Zin.";
  string res = uppercase( line );
  assert_eq( res, "EEN CAMELCAPPED ZIN." );
}

void test_lowercase(){
  string line = "Een CamelCapped Zin.";
  string res = lowercase( line );
  assert_eq( res, "een camelcapped zin." );
}

int main(){
  test_trim();
  test_trim_front();
  test_trim_back();
  test_format_non_ascii();
  test_split();
  test_split_at();
  test_split_at_first();
  test_to_upper();
  test_to_lower();
  test_uppercase();
  test_lowercase();
  cout << "performed " << tests << " tests, " << fails << " failures." << endl;
  return fails;
}