let server = (dir, port) => 
  let serverConfig: Naboris.ServerConfig.t(unit) =
    Naboris.ServerConfig.create()
    |> Naboris.ServerConfig.setRequestHandler((route, req, res) =>
         switch (Naboris.Route.path(route)) {
         | ["hello"] =>
           res
           |> Naboris.Res.status(200)
           |> Naboris.Res.text(req, "Hello world!")
         | _ =>
           res
           |> Naboris.Res.status(404)
           |> Naboris.Res.text(req, "Resource not found.")
         }
       );
    |> Lwt_main.run(Naboris.listenAndWaitForever(port))