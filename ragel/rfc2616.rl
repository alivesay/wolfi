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
  CRLF_OR_LF    = CRLF | LF;
  LWS           = CRLF?  (SP | HT)+;
  TEXT          = (OCTET - CTL) | LWS;
  TEXT_NO_CRLF  = (TEXT - CR) - LF;

  seperators    = '(' | ')' | '<' | '>' | '@'
                | ',' | ';' | ':' | '\\'| QUOTE
                | '/' | '[' | ']' | '?' | '='
                | '{' | '}' | SP  | HT;

  token         = (CHAR - CTL - seperators)+;
  
  qdtext        = TEXT - QUOTE;
  quoted_pair   = '\\' CHAR;
  quoted_string = QUOTE (qdtext | quoted_pair)* QUOTE;

  minor_version = DIGIT+; 
  major_version = DIGIT+;
  HTTP_Version  = 'HTTP' '/' major_version >mark %major_version '.' minor_version >mark %minor_version;

  # rfc3986.rl contains URI grammar

  Method        = (UPALPHA - CTL - seperators)+;
  Request_URI   = (OCTET - CTL - LWS)+;
  Request_Line  = Method >method %method SP Request_URI >mark %request_uri SP HTTP_Version;

  Status_Code   = DIGIT{3};
  Reason_Phrase = TEXT_NO_CRLF*; 
  Status_Line   = HTTP_Version SP Status_Code SP Reason_Phrase CRLF_OR_LF;

  field_name    = token;
  field_value   = TEXT_NO_CRLF*;
  msg_header    = field_name >mark %header_name ':' (SP | HT)* (field_value >mark %header_value)? %header_set;

  message_body  = OCTET*;

  HTTP_message  = (Request_Line | Status_Line) CRLF_OR_LF (msg_header CRLF_OR_LF)*  CRLF_OR_LF message_body?;
}%%
