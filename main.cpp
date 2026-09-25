#define EXPRESS_ALLOW_ZLIB_COMPRESSION 0

#include <nodepp/nodepp.h>
#include <nodepp/worker.h>
#include <nodepp/query.h>
#include <nodepp/json.h>
#include <nodepp/fs.h>

#include <express/http.h>

using namespace nodepp;

#include "./controller/main.cpp"

void clients() {

    auto file = fs::writable ( "./www/uikit.css" );
    auto data = fs::read_file( "./package.json" ).await();
    auto obj  = json::parse  ( data.value() );

    for( auto x: obj["list"].as<array_t<object_t>>() ){
         
        fetch_t args;
                args.url    = x.as<string_t>();
                args.headers= header_t({  });
                args.method = "GET";

        auto fetch = http::fetch( args ).await();

        if( !fetch.has_value() ) /*---*/ { break; }
        if( fetch.value().status != 200 ){ break; }

        while( fetch.value().is_available() )
             { file.write( fetch.value().read() ); }

    }

    process::exit();

}

void compile() { do { if( process::is_child() ){ break; }

    auto app = express::http::add();

    app.USE([=]( express_http_t cli, function_t<void> next ){
        console::log( "->", cli.path );
    next(); }); 
    
    app.USE( uk::controller() );

    app.listen( "0.0.0.0", 8000, []( socket_t /*unused*/ ){
        console::log( "-> http://localhost:8000" );
        worker::add([=](){ clients(); return -1; });
    });

} while(0); }

void test() {

    auto app = express::http::add();

    app.USE([=]( express_http_t cli, function_t<void> next ){
        console::log( "->", cli.path );
    next(); });

    app.USE( express::http::file( "./www" ) );

    app.listen( "0.0.0.0", 8000, []( ... ){
        console::log( "-> http://localhost:8000" );
    });

}

void onMain(){

    if( process::env::get("mode") == "test" )
      { test(); } else { compile(); }

}
