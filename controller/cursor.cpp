#pragma once

namespace uk {

    express_tcp_t cursor() { auto app = express::http::add();
    app.ALL([=]( express_http_t cli ){ 
        
        cli.send(); string_t data;

        forEach( item, ptr_t<string_t>({
            "alias"  , "all-scroll", "cell", "col-resize" , "crosshair" , "none", "copy",
            "grab"   , "grabbing"  , "move", "not-allowed", "pointer"   , "wait",
            "zoom-in", "zoom-out"  , "text", "nwse-reize" , "row-resize", "nesw-resize"
        }) ){

            data += regex::format( NODEPP_STRINGIFY(

                .uk-cursor-${0}-hover:hover { cursor: ${0}; }
                .uk-cursor-${0}             { cursor: ${0}; }

            ), item );

        }

    cli.write( data ); }); return app; }

}