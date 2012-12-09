%%{
  machine rfc3986;

  UPALPHA       = upper;
  LOALPHA       = lower;
  ALPHA         = UPALPHA | LOALPHA;
  DIGIT         = digit;
  HEXDIG        = xdigit;

  sub_delims    = '!' | '$' | '&' | "'" | '(' | ')'
                | '*' | '+' | ',' | ';' | '=';
  gen_delims    = ':' | '/' | '?' | '#' | '[' | ']' | '@';
  reserved      = gen_delims | sub_delims;
  unreserved    = ALPHA | DIGIT | '-' | '.' | '_' | '~';

  pct_encoded   = '%' HEXDIG HEXDIG;
  
  pchar         = unreserved | pct_encoded | sub_delims | ':' | '@';
  
  fragment      = (pchar | '/' | '?')* >mark %fragment;
  query         = (pchar | '/' | '?')* >mark %query;
  
  segment       = pchar*;
  segment_nz    = pchar+;
  segment_nz_nc = (unreserved | pct_encoded | sub_delims | '@')+;
  
  path_abempty  = ('/' segment)* %path;
  path_absolute = '/' (segment_nz ('/' segment)*)? %path;
  path_noscheme = segment_nz_nc ('/' segment)* %path;
  path_rootless = segment_nz ('/' segment)* %path;
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
  
  port          = DIGIT* >mark %port;
  host          = IP_literal | IPv4address | reg_name >mark %host; 
  userinfo      = (unreserved | pct_encoded | sub_delims | ':')* >mark %userinfo;
  authority     = (userinfo '@')? host (':' port)?;
  
  scheme        = ALPHA >mark (ALPHA | DIGIT | '+' | '-' | '.')* %scheme; 
  
  relative_part = '//' authority %mark path_abempty 
                | path_absolute
                | path_noscheme
                | path_empty;
  
  hier_part     = '//' authority %mark path_abempty
                | path_absolute
                | path_rootless
                | path_empty;
  
  relative_ref  = relative_part ('?' query)? ('#' fragment){0,1};
  
  absolute_URI  = scheme ':' hier_part ('?' query)?; 
  
  URI           = scheme ':' hier_part ('?' query)? ('#' fragment){0,1};
  
  URI_reference = URI | relative_ref;
}%%
