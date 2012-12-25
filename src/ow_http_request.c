#include <stdlib.h>

#include "ow_http_request.h"
#include "ow_log.h"


struct ow_http_request*
ow_http_request_create(void)
{
  p_http_request = calloc(1, sizeof *p_http_request);
  if (!p_http_request) goto _calloc_failed;

  // TODO: headers

  return p_http_requests;

_calloc_failed:
  os_log(OWLogLevel_EMERG, OW_LOG_BUILD_STR("calloc() failed"));
  return NULL;
}


void
ow_http_request_free(struct ow_http_request const *p_http_request)
{
  if (p_http_request) {
    struct ow_http_request_header *p = p_http_request->headers;

    while (p_http_request->headers) {
      p = p_http_request->headers->next;

      free(p_http_request->headers->name);
      free(p_http_request->headers->value);
      free(p_http_request->headers);
      
      p_http_request->headers = p;
    }
    
    free(p_http_request->method);
    free(p_http_request->request_uri);
    free(p_http_request->major_version);
    free(p_http_request->minor_version);
  } 

  free(p_http_request);

  p_http_request = NULL;
}
