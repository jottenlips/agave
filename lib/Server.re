let content_type_of_ext = ext =>
  switch (ext) {
  | ".html" => "text/html"
  | ".css" => "text/css"
  | ".js" => "application/javascript"
  | ".json" => "application/json"
  | ".png" => "image/png"
  | ".jpg"
  | ".jpeg" => "image/jpeg"
  | ".gif" => "image/gif"
  | ".svg" => "image/svg+xml"
  | ".ico" => "image/x-icon"
  | _ => "application/octet-stream"
  };

let read_file = path => {
  let ic = open_in_bin(path);
  let n = in_channel_length(ic);
  let buf = Bytes.create(n);
  really_input(ic, buf, 0, n);
  close_in(ic);
  Bytes.to_string(buf);
};

let resolve_path = (public_dir, request_path) => {
  let path =
    if (request_path == "/" || request_path == "") {
      "/index.html";
    } else if (!String.contains(Filename.basename(request_path), '.')) {
      request_path ++ "/index.html";
    } else {
      request_path;
    };
  public_dir ++ path;
};

let send_response = (client_fd, status, content_type, body) => {
  let header =
    Printf.sprintf(
      "HTTP/1.1 %s\r\nContent-Type: %s\r\nContent-Length: %d\r\nConnection: close\r\n\r\n",
      status,
      content_type,
      String.length(body),
    );
  let response = header ++ body;
  let _ = Unix.write_substring(client_fd, response, 0, String.length(response));
  ();
};

let handle_request = (public_dir, client_fd) => {
  let buf = Bytes.create(4096);
  let n = Unix.read(client_fd, buf, 0, 4096);
  let request = Bytes.sub_string(buf, 0, n);

  let first_line =
    switch (String.split_on_char('\n', request)) {
    | [line, ..._] => String.trim(line)
    | _ => ""
    };

  let request_path =
    switch (String.split_on_char(' ', first_line)) {
    | ["GET", path, ..._] => path
    | _ => "/"
    };

  Printf.printf("%s -> %s\n%!", first_line, resolve_path(public_dir, request_path));

  let file_path = resolve_path(public_dir, request_path);

  if (Sys.file_exists(file_path) && !Sys.is_directory(file_path)) {
    let ext = Filename.extension(file_path);
    let content_type = content_type_of_ext(ext);
    let body = read_file(file_path);
    send_response(client_fd, "200 OK", content_type, body);
  } else {
    let body = "404 Not Found";
    send_response(client_fd, "404 Not Found", "text/plain", body);
  };
};

let serveFiles = dir => {
  let public_dir =
    if (Filename.is_relative(dir)) {
      Sys.getcwd() ++ "/" ++ dir;
    } else {
      dir;
    };
  let port = 8080;
  let addr = Unix.inet_addr_loopback;
  let sockaddr = Unix.ADDR_INET(addr, port);
  let sock = Unix.socket(Unix.PF_INET, Unix.SOCK_STREAM, 0);
  Unix.setsockopt(sock, Unix.SO_REUSEADDR, true);
  Unix.bind(sock, sockaddr);
  Unix.listen(sock, 5);

  Printf.printf("Server running at http://localhost:%d/\n%!", port);

  while (true) {
    let (client_fd, _client_addr) = Unix.accept(sock);
    switch (handle_request(public_dir, client_fd)) {
    | () => Unix.close(client_fd)
    | exception e =>
      Printf.eprintf("Error handling request: %s\n%!", Printexc.to_string(e));
      Unix.close(client_fd);
    };
  };

  "";
};
