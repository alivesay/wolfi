%%{
  machine rfc2616;

  OCTET         = any;
  CHAR          = ascii;
  UPALPHA       = upper;
  LOALPHA       = lower;
  ALPHA         = UPALPHA | LOALPHA;
  DIGIT         = digit;
  CTL           = cntrl | 127;
  CR            = 13;
  LF            = 10;
  SP            = 32;
  HT            = 9;
  QUOTE         = 34;
  CRLF          = CR LF;
  LWS           = CRLF?  (SP | HT)+;
  TEXT          = (OCTET - CTL) | LWS;
  HEX           = xdigit;

  seperators    = '(' | ')' | '<' | '>' | '@'
                | ',' | ';' | ':' | '\\'| QUOTE
                | '/' | '[' | ']' | '?' | '='
                | '{' | '}' | SP  | HT;

  token         = (CHAR - [CTL seperators])+;
  
#  CTEXT        =  TEXT - '(') - ')'; 
#  COMMENT      = '(' (

  qdtext        = TEXT - QUOTE;
  quoted_pair   = '\\' CHAR;
  quoted_string = QUOTE (qdtext | quoted_pair)* QUOTE;

  minor_version = DIGIT+; 
  major_version = DIGIT+;
  HTTP_Version  = 'HTTP' '/' major_version '.' minor_version;


  # rfc3986
  HEXDIG        = HEX;
  sub_delims    = '!' | '$' | '&' | "'" | '(' | ')'
                | '*' | '+' | ',' | ';' | '=';
  gen_delims    = ':' | '/' | '?' | '#' | '[' | ']' | '@';
  reserved      = gen_delims | sub_delims;
  unreserved    = ALPHA | DIGIT | '-' | '.' | '_' | '~';

  pct_encoded   = '%' HEXDIG HEXDIG;
  
  pchar         = unreserved | pct_encoded | sub_delims | ':' | '@';
  
  fragment      = (pchar | '/' | '?')*;
  query         = (pchar | '/' | '?')*;
  
  segment       = pchar*;
  segment_nz    = pchar+;
  segment_nz_nc = (unreserved | pct_encoded | sub_delims | '@')+;
  
  path_abempty  = ('/' segment)*;
  path_absolute = '/' (segment_nz ('/' segment)*)?;
  path_noscheme = segment_nz_nc ('/' segment)*;
  path_rootless = segment_nz ('/' segment)*;
  path_empty    = zlen;
  
  reg_name      = (unreserved | pct_encoded | sub_delims)*;
  
  dec_octet     = DIGIT                  # 0-9
                | 0x31..0x39 digit       # 10-99
                | '1' DIGIT{2}           # 100-199
                | '2' 0x30..0x34 DIGIT   # 200-249
                | '25' 0x30..0x35;       # 250-255
  
  IPv4address   = dec_octet '.' dec_octet '.' dec_octet '.' dec_octet;
  h16           = HEXDIG{1,4};
  ls32          = (h16 ':' h16) | IPv4address;
  
  IPv6address   =                              ( h16 ':' ){6} ls32
                |                         '::' ( h16 ':' ){5} ls32
                | (                h16 )? '::' ( h16 ':' ){4} ls32
                | (( h16 ':' ){,1} h16 )? '::' ( h16 ':' ){3} ls32
                | (( h16 ':' ){,2} h16 )? '::' ( h16 ':' ){2} ls32
                | (( h16 ':' ){,3} h16 )? '::'   h16 ':'      ls32
                | (( h16 ':' ){,4} h16 )? '::'                ls32
                | (( h16 ':' ){,5} h16 )? '::'                h16
                | (( h16 ':' ){,6} h16 )? '::';
  
  IPvFuture     = 'v' HEXDIG{1} '.' (unreserved | sub_delims | ':'){1};
  
  IP_literal    = '[' (IPv6address | IPvFuture) ']';
  
  port          = DIGIT*;
  host          = IP_literal | IPv4address | reg_name; 
  userinfo      = (unreserved | pct_encoded | sub_delims | ':')*;
  authority     = (userinfo '@')? host (':' port)?;
  
  scheme        = ALPHA (ALPHA | DIGIT | '+' | '-' | '.')*; 
  
  relative_part = '//' authority path_abempty 
                | path_absolute
                | path_noscheme
                | path_empty;
  
  hier_part     = '//' authority path_abempty
                | path_absolute
                | path_rootless
                | path_empty;
  
  relative_ref  = relative_part ('?' query)? ('#' fragment){0,1};
  
  absolute_URI  = scheme ':' hier_part ('?' query)?; 
  
  URI           = scheme ':' hier_part ('?' query)? ('#' fragment){0,1};
  
  URI_reference = URI | relative_ref;

  ext_method    = token;

  Method        = 'OPTIONS'
                | 'GET'
                | 'POST'
                | 'PUT'
                | 'DELETE'
                | 'TRACE'
                | 'CONNECT'
                | ext_method;

  Request_URI   = '*' | URI_reference | authority;

  Request_Line  = Method SP Request_URI SP HTTP_Version CRLF;

  field_name    = token;
  field_value   = TEXT*;
  header        = field_name ':' (SP | HT)* field_value?;

  message_body  = OCTET*;

  Request       = Request_Line (header CRLF)* CRLF message_body?;

  main := Request;
}%%
