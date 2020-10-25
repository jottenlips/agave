let main ()=
  let public_dir = Sys.getcwd () ^ "/public/" in
  let conf = Naboris.ServerConfig.create ()
    |> Naboris.ServerConfig.setOnListen(fun () ->
      let () = print_endline "Naboris now listening on port 9000" in
      print_endline "Visit http://localhost:9000")
    |> Naboris.ServerConfig.addStaticMiddleware ["static"] public_dir
    |> Naboris.ServerConfig.setRequestHandler(fun route req res ->
      match (Naboris.Route.meth route, Naboris.Route.path route) with
        | (GET, []) | (GET, [""]) ->
          Naboris.Res.redirect
            "/static/index.html"
            req
            res
        | _ ->
          Naboris.Res.status 404 res
            |> Naboris.Res.static
              public_dir
              ["not_found.html"]
              req) in
  Naboris.listenAndWaitForever 9000 conf

let _ = Lwt_main.run(main ())