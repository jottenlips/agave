open Markdown;
open Html;

let buildSitemapHtml: list(page_entry) => string =
  entries => {
    let jsonEntries =
      entries
      |> List.map(e =>
           "{\"url\":\""
           ++ escapeJson(e.url)
           ++ "\",\"title\":\""
           ++ escapeJson(e.pageTitle)
           ++ "\",\"description\":\""
           ++ escapeJson(e.pageDescription)
           ++ "\",\"filename\":\""
           ++ escapeJson(e.filename)
           ++ "\"}"
         )
      |> String.concat(",");
    let json = "[" ++ jsonEntries ++ "]";
    "<div id=\"sitemap-container\">"
    ++ "<input type=\"text\" id=\"sitemap-search\" placeholder=\"Search pages...\" "
    ++ "style=\"width:100%;padding:8px;margin-bottom:16px;box-sizing:border-box;font-size:16px;\" />"
    ++ "<ul id=\"sitemap-results\" style=\"list-style:none;padding:0;\"></ul>"
    ++ "</div>"
    ++ "<script>"
    ++ "var pages = "
    ++ json
    ++ ";"
    ++ "var input = document.getElementById('sitemap-search');"
    ++ "var results = document.getElementById('sitemap-results');"
    ++ "function render(filter) {"
    ++ "  var q = filter.toLowerCase();"
    ++ "  results.innerHTML = '';"
    ++ "  pages.forEach(function(p) {"
    ++ "    if (!q || p.title.toLowerCase().indexOf(q) !== -1 || p.description.toLowerCase().indexOf(q) !== -1 || p.filename.toLowerCase().indexOf(q) !== -1) {"
    ++ "      var li = document.createElement('li');"
    ++ "      li.style.marginBottom = '12px';"
    ++ "      li.innerHTML = '<a href=\"' + p.url + '\">' + p.title + '</a>' + (p.description ? '<br/><small>' + p.description + '</small>' : '');"
    ++ "      results.appendChild(li);"
    ++ "    }"
    ++ "  });"
    ++ "}"
    ++ "input.addEventListener('input', function() { render(this.value); });"
    ++ "render('');"
    ++ "</script>";
  };
