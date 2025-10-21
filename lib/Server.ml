open ReWeb;

let addIndexToPath = (public, path) => public++ "/"++ path ++ "index.html"
let addPath = (public, path) => public++ "/"++ path


let getPage = (public, path, _request) => {
  let resp = path |> String.concat("/") |> addIndexToPath(public) |> Response.of_file
  resp
}

let getFile = (public, path, _request) => {
  let resp = path |> String.concat("/") |> addPath(public)  |> Response.of_file
  resp
}
  
let server = (public) => {
    fun
    | (`GET, [...path]) => { 
      switch (List.find(item => String.contains(item, '.'), path)) {
        /* ANY FILE */
        | item => {
          let file = getFile(public, [...path])
          file
        }
        /* Folder, so add index.html */
        | exception Not_found => {
          let file = getPage(public, [...path])    
          file
        }
      }
      }
    | _ => (_ => `Not_found |> Response.of_status |> Lwt.return);
  }

let serveFiles = (path) => {
  let fileServer = server(path);
  Server.serve(fileServer);
  ""
}