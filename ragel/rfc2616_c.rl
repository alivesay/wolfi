%%{
  machine rfc2616_c;

  action mark { mark = fpc; }

  include rfc2616 'rfc2616.rl';

  main := HTTP_message;
}%%

%% write data;
