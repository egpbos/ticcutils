/*
  Copyright (c) 2006 - 2017
  CLST  - Radboud University
  ILK   - Tilburg University

  This file is part of ticcutils

  ticcutils is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.

  ticcutils is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, see <http://www.gnu.org/licenses/>.

  For questions and suggestions, see:
      https://github.com/LanguageMachines/ticcutils/issues
  or send mail to:
      lamasoftware (at ) science.ru.nl

*/

#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>

#include <cerrno>
#include <cfloat>
#include "ticcutils/Version.h"
#include "ticcutils/StringOps.h"

using namespace std;
namespace TiCC {

  string BuildInfo() {
    // cannot be defined in the header becaus otherwise __DATE__ ans
    // __TIME__ would be dynamic. (changing every time it is included)
    return VersionName() + "-" + Version() + ". Compiled on "
      + __DATE__ + " " + __TIME__;
  }

  string trim( const string& s, const string& chars ){
    // remove leading and trailing characters from a string
    string result;
    if ( !s.empty() ){
      string::size_type b_pos = s.find_first_not_of( chars );
      if ( b_pos == string::npos )
	return result; // 'empty' string. only garbage
      string::size_type e_pos = s.find_last_not_of( chars );
      if ( e_pos == string::npos )
	result = s.substr( b_pos );
      else
	result = s.substr( b_pos, e_pos-b_pos+1 );
    }
    return result;
  }

  string trim_front( const string& s, const string& chars ){
    // remove leading characters from a string
    string result;
    if ( !s.empty() ){
      string::size_type b_pos = s.find_first_not_of( chars );
      if ( b_pos != string::npos )
	result = s.substr( b_pos );
    }
    return result;
  }

  string trim_back( const string& s, const string& chars ){
    // remove trailing characters from a string
    string result;
    if ( !s.empty() ){
      string::size_type e_pos = s.find_last_not_of( chars );
      if ( e_pos != string::npos )
	result = s.substr( 0, e_pos+1 );
    }
    return result;
  }

  static int toLower( const int& i ){ return tolower(i); }
  static int toUpper( const int& i ){ return toupper(i); }

  void to_lower( string& s ){
    transform( s.begin(), s.end(), s.begin(), toLower );
  }

  void to_upper( string& s ){
    transform( s.begin(), s.end(), s.begin(), toUpper );
  }

  string lowercase( const string& s ){
    string result = s;
    to_lower( result );
    return result;
  }

  string uppercase( const string& s ){
    string result = s;
    to_upper( result );
    return result;
  }

  bool match_back( const std::string& s, const std::string& tail ){
    string::size_type pos = s.rfind( tail );
    if ( pos != string::npos && (s.length() - pos == tail.length() ) ){
      return true;
    }
    return false;
  }

  bool match_front( const std::string& s, const std::string& head ){
    string::size_type pos = s.find( head );
    if ( pos == 0  ){
      return true;
    }
    return false;
  }

  size_t split_at( const string& src, vector<string>& results,
		   const string& sep, bool exact ){
    // split a string into substrings, using seps as separator
    // silently skip empty entries (e.g. when two or more separators co-incide)
    // unless exact=true;
    results.clear();
    string::size_type pos = 0;
    while ( pos != string::npos ){
      string res;
      string::size_type p = src.find( sep, pos );
      if ( p == string::npos ){
	res = src.substr( pos );
	pos = p;
      }
      else {
	res = src.substr( pos, p - pos );
	pos = p + sep.length();
      }
      if ( !res.empty() || exact )
	results.push_back( res );
    }
    return results.size();
  }

  size_t split_at_first_of( const string& src, vector<string>& results,
			    const string& seps, bool exact ){
    // split a string into substrings, using the characters in seps
    // as seperators
    // silently skip empty entries (e.g. when two or more seperators co-incide)
    // unless exact=true;
    results.clear();
    string::size_type s = 0;
    while ( s != string::npos ){
      string res;
      string::size_type e = src.find_first_of( seps, s );
      if ( e == string::npos ){
	res = src.substr( s );
	s = e;
      }
      else {
	res = src.substr( s, e - s );
	s = e+1;
      }
      if ( !res.empty() || exact ){
	results.push_back( res );
      }
    }
    return results.size();
  }

  // format weird strings (like UTF8, LATIN1) printable
  // useful for debugging
  string format_nonascii( const string& s ){
    stringstream os;
    os << showbase << hex;
    unsigned int i;
    for ( i=0; i < s.length(); ++i )
      if ( isprint(s[i]) && (int)s[i] > 31 )
	os << s[i];
      else
	os << "-" << (short int)s[i] << "-";
    os << noshowbase << dec;
    return os.str();
  }

  std::string basename( const std::string& path ){
    string::size_type pos = path.rfind( "/" );
    if ( pos != string::npos )
      return path.substr(pos+1);
    else
      return path;
  }

  std::string dirname( const std::string& path ){
    string::size_type pos = path.rfind( "/" );
    if ( pos != string::npos )
      return path.substr(0,pos);
    else
      return ".";
  }

} // namespace TiCC
