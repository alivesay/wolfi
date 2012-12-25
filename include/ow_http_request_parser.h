#ifndef OW_HTTP_REQUEST_PARSER_H
#define OW_HTTP_REQUEST_PARSER_H


struct ow_http_request*   ow_http_request_parse   (struct ow_http_request *const p_http_request,
                                                   char const *p_buffer);

// bool ow_http_request_validate?


#endif // OW_HTTP_REQUEST_PARSER_H
