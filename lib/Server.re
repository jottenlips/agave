open ReWeb;


let buildHtmlPath = (path) => path ++ "/index.html"

let getFile = (path, _request) => 
  path |> String.concat("/") |> buildHtmlPath |> Response.of_file;
  

let server = (public) => {
    fun
    /* // [GET /] */
    | (`GET, [""]) => getFile([public])
    | (`GET, [public] as path) => {
      let filePath = [public, ...path]
      print_endline(filePath |> String.concat("/") |> buildHtmlPath)
      let file = getFile(filePath)
      file
    }
    | _ => (_ => `Not_found |> Response.of_status |> Lwt.return);
  }

let serveFiles = (path) => {
  let fileServer = server(path);
  Server.serve(fileServer);
  ""
}