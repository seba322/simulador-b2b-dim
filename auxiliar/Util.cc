#include "Util.h"

//--------------------------------------------
void UTIL::Tokenize(const string& str,
                    vector<string>& tokens,
                    const string& delimiters = " ")
{
  string::size_type lastPos = str.find_first_not_of(delimiters, 0);
  string::size_type pos     = str.find_first_of(delimiters, lastPos);
  while (string::npos != pos || string::npos != lastPos)
  {
    tokens.push_back(str.substr(lastPos, pos - lastPos));
    lastPos = str.find_first_not_of(delimiters, pos);
    pos = str.find_first_of(delimiters, lastPos);
  }
}

//--------------------------------------------

char* UTIL::obtener_terminos( vector<string> t)
{
    char buffer[MAX_BUFFER];
    set<string> set_int;
    for( int i=1; i< (int)t.size(); i++ )
    {
      set_int.insert( t[i] ); //termino
    }
    ASSERT( !set_int.empty( ) );

    set<string>:: iterator itsi = set_int.begin( );
    sprintf( buffer, "%d", atoi( (*itsi).c_str() ) );
    itsi++;
    for( ; itsi != set_int.end( ); itsi++ )
    {
      int shift = strlen( buffer );
      sprintf( buffer + shift , "%d", atoi( (*itsi).c_str() ) );
      ASSERT( strlen( buffer ) < MAX_BUFFER );
    }

    char *ret = (char*)malloc( strlen( buffer ) + 1 );
    sprintf( ret, "%s", buffer );

    return ret;
}
