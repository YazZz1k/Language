#include"token_struct.hpp"

token::token()
{

}

token::token(string _value, Type _type, size_t _line)
{
    value = _value;
    type  = _type;
    line  = _line;
}


token::~token()
{

}


token::token(const token& token)
{
    value = token.value;
    type  = token.type;
    line  = token.line;
}


token token::operator= (const token& t)
{
    value = t.value;
    type  = t.type;
    return *this;
}
