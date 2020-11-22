open ReWeb;

let addPath = (public, path) => public++ "/"++ path ++ "index.html"

let getPage = (public, path, _request) => 
  path |> String.concat("/") |> addPath(public) |> Response.of_file;
  
let server = (public) => {
    fun
    | (`GET, [...path]) => {
      let file = getPage(public, [...path])
      file
      }
    | _ => (_ => `Not_found |> Response.of_status |> Lwt.return);
  }

let serveFiles = (path) => {
  let fileServer = server(path);
  Server.serve(fileServer);
  ""
}