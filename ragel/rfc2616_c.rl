%%{
  machine rfc2616_c;
  
  action mark { printf("MARK!\n"); mark = fpc; }
  action pchar { printf("%c", fc); }
  action request_uri{ printf("request_uri:"); fwrite(mark, fpc - mark, 1, stdout); printf("\n");}
  action method{ printf("method:"); fwrite(mark, fpc - mark, 1, stdout); printf("\n");}
  action major_version{ printf("http_major_version:"); fwrite(mark, fpc - mark, 1, stdout); printf("\n");}
  action minor_version{ printf("http_minor_version:"); fwrite(mark, fpc - mark, 1, stdout); printf("\n");}


  include rfc2616 'rfc2616.rl';

  main := HTTP_message;
}%%

#include <stdio.h>
#include <string.h>

%% write data;

int main()
{
  const char *request = "GET /index.html HTTP/1.0\r\n";

  int cs;
  const char *p, *pe, *mark, *eof;

  p = request;
  mark = p;
  eof = pe = p + strlen(p);

  %% write init;
  %% write exec;
}
